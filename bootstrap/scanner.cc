/* Generated by re2c 0.10.2.dev on Sat Apr  8 20:31:13 2006 */
#line 1 "scanner.re"
/* $Id$ */
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <sstream>
#include "scanner.h"
#include "parser.h"
#include "y.tab.h"
#include "globals.h"
#include "dfa.h"

extern YYSTYPE yylval;

#ifndef MAX
#define MAX(a,b) (((a)>(b))?(a):(b))
#endif

#define	BSIZE	8192

#define	YYCTYPE		char
#define	YYCURSOR	cursor
#define	YYLIMIT		lim
#define	YYMARKER	ptr
#define	YYFILL(n)	{cursor = fill(cursor);}

#define	RETURN(i)	{cur = cursor; return i;}

namespace re2c
{

Scanner::Scanner(std::istream& i, std::ostream& o)
	: in(i)
	, out(o)
	, bot(NULL), tok(NULL), ptr(NULL), cur(NULL), pos(NULL), lim(NULL)
	, top(NULL), eof(NULL), tchar(0), tline(0), cline(1), iscfg(0)
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
		if ((cnt = in.gcount()) != BSIZE )
		{
			eof = &lim[cnt]; *eof++ = '\0';
		}
		lim += cnt;
	}
	return cursor;
}

#line 95 "scanner.re"


int Scanner::echo()
{
    char *cursor = cur;
    bool ignore_eoc = false;

    if (eof && cursor == eof) // Catch EOF
	{
    	return 0;
	}

    tok = cursor;
echo:

#line 96 "scanner.cc"
{
	YYCTYPE yych;

	if((YYLIMIT - YYCURSOR) < 16) YYFILL(16);
	yych = *YYCURSOR;
	if(yych <= ')') {
		if(yych <= 0x00) goto yy7;
		if(yych == 0x0A) goto yy5;
		goto yy9;
	} else {
		if(yych <= '*') goto yy4;
		if(yych != '/') goto yy9;
	}
	yych = *(YYMARKER = ++YYCURSOR);
	if(yych == '*') goto yy12;
yy3:
#line 147 "scanner.re"
	{
					goto echo;
				}
#line 117 "scanner.cc"
yy4:
	yych = *++YYCURSOR;
	if(yych == '/') goto yy10;
	goto yy3;
yy5:
	++YYCURSOR;
#line 136 "scanner.re"
	{
					out.write((const char*)(tok), (const char*)(cursor) - (const char*)(tok));
					tok = pos = cursor; cline++;
				  	goto echo;
				}
#line 130 "scanner.cc"
yy7:
	++YYCURSOR;
#line 141 "scanner.re"
	{
					out.write((const char*)(tok), (const char*)(cursor) - (const char*)(tok) - 1); // -1 so we don't write out the \0
					if(cursor == eof) {
						RETURN(0);
					}
				}
#line 140 "scanner.cc"
yy9:
	yych = *++YYCURSOR;
	goto yy3;
yy10:
	++YYCURSOR;
#line 127 "scanner.re"
	{
					if (ignore_eoc) {
						ignore_eoc = false;
					} else {
						out.write((const char*)(tok), (const char*)(cursor) - (const char*)(tok));
					}
					tok = pos = cursor;
					goto echo;
				}
#line 156 "scanner.cc"
yy12:
	yych = *++YYCURSOR;
	if(yych == '!') goto yy14;
yy13:
	YYCURSOR = YYMARKER;
	goto yy3;
yy14:
	yych = *++YYCURSOR;
	if(yych <= 'l') {
		if(yych != 'g') goto yy13;
	} else {
		if(yych <= 'm') goto yy16;
		if(yych == 'r') goto yy17;
		goto yy13;
	}
	yych = *++YYCURSOR;
	if(yych == 'e') goto yy30;
	goto yy13;
yy16:
	yych = *++YYCURSOR;
	if(yych == 'a') goto yy22;
	goto yy13;
yy17:
	yych = *++YYCURSOR;
	if(yych != 'e') goto yy13;
	yych = *++YYCURSOR;
	if(yych != '2') goto yy13;
	yych = *++YYCURSOR;
	if(yych != 'c') goto yy13;
	++YYCURSOR;
#line 110 "scanner.re"
	{ 
					out.write((const char*)(tok), (const char*)(&cursor[-7]) - (const char*)(tok));
					tok = cursor;
					RETURN(1);
				}
#line 193 "scanner.cc"
yy22:
	yych = *++YYCURSOR;
	if(yych != 'x') goto yy13;
	yych = *++YYCURSOR;
	if(yych != ':') goto yy13;
	yych = *++YYCURSOR;
	if(yych != 'r') goto yy13;
	yych = *++YYCURSOR;
	if(yych != 'e') goto yy13;
	yych = *++YYCURSOR;
	if(yych != '2') goto yy13;
	yych = *++YYCURSOR;
	if(yych != 'c') goto yy13;
	++YYCURSOR;
#line 115 "scanner.re"
	{
					out << "#define YYMAXFILL " << maxFill << std::endl;
					tok = pos = cursor;
					ignore_eoc = true;
					goto echo;
				}
#line 215 "scanner.cc"
yy30:
	yych = *++YYCURSOR;
	if(yych != 't') goto yy13;
	yych = *++YYCURSOR;
	if(yych != 's') goto yy13;
	yych = *++YYCURSOR;
	if(yych != 't') goto yy13;
	yych = *++YYCURSOR;
	if(yych != 'a') goto yy13;
	yych = *++YYCURSOR;
	if(yych != 't') goto yy13;
	yych = *++YYCURSOR;
	if(yych != 'e') goto yy13;
	yych = *++YYCURSOR;
	if(yych != ':') goto yy13;
	yych = *++YYCURSOR;
	if(yych != 'r') goto yy13;
	yych = *++YYCURSOR;
	if(yych != 'e') goto yy13;
	yych = *++YYCURSOR;
	if(yych != '2') goto yy13;
	yych = *++YYCURSOR;
	if(yych != 'c') goto yy13;
	++YYCURSOR;
#line 121 "scanner.re"
	{
					tok = pos = cursor;
					genGetState(out, topIndent, 0);
					ignore_eoc = true;
					goto echo;
				}
#line 247 "scanner.cc"
}
#line 150 "scanner.re"

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

#line 272 "scanner.cc"
{
	YYCTYPE yych;
	unsigned int yyaccept = 0;
	if((YYLIMIT - YYCURSOR) < 5) YYFILL(5);
	yych = *YYCURSOR;
	if(yych <= '/') {
		if(yych <= '!') {
			if(yych <= 0x0C) {
				if(yych <= 0x08) goto yy70;
				if(yych <= 0x09) goto yy64;
				if(yych <= 0x0A) goto yy66;
				goto yy70;
			} else {
				if(yych <= 0x0D) goto yy68;
				if(yych == ' ') goto yy64;
				goto yy70;
			}
		} else {
			if(yych <= ')') {
				if(yych <= '"') goto yy51;
				if(yych <= '&') goto yy70;
				if(yych <= '\'') goto yy53;
				goto yy57;
			} else {
				if(yych <= '+') {
					if(yych <= '*') goto yy49;
					goto yy58;
				} else {
					if(yych <= '-') goto yy70;
					if(yych <= '.') goto yy62;
					goto yy47;
				}
			}
		}
	} else {
		if(yych <= 'Z') {
			if(yych <= '=') {
				if(yych == ';') goto yy57;
				if(yych <= '<') goto yy70;
				goto yy57;
			} else {
				if(yych == '?') goto yy58;
				if(yych <= '@') goto yy70;
				goto yy61;
			}
		} else {
			if(yych <= 'q') {
				if(yych <= '[') goto yy55;
				if(yych <= '\\') goto yy57;
				if(yych <= '`') goto yy70;
				goto yy61;
			} else {
				if(yych <= 'z') {
					if(yych <= 'r') goto yy59;
					goto yy61;
				} else {
					if(yych <= '{') goto yy45;
					if(yych <= '|') goto yy57;
					goto yy70;
				}
			}
		}
	}
yy45:
	yyaccept = 0;
	yych = *(YYMARKER = ++YYCURSOR);
	if(yych <= '/') {
		if(yych == ',') goto yy111;
	} else {
		if(yych <= '0') goto yy108;
		if(yych <= '9') goto yy109;
	}
yy46:
#line 172 "scanner.re"
	{ depth = 1;
				  goto code;
				}
#line 350 "scanner.cc"
yy47:
	++YYCURSOR;
	if((yych = *YYCURSOR) == '*') goto yy106;
yy48:
#line 202 "scanner.re"
	{ RETURN(*tok); }
#line 357 "scanner.cc"
yy49:
	++YYCURSOR;
	if((yych = *YYCURSOR) == '/') goto yy104;
yy50:
#line 204 "scanner.re"
	{ yylval.op = *tok;
				  RETURN(CLOSE); }
#line 365 "scanner.cc"
yy51:
	yyaccept = 1;
	yych = *(YYMARKER = ++YYCURSOR);
	if(yych != 0x0A) goto yy100;
yy52:
#line 189 "scanner.re"
	{ fatal("unterminated string constant (missing \")"); }
#line 373 "scanner.cc"
yy53:
	yyaccept = 2;
	yych = *(YYMARKER = ++YYCURSOR);
	if(yych != 0x0A) goto yy95;
yy54:
#line 190 "scanner.re"
	{ fatal("unterminated string constant (missing ')"); }
#line 381 "scanner.cc"
yy55:
	yyaccept = 3;
	yych = *(YYMARKER = ++YYCURSOR);
	if(yych == 0x0A) goto yy56;
	if(yych == '^') goto yy86;
	goto yy85;
yy56:
#line 200 "scanner.re"
	{ fatal("unterminated range (missing ])"); }
#line 391 "scanner.cc"
yy57:
	yych = *++YYCURSOR;
	goto yy48;
yy58:
	yych = *++YYCURSOR;
	goto yy50;
yy59:
	++YYCURSOR;
	if((yych = *YYCURSOR) == 'e') goto yy76;
	goto yy75;
yy60:
#line 231 "scanner.re"
	{ cur = cursor;
				  yylval.symbol = Symbol::find(token());
				  return ID; }
#line 407 "scanner.cc"
yy61:
	yych = *++YYCURSOR;
	goto yy75;
yy62:
	++YYCURSOR;
#line 235 "scanner.re"
	{ cur = cursor;
				  yylval.regexp = mkDot();
				  return RANGE;
				}
#line 418 "scanner.cc"
yy64:
	++YYCURSOR;
	yych = *YYCURSOR;
	goto yy73;
yy65:
#line 240 "scanner.re"
	{ goto scan; }
#line 426 "scanner.cc"
yy66:
	++YYCURSOR;
yy67:
#line 242 "scanner.re"
	{ if(cursor == eof) RETURN(0);
				  pos = cursor; cline++;
				  goto scan;
	    			}
#line 435 "scanner.cc"
yy68:
	++YYCURSOR;
	if((yych = *YYCURSOR) == 0x0A) goto yy71;
yy69:
#line 247 "scanner.re"
	{ std::ostringstream msg;
				  msg << "unexpected character: ";
				  prtChOrHex(msg, *tok);
				  fatal(msg.str().c_str());
				  goto scan;
				}
#line 447 "scanner.cc"
yy70:
	yych = *++YYCURSOR;
	goto yy69;
yy71:
	yych = *++YYCURSOR;
	goto yy67;
yy72:
	++YYCURSOR;
	if(YYLIMIT == YYCURSOR) YYFILL(1);
	yych = *YYCURSOR;
yy73:
	if(yych == 0x09) goto yy72;
	if(yych == ' ') goto yy72;
	goto yy65;
yy74:
	++YYCURSOR;
	if(YYLIMIT == YYCURSOR) YYFILL(1);
	yych = *YYCURSOR;
yy75:
	if(yych <= '@') {
		if(yych <= '/') goto yy60;
		if(yych <= '9') goto yy74;
		goto yy60;
	} else {
		if(yych <= 'Z') goto yy74;
		if(yych <= '`') goto yy60;
		if(yych <= 'z') goto yy74;
		goto yy60;
	}
yy76:
	yych = *++YYCURSOR;
	if(yych != '2') goto yy75;
	yych = *++YYCURSOR;
	if(yych != 'c') goto yy75;
	yyaccept = 4;
	yych = *(YYMARKER = ++YYCURSOR);
	if(yych != ':') goto yy75;
yy79:
	++YYCURSOR;
	if(YYLIMIT == YYCURSOR) YYFILL(1);
	yych = *YYCURSOR;
	if(yych <= '@') goto yy80;
	if(yych <= 'Z') goto yy81;
	if(yych <= '`') goto yy80;
	if(yych <= 'z') goto yy81;
yy80:
	YYCURSOR = YYMARKER;
	switch(yyaccept) {
	case 0:	goto yy46;
	case 1:	goto yy52;
	case 2:	goto yy54;
	case 3:	goto yy56;
	case 6:	goto yy112;
	case 5:	goto yy83;
	case 4:	goto yy60;
	}
yy81:
	yyaccept = 5;
	YYMARKER = ++YYCURSOR;
	if(YYLIMIT == YYCURSOR) YYFILL(1);
	yych = *YYCURSOR;
	if(yych <= 'Z') {
		if(yych <= '9') {
			if(yych >= '0') goto yy81;
		} else {
			if(yych <= ':') goto yy79;
			if(yych >= 'A') goto yy81;
		}
	} else {
		if(yych <= '_') {
			if(yych >= '_') goto yy81;
		} else {
			if(yych <= '`') goto yy83;
			if(yych <= 'z') goto yy81;
		}
	}
yy83:
#line 224 "scanner.re"
	{ cur = cursor;
				  tok+= 5; /* skip "re2c:" */
				  iscfg = 1;
				  yylval.str = new Str(token());
				  return CONFIG;
				}
#line 532 "scanner.cc"
yy84:
	++YYCURSOR;
	if(YYLIMIT == YYCURSOR) YYFILL(1);
	yych = *YYCURSOR;
yy85:
	if(yych <= '[') {
		if(yych == 0x0A) goto yy80;
		goto yy84;
	} else {
		if(yych <= '\\') goto yy88;
		if(yych <= ']') goto yy89;
		goto yy84;
	}
yy86:
	++YYCURSOR;
	if(YYLIMIT == YYCURSOR) YYFILL(1);
	yych = *YYCURSOR;
	if(yych <= '[') {
		if(yych == 0x0A) goto yy80;
		goto yy86;
	} else {
		if(yych <= '\\') goto yy91;
		if(yych <= ']') goto yy92;
		goto yy86;
	}
yy88:
	++YYCURSOR;
	if(YYLIMIT == YYCURSOR) YYFILL(1);
	yych = *YYCURSOR;
	if(yych == 0x0A) goto yy80;
	goto yy84;
yy89:
	++YYCURSOR;
#line 196 "scanner.re"
	{ cur = cursor;
				  yylval.regexp = ranToRE(token());
				  return RANGE; }
#line 570 "scanner.cc"
yy91:
	++YYCURSOR;
	if(YYLIMIT == YYCURSOR) YYFILL(1);
	yych = *YYCURSOR;
	if(yych == 0x0A) goto yy80;
	goto yy86;
yy92:
	++YYCURSOR;
#line 192 "scanner.re"
	{ cur = cursor;
				  yylval.regexp = invToRE(token());
				  return RANGE; }
#line 583 "scanner.cc"
yy94:
	++YYCURSOR;
	if(YYLIMIT == YYCURSOR) YYFILL(1);
	yych = *YYCURSOR;
yy95:
	if(yych <= '&') {
		if(yych == 0x0A) goto yy80;
		goto yy94;
	} else {
		if(yych <= '\'') goto yy97;
		if(yych != '\\') goto yy94;
	}
	++YYCURSOR;
	if(YYLIMIT == YYCURSOR) YYFILL(1);
	yych = *YYCURSOR;
	if(yych == 0x0A) goto yy80;
	goto yy94;
yy97:
	++YYCURSOR;
#line 185 "scanner.re"
	{ cur = cursor;
				  yylval.regexp = strToCaseInsensitiveRE(token());
				  return STRING; }
#line 607 "scanner.cc"
yy99:
	++YYCURSOR;
	if(YYLIMIT == YYCURSOR) YYFILL(1);
	yych = *YYCURSOR;
yy100:
	if(yych <= '!') {
		if(yych == 0x0A) goto yy80;
		goto yy99;
	} else {
		if(yych <= '"') goto yy102;
		if(yych != '\\') goto yy99;
	}
	++YYCURSOR;
	if(YYLIMIT == YYCURSOR) YYFILL(1);
	yych = *YYCURSOR;
	if(yych == 0x0A) goto yy80;
	goto yy99;
yy102:
	++YYCURSOR;
#line 181 "scanner.re"
	{ cur = cursor;
				  yylval.regexp = strToRE(token());
				  return STRING; }
#line 631 "scanner.cc"
yy104:
	++YYCURSOR;
#line 178 "scanner.re"
	{ tok = cursor;
				  RETURN(0); }
#line 637 "scanner.cc"
yy106:
	++YYCURSOR;
#line 175 "scanner.re"
	{ depth = 1;
				  goto comment; }
#line 643 "scanner.cc"
yy108:
	yych = *++YYCURSOR;
	if(yych == ',') goto yy122;
	goto yy110;
yy109:
	++YYCURSOR;
	if((YYLIMIT - YYCURSOR) < 2) YYFILL(2);
	yych = *YYCURSOR;
yy110:
	if(yych <= '/') {
		if(yych == ',') goto yy115;
		goto yy80;
	} else {
		if(yych <= '9') goto yy109;
		if(yych == '}') goto yy113;
		goto yy80;
	}
yy111:
	++YYCURSOR;
yy112:
#line 222 "scanner.re"
	{ fatal("illegal closure form, use '{n}', '{n,}', '{n,m}' where n and m are numbers"); }
#line 666 "scanner.cc"
yy113:
	++YYCURSOR;
#line 210 "scanner.re"
	{ yylval.extop.minsize = atoi((char *)tok+1);
				  yylval.extop.maxsize = atoi((char *)tok+1);
				  RETURN(CLOSESIZE); }
#line 673 "scanner.cc"
yy115:
	yyaccept = 6;
	yych = *(YYMARKER = ++YYCURSOR);
	if(yych <= '/') goto yy112;
	if(yych <= '9') goto yy118;
	if(yych != '}') goto yy112;
	++YYCURSOR;
#line 218 "scanner.re"
	{ yylval.extop.minsize = atoi((char *)tok+1);
				  yylval.extop.maxsize = -1;
				  RETURN(CLOSESIZE); }
#line 685 "scanner.cc"
yy118:
	++YYCURSOR;
	if(YYLIMIT == YYCURSOR) YYFILL(1);
	yych = *YYCURSOR;
	if(yych <= '/') goto yy80;
	if(yych <= '9') goto yy118;
	if(yych != '}') goto yy80;
	++YYCURSOR;
#line 214 "scanner.re"
	{ yylval.extop.minsize = atoi((char *)tok+1);
				  yylval.extop.maxsize = MAX(yylval.extop.minsize,atoi(strchr((char *)tok, ',')+1));
				  RETURN(CLOSESIZE); }
#line 698 "scanner.cc"
yy122:
	yyaccept = 6;
	yych = *(YYMARKER = ++YYCURSOR);
	if(yych <= '/') goto yy112;
	if(yych <= '9') goto yy118;
	if(yych != '}') goto yy112;
	++YYCURSOR;
#line 207 "scanner.re"
	{ yylval.op = '*';
				  RETURN(CLOSE); }
#line 709 "scanner.cc"
}
#line 253 "scanner.re"


code:

#line 716 "scanner.cc"
{
	YYCTYPE yych;
	if((YYLIMIT - YYCURSOR) < 2) YYFILL(2);
	yych = *YYCURSOR;
	if(yych <= '&') {
		if(yych <= 0x0A) {
			if(yych <= 0x09) goto yy133;
			goto yy131;
		} else {
			if(yych == '"') goto yy135;
			goto yy133;
		}
	} else {
		if(yych <= '{') {
			if(yych <= '\'') goto yy136;
			if(yych <= 'z') goto yy133;
			goto yy129;
		} else {
			if(yych != '}') goto yy133;
		}
	}
	++YYCURSOR;
#line 257 "scanner.re"
	{ if(--depth == 0){
					cur = cursor;
					yylval.token = new Token(token(), tline);
					return CODE;
				  }
				  goto code; }
#line 746 "scanner.cc"
yy129:
	++YYCURSOR;
#line 263 "scanner.re"
	{ ++depth;
				  goto code; }
#line 752 "scanner.cc"
yy131:
	++YYCURSOR;
#line 265 "scanner.re"
	{ if(cursor == eof) fatal("missing '}'");
				  pos = cursor; cline++;
				  goto code;
				}
#line 760 "scanner.cc"
yy133:
	++YYCURSOR;
yy134:
#line 269 "scanner.re"
	{ goto code; }
#line 766 "scanner.cc"
yy135:
	yych = *(YYMARKER = ++YYCURSOR);
	if(yych == 0x0A) goto yy134;
	goto yy142;
yy136:
	yych = *(YYMARKER = ++YYCURSOR);
	if(yych == 0x0A) goto yy134;
	goto yy138;
yy137:
	++YYCURSOR;
	if(YYLIMIT == YYCURSOR) YYFILL(1);
	yych = *YYCURSOR;
yy138:
	if(yych <= '&') {
		if(yych != 0x0A) goto yy137;
	} else {
		if(yych <= '\'') goto yy133;
		if(yych == '\\') goto yy140;
		goto yy137;
	}
yy139:
	YYCURSOR = YYMARKER;
	goto yy134;
yy140:
	++YYCURSOR;
	if(YYLIMIT == YYCURSOR) YYFILL(1);
	yych = *YYCURSOR;
	if(yych == 0x0A) goto yy139;
	goto yy137;
yy141:
	++YYCURSOR;
	if(YYLIMIT == YYCURSOR) YYFILL(1);
	yych = *YYCURSOR;
yy142:
	if(yych <= '!') {
		if(yych == 0x0A) goto yy139;
		goto yy141;
	} else {
		if(yych <= '"') goto yy133;
		if(yych != '\\') goto yy141;
	}
	++YYCURSOR;
	if(YYLIMIT == YYCURSOR) YYFILL(1);
	yych = *YYCURSOR;
	if(yych == 0x0A) goto yy139;
	goto yy141;
}
#line 270 "scanner.re"


comment:

#line 819 "scanner.cc"
{
	YYCTYPE yych;
	if((YYLIMIT - YYCURSOR) < 2) YYFILL(2);
	yych = *YYCURSOR;
	if(yych <= ')') {
		if(yych == 0x0A) goto yy149;
		goto yy151;
	} else {
		if(yych <= '*') goto yy146;
		if(yych == '/') goto yy148;
		goto yy151;
	}
yy146:
	++YYCURSOR;
	if((yych = *YYCURSOR) == '/') goto yy154;
yy147:
#line 285 "scanner.re"
	{ if(cursor == eof) RETURN(0);
				  goto comment; }
#line 839 "scanner.cc"
yy148:
	yych = *++YYCURSOR;
	if(yych == '*') goto yy152;
	goto yy147;
yy149:
	++YYCURSOR;
#line 281 "scanner.re"
	{ if(cursor == eof) RETURN(0);
				  tok = pos = cursor; cline++;
				  goto comment;
				}
#line 851 "scanner.cc"
yy151:
	yych = *++YYCURSOR;
	goto yy147;
yy152:
	++YYCURSOR;
#line 278 "scanner.re"
	{ ++depth;
				  fatal("ambiguous /* found");
				  goto comment; }
#line 861 "scanner.cc"
yy154:
	++YYCURSOR;
#line 274 "scanner.re"
	{ if(--depth == 0)
					goto scan;
				    else
					goto comment; }
#line 869 "scanner.cc"
}
#line 287 "scanner.re"


config:

#line 876 "scanner.cc"
{
	YYCTYPE yych;
	if((YYLIMIT - YYCURSOR) < 2) YYFILL(2);
	yych = *YYCURSOR;
	if(yych <= 0x1F) {
		if(yych != 0x09) goto yy162;
	} else {
		if(yych <= ' ') goto yy158;
		if(yych == '=') goto yy160;
		goto yy162;
	}
yy158:
	++YYCURSOR;
	yych = *YYCURSOR;
	goto yy167;
yy159:
#line 291 "scanner.re"
	{ goto config; }
#line 895 "scanner.cc"
yy160:
	++YYCURSOR;
	yych = *YYCURSOR;
	goto yy165;
yy161:
#line 292 "scanner.re"
	{ iscfg = 2;
				  cur = cursor;
				  RETURN('='); 
				}
#line 906 "scanner.cc"
yy162:
	++YYCURSOR;
#line 296 "scanner.re"
	{ fatal("missing '='"); }
#line 911 "scanner.cc"
yy164:
	++YYCURSOR;
	if(YYLIMIT == YYCURSOR) YYFILL(1);
	yych = *YYCURSOR;
yy165:
	if(yych == 0x09) goto yy164;
	if(yych == ' ') goto yy164;
	goto yy161;
yy166:
	++YYCURSOR;
	if(YYLIMIT == YYCURSOR) YYFILL(1);
	yych = *YYCURSOR;
yy167:
	if(yych == 0x09) goto yy166;
	if(yych == ' ') goto yy166;
	goto yy159;
}
#line 297 "scanner.re"


value:

#line 934 "scanner.cc"
{
	YYCTYPE yych;
	if((YYLIMIT - YYCURSOR) < 2) YYFILL(2);
	yych = *YYCURSOR;
	if(yych <= '&') {
		if(yych <= 0x0D) {
			if(yych <= 0x08) goto yy176;
			if(yych <= 0x0A) goto yy170;
			if(yych <= 0x0C) goto yy176;
		} else {
			if(yych <= ' ') {
				if(yych <= 0x1F) goto yy176;
			} else {
				if(yych == '"') goto yy178;
				goto yy176;
			}
		}
	} else {
		if(yych <= '/') {
			if(yych <= '\'') goto yy180;
			if(yych == '-') goto yy173;
			goto yy176;
		} else {
			if(yych <= '9') {
				if(yych <= '0') goto yy171;
				goto yy174;
			} else {
				if(yych != ';') goto yy176;
			}
		}
	}
yy170:
#line 306 "scanner.re"
	{ cur = cursor;
				  yylval.str = new Str(token());
				  iscfg = 0;
				  return VALUE;
				}
#line 973 "scanner.cc"
yy171:
	++YYCURSOR;
	if((yych = *YYCURSOR) <= 0x0D) {
		if(yych <= 0x08) goto yy176;
		if(yych <= 0x0A) goto yy172;
		if(yych <= 0x0C) goto yy176;
	} else {
		if(yych <= ' ') {
			if(yych <= 0x1F) goto yy176;
		} else {
			if(yych != ';') goto yy176;
		}
	}
yy172:
#line 301 "scanner.re"
	{ cur = cursor;
				  yylval.number = atoi(token().to_string().c_str());
				  iscfg = 0;
				  return NUMBER;
				}
#line 994 "scanner.cc"
yy173:
	yych = *++YYCURSOR;
	if(yych <= '0') goto yy177;
	if(yych >= ':') goto yy177;
yy174:
	++YYCURSOR;
	if(YYLIMIT == YYCURSOR) YYFILL(1);
	yych = *YYCURSOR;
	if(yych <= 0x1F) {
		if(yych <= 0x0A) {
			if(yych >= 0x09) goto yy172;
		} else {
			if(yych == 0x0D) goto yy172;
		}
	} else {
		if(yych <= '9') {
			if(yych <= ' ') goto yy172;
			if(yych >= '0') goto yy174;
		} else {
			if(yych == ';') goto yy172;
		}
	}
yy176:
	++YYCURSOR;
	if(YYLIMIT == YYCURSOR) YYFILL(1);
	yych = *YYCURSOR;
yy177:
	if(yych <= 0x0D) {
		if(yych <= 0x08) goto yy176;
		if(yych <= 0x0A) goto yy170;
		if(yych <= 0x0C) goto yy176;
		goto yy170;
	} else {
		if(yych <= ' ') {
			if(yych <= 0x1F) goto yy176;
			goto yy170;
		} else {
			if(yych == ';') goto yy170;
			goto yy176;
		}
	}
yy178:
	YYMARKER = ++YYCURSOR;
	if(YYLIMIT == YYCURSOR) YYFILL(1);
	yych = *YYCURSOR;
	if(yych <= ' ') {
		if(yych <= 0x0A) {
			if(yych <= 0x08) goto yy178;
			if(yych <= 0x09) goto yy188;
			goto yy170;
		} else {
			if(yych == 0x0D) goto yy188;
			if(yych <= 0x1F) goto yy178;
			goto yy188;
		}
	} else {
		if(yych <= ':') {
			if(yych == '"') goto yy176;
			goto yy178;
		} else {
			if(yych <= ';') goto yy188;
			if(yych == '\\') goto yy190;
			goto yy178;
		}
	}
yy180:
	YYMARKER = ++YYCURSOR;
	if(YYLIMIT == YYCURSOR) YYFILL(1);
	yych = *YYCURSOR;
	if(yych <= ' ') {
		if(yych <= 0x0A) {
			if(yych <= 0x08) goto yy180;
			if(yych >= 0x0A) goto yy170;
		} else {
			if(yych == 0x0D) goto yy182;
			if(yych <= 0x1F) goto yy180;
		}
	} else {
		if(yych <= ':') {
			if(yych == '\'') goto yy176;
			goto yy180;
		} else {
			if(yych <= ';') goto yy182;
			if(yych == '\\') goto yy185;
			goto yy180;
		}
	}
yy182:
	++YYCURSOR;
	if(YYLIMIT == YYCURSOR) YYFILL(1);
	yych = *YYCURSOR;
	if(yych <= '&') {
		if(yych != 0x0A) goto yy182;
	} else {
		if(yych <= '\'') goto yy186;
		if(yych == '\\') goto yy187;
		goto yy182;
	}
yy184:
	YYCURSOR = YYMARKER;
	goto yy170;
yy185:
	YYMARKER = ++YYCURSOR;
	if(YYLIMIT == YYCURSOR) YYFILL(1);
	yych = *YYCURSOR;
	if(yych <= 0x0D) {
		if(yych <= 0x09) {
			if(yych <= 0x08) goto yy180;
			goto yy182;
		} else {
			if(yych <= 0x0A) goto yy170;
			if(yych <= 0x0C) goto yy180;
			goto yy182;
		}
	} else {
		if(yych <= ' ') {
			if(yych <= 0x1F) goto yy180;
			goto yy182;
		} else {
			if(yych == ';') goto yy182;
			goto yy180;
		}
	}
yy186:
	yych = *++YYCURSOR;
	goto yy170;
yy187:
	++YYCURSOR;
	if(YYLIMIT == YYCURSOR) YYFILL(1);
	yych = *YYCURSOR;
	if(yych == 0x0A) goto yy184;
	goto yy182;
yy188:
	++YYCURSOR;
	if(YYLIMIT == YYCURSOR) YYFILL(1);
	yych = *YYCURSOR;
	if(yych <= '!') {
		if(yych == 0x0A) goto yy184;
		goto yy188;
	} else {
		if(yych <= '"') goto yy186;
		if(yych == '\\') goto yy191;
		goto yy188;
	}
yy190:
	YYMARKER = ++YYCURSOR;
	if(YYLIMIT == YYCURSOR) YYFILL(1);
	yych = *YYCURSOR;
	if(yych <= 0x0D) {
		if(yych <= 0x09) {
			if(yych <= 0x08) goto yy178;
			goto yy188;
		} else {
			if(yych <= 0x0A) goto yy170;
			if(yych <= 0x0C) goto yy178;
			goto yy188;
		}
	} else {
		if(yych <= ' ') {
			if(yych <= 0x1F) goto yy178;
			goto yy188;
		} else {
			if(yych == ';') goto yy188;
			goto yy178;
		}
	}
yy191:
	++YYCURSOR;
	if(YYLIMIT == YYCURSOR) YYFILL(1);
	yych = *YYCURSOR;
	if(yych == 0x0A) goto yy184;
	goto yy188;
}
#line 311 "scanner.re"

}

void Scanner::fatal(uint ofs, const char *msg) const
{
	out.flush();
	std::cerr << "re2c: error: "
		<< "line " << tline << ", column " << (tchar + ofs + 1) << ": "
		<< msg << std::endl;
   	exit(1);
}

} // end namespace re2c

