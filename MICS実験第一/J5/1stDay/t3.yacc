%token NUM;
%%
expr	: NUM
		| expr '+' NUM
		;
