/* Generated by re2c */
// overlapping trailing contexts of variable length:
// we need multiple tags and we cannot deduplicate them


{
	YYCTYPE yych;
	if (YYLESSTHAN (4)) YYFILL(4);
	yych = YYPEEK ();
	YYSKIP ();
	switch (yych) {
	case 'a':	goto yy4;
	default:	goto yy2;
	}
yy2:
	{ d }
yy4:
	yych = YYPEEK ();
	YYBACKUPTAG (yyt1);
	switch (yych) {
	case 'b':
		YYSKIP ();
		goto yy6;
	default:	goto yy5;
	}
yy5:
	YYRESTORETAG (yyt1);
	{ 1 }
yy6:
	YYBACKUP ();
	yych = YYPEEK ();
	switch (yych) {
	case 'c':
		YYBACKUPTAG (yyt2);
		YYSKIP ();
		goto yy9;
	default:	goto yy8;
	}
yy7:
	if (YYLESSTHAN (1)) YYFILL(1);
	yych = YYPEEK ();
yy8:
	switch (yych) {
	case 'b':
		YYSKIP ();
		goto yy7;
	default:	goto yy5;
	}
yy9:
	yych = YYPEEK ();
	switch (yych) {
	case 'c':
		YYSKIP ();
		goto yy11;
	default:	goto yy10;
	}
yy10:
	YYRESTORE ();
	goto yy5;
yy11:
	if (YYLESSTHAN (1)) YYFILL(1);
	yych = YYPEEK ();
	switch (yych) {
	case 'c':
		YYSKIP ();
		goto yy11;
	default:	goto yy13;
	}
yy13:
	YYRESTORETAG (yyt2);
	{ 0 }
}

