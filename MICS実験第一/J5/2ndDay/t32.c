#include <stdio.h>

int value;
extern char *yytext;

#include "y.tab.c"
#include "lex.yy.c"

int main() {
	yyparse();
	printf("%d\n", value);
	return 0;
}