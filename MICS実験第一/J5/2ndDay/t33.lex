digit	[0-9]
white	[\t ]
%%
{digit}+	{ return NUM; }
{digit}-	{ return NUM; }
"+"			{ return '+'; }
"-"			{ return '-'; }
"\n"		{ return '\n'; }
{white}		{ ; }