%{


#include <iostream>
#include <string>
#include <stdlib.h>
#include <stdio.h>
#include <map>
#include <list>
#include "myC.h"



using namespace std;

 extern FILE *yyin;

// the root of the abstract syntax tree
 stmt_node *root;

// for keeping track of line numbers in the program we are parsing
  int line_num = 1;

// function prototypes, we need the yylex return prototype so C++ won't complain
int yylex();
void yyerror(const char* s);

%}

%start program

%union {
  float number;
  char * var_name;
  exp_node *exp_node_ptr;
  stmt_node *stmt_node_ptr;
}

%error-verbose

%token <number> NUMBER
%token <var_name> ID

%token <bool_val> bool_val
%token <float_val> float_val
%token <int_val> int_val
%token <string_val> string_val  
%token <char_val> char_val



%token SEMICOLON  EQUALS PRINT  PLUS MINUS TIMES DIVIDE  LPAREN RPAREN LBRACE RBRACE LBRACKET RBRACKET EQUAL NOTEQUAL NOT LESS GREATER LESSEQUAL GREATEREQUAL EXPO COMMA ADD AND OR IF THEN ELSE WHILE 

//%type <exp_node_ptr> exp
//%type <exp_node_ptr> mulexp
//%type <exp_node_ptr> primexp 
//%type <stmt_node_ptr> stmtlist
%type <stmt_node_ptr> stmt
%type <stmt_node_ptr> program

%type <variable_node_ptr> var_dec
%type <array_dec_node_ptr> array_dec
%type <typename_node_ptr> typename
%type <dimension_node_ptr> dimension
%type <or_node_ptr> boolexpr
%type <and_node_ptr> andexpr
%type <equal_node_ptr> equalexpr
%type <less_node_ptr> compareexpr
%type <negation_node_ptr> negateexpr
%type <exp_node_ptr> endexpr          //??todo
%type <add_node_ptr> arithexpr
%type <multiply_node_ptr> mul_div_expr
%type <expo_node_ptr> expoexpr
%type <neg_node_ptr> negativeexpr
%type <concatenate_node_ptr> strexpr
%type <variable_node_ptr> rootstr  
%type <if_else_node_ptr> if_stmt
%type <if_node_ptr> matched_stmt
%type <if_node_ptr> matched_if
%type <loop_node_ptr> loop
%type <assign_node_ptr> assignexpr
%type <assign_node_ptr> assignroot  
%type <neg_node_ptr> rootexpr



%%

program : stmt { root = $$; }
;
/*
stmt : func_dec { $$ = $1;   }
         |  func_call { $$ = $1;   }
         |  loop { $$ = $1;   }
	 |  if_stmt { $$ = $1;   }
	 |  var_dec { $$ = $1;   }
	 |	array_dec { $$ = $1; }    //todo no array_dec_node
	 |  assignexpr { $$ = $1;   }
	 |  boolexpr { $$ = $1;   }
;
*/
stmt : loop { $$ = $1;   }
	 |  if_stmt { $$ = $1;   }
	 |  var_dec { $$ = $1;   }
	 |	array_dec { $$ = $1; }
	 |  assignexpr { $$ = $1;   }
	 |  boolexpr { $$ = $1;   }
;

//Simplified declarations
var_dec : typename ID { $$ = new var_dec_node($1, $2);} //var_dec_node is overloaded
		| typename ID EQUALS boolexpr { $$ = new var_dec_assign_node($1, $2, $4); }
;

array_dec : typename ID LBRACKET dimension RBRACKET { $$ = new array_dec_node($1, $2, $4); } //array_dec_node is overloaded
		| typename ID LBRACKET RBRACKET { $$ = new array_dec_node($1, $2); }

typename : ID { $$ = new string_node( $1 ); }	//Defines the type name as a string
; 

dimension : NUMBER { $$ = new int_node( $1 ); } //Defines the dimensions as an int
;
 
boolexpr : boolexpr OR andexpr  { $$ = new or_node($1, $3); }
         | andexpr { $$ = $1;  }
;

andexpr : andexpr AND equalexpr { $$ = new and_node($1, $3); }
         | equalexpr { $$ = $1;  }
;

equalexpr : equalexpr EQUAL compareexpr { $$ = new equal_node($1, $3); }
         | equalexpr NOTEQUAL compareexpr { $$ = new notequal_node($1, $3); }
	 | compareexpr { $$ = $1;  }
;

compareexpr : compareexpr LESS negateexpr { $$ = new less_node($1, $3); }
         | compareexpr GREATER negateexpr { $$ = new greater_node($1, $3); }
	 | compareexpr LESSEQUAL negateexpr { $$ = new lessequal_node($1, $3); }
         | compareexpr GREATEREQUAL negateexpr { $$ = new greaterequal_node($1, $3); }
	 | negateexpr { $$ = $1;  }
;

negateexpr : NOT endexpr { $$ = new negation_node($2); }   
         | endexpr { $$ = $1;  }
;

endexpr : arithexpr { $$ = $1;   }
         |  strexpr { $$ = $1;   }   //todo no string_node
;


arithexpr : arithexpr PLUS mul_div_expr  { $$ = new add_node($1, $3); }
         | arithexpr MINUS mul_div_expr  { $$ = new subtract_node($1, $3); }
	 | mul_div_expr { $$ = $1;   }
;

mul_div_expr : mul_div_expr TIMES expoexpr  { $$ = new multiply_node($1, $3); }
         | mul_div_expr DIVIDE expoexpr  { $$ = new divide_node($1, $3); }
	 | expoexpr { $$ = $1;   }
;

expoexpr : expoexpr EXPO negativeexpr  { $$ = new expo_node($1, $3); }        
	 | negativeexpr { $$ = $1;   }
;

negativeexpr : MINUS rootexpr { $$ = new neg_node( $2 ); }
		| rootexpr { $$ = $1 } 

strexpr : strexpr ADD rootstr  { $$ = new concatenate_node($1, $3); }        
	 | rootstr { $$ = $1; }
;

rootstr : string_val { $$ = new string_node($1) ; }  //Added rootstr so that concatenation only occurs on strings
;

rootexpr: LPAREN boolexpr RPAREN { $$ = $2 }
		| ID { $$ = new variable_node($1); }
		| float_val { $$ = new float_node($1); }
		| char_val { $$ = new char_node($1); }
		| int_val { $$ = new int_node($1); }
		| bool_val { $$ = new bool_node($1); }
		| string_val { $$ = new string_node($1); }


if_stmt : IF LPAREN boolexpr RPAREN THEN LBRACE matched_stmt RBRACE ELSE LBRACE matched_stmt RBRACE    {$$ = new if_else_node($3,$7,$11); }
		|IF LPAREN boolexpr RPAREN THEN LBRACE stmt RBRACE {$$ = new if_node($3,$7); }
;

matched_stmt : stmt { $$ = $1;   }
        |  matched_if { $$ = $1;  }
;

matched_if : IF LPAREN boolexpr RPAREN THEN LBRACE matched_stmt RBRACE ELSE LBRACE matched_stmt RBRACE {
              $$ = new if_else_node($3,$7,$11);   }
;

loop : WHILE LPAREN boolexpr RPAREN LBRACE stmt RBRACE {
             $$ = new loop_node($3,$6);   }
;
/*
//------------------------------------NEED TO DEFINE IN .cpp
func_dec : typename ID  LPAREN func_params RPAREN LBRACE stmt RBRACE {
                $$ = new func_dec_node($1,$2,$4,$7);   }     //todo: func_dec_node doesn't be difined in myC.cpp
;

func_params : typename ID { $$ = new func_params($1, $2); }
        | typename ID COMMA func_params {  $$ = new func_params($1, $2, $4); } //Need to fix
		|   {}
;

func_call: ID EQUALS ID LPAREN func_param_list RPAREN { $$ = new func_call_node($3,$5);  }    //todo: func_call_node doesn't be difined in myC.cpp
		| ID LPAREN func_param_list RPAREN { $$ = new func_call_node($1,$3);  }  
;

func_param_list: boolexpr{ $$ = $1; }
		| boolexpr COMMA func_param_list { $$ = new func_param_list ($1, $3); } //How to create list and pass new parameters to itself?
		| {}
		
//----------------------------------------------
*/

assignexpr : ID EQUALS assignroot {$$ = new assign_node($1, $3); }
		| ID LBRACKET dimension RBRACKET EQUALS assignroot { $$ = new assign_node( $1, $6); }
;

assignroot : boolexpr {$$=$1; } 
         | ID EQUALS assignroot {$$ = new assign_node($1, $3); }
;

 
%%
int main(int argc, char **argv)
{ 
  if (argc>1) yyin=fopen(argv[1],"r");

  //  yydebug = 1;
  yyparse();

  cout << "---------- list of input program------------" << endl << endl;

  root -> print();

  cout << "---------- exeuction of input program------------" << endl << endl;
  

  root->evaluate();
}

void yyerror(const char * s)
{
  fprintf(stderr, "line %d: %s\n", line_num, s);
}

