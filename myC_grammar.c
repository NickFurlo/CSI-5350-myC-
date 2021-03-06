Eric Cai, Mingshuai Ye, Nick Furlo
CSE 5350

<prog> ::= <stmtlist>
<stmlist>::= <stmt> | <stmtlist>;<stmt>
<stmt> ::= <loop> | <if_stmt> | <var_dec> | <array_dec> | <floatassignexpr> | <stringassignexpr> | <boolexpr> |<printfloat> | <printstring>

//Variable declaration
<var_dec> ::= <typename> id //Set the variable name 

//<array_dec> ::= <typename> id[<arithexpr>] | <typename> id[] //Array dimensions. Could be empty  NEW

<typename> ::= int | float | char | bool | string //Types

//Precedence of expressions.
<boolexpr> ::= <boolexpr> or <andexpr> | <andexpr> //OR
<andexpr> ::= <andexpr> and <equalexpr> | <equalexpr> //AND
<equalexpr> ::= <equalexpr> == <compareexpr> | <equalexpr> != <compareexpr> | <compareexpr> //Equality
<compareexpr> ::= <compareexpr> < <negateexpr | <compareexpr> > <negateexpr> | <compareexpr> <= <negateexpr> | <compareexpr> >= <negateexpr> | <negateexpr> //Boolean less/greater
<negateexpr> ::= !<endexpr> | <endexpr> //Negation
<endexpr> ::= <arithexpr>

<arithexpr> ::= <arithexpr> + <mul_div_expr> | <arithexpr> - <mul_div_expr> | <mul_div_expr> //Addition and subtraction
<mul_div_expr> ::= <mul_div_expr> * <expoexpr> | <mul_div_expr> / <expoexpr> | <expoexpr> //Multiplation and division
<expoexpr> ::= <expoexpr> ^ <negativeexpr> | <negativeexpr> //Exponentiation
<negativeexpr>::= - <rootexpr> | <rootexpr>

<rootexpr> ::= (<boolexpr>) | id | float_val | int_val | bool_val //Root of precedence. Can do operations again in parenthesis NEW

<strexpr> ::= <strexpr> + <rootstr> | <rootstr> //Modified to be left associative
<rootstr> ::= id | string_val | char_val  //NEW
//If statements
<if_stmt> ::= if (<boolexpr>) then {<matched_stmt>} else {<matched_stmt>} | if (<boolexpr>) then {<stmt>} 
<matched_stmt> ::= <stmt> | <matched_if> //Matched if makes sure that all further ifs have an else statement to remove ambiguous else
<matched_if> ::= if (<boolexpr>) then {<matched_stmt>} else {<matched_stmt>} 

//Loop statement
<loop> ::= while(<boolexpr>) {<stmt>}

//Function creation and calls
//<func_dec> ::= <typename> id(<func_params>) {<stmt>}
//<func_params> ::= <typname> id | <typename> id, <func_params> | <empty> //Can pass in arrays and empty also. 

//<func_call> ::= id = id(<func_param_list>) | id(<func_param_list>)  //Function can return value to a variable, or function can be called without returning anything
//<func_param_list>::= <boolexpr> | <boolexpr>, <func_param_list> | <empty> 

<floatassignexpr> ::= id= <floatassignroot> //| id[dimension] = <floatassignroot> 
<floatassignroot> ::= <boolexpr> | id = <floatassignroot> 

<stringassignexpr> ::= id= <stringassignroot> //| id[dimension] = <stringassignroot> 
<stringassignroot> ::= <strexpr> | id = <stringassignroot> 

<printfloat> ::= 
<printstring> ::=