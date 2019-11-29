%{
#include <math.h>
#include <stdio.h>
#include "dataStruct.c"


int yyerror (char const *s);
extern int yylex (void);

%}

%union{
  char *str;
  double num;
  int integer;
  struct NODE *node;
}

%token<num> NUMBER
%token LEFT RIGHT
%token PLUS MINUS TIMES DIVIDE POWER
%token END
%token <node> PRINT
%token<str> TAG
%token EQUAL
%token<num> REAL
%token<integer> INTEGER

%type<node> Expression
%type<node> Line
%type<node> Program

%left PLUS MINUS
%left TIMES DIVIDE
%left NEG
%right POWER

%define parse.error verbose

%start Program
%%

Program: List_Exp {root = $1;}

List_Exp: Exp {$$ = insertNodeList($1, NULL)}
List_Exp: List_Exp Exp {$$ = insertNodeList($1, $2);}

Exp: INTEGER { $$ = create_TP_unit_Integer($1, 0, 0); };
Exp: REAL { $$ = create_TP_unit_Real($1, 0, 0); };
Exp: Exp PLUS Exp {$$ = create_TPBIN($1, $3, 0, 0)}



Program: Program Line {insertNextNode($2);}

Line: END {$$ = NULL;}
Line: Expression END {$$ = $1;};
Line: PRINT END {printTree();};
/*Line: PRINT Expression {$$ = create_TP_Print($2);};*/
/*Line: TAG EQUAL Expression {printf("o valor de %s: %f\n", $1, $3);}*/



Expression: REAL PLUS REAL { $$ = create_OP_BIN_F($1, $3, "PLUS");};
/*Expression: INTEGER PLUS INTEGER { $$ = create_OP_BIN_F($1, $3, "PLUS"); }; */
Expression: Expression PLUS Expression { $$ = create_EX_BIN_E($1, $3, "PLUS"); };

Expression: REAL MINUS REAL { $$ = create_OP_BIN_F($1, $3, "MINUS"); };
Expression: INTEGER MINUS INTEGER { $$ = create_OP_BIN_F($1, $3, "MINUS");};
Expression: Expression TIMES Expression { $$ = $1; };

Expression: Expression DIVIDE Expression { $$ = $1; };

Expression: MINUS Expression %prec NEG { $$ = $2; };

Expression: Expression POWER Expression { $$ = $1; };

Expression: LEFT Expression RIGHT { $$ = $2; };

%%

int yyerror(char const *s) {
  printf("%s\n", s);
}

int main() {
    int ret = yyparse();
    
    if (ret){
	    fprintf(stderr, "%d error found.\n",ret);
    }


    return 0;
}

