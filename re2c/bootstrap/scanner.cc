/* Generated by re2c 0.13.3.dev on Mon Feb 18 22:23:11 2008 */
/* $Id$ */
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <sstream>
#include <stdarg.h>
#include "scanner.h"
#include "parser.h"
#include "y.tab.h"
#include "globals.h"
#include "dfa.h"

extern YYSTYPE yylval;

#ifndef MAX
#define MAX(a,b) (((a)>(b))?(a):(b))
#endif

#define	BSIZE		8192
#define	YYCTYPE		unsigned char
#define	YYCURSOR	cursor
#define	YYLIMIT		lim
#define	YYMARKER	ptr
#define YYCTXMARKER ctx
#define	YYFILL(n)	{cursor = fill(cursor);}

#define	RETURN(i)	{cur = cursor; return i;}

namespace re2c
{

Scanner::Scanner(std::istream& i, std::ostream& o)
	: in(i)
	, out(o)
	, bot(NULL), tok(NULL), ptr(NULL), cur(NULL), pos(NULL), lim(NULL)
	, top(NULL), eof(NULL), ctx(NULL), tchar(0), tline(0), cline(1), iscfg(0)
{
	;
}

char *Scanner::fill(char *cursor)
{
	if(!eof)
	{
		uint cnt = tok - bot;
		if(cnt)
		{
			memcpy(bot, tok, lim - tok);
			tok = bot;
			ptr -= cnt;
			cursor -= cnt;
			pos -= cnt;
			lim -= cnt;
		}
		if((top - lim) < BSIZE)
		{
			char *buf = new char[(lim - bot) + BSIZE];
			memcpy(buf, tok, lim - tok);
			tok = buf;
			ptr = &buf[ptr - bot];
			cursor = &buf[cursor - bot];
			pos = &buf[pos - bot];
			lim = &buf[lim - bot];
			top = &lim[BSIZE];
			delete [] bot;
			bot = buf;
		}
		in.read(lim, BSIZE);
		if((cnt = in.gcount()) != BSIZE)
		{
			eof = &lim[cnt];
			*eof++ = '\0';
		}
		lim += cnt;
	}
	return cursor;
}



int Scanner::echo()
{
	char *cursor = cur;
	bool ignore_eoc = false;
	int  ignore_cnt = 0;

	if (eof && cursor == eof) // Catch EOF
	{
		return 0;
	}
	
	tok = cursor;
echo:

{
	YYCTYPE yych;
	unsigned int yyaccept = 0;

	if ((YYLIMIT - YYCURSOR) < 16) YYFILL(16);
	yych = *YYCURSOR;
	if (yych <= ')') {
		if (yych <= 0x00) goto yy7;
		if (yych == 0x0A) goto yy5;
		goto yy9;
	} else {
		if (yych <= '*') goto yy4;
		if (yych != '/') goto yy9;
	}
	yyaccept = 0;
	yych = *(YYMARKER = ++YYCURSOR);
	if (yych == '*') goto yy16;
yy3:
	{
					goto echo;
				}
yy4:
	yych = *++YYCURSOR;
	if (yych == '/') goto yy10;
	goto yy3;
yy5:
	++YYCURSOR;
	{
					if (ignore_eoc)
					{
						ignore_cnt++;
					}
					else
					{
						out.write((const char*)(tok), (const char*)(cursor) - (const char*)(tok));
					}
					tok = pos = cursor;
					cline++;
					goto echo;
				}
yy7:
	++YYCURSOR;
	{
					if (!ignore_eoc)
					{
						out.write((const char*)(tok), (const char*)(cursor) - (const char*)(tok) - 1);
						// -1 so we don't write out the \0
					}
					if(cursor == eof)
					{
						RETURN(0);
					}
				}
yy9:
	yych = *++YYCURSOR;
	goto yy3;
yy10:
	yyaccept = 1;
	yych = *(YYMARKER = ++YYCURSOR);
	if (yych == 0x0A) goto yy14;
	if (yych == 0x0D) goto yy12;
yy11:
	{
					if (ignore_eoc)
					{
						if (ignore_cnt)
						{
							out << "\n" << sourceFileInfo;
						}
						ignore_eoc = false;
						ignore_cnt = 0;
					}
					else
					{
						out.write((const char*)(tok), (const char*)(cursor) - (const char*)(tok));
					}
					tok = pos = cursor;
					goto echo;
				}
yy12:
	yych = *++YYCURSOR;
	if (yych == 0x0A) goto yy14;
yy13:
	YYCURSOR = YYMARKER;
	if (yyaccept <= 0) {
		goto yy3;
	} else {
		goto yy11;
	}
yy14:
	++YYCURSOR;
	{
					cline++;
					if (ignore_eoc)
					{
						if (ignore_cnt)
						{
							out << sourceFileInfo;
						}
						ignore_eoc = false;
						ignore_cnt = 0;
					}
					else
					{
						out.write((const char*)(tok), (const char*)(cursor) - (const char*)(tok));
					}
					tok = pos = cursor;
					goto echo;
				}
yy16:
	yych = *++YYCURSOR;
	if (yych != '!') goto yy13;
	yych = *++YYCURSOR;
	switch (yych) {
	case 'g':	goto yy20;
	case 'i':	goto yy19;
	case 'm':	goto yy21;
	case 'r':	goto yy22;
	case 't':	goto yy18;
	default:	goto yy13;
	}
yy18:
	yych = *++YYCURSOR;
	if (yych == 'y') goto yy59;
	goto yy13;
yy19:
	yych = *++YYCURSOR;
	if (yych == 'g') goto yy48;
	goto yy13;
yy20:
	yych = *++YYCURSOR;
	if (yych == 'e') goto yy35;
	goto yy13;
yy21:
	yych = *++YYCURSOR;
	if (yych == 'a') goto yy27;
	goto yy13;
yy22:
	yych = *++YYCURSOR;
	if (yych != 'e') goto yy13;
	yych = *++YYCURSOR;
	if (yych != '2') goto yy13;
	yych = *++YYCURSOR;
	if (yych != 'c') goto yy13;
	++YYCURSOR;
	{
					if (bUsedYYMaxFill && bSinglePass)
					{
						fatal("found scanner block after YYMAXFILL declaration");
					}
					out.write((const char*)(tok), (const char*)(&cursor[-7]) - (const char*)(tok));
					tok = cursor;
					RETURN(1);
				}
yy27:
	yych = *++YYCURSOR;
	if (yych != 'x') goto yy13;
	yych = *++YYCURSOR;
	if (yych != ':') goto yy13;
	yych = *++YYCURSOR;
	if (yych != 'r') goto yy13;
	yych = *++YYCURSOR;
	if (yych != 'e') goto yy13;
	yych = *++YYCURSOR;
	if (yych != '2') goto yy13;
	yych = *++YYCURSOR;
	if (yych != 'c') goto yy13;
	++YYCURSOR;
	{
					if (bUsedYYMaxFill)
					{
						fatal("cannot generate YYMAXFILL twice");
					}
					out << "#define YYMAXFILL " << maxFill << std::endl;
					tok = pos = cursor;
					ignore_eoc = true;
					bUsedYYMaxFill = true;
					goto echo;
				}
yy35:
	yych = *++YYCURSOR;
	if (yych != 't') goto yy13;
	yych = *++YYCURSOR;
	if (yych != 's') goto yy13;
	yych = *++YYCURSOR;
	if (yych != 't') goto yy13;
	yych = *++YYCURSOR;
	if (yych != 'a') goto yy13;
	yych = *++YYCURSOR;
	if (yych != 't') goto yy13;
	yych = *++YYCURSOR;
	if (yych != 'e') goto yy13;
	yych = *++YYCURSOR;
	if (yych != ':') goto yy13;
	yych = *++YYCURSOR;
	if (yych != 'r') goto yy13;
	yych = *++YYCURSOR;
	if (yych != 'e') goto yy13;
	yych = *++YYCURSOR;
	if (yych != '2') goto yy13;
	yych = *++YYCURSOR;
	if (yych != 'c') goto yy13;
	++YYCURSOR;
	{
					tok = pos = cursor;
					genGetStateGoto(out, topIndent, 0);
					ignore_eoc = true;
					goto echo;
				}
yy48:
	yych = *++YYCURSOR;
	if (yych != 'n') goto yy13;
	yych = *++YYCURSOR;
	if (yych != 'o') goto yy13;
	yych = *++YYCURSOR;
	if (yych != 'r') goto yy13;
	yych = *++YYCURSOR;
	if (yych != 'e') goto yy13;
	yych = *++YYCURSOR;
	if (yych != ':') goto yy13;
	yych = *++YYCURSOR;
	if (yych != 'r') goto yy13;
	yych = *++YYCURSOR;
	if (yych != 'e') goto yy13;
	yych = *++YYCURSOR;
	if (yych != '2') goto yy13;
	yych = *++YYCURSOR;
	if (yych != 'c') goto yy13;
	++YYCURSOR;
	{
					tok = pos = cursor;
					ignore_eoc = true;
					goto echo;
				}
yy59:
	yych = *++YYCURSOR;
	if (yych != 'p') goto yy13;
	yych = *++YYCURSOR;
	if (yych != 'e') goto yy13;
	yych = *++YYCURSOR;
	if (yych != 's') goto yy13;
	yych = *++YYCURSOR;
	if (yych != ':') goto yy13;
	yych = *++YYCURSOR;
	if (yych != 'r') goto yy13;
	yych = *++YYCURSOR;
	if (yych != 'e') goto yy13;
	yych = *++YYCURSOR;
	if (yych != '2') goto yy13;
	yych = *++YYCURSOR;
	if (yych != 'c') goto yy13;
	++YYCURSOR;
	{
					if (bSinglePass)
					{
						fatal("cannot generate types inline in single pass mode");
					}
					tok = pos = cursor;
					ignore_eoc = true;
					if (bLastPass)
					{
						out << outputFileInfo;
						out << "\n";
						out << typesInline;
						out << "\n";
						out << sourceFileInfo;
					}
					goto echo;
				}
}

}


int Scanner::scan()
{
	char *cursor = cur;
	uint depth;

scan:
	tchar = cursor - pos;
	tline = cline;
	tok = cursor;
	if (iscfg == 1)
	{
		goto config;
	}
	else if (iscfg == 2)
	{
		goto value;
	}

{
	YYCTYPE yych;
	unsigned int yyaccept = 0;
	static const unsigned char yybm[] = {
		112, 112, 112, 112, 112, 112, 112, 112, 
		112, 122,   8, 112, 112, 120, 112, 112, 
		112, 112, 112, 112, 112, 112, 112, 112, 
		112, 112, 112, 112, 112, 112, 112, 112, 
		122, 112,  48, 112, 112, 112, 112,  80, 
		112, 112, 112, 112, 112, 112, 112, 112, 
		244, 244, 244, 244, 244, 244, 244, 244, 
		244, 244, 112, 112, 112, 112, 112, 112, 
		112, 116, 116, 116, 116, 116, 116, 116, 
		116, 116, 116, 116, 116, 116, 116, 116, 
		116, 116, 116, 116, 116, 116, 116, 116, 
		116, 116, 116, 112,   0,  96, 112, 116, 
		112, 116, 116, 116, 116, 116, 116, 116, 
		116, 116, 116, 116, 116, 116, 116, 116, 
		116, 116, 116, 116, 116, 116, 116, 116, 
		116, 116, 116, 112, 112, 112, 112, 112, 
		112, 112, 112, 112, 112, 112, 112, 112, 
		112, 112, 112, 112, 112, 112, 112, 112, 
		112, 112, 112, 112, 112, 112, 112, 112, 
		112, 112, 112, 112, 112, 112, 112, 112, 
		112, 112, 112, 112, 112, 112, 112, 112, 
		112, 112, 112, 112, 112, 112, 112, 112, 
		112, 112, 112, 112, 112, 112, 112, 112, 
		112, 112, 112, 112, 112, 112, 112, 112, 
		112, 112, 112, 112, 112, 112, 112, 112, 
		112, 112, 112, 112, 112, 112, 112, 112, 
		112, 112, 112, 112, 112, 112, 112, 112, 
		112, 112, 112, 112, 112, 112, 112, 112, 
		112, 112, 112, 112, 112, 112, 112, 112, 
		112, 112, 112, 112, 112, 112, 112, 112, 
		112, 112, 112, 112, 112, 112, 112, 112, 
		112, 112, 112, 112, 112, 112, 112, 112, 
	};
	if ((YYLIMIT - YYCURSOR) < 5) YYFILL(5);
	yych = *YYCURSOR;
	if (yych <= '/') {
		if (yych <= '"') {
			if (yych <= 0x0C) {
				if (yych <= 0x08) goto yy99;
				if (yych <= 0x09) goto yy94;
				if (yych <= 0x0A) goto yy96;
				goto yy99;
			} else {
				if (yych <= 0x1F) {
					if (yych <= 0x0D) goto yy98;
					goto yy99;
				} else {
					if (yych <= ' ') goto yy94;
					if (yych <= '!') goto yy99;
					goto yy79;
				}
			}
		} else {
			if (yych <= '*') {
				if (yych <= '&') goto yy99;
				if (yych <= '\'') goto yy81;
				if (yych <= ')') goto yy86;
				goto yy77;
			} else {
				if (yych <= ',') {
					if (yych <= '+') goto yy87;
					goto yy86;
				} else {
					if (yych <= '-') goto yy99;
					if (yych <= '.') goto yy92;
					goto yy75;
				}
			}
		}
	} else {
		if (yych <= '[') {
			if (yych <= '<') {
				if (yych <= '9') goto yy99;
				if (yych <= ':') goto yy73;
				if (yych <= ';') goto yy86;
				goto yy85;
			} else {
				if (yych <= '?') {
					if (yych <= '>') goto yy86;
					goto yy87;
				} else {
					if (yych <= '@') goto yy99;
					if (yych <= 'Z') goto yy91;
					goto yy83;
				}
			}
		} else {
			if (yych <= 'q') {
				if (yych <= '^') {
					if (yych <= '\\') goto yy86;
					goto yy99;
				} else {
					if (yych == '`') goto yy99;
					goto yy91;
				}
			} else {
				if (yych <= 'z') {
					if (yych <= 'r') goto yy89;
					goto yy91;
				} else {
					if (yych <= '{') goto yy71;
					if (yych <= '|') goto yy86;
					goto yy99;
				}
			}
		}
	}
yy71:
	yyaccept = 0;
	yych = *(YYMARKER = ++YYCURSOR);
	if (yych <= '@') {
		if (yych <= '/') {
			if (yych == ',') goto yy158;
		} else {
			if (yych <= '0') goto yy155;
			if (yych <= '9') goto yy156;
		}
	} else {
		if (yych <= '_') {
			if (yych <= 'Z') goto yy153;
			if (yych >= '_') goto yy153;
		} else {
			if (yych <= '`') goto yy72;
			if (yych <= 'z') goto yy153;
		}
	}
yy72:
	{
					depth = 1;
					goto code;
				}
yy73:
	YYCTXMARKER = YYCURSOR + 1;
	++YYCURSOR;
	if ((yych = *YYCURSOR) == '=') goto yy149;
yy74:
	{
					std::ostringstream msg;
					msg << "unexpected character: ";
					prtChOrHex(msg, *tok);
					fatal(msg.str().c_str());
					goto scan;
				}
yy75:
	++YYCURSOR;
	if ((yych = *YYCURSOR) == '*') goto yy147;
yy76:
	{
					RETURN(*tok);
				}
yy77:
	++YYCURSOR;
	if ((yych = *YYCURSOR) == '/') goto yy145;
	{
					yylval.op = *tok;
					RETURN(STAR);
				}
yy79:
	yyaccept = 1;
	yych = *(YYMARKER = ++YYCURSOR);
	if (yych != 0x0A) goto yy141;
yy80:
	{
					fatal("unterminated string constant (missing \")");
				}
yy81:
	yyaccept = 2;
	yych = *(YYMARKER = ++YYCURSOR);
	if (yych != 0x0A) goto yy136;
yy82:
	{
					fatal("unterminated string constant (missing ')");
				}
yy83:
	yyaccept = 3;
	yych = *(YYMARKER = ++YYCURSOR);
	if (yych == 0x0A) goto yy84;
	if (yych == '^') goto yy127;
	goto yy126;
yy84:
	{
					fatal("unterminated range (missing ])");
				}
yy85:
	yyaccept = 4;
	yych = *(YYMARKER = ++YYCURSOR);
	if (yych == '!') goto yy116;
	if (yych == '>') goto yy118;
	goto yy76;
yy86:
	yych = *++YYCURSOR;
	goto yy76;
yy87:
	++YYCURSOR;
	{
					yylval.op = *tok;
					RETURN(CLOSE);
				}
yy89:
	++YYCURSOR;
	if ((yych = *YYCURSOR) == 'e') goto yy105;
	goto yy104;
yy90:
	{
					cur = cursor;
					yylval.symbol = Symbol::find(token());
					return ID;
				}
yy91:
	yych = *++YYCURSOR;
	goto yy104;
yy92:
	++YYCURSOR;
	{
					cur = cursor;
					yylval.regexp = mkDot();
					return RANGE;
				}
yy94:
	++YYCURSOR;
	yych = *YYCURSOR;
	goto yy102;
yy95:
	{
					goto scan;
				}
yy96:
	++YYCURSOR;
yy97:
	{
					if(cursor == eof) RETURN(0);
					pos = cursor;
					cline++;
					goto scan;
				}
yy98:
	yych = *++YYCURSOR;
	if (yych == 0x0A) goto yy100;
	goto yy74;
yy99:
	yych = *++YYCURSOR;
	goto yy74;
yy100:
	yych = *++YYCURSOR;
	goto yy97;
yy101:
	++YYCURSOR;
	if (YYLIMIT == YYCURSOR) YYFILL(1);
	yych = *YYCURSOR;
yy102:
	if (yybm[0+yych] & 2) {
		goto yy101;
	}
	goto yy95;
yy103:
	++YYCURSOR;
	if (YYLIMIT == YYCURSOR) YYFILL(1);
	yych = *YYCURSOR;
yy104:
	if (yybm[0+yych] & 4) {
		goto yy103;
	}
	goto yy90;
yy105:
	yych = *++YYCURSOR;
	if (yych != '2') goto yy104;
	yych = *++YYCURSOR;
	if (yych != 'c') goto yy104;
	yyaccept = 5;
	yych = *(YYMARKER = ++YYCURSOR);
	if (yych != ':') goto yy104;
yy108:
	++YYCURSOR;
	if (YYLIMIT == YYCURSOR) YYFILL(1);
	yych = *YYCURSOR;
	if (yych <= '^') {
		if (yych <= '@') goto yy109;
		if (yych <= 'Z') goto yy110;
	} else {
		if (yych == '`') goto yy109;
		if (yych <= 'z') goto yy110;
	}
yy109:
	YYCURSOR = YYMARKER;
	if (yyaccept <= 3) {
		if (yyaccept <= 1) {
			if (yyaccept <= 0) {
				goto yy72;
			} else {
				goto yy80;
			}
		} else {
			if (yyaccept <= 2) {
				goto yy82;
			} else {
				goto yy84;
			}
		}
	} else {
		if (yyaccept <= 5) {
			if (yyaccept <= 4) {
				goto yy76;
			} else {
				goto yy90;
			}
		} else {
			if (yyaccept <= 6) {
				goto yy112;
			} else {
				goto yy159;
			}
		}
	}
yy110:
	yyaccept = 6;
	YYMARKER = ++YYCURSOR;
	if ((YYLIMIT - YYCURSOR) < 2) YYFILL(2);
	yych = *YYCURSOR;
	if (yych <= '@') {
		if (yych <= '9') {
			if (yych >= '0') goto yy110;
		} else {
			if (yych <= ':') goto yy108;
			if (yych >= '@') goto yy113;
		}
	} else {
		if (yych <= '_') {
			if (yych <= 'Z') goto yy110;
			if (yych >= '_') goto yy110;
		} else {
			if (yych <= '`') goto yy112;
			if (yych <= 'z') goto yy110;
		}
	}
yy112:
	{
					cur = cursor;
					tok+= 5; /* skip "re2c:" */
					iscfg = 1;
					yylval.str = new Str(token());
					return CONFIG;
				}
yy113:
	yych = *++YYCURSOR;
	if (yych <= '^') {
		if (yych <= '@') goto yy109;
		if (yych >= '[') goto yy109;
	} else {
		if (yych == '`') goto yy109;
		if (yych >= '{') goto yy109;
	}
yy114:
	++YYCURSOR;
	if (YYLIMIT == YYCURSOR) YYFILL(1);
	yych = *YYCURSOR;
	if (yych <= 'Z') {
		if (yych <= '/') goto yy112;
		if (yych <= '9') goto yy114;
		if (yych <= '@') goto yy112;
		goto yy114;
	} else {
		if (yych <= '_') {
			if (yych <= '^') goto yy112;
			goto yy114;
		} else {
			if (yych <= '`') goto yy112;
			if (yych <= 'z') goto yy114;
			goto yy112;
		}
	}
yy116:
	++YYCURSOR;
	{
					RETURN(SETUP);
				}
yy118:
	YYCTXMARKER = YYCURSOR + 1;
	yych = *++YYCURSOR;
	goto yy120;
yy119:
	++YYCURSOR;
	if ((YYLIMIT - YYCURSOR) < 2) YYFILL(2);
	yych = *YYCURSOR;
yy120:
	if (yybm[0+yych] & 8) {
		goto yy119;
	}
	if (yych <= '<') {
		if (yych == ':') goto yy124;
		goto yy109;
	} else {
		if (yych <= '=') goto yy123;
		if (yych != '{') goto yy109;
	}
yy121:
	++YYCURSOR;
	YYCURSOR = YYCTXMARKER;
	{
					RETURN(NOCOND);
				}
yy123:
	yych = *++YYCURSOR;
	if (yych == '>') goto yy121;
	goto yy109;
yy124:
	yych = *++YYCURSOR;
	if (yych == '=') goto yy121;
	goto yy109;
yy125:
	++YYCURSOR;
	if (YYLIMIT == YYCURSOR) YYFILL(1);
	yych = *YYCURSOR;
yy126:
	if (yybm[0+yych] & 16) {
		goto yy125;
	}
	if (yych <= '[') goto yy109;
	if (yych <= '\\') goto yy129;
	goto yy130;
yy127:
	++YYCURSOR;
	if (YYLIMIT == YYCURSOR) YYFILL(1);
	yych = *YYCURSOR;
	if (yych <= '[') {
		if (yych == 0x0A) goto yy109;
		goto yy127;
	} else {
		if (yych <= '\\') goto yy132;
		if (yych <= ']') goto yy133;
		goto yy127;
	}
yy129:
	++YYCURSOR;
	if (YYLIMIT == YYCURSOR) YYFILL(1);
	yych = *YYCURSOR;
	if (yych == 0x0A) goto yy109;
	goto yy125;
yy130:
	++YYCURSOR;
	{
					cur = cursor;
					yylval.regexp = ranToRE(token());
					return RANGE;
				}
yy132:
	++YYCURSOR;
	if (YYLIMIT == YYCURSOR) YYFILL(1);
	yych = *YYCURSOR;
	if (yych == 0x0A) goto yy109;
	goto yy127;
yy133:
	++YYCURSOR;
	{
					cur = cursor;
					yylval.regexp = invToRE(token());
					return RANGE;
				}
yy135:
	++YYCURSOR;
	if (YYLIMIT == YYCURSOR) YYFILL(1);
	yych = *YYCURSOR;
yy136:
	if (yybm[0+yych] & 32) {
		goto yy135;
	}
	if (yych <= '&') goto yy109;
	if (yych <= '\'') goto yy138;
	++YYCURSOR;
	if (YYLIMIT == YYCURSOR) YYFILL(1);
	yych = *YYCURSOR;
	if (yych == 0x0A) goto yy109;
	goto yy135;
yy138:
	++YYCURSOR;
	{
					cur = cursor;
					if (bCaseInverted)
					{
						yylval.regexp = strToRE(token());
					}
					else
					{
						yylval.regexp = strToCaseInsensitiveRE(token());
					}
					return STRING;
				}
yy140:
	++YYCURSOR;
	if (YYLIMIT == YYCURSOR) YYFILL(1);
	yych = *YYCURSOR;
yy141:
	if (yybm[0+yych] & 64) {
		goto yy140;
	}
	if (yych <= '!') goto yy109;
	if (yych <= '"') goto yy143;
	++YYCURSOR;
	if (YYLIMIT == YYCURSOR) YYFILL(1);
	yych = *YYCURSOR;
	if (yych == 0x0A) goto yy109;
	goto yy140;
yy143:
	++YYCURSOR;
	{
					cur = cursor;
					if (bCaseInsensitive || bCaseInverted)
					{
						yylval.regexp = strToCaseInsensitiveRE(token());
					}
					else
					{
						yylval.regexp = strToRE(token());
					}
					return STRING;
				}
yy145:
	++YYCURSOR;
	{
					tok = cursor;
					RETURN(0);
				}
yy147:
	++YYCURSOR;
	{
					depth = 1;
					goto comment;
				}
yy149:
	++YYCURSOR;
	if ((yych = *YYCURSOR) == '>') goto yy151;
	{
					cur = cursor;
					tok+= 2; /* skip ":=" */
					depth = 0;
					goto code;
				}
yy151:
	++YYCURSOR;
	YYCURSOR = YYCTXMARKER;
	{
					RETURN(*tok);
				}
yy153:
	++YYCURSOR;
	if (YYLIMIT == YYCURSOR) YYFILL(1);
	yych = *YYCURSOR;
	if (yych <= '^') {
		if (yych <= '9') {
			if (yych <= '/') goto yy109;
			goto yy153;
		} else {
			if (yych <= '@') goto yy109;
			if (yych <= 'Z') goto yy153;
			goto yy109;
		}
	} else {
		if (yych <= 'z') {
			if (yych == '`') goto yy109;
			goto yy153;
		} else {
			if (yych == '}') goto yy172;
			goto yy109;
		}
	}
yy155:
	yych = *++YYCURSOR;
	if (yych == ',') goto yy169;
	goto yy157;
yy156:
	++YYCURSOR;
	if ((YYLIMIT - YYCURSOR) < 2) YYFILL(2);
	yych = *YYCURSOR;
yy157:
	if (yybm[0+yych] & 128) {
		goto yy156;
	}
	if (yych == ',') goto yy162;
	if (yych == '}') goto yy160;
	goto yy109;
yy158:
	++YYCURSOR;
yy159:
	{
					fatal("illegal closure form, use '{n}', '{n,}', '{n,m}' where n and m are numbers");
				}
yy160:
	++YYCURSOR;
	{
					yylval.extop.minsize = atoi((char *)tok+1);
					yylval.extop.maxsize = atoi((char *)tok+1);
					RETURN(CLOSESIZE);
				}
yy162:
	yyaccept = 7;
	yych = *(YYMARKER = ++YYCURSOR);
	if (yych <= '/') goto yy159;
	if (yych <= '9') goto yy165;
	if (yych != '}') goto yy159;
	++YYCURSOR;
	{
					yylval.extop.minsize = atoi((char *)tok+1);
					yylval.extop.maxsize = -1;
					RETURN(CLOSESIZE);
				}
yy165:
	++YYCURSOR;
	if (YYLIMIT == YYCURSOR) YYFILL(1);
	yych = *YYCURSOR;
	if (yych <= '/') goto yy109;
	if (yych <= '9') goto yy165;
	if (yych != '}') goto yy109;
	++YYCURSOR;
	{
					yylval.extop.minsize = atoi((char *)tok+1);
					yylval.extop.maxsize = MAX(yylval.extop.minsize,atoi(strchr((char *)tok, ',')+1));
					RETURN(CLOSESIZE);
				}
yy169:
	yyaccept = 7;
	yych = *(YYMARKER = ++YYCURSOR);
	if (yych <= '/') goto yy159;
	if (yych <= '9') goto yy165;
	if (yych != '}') goto yy159;
	++YYCURSOR;
	{
					yylval.op = '*';
					RETURN(CLOSE);
				}
yy172:
	++YYCURSOR;
	{
					if (!FFlag) {
						fatal("curly braces for names only allowed with -F switch");
					}
					cur = cursor;
					yylval.symbol = Symbol::find(token(1, cur - tok - 2));
					return ID;
				}
}


code:

{
	YYCTYPE yych;
	static const unsigned char yybm[] = {
		192, 192, 192, 192, 192, 192, 192, 192, 
		192, 192,   0, 192, 192, 192, 192, 192, 
		192, 192, 192, 192, 192, 192, 192, 192, 
		192, 192, 192, 192, 192, 192, 192, 192, 
		192, 192,  64, 192, 192, 192, 192, 128, 
		192, 192, 192, 192, 192, 192, 192, 192, 
		192, 192, 192, 192, 192, 192, 192, 192, 
		192, 192, 192, 192, 192, 192, 192, 192, 
		192, 192, 192, 192, 192, 192, 192, 192, 
		192, 192, 192, 192, 192, 192, 192, 192, 
		192, 192, 192, 192, 192, 192, 192, 192, 
		192, 192, 192, 192,   0, 192, 192, 192, 
		192, 192, 192, 192, 192, 192, 192, 192, 
		192, 192, 192, 192, 192, 192, 192, 192, 
		192, 192, 192, 192, 192, 192, 192, 192, 
		192, 192, 192, 192, 192, 192, 192, 192, 
		192, 192, 192, 192, 192, 192, 192, 192, 
		192, 192, 192, 192, 192, 192, 192, 192, 
		192, 192, 192, 192, 192, 192, 192, 192, 
		192, 192, 192, 192, 192, 192, 192, 192, 
		192, 192, 192, 192, 192, 192, 192, 192, 
		192, 192, 192, 192, 192, 192, 192, 192, 
		192, 192, 192, 192, 192, 192, 192, 192, 
		192, 192, 192, 192, 192, 192, 192, 192, 
		192, 192, 192, 192, 192, 192, 192, 192, 
		192, 192, 192, 192, 192, 192, 192, 192, 
		192, 192, 192, 192, 192, 192, 192, 192, 
		192, 192, 192, 192, 192, 192, 192, 192, 
		192, 192, 192, 192, 192, 192, 192, 192, 
		192, 192, 192, 192, 192, 192, 192, 192, 
		192, 192, 192, 192, 192, 192, 192, 192, 
		192, 192, 192, 192, 192, 192, 192, 192, 
	};
	if ((YYLIMIT - YYCURSOR) < 2) YYFILL(2);
	yych = *YYCURSOR;
	if (yych <= '&') {
		if (yych <= 0x0A) {
			if (yych <= 0x00) goto yy182;
			if (yych <= 0x09) goto yy184;
			goto yy180;
		} else {
			if (yych == '"') goto yy186;
			goto yy184;
		}
	} else {
		if (yych <= '{') {
			if (yych <= '\'') goto yy187;
			if (yych <= 'z') goto yy184;
			goto yy178;
		} else {
			if (yych != '}') goto yy184;
		}
	}
	++YYCURSOR;
	{
					if (depth == 0)
					{
						fatal("Curly braces are not allowed after ':='");
					}
					else if (--depth == 0)
					{
						cur = cursor;
						yylval.token = new Token(token(), tline);
						return CODE;
					}
					goto code;
				}
yy178:
	++YYCURSOR;
	{
					if (depth == 0)
					{
						fatal("Curly braces are not allowed after ':='");
					}
					else
					{
						++depth;
					}
					goto code;
				}
yy180:
	YYCTXMARKER = YYCURSOR + 1;
	++YYCURSOR;
	if ((yych = *YYCURSOR) <= 0x0C) {
		if (yych <= 0x08) goto yy181;
		if (yych <= 0x0A) goto yy195;
	} else {
		if (yych <= 0x0D) goto yy195;
		if (yych == ' ') goto yy195;
	}
yy181:
	{
					if (depth == 0)
					{
						cur = cursor;
						tok += strspn(tok, " \t\r\n");
						while (cur > tok && strchr(" \t\r\n", cur[-1]))
						{
							--cur;
						}
						yylval.token = new Token(token(), tline);
						return CODE;
					}
					else if (cursor == eof)
					{
						fatal("missing '}'");
					}
					pos = cursor;
					cline++;
					goto code;
				}
yy182:
	++YYCURSOR;
	{
					if (cursor == eof)
					{
						if (depth)
						{
							fatal("missing '}'");
						}
						RETURN(0);
					}
					goto code;
				}
yy184:
	++YYCURSOR;
yy185:
	{
					goto code;
				}
yy186:
	yych = *(YYMARKER = ++YYCURSOR);
	if (yych == 0x0A) goto yy185;
	goto yy193;
yy187:
	yych = *(YYMARKER = ++YYCURSOR);
	if (yych == 0x0A) goto yy185;
	goto yy189;
yy188:
	++YYCURSOR;
	if (YYLIMIT == YYCURSOR) YYFILL(1);
	yych = *YYCURSOR;
yy189:
	if (yybm[0+yych] & 64) {
		goto yy188;
	}
	if (yych <= '&') goto yy190;
	if (yych <= '\'') goto yy184;
	goto yy191;
yy190:
	YYCURSOR = YYMARKER;
	goto yy185;
yy191:
	++YYCURSOR;
	if (YYLIMIT == YYCURSOR) YYFILL(1);
	yych = *YYCURSOR;
	if (yych == 0x0A) goto yy190;
	goto yy188;
yy192:
	++YYCURSOR;
	if (YYLIMIT == YYCURSOR) YYFILL(1);
	yych = *YYCURSOR;
yy193:
	if (yybm[0+yych] & 128) {
		goto yy192;
	}
	if (yych <= '!') goto yy190;
	if (yych <= '"') goto yy184;
	++YYCURSOR;
	if (YYLIMIT == YYCURSOR) YYFILL(1);
	yych = *YYCURSOR;
	if (yych == 0x0A) goto yy190;
	goto yy192;
yy195:
	++YYCURSOR;
	YYCURSOR = YYCTXMARKER;
	{
					if (depth == 0)
					{
						goto code;
					}
					else if (cursor == eof)
					{
						fatal("missing '}'");
					}
					pos = cursor;
					cline++;
					goto code;
				}
}


comment:

{
	YYCTYPE yych;
	if ((YYLIMIT - YYCURSOR) < 2) YYFILL(2);
	yych = *YYCURSOR;
	if (yych <= ')') {
		if (yych == 0x0A) goto yy202;
		goto yy204;
	} else {
		if (yych <= '*') goto yy199;
		if (yych == '/') goto yy201;
		goto yy204;
	}
yy199:
	++YYCURSOR;
	if ((yych = *YYCURSOR) == '/') goto yy207;
yy200:
	{
					if(cursor == eof)
					{
						RETURN(0);
					}
					goto comment;
				}
yy201:
	yych = *++YYCURSOR;
	if (yych == '*') goto yy205;
	goto yy200;
yy202:
	++YYCURSOR;
	{
					if(cursor == eof)
					{
						RETURN(0);
					}
					tok = pos = cursor;
					cline++;
					goto comment;
				}
yy204:
	yych = *++YYCURSOR;
	goto yy200;
yy205:
	++YYCURSOR;
	{
					++depth;
					fatal("ambiguous /* found");
					goto comment;
				}
yy207:
	++YYCURSOR;
	{
					if(--depth == 0)
					{
						goto scan;
					}
					else
					{
						goto comment;
					}
				}
}


config:

{
	YYCTYPE yych;
	static const unsigned char yybm[] = {
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0, 128,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		128,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
	};
	if ((YYLIMIT - YYCURSOR) < 2) YYFILL(2);
	yych = *YYCURSOR;
	if (yych <= 0x1F) {
		if (yych != 0x09) goto yy215;
	} else {
		if (yych <= ' ') goto yy211;
		if (yych == '=') goto yy213;
		goto yy215;
	}
yy211:
	++YYCURSOR;
	yych = *YYCURSOR;
	goto yy220;
yy212:
	{
					goto config;
				}
yy213:
	++YYCURSOR;
	yych = *YYCURSOR;
	goto yy218;
yy214:
	{
					iscfg = 2;
					cur = cursor;
					RETURN('=');
				}
yy215:
	++YYCURSOR;
	{
					fatal("missing '='");
				}
yy217:
	++YYCURSOR;
	if (YYLIMIT == YYCURSOR) YYFILL(1);
	yych = *YYCURSOR;
yy218:
	if (yybm[0+yych] & 128) {
		goto yy217;
	}
	goto yy214;
yy219:
	++YYCURSOR;
	if (YYLIMIT == YYCURSOR) YYFILL(1);
	yych = *YYCURSOR;
yy220:
	if (yych == 0x09) goto yy219;
	if (yych == ' ') goto yy219;
	goto yy212;
}


value:

{
	YYCTYPE yych;
	static const unsigned char yybm[] = {
		248, 248, 248, 248, 248, 248, 248, 248, 
		248, 192,   0, 248, 248, 192, 248, 248, 
		248, 248, 248, 248, 248, 248, 248, 248, 
		248, 248, 248, 248, 248, 248, 248, 248, 
		192, 248, 104, 248, 248, 248, 248, 152, 
		248, 248, 248, 248, 248, 248, 248, 248, 
		252, 252, 252, 252, 252, 252, 252, 252, 
		252, 252, 248, 192, 248, 248, 248, 248, 
		248, 248, 248, 248, 248, 248, 248, 248, 
		248, 248, 248, 248, 248, 248, 248, 248, 
		248, 248, 248, 248, 248, 248, 248, 248, 
		248, 248, 248, 248,   8, 248, 248, 248, 
		248, 248, 248, 248, 248, 248, 248, 248, 
		248, 248, 248, 248, 248, 248, 248, 248, 
		248, 248, 248, 248, 248, 248, 248, 248, 
		248, 248, 248, 248, 248, 248, 248, 248, 
		248, 248, 248, 248, 248, 248, 248, 248, 
		248, 248, 248, 248, 248, 248, 248, 248, 
		248, 248, 248, 248, 248, 248, 248, 248, 
		248, 248, 248, 248, 248, 248, 248, 248, 
		248, 248, 248, 248, 248, 248, 248, 248, 
		248, 248, 248, 248, 248, 248, 248, 248, 
		248, 248, 248, 248, 248, 248, 248, 248, 
		248, 248, 248, 248, 248, 248, 248, 248, 
		248, 248, 248, 248, 248, 248, 248, 248, 
		248, 248, 248, 248, 248, 248, 248, 248, 
		248, 248, 248, 248, 248, 248, 248, 248, 
		248, 248, 248, 248, 248, 248, 248, 248, 
		248, 248, 248, 248, 248, 248, 248, 248, 
		248, 248, 248, 248, 248, 248, 248, 248, 
		248, 248, 248, 248, 248, 248, 248, 248, 
		248, 248, 248, 248, 248, 248, 248, 248, 
	};
	if ((YYLIMIT - YYCURSOR) < 2) YYFILL(2);
	yych = *YYCURSOR;
	if (yych <= '&') {
		if (yych <= 0x0D) {
			if (yych <= 0x08) goto yy229;
			if (yych <= 0x0A) goto yy223;
			if (yych <= 0x0C) goto yy229;
		} else {
			if (yych <= ' ') {
				if (yych <= 0x1F) goto yy229;
			} else {
				if (yych == '"') goto yy231;
				goto yy229;
			}
		}
	} else {
		if (yych <= '/') {
			if (yych <= '\'') goto yy233;
			if (yych == '-') goto yy226;
			goto yy229;
		} else {
			if (yych <= '9') {
				if (yych <= '0') goto yy224;
				goto yy227;
			} else {
				if (yych != ';') goto yy229;
			}
		}
	}
yy223:
	{
					cur = cursor;
					yylval.str = new Str(token());
					iscfg = 0;
					return VALUE;
				}
yy224:
	++YYCURSOR;
	if (yybm[0+(yych = *YYCURSOR)] & 8) {
		goto yy229;
	}
yy225:
	{
					cur = cursor;
					yylval.number = atoi(token().to_string().c_str());
					iscfg = 0;
					return NUMBER;
				}
yy226:
	yych = *++YYCURSOR;
	if (yych <= '0') goto yy230;
	if (yych >= ':') goto yy230;
yy227:
	++YYCURSOR;
	if (YYLIMIT == YYCURSOR) YYFILL(1);
	yych = *YYCURSOR;
	if (yybm[0+yych] & 4) {
		goto yy227;
	}
	if (yych <= 0x0D) {
		if (yych <= 0x08) goto yy229;
		if (yych <= 0x0A) goto yy225;
		if (yych >= 0x0D) goto yy225;
	} else {
		if (yych <= ' ') {
			if (yych >= ' ') goto yy225;
		} else {
			if (yych == ';') goto yy225;
		}
	}
yy229:
	++YYCURSOR;
	if (YYLIMIT == YYCURSOR) YYFILL(1);
	yych = *YYCURSOR;
yy230:
	if (yybm[0+yych] & 8) {
		goto yy229;
	}
	goto yy223;
yy231:
	YYMARKER = ++YYCURSOR;
	if (YYLIMIT == YYCURSOR) YYFILL(1);
	yych = *YYCURSOR;
	if (yybm[0+yych] & 16) {
		goto yy231;
	}
	if (yych <= '!') {
		if (yych == 0x0A) goto yy223;
		goto yy241;
	} else {
		if (yych <= '"') goto yy229;
		if (yych <= '[') goto yy241;
		goto yy243;
	}
yy233:
	YYMARKER = ++YYCURSOR;
	if (YYLIMIT == YYCURSOR) YYFILL(1);
	yych = *YYCURSOR;
	if (yybm[0+yych] & 32) {
		goto yy233;
	}
	if (yych <= '&') {
		if (yych == 0x0A) goto yy223;
	} else {
		if (yych <= '\'') goto yy229;
		if (yych >= '\\') goto yy238;
	}
yy235:
	++YYCURSOR;
	if (YYLIMIT == YYCURSOR) YYFILL(1);
	yych = *YYCURSOR;
	if (yybm[0+yych] & 64) {
		goto yy235;
	}
	if (yych <= '&') goto yy237;
	if (yych <= '\'') goto yy239;
	goto yy240;
yy237:
	YYCURSOR = YYMARKER;
	goto yy223;
yy238:
	YYMARKER = ++YYCURSOR;
	if (YYLIMIT == YYCURSOR) YYFILL(1);
	yych = *YYCURSOR;
	if (yych <= 0x0D) {
		if (yych <= 0x09) {
			if (yych <= 0x08) goto yy233;
			goto yy235;
		} else {
			if (yych <= 0x0A) goto yy223;
			if (yych <= 0x0C) goto yy233;
			goto yy235;
		}
	} else {
		if (yych <= ' ') {
			if (yych <= 0x1F) goto yy233;
			goto yy235;
		} else {
			if (yych == ';') goto yy235;
			goto yy233;
		}
	}
yy239:
	yych = *++YYCURSOR;
	goto yy223;
yy240:
	++YYCURSOR;
	if (YYLIMIT == YYCURSOR) YYFILL(1);
	yych = *YYCURSOR;
	if (yych == 0x0A) goto yy237;
	goto yy235;
yy241:
	++YYCURSOR;
	if (YYLIMIT == YYCURSOR) YYFILL(1);
	yych = *YYCURSOR;
	if (yybm[0+yych] & 128) {
		goto yy241;
	}
	if (yych <= '!') goto yy237;
	if (yych <= '"') goto yy239;
	goto yy244;
yy243:
	YYMARKER = ++YYCURSOR;
	if (YYLIMIT == YYCURSOR) YYFILL(1);
	yych = *YYCURSOR;
	if (yych <= 0x0D) {
		if (yych <= 0x09) {
			if (yych <= 0x08) goto yy231;
			goto yy241;
		} else {
			if (yych <= 0x0A) goto yy223;
			if (yych <= 0x0C) goto yy231;
			goto yy241;
		}
	} else {
		if (yych <= ' ') {
			if (yych <= 0x1F) goto yy231;
			goto yy241;
		} else {
			if (yych == ';') goto yy241;
			goto yy231;
		}
	}
yy244:
	++YYCURSOR;
	if (YYLIMIT == YYCURSOR) YYFILL(1);
	yych = *YYCURSOR;
	if (yych == 0x0A) goto yy237;
	goto yy241;
}

}

void Scanner::fatal(uint ofs, const char *msg) const
{
	out.flush();
	std::cerr << "re2c: error: "
		<< "line " << tline << ", column " << (tchar + ofs + 1) << ": "
		<< msg << std::endl;
	exit(1);
}

void Scanner::fatalf(const char *fmt, ...) const
{
	char szBuf[4096];

	va_list args;
	
	va_start(args, fmt);
	vsnprintf(szBuf, sizeof(szBuf), fmt, args);
	va_end(args);
	
	szBuf[sizeof(szBuf)-1] = '0';
	
	fatal(szBuf);
}

Scanner::~Scanner()
{
	if (bot)
	{
		delete [] bot;
	}
}

} // end namespace re2c
