digit	[0-9]
white	[\t ]
%%
{digit}+	{ return NUM; }
"+"			{ return '+'; }
"-"			{ return '-'; }
"*"			{ return '*'; }
"/"			{ return '/'; }
"\n"		{ return '\n'; }
{white}		{ ; }
