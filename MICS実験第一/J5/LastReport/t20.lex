/* t20.lex -- lexical definitions for a simple language */
alpha [a-zA-Z]
digit [0-9]
white [\n\t ]
%%
while						{ return WHILE; }
if							{ return IF; }
read						{ return READ; }
print						{ return PRINT; }
printx						{ return PRINTX; }
{alpha}({alpha}|{digit})*	{ return IDENT; }
{digit}+					{ return NUM; }
[-+()=;{}<>*/%]				{ return yytext[0]; }
{white}						{ ; }
