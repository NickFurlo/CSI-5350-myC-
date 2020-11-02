%option interactive
%{
/* * * * * * * * * * * *
 * * * DEFINITIONS * * *
 * * * * * * * * * * * */
%}

%{

// y.tab.h contains the token number values produced by the parser

#include <iostream>
#include <stdlib.h>
#include <string>
#include <map>
#include <list>

#include "myC2.h"
#include "y.tab.h"

extern int line_num;

%}


%option noyywrap
DIGIT [0-9]
LETTER [a-zA-Z]

%{ 
  /* * * * * * * * * *
   * * * STATES  * * *
   * * * * * * * * * */
%}

%x ERROR

%%

%{
/* * * * * * * * * 
 * * * RULES * * *
 * * * * * * * * */
%}

print   { return PRINT; }
or   { return OR; }
and   { return AND; }
if   { return IF; }
then   { return THEN; }
else   { return ELSE; }
while   { return WHILE; }

{DIGIT}+ {
	yylval.number = atof(yytext); return NUMBER;
	}

{LETTER}[0-9a-zA-Z]* {
        yylval.var_name = strdup(yytext); return ID;
	}

[ \t\f\r]	;		 // ignore white space 

\n      { line_num++; }
"-"	{ return MINUS;  }
"+"	{ return PLUS;   }
"*"	{ return TIMES;  }
"/"	{ return DIVIDE; }
"("	{ return LPAREN; }
")"	{ return RPAREN; }
"{"	{ return LBRACE; }
"}"	{ return RBRACE; }
"["	{ return LBRACKET; }
"]"	{ return RBRACKET; }
"="     { return EQUALS; }
";"    {return SEMICOLON;}
","    {return COMMA;}
"=="    {return EQUAL;}
"!="    {return NOTEQUAL;}
"!"    {return NOT;}
"<"    {return LESS;}
">"    {return GREATER;}
"<="    {return LESSEQUAL;}
">="    {return GREATEREQUAL;}
"^"    {return EXPO;}


. { BEGIN(ERROR); yymore(); }
<ERROR>[^{DIGIT}{LETTER}+\-/*(){}= \t\n\f\r] { yymore(); }
<ERROR>(.|\n) { yyless(yyleng-1); printf("error token: %s on line %d\n", yytext, line_num); 
           BEGIN(INITIAL); }

%%

