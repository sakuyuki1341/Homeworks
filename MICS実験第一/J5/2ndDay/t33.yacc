%token NUM;
%%
explist : 
		| explist expr '\n' { printf("%d\n", value); }
		;
expr	: NUM			{ value = atoi(yytext); }
		| expr '+' NUM	{ value = value + atoi(yytext); }
		| expr '-' NUM { value = value - atoi(yytext); }
		| expr '*' NUM { value = value * atoi(yytext); }
		| expr '/' NUM { value = value / atoi(yytext); }
		;
