/* Generated by re2c */

{
	YYCTYPE yych;
	if ((YYLIMIT - YYCURSOR) < 4) YYFILL(4);
	yych = *(YYMARKER = YYCURSOR);
	switch (yych) {
	case 'a':
		yyt5 = NULL;
		yyt1 = YYCURSOR;
		goto yy3;
	default:	goto yy2;
	}
yy2:
	{}
yy3:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'a':
		yyt2 = YYCURSOR;
		goto yy5;
	default:	goto yy4;
	}
yy4:
	YYCURSOR = YYMARKER;
	goto yy2;
yy5:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'a':
		yyt3 = YYCURSOR;
		goto yy6;
	default:	goto yy4;
	}
yy6:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'a':
		yyt4 = YYCURSOR;
		goto yy7;
	default:	goto yy4;
	}
yy7:
	++YYCURSOR;
	if (YYLIMIT <= YYCURSOR) YYFILL(1);
	yych = *YYCURSOR;
	switch (yych) {
	case 'a':
		yyt5 = yyt1;
		yyt1 = yyt2;
		yyt2 = yyt3;
		yyt3 = yyt4;
		yyt4 = YYCURSOR;
		goto yy7;
	default:	goto yy9;
	}
yy9:
	p = yyt5;
	{}
}

re2c: warning: line 4: rule matches empty string [-Wmatch-empty-string]
re2c: warning: line 3: tag 'p' is non-deterministic and induces 5 parallel instances [-Wnondeterministic-tags]
