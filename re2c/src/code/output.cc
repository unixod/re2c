#include <stdio.h>
#include <time.h>
#include <iomanip>

#include "src/code/emit.h"
#include "src/code/output.h"
#include "src/code/print.h"
#include "src/conf/msg.h"
#include "src/util/string_utils.h"

namespace re2c
{

OutputFragment::OutputFragment (type_t t, uint32_t i)
	: type (t)
	, stream ()
	, indent (i)
{}

OutputFragment::~OutputFragment()
{
	if (type == TAGS) {
		delete tags;
	}
}

uint32_t OutputFragment::count_lines ()
{
	uint32_t lines = 0;
	const std::string content = stream.str ();
	const char * p = content.c_str ();
	for (uint32_t i = 0; i < content.size (); ++i)
	{
		if (p[i] == '\n')
		{
			++lines;
		}
	}
	return lines;
}

OutputBlock::OutputBlock ()
	: fragments ()
	, used_yyaccept (false)
	, line (0)
	, types ()
	, tags ()
	, opts(NULL)
{
	fragments.push_back (new OutputFragment (OutputFragment::CODE, 0));
}

OutputBlock::~OutputBlock ()
{
	for (unsigned int i = 0; i < fragments.size (); ++i)
	{
		delete fragments[i];
	}
	delete opts;
}

OutputFile::OutputFile(bool tflag, Warn &w)
	: blocks ()
	, label_counter ()
	, fill_index(0)
	, state_goto(false)
	, cond_goto(false)
	, warn_condition_order (!tflag) // see note [condition order]
	, warn(w)
{}

OutputFile::~OutputFile ()
{
	for (unsigned int i = 0; i < blocks.size(); ++i) {
		delete blocks[i];
	}
}

OutputBlock& OutputFile::block()
{
	return *blocks.back();
}

std::ostream & OutputFile::stream ()
{
	return block().fragments.back ()->stream;
}

OutputFile &OutputFile::wraw(const char *s, const char *e)
{
	if (block().opts->target == opt_t::CODE) {
		insert_code();
		stream().write(s, static_cast<std::streamsize>(e - s));
	}
	return *this;
}

OutputFile & OutputFile::wu32_hex (uint32_t n)
{
	insert_code();
	prtHex(stream(), n, block().opts->encoding.szCodeUnit());
	return *this;
}

OutputFile & OutputFile::wc_hex (uint32_t n)
{
	insert_code();
	const opt_t *opts = block().opts;
	const Enc &e = opts->encoding;
	prtChOrHex(stream(), n, e.szCodeUnit(), e.type() == Enc::EBCDIC, opts->target == opt_t::DOT);
	return *this;
}

OutputFile & OutputFile::wrange (uint32_t l, uint32_t u)
{
	insert_code();
	const opt_t *opts = block().opts;
	const Enc &e = opts->encoding;
	printSpan(stream(), l, u, e.szCodeUnit(), e.type() == Enc::EBCDIC, opts->target == opt_t::DOT);
	return *this;
}

OutputFile & OutputFile::wu32_width (uint32_t n, int w)
{
	insert_code();
	stream () << std::setw (w);
	stream () << n;
	return *this;
}

OutputFile & OutputFile::wline_info (uint32_t l, const char * fn)
{
	insert_code();
	output_line_info (stream (), l, fn, block().opts->iFlag);
	return *this;
}

OutputFile & OutputFile::wversion_time ()
{
	insert_code();
	output_version_time(stream(), block().opts->version, !block().opts->bNoGenerationDate);
	return *this;
}

OutputFile & OutputFile::wuser_start_label ()
{
	insert_code();
	const std::string label = block().opts->startlabel;
	if (!label.empty())
	{
		wstring(label).ws(":\n");
	}
	return *this;
}

OutputFile & OutputFile::wc (char c)
{
	insert_code();
	stream () << c;
	return *this;
}

OutputFile & OutputFile::wu32 (uint32_t n)
{
	insert_code();
	stream () << n;
	return *this;
}

OutputFile & OutputFile::wu64 (uint64_t n)
{
	insert_code();
	stream () << n;
	return *this;
}

OutputFile & OutputFile::wstring (const std::string & s)
{
	insert_code();
	stream () << s;
	return *this;
}

OutputFile & OutputFile::ws (const char * s)
{
	insert_code();
	stream () << s;
	return *this;
}

OutputFile & OutputFile::wlabel (label_t l)
{
	insert_code();
	stream () << l;
	return *this;
}

OutputFile & OutputFile::wind (uint32_t ind)
{
	insert_code();
	stream () << indent(ind, block().opts->indString);
	return *this;
}

void OutputFile::insert_code ()
{
	if (block().fragments.back()->type != OutputFragment::CODE) {
		block().fragments.push_back(new OutputFragment(OutputFragment::CODE, 0));
	}
}

OutputFile &OutputFile::wdelay_tags(const ConfTags *cf)
{
	if (block().opts->target == opt_t::CODE) {
		OutputFragment *frag = new OutputFragment(OutputFragment::TAGS, 0);
		frag->tags = cf;
		blocks.back()->fragments.push_back(frag);
	}
	return *this;
}

OutputFile & OutputFile::wdelay_line_info ()
{
	block().fragments.push_back (new OutputFragment (OutputFragment::LINE_INFO, 0));
	return *this;
}

OutputFile & OutputFile::wdelay_cond_goto(uint32_t ind)
{
	if (block().opts->cFlag && !cond_goto) {
		block().fragments.push_back(new OutputFragment(OutputFragment::COND_GOTO, ind));
		cond_goto = true;
	}
	return *this;
}

OutputFile & OutputFile::wdelay_cond_table(uint32_t ind)
{
	if (block().opts->gFlag && block().opts->cFlag && !cond_goto) {
		block().fragments.push_back(new OutputFragment(OutputFragment::COND_TABLE, ind));
	}
	return *this;
}

OutputFile & OutputFile::wdelay_state_goto (uint32_t ind)
{
	if (block().opts->target == opt_t::CODE
		&& block().opts->fFlag && !state_goto) {
		block().fragments.push_back (new OutputFragment (OutputFragment::STATE_GOTO, ind));
		state_goto = true;
	}
	return *this;
}

OutputFile & OutputFile::wdelay_types ()
{
	if (block().opts->target == opt_t::CODE) {
		warn_condition_order = false; // see note [condition order]
		block().fragments.push_back (new OutputFragment (OutputFragment::TYPES, 0));
	}
	return *this;
}

OutputFile & OutputFile::wdelay_yyaccept_init (uint32_t ind)
{
	block().fragments.push_back (new OutputFragment (OutputFragment::YYACCEPT_INIT, ind));
	return *this;
}

OutputFile & OutputFile::wdelay_yymaxfill ()
{
	if (block().opts->target == opt_t::CODE) {
		block().fragments.push_back (new OutputFragment (OutputFragment::YYMAXFILL, 0));
	}
	return *this;
}

OutputFile& OutputFile::wdelay_skip(uint32_t ind, bool skip)
{
	if (skip) {
		OutputFragment *f = new OutputFragment(OutputFragment::SKIP, ind);
		block().fragments.push_back(f);
	}
	return *this;
}

OutputFile& OutputFile::wdelay_peek(uint32_t ind, bool peek)
{
	if (peek) {
		OutputFragment *f = new OutputFragment(OutputFragment::PEEK, ind);
		block().fragments.push_back(f);
	}
	return *this;
}

OutputFile& OutputFile::wdelay_backup(uint32_t ind, bool backup)
{
	if (backup) {
		OutputFragment *f = new OutputFragment(OutputFragment::BACKUP, ind);
		block().fragments.push_back(f);
	}
	return *this;
}

void OutputFile::new_block(Opt &opts)
{
	OutputBlock *b = new OutputBlock;
	b->opts = opts.snapshot();
	blocks.push_back(b);

	// start label hapens to be the only option
	// that must be reset for each new block
	opts.reset_startlabel();
}

void OutputFile::global_lists(
	uniq_vector_t<std::string> &types,
	std::set<std::string> &tags) const
{
	for (unsigned int i = 0; i < blocks.size(); ++i) {

		const std::vector<std::string> &ts = blocks[i]->types;
		for (size_t j = 0; j < ts.size(); ++j) {
			types.find_or_add(ts[j]);
		}

		const std::set<std::string> &cs = blocks[i]->tags;
		tags.insert(cs.begin(), cs.end());
	}
}

static void foldexpr(std::vector<OutputFragment*> &frags)
{
	const size_t n = frags.size();
	for (size_t i = 0; i < n;) {

		if (i + 2 < n) {
			OutputFragment::type_t
				&x = frags[i]->type,
				&y = frags[i + 1]->type,
				&z = frags[i + 2]->type;
			if (x == OutputFragment::BACKUP && y == OutputFragment::PEEK && z == OutputFragment::SKIP) {
				x = OutputFragment::BACKUP_PEEK_SKIP;
				y = z = OutputFragment::EMPTY;
				i += 3;
				continue;
			} else if (x == OutputFragment::SKIP && y == OutputFragment::BACKUP && z == OutputFragment::PEEK) {
				x = OutputFragment::SKIP_BACKUP_PEEK;
				y = z = OutputFragment::EMPTY;
				i += 3;
				continue;
			}
		}

		if (i + 1 < n) {
			OutputFragment::type_t
				&x = frags[i]->type,
				&y = frags[i + 1]->type;
			if (x == OutputFragment::PEEK && y == OutputFragment::SKIP) {
				x = OutputFragment::PEEK_SKIP;
				y = OutputFragment::EMPTY;
				i += 2;
				continue;
			} else if (x == OutputFragment::SKIP && y == OutputFragment::PEEK) {
				x = OutputFragment::SKIP_PEEK;
				y = OutputFragment::EMPTY;
				i += 2;
				continue;
			} else if (x == OutputFragment::SKIP && y == OutputFragment::BACKUP) {
				x = OutputFragment::SKIP_BACKUP;
				y = OutputFragment::EMPTY;
				i += 2;
				continue;
			} else if (x == OutputFragment::BACKUP && y == OutputFragment::PEEK) {
				x = OutputFragment::BACKUP_PEEK;
				y = OutputFragment::EMPTY;
				i += 2;
				continue;
			} else if (x == OutputFragment::BACKUP && y == OutputFragment::SKIP) {
				x = OutputFragment::BACKUP_SKIP;
				y = OutputFragment::EMPTY;
				i += 2;
				continue;
			}
		}

		++i;
	}
}

bool OutputFile::emit(const uniq_vector_t<std::string> &global_types,
	const std::set<std::string> &global_tags,
	size_t max_fill)
{
	FILE *file = NULL;
	std::string filename = block().opts->output_file;
	if (filename.empty()) {
		filename = "<stdout>";
		file = stdout;
	} else {
		file = fopen(filename.c_str(), "wb");
		if (!file) {
			error("cannot open output file: %s", filename.c_str());
			return false;
		}
	}

	unsigned int line_count = 1;
	for (unsigned int j = 0; j < blocks.size(); ++j) {
		OutputBlock & b = * blocks[j];
		const opt_t *bopt = b.opts;

		if (bopt->input_api == INPUT_DEFAULT) {
			foldexpr(b.fragments);
		}

		const size_t n = b.fragments.size();
		for (size_t i = 0; i < n; ++i) {
			OutputFragment & f = * b.fragments[i];
			std::ostringstream &o = f.stream;
			const uint32_t ind = f.indent ? f.indent : bopt->topIndent;

			switch (f.type) {
			case OutputFragment::EMPTY:
			case OutputFragment::CODE: break;
			case OutputFragment::LINE_INFO:
				output_line_info(o, line_count + 1, filename, bopt->iFlag);
				break;
			case OutputFragment::COND_GOTO:
				output_cond_goto(o, ind, b.types,
					bopt, warn, warn_condition_order, b.line);
				break;
			case OutputFragment::COND_TABLE:
				output_cond_table(o, ind, b.types, bopt);
				break;
			case OutputFragment::STATE_GOTO:
				output_state_goto(o, ind, 0, fill_index, bopt);
				break;
			case OutputFragment::TAGS:
				output_tags(o, ind, *f.tags, global_tags, bopt);
				break;
			case OutputFragment::TYPES:
				output_types(o, ind, block().opts, global_types);
				break;
			case OutputFragment::YYACCEPT_INIT:
				output_yyaccept_init(o, ind, b.used_yyaccept, bopt);
				break;
			case OutputFragment::YYMAXFILL:
				output_yymaxfill(o, ind, max_fill, bopt);
				break;
			case OutputFragment::SKIP:
				output_skip(o, ind, bopt);
				break;
			case OutputFragment::PEEK:
				output_peek(o, ind, bopt);
				break;
			case OutputFragment::BACKUP:
				output_backup(o, ind, bopt);
				break;
			case OutputFragment::PEEK_SKIP:
				output_peek_skip(o, ind, bopt);
				break;
			case OutputFragment::SKIP_PEEK:
				output_skip_peek(o, ind, bopt);
				break;
			case OutputFragment::SKIP_BACKUP:
				output_skip_backup(o, ind, bopt);
				break;
			case OutputFragment::BACKUP_SKIP:
				output_backup_skip(o, ind, bopt);
				break;
			case OutputFragment::BACKUP_PEEK:
				output_backup_peek(o, ind, bopt);
				break;
			case OutputFragment::BACKUP_PEEK_SKIP:
				output_backup_peek_skip(o, ind, bopt);
				break;
			case OutputFragment::SKIP_BACKUP_PEEK:
				output_skip_backup_peek(o, ind, bopt);
				break;
			}

			std::string content = o.str();
			fwrite(content.c_str(), 1, content.size(), file);
			line_count += f.count_lines();
		}
	}

	fclose(file);
	return true;
}

bool HeaderFile::emit(const opt_t *opts, const uniq_vector_t<std::string> &types)
{
	if (!opts->tFlag) {
		return true;
	}

	FILE *file = NULL;
	std::string filename = opts->header_file;
	if (filename.empty()) {
		filename = "<stdout>.h";
		file = stdout;
	} else {
		file = fopen(filename.c_str(), "wb");
		if (!file) {
			error("cannot open header file: %s", filename.c_str());
			return false;
		}
	}

	output_version_time(stream, opts->version, !opts->bNoGenerationDate);
	output_line_info(stream, 3, filename, opts->iFlag);
	stream << "\n";
	output_types(stream, 0, opts, types);

	std::string content = stream.str();
	fwrite(content.c_str(), 1, content.size(), file);

	fclose(file);
	return true;
}

Output::Output(bool tflag, Warn &w)
	: source(tflag, w)
	, header()
	, skeletons()
	, max_fill(1)
{}

bool Output::emit()
{
	if (source.warn.error()) {
		return false;
	}

	uniq_vector_t<std::string> types;
	std::set<std::string> tags;
	source.global_lists(types, tags);

	// global options are last block's options
	const opt_t *opts = source.block().opts;

	return source.emit(types, tags, max_fill)
		&& header.emit(opts, types);
}

void output_tags(std::ostream &o, uint32_t ind, const ConfTags &conf,
	const std::set<std::string> &tags, const opt_t *opts)
{
	std::set<std::string>::const_iterator
		tag = tags.begin(),
		end = tags.end();
	o << indent(ind, opts->indString);
	for (;tag != end;) {
		std::string fmt = conf.format;
		strrreplace(fmt, "@@", *tag);
		o << fmt;
		if (++tag == end) {
			break;
		}
		o << conf.separator;
	}
}

void output_state_goto(std::ostream & o, uint32_t ind,
	uint32_t start_label, uint32_t fill_index, const opt_t *opts)
{
	const std::string
		indstr = indent(ind, opts->indString),
		getstate = opts->state_get_naked
			? opts->state_get
			: opts->state_get + "()";

	o << indstr << "switch (" << getstate << ") {\n";
	if (opts->bUseStateAbort)
	{
		o << indstr << "default: abort();\n";
		o << indstr << "case -1: goto " << opts->labelPrefix << start_label << ";\n";
	}
	else
	{
		o << indstr << "default: goto " << opts->labelPrefix << start_label << ";\n";
	}
	for (uint32_t i = 0; i < fill_index; ++i)
	{
		o << indstr << "case " << i << ": goto " << opts->yyfilllabel << i << ";\n";
	}
	o << indstr << "}\n";
	if (opts->bUseStateNext)
	{
		o << opts->yynext << ":\n";
	}
}

void output_yyaccept_init (std::ostream & o, uint32_t ind, bool used_yyaccept, const opt_t *opts)
{
	if (used_yyaccept)
	{
		o << indent(ind, opts->indString) << "unsigned int " << opts->yyaccept << " = 0;\n";
	}
}

void output_yymaxfill(std::ostream &o, uint32_t ind,
	size_t max_fill, const opt_t *opts)
{
	o << indent(ind, opts->indString) << "#define YYMAXFILL " << max_fill << "\n";
}

void output_line_info(std::ostream &o, uint32_t line,
	const std::string &fname, bool iflag)
{
	if (!iflag) {
		o << "#line " << line << " \"" << fname << "\"\n";
	}
}

void output_types(std::ostream &o, uint32_t ind, const opt_t *opts,
	const uniq_vector_t<std::string> &types)
{
	const std::string indstr = opts->indString;
	o << indent(ind++, indstr) << "enum " << opts->yycondtype << " {\n";
	for (size_t i = 0; i < types.size(); ++i) {
		o << indent(ind, indstr) << opts->condEnumPrefix << types[i] << ",\n";
	}
	o << indent(--ind, indstr) << "};\n";
}

void output_version_time(std::ostream &o, bool version, bool date)
{
	o << "/* Generated by re2c";
	if (version) {
		o << " " << PACKAGE_VERSION;
	}
	if (date) {
		o << " on ";
		time_t now = time (NULL);
		o.write (ctime (&now), 24);
	}
	o << " */" << "\n";
}

/*
 * note [condition order]
 *
 * In theory re2c makes no guarantee about the order of conditions in
 * the generated lexer. Users should define condition type 'YYCONDTYPE'
 * and use values of this type with 'YYGETCONDITION' and 'YYSETCONDITION'.
 * This way code is independent of internal re2c condition numbering.
 *
 * However, it is possible to manually hardcode condition numbers and make
 * re2c generate condition dispatch without explicit use of condition names
 * (nested 'if' statements with '-b' or computed 'goto' table with '-g').
 * This code is syntactically valid (compiles), but unsafe:
 *     - change of re2c options may break compilation
 *     - change of internal re2c condition numbering may break runtime
 *
 * re2c has to preserve the existing numbering scheme.
 *
 * re2c warns about implicit assumptions about condition order, unless:
 *     - condition type is defined with 'types:re2c' or '-t, --type-header'
 *     - dispatch is independent of condition order: either it uses
 *       explicit condition names or there's only one condition and
 *       dispatch shrinks to unconditional jump
 */

static std::string output_cond_get(const opt_t *opts)
{
	return opts->cond_get + (opts->cond_get_naked ? "" : "()");
}

static void output_cond_goto_binary(std::ostream &o, uint32_t ind,
	const std::vector<std::string> &conds, const opt_t *opts,
	size_t lower, size_t upper)
{
	const std::string indstr = indent(ind, opts->indString);

	if (lower == upper) {
		o << indstr << "goto " << opts->condPrefix << conds[lower] << ";\n";
	} else {
		const size_t middle = lower + (upper - lower + 1) / 2;
		o << indstr << "if (" << output_cond_get(opts) << " < " << middle << ") {\n";
		output_cond_goto_binary(o, ind + 1, conds, opts, lower, middle - 1);
		o << indstr << "} else {\n";
		output_cond_goto_binary(o, ind + 1, conds, opts, middle, upper);
		o << indstr << "}\n";
	}
}

void output_cond_goto(std::ostream &o, uint32_t ind,
	const std::vector<std::string> &conds, const opt_t *opts,
	Warn &warn, bool warn_cond_order, uint32_t line)
{
	const size_t ncond = conds.size();
	const std::string indstr = indent(ind, opts->indString);

	if (opts->target == opt_t::DOT) {
		for (size_t i = 0; i < ncond; ++i) {
			const std::string &cond = conds[i];
			o << "0 -> " << cond << " [label=\"state=" << cond << "\"]\n";
		}
		return;
	}

	if (opts->gFlag) {
		o << indstr << "goto *" << opts->yyctable
			<< "[" << output_cond_get(opts) << "];\n";
	} else if (opts->sFlag) {
		if (ncond == 1) warn_cond_order = false;
		output_cond_goto_binary(o, ind, conds, opts, 0, ncond - 1);
	} else {
		warn_cond_order = false;
		o << indstr << "switch (" << output_cond_get(opts) << ") {\n";
		for (size_t i = 0; i < ncond; ++i) {
			const std::string &cond = conds[i];
			o << indstr << "case " << opts->condEnumPrefix << cond
				<<": goto " << opts->condPrefix << cond << ";\n";
		}
		o << indstr << "}\n";
	}

	// see note [condition order]
	if (warn_cond_order) warn.condition_order(line);
}

void output_cond_table(std::ostream &o, uint32_t ind,
	const std::vector<std::string> &conds, const opt_t *opts)
{
	const size_t ncond = conds.size();
	const std::string indstr = opts->indString;

	o << indent(ind++, indstr) << "static void *" << opts->yyctable << "[" << ncond << "] = {\n";
	for (size_t i = 0; i < ncond; ++i) {
		o << indent(ind, indstr) << "&&" << opts->condPrefix << conds[i] << ",\n";
	}
	o << indent(--ind, indstr) << "};\n";
}

} // namespace re2c