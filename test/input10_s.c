/* Generated by re2c */
#line 1 "input10_s.re"
// re2c $INPUT -o $OUTPUT -s

#line 6 "input10_s.c"
{
	YYCTYPE yych;
	if (YYLIMIT <= YYCURSOR) YYFILL(1);
	yych = *YYCURSOR;
	if (yych <= 'E') {
		if (yych <= '@') goto yy2;
		if (yych <= 'D') goto yy4;
	} else {
		if (yych <= 'G') goto yy4;
		if (yych <= '`') goto yy2;
		if (yych <= 'g') goto yy4;
	}
yy2:
	++YYCURSOR;
#line 11 "input10_s.re"
	{ return -1; }
#line 23 "input10_s.c"
yy4:
	++YYCURSOR;
#line 9 "input10_s.re"
	{ return 1; }
#line 28 "input10_s.c"
}
#line 13 "input10_s.re"
