#include <iostream>
#include <stdlib.h>
#include <string>
#include <map>
#include <list>
#include <cmath> //Added for pow() for exponentiation
#include <typeinfo> //added to determine type for assignment
#include "myC.h"

using namespace std;

  // the constructor for node links the node to its children,
  // and stores the character representation of the operator.
binaryOp_node::binaryOp_node(exp_node *L, exp_node *R) {
	left    = L;
    right   = R;
}

trinaryOp_node::trinaryOp_node(exp_node *L, exp_node *M, exp_node *R){ //Used for if-then-else
	left=L;
	middle=M;
	right=R;
}

int_node::int_node(int value) {
    num = value;
}
void int_node:: print() {
	cout << num;
}
int int_node::evaluate() { 
	return num; 
}

char_node::char_node(char value) {
    c = value;
}
void char_node:: print() {
	cout << c;
}
char char_node::evaluate() { 
	return c; 
}

float_node::float_node(float value) {
    num = value;
}
void float_node:: print() {
	cout << num;
}
float float_node::evaluate() { 
	return num; 
}

//Defining string
string_node::string_node(string val){
	str=val;
}
void string_node::print(){
	cout<<str;
}
string string_node::evaluate(){
	return str;
}

//Defining bool
bool_node::bool_node(bool val){
	bl=val;
}
void bool_node::print(){
	cout<<bl;
}
bool bool_node::evaluate(){
	return bl;
}

//Variable
variable_node::variable_node(string value) : id(value) {}
void variable_node:: print() {
	cout << id;
}
string variable_node::evaluate() { 
	return state_s[id]; 
}
  
//Negative
neg_node::neg_node(float_exp_node *L) : exp(L) {}
void neg_node:: print() {
	cout << "- ( ";
	exp->print();
	cout << " ) ";
}
float neg_node::evaluate() {
	float expValue = exp->evaluate();
	float result=-1*expValue;
	return result;
}


// add_node inherits the characteristics of node and adds its own evaluate function
// add_node's constructor just uses node's constructor
add_node::add_node(float_exp_node *L, float_exp_node *R) : binaryOp_node(L,R) {}
void add_node:: print() {
	cout << "( ";
	left->print();
	cout << " + ";
	right->print();
	cout << " ) ";
}
float add_node::evaluate() {
    float left_val, right_val;

    left_val  = left->evaluate();
    right_val = right->evaluate();
    
    return left_val + right_val;
}


// subtract_node inherits the characteristics of node and adds its own evaluate function
subtract_node::subtract_node(float_exp_node *L, float_exp_node *R) : binaryOp_node(L,R) {}
void subtract_node:: print() {
	cout << " ( ";
	left->print();
	cout << " - ";
	right->print();
	cout << " ) ";
}
float subtract_node::evaluate() {
    float left_val, right_val;

    left_val  = left->evaluate();
    right_val = right->evaluate();

    return  left_val - right_val;

}


// multiply_node inherits the characteristics of node and adds its own evaluate function
multiply_node::multiply_node(float_exp_node *L, float_exp_node *R) : binaryOp_node(L,R) {}
void multiply_node:: print() {
  cout << "( ";
  left->print();
  cout << " * ";
  right->print();
  cout << " ) ";
}
float multiply_node::evaluate() {
    float left_val, right_val;

    left_val = left->evaluate();
    right_val = right->evaluate();

    return left_val * right_val;

}


// divide_node inherits the characteristics of node and adds its own evaluate function
divide_node::divide_node(float_exp_node *L, float_exp_node *R) : binaryOp_node(L,R) {
}
void divide_node:: print() {
	cout << "( ";
	left->print();
	cout << " / ";
	right->print();
	cout << " ) ";
}

float divide_node::evaluate() {
    float left_val, right_val;

    left_val = left->evaluate();
    right_val = right->evaluate();

    if(right_val){
        return  left_val / right_val;
    }
    else{
	cout << "division by zero -> " << left_val << " / " << 0 << endl;
	//  include stdlib.h for exit
	exit(1);
    }
}

//--------------------------------------------------------------------------------------------------
//OR functions. Evaluate returns bool
or_node::or_node(bool_exp_node *L, bool_exp_node *R) : binaryOp_node(L, R){}
void or_node:: print(){
	cout<< " ( ";
	left->print();
	cout<<" OR ";
	right->print();
	cout<<" ) ";
}
bool or_node::evaluate(){
	bool left_val=left->evaluate();
	bool right_val=right->evaluate();
	 
	return left_val || right_val;
}

//AND functions. Evaluate returns bool
and_node::and_node(bool_exp_node *L, bool_exp_node *R) : binaryOp_node(L, R){}
void and_node:: print(){
	cout<< " ( ";
	left->print();
	cout<<" AND ";
	right->print();
	cout<<" ) ";
}
bool and_node::evaluate(){
	bool left_val=left->evaluate();
	bool right_val=right->evaluate();
	 
	return left_val && right_val;
}

//Equal functions. Evaluate returns bool
equal_node::equal_node(exp_node *L, exp_node *R) : binaryOp_node(L, R){}
void equal_node:: print(){
	cout<< " ( ";
	left->print();
	cout<<" == ";
	right->print();
	cout<<" ) ";
}
bool equal_node::evaluate(){
	auto left_val=left->evaluate();
	auto right_val=right->evaluate();
	 
	return left_val == right_val;
}

//Not equal. Evaluate returns bool
notequal_node::notequal_node(exp_node *L, exp_node *R) : binaryOp_node(L, R){}
void notequal_node:: print(){
	cout<< "( ";
	left->print();
	cout<<" != ";
	right->print();
	cout<<" ) ";
}
bool notequal_node::evaluate(){
	auto left_val=left->evaluate();
	auto right_val=right->evaluate();
	 
	return left_val != right_val;
}

//Less than. Evaluate returns bool
less_node::less_node(float_exp_node *L, float_exp_node *R) : binaryOp_node(L, R){}
void less_node:: print(){
	cout<< "( ";
	left->print();
	cout<<" < ";
	right->print();
	cout<<" ) ";
}
bool less_node::evaluate(){

	float left_val=left->evaluate();
	float right_val=right->evaluate();
	 
	return left_val < right_val;
}

//Greater than. Evaluate returns bool
greater_node::greater_node(float_exp_node *L, float_exp_node *R) : binaryOp_node(L, R){}
void greater_node:: print(){
	cout<< "( ";
	left->print();
	cout<<" > ";
	right->print();
	cout<<" ) ";
}
bool greater_node::evaluate(){
	float left_val=left->evaluate();
	float right_val=right->evaluate();
	 
	return left_val > right_val;
}

//Less than equal to. Evaluate returns bool
lessequal_node::lessequal_node(float_exp_node *L, float_exp_node *R) : binaryOp_node(L, R){}
void lessequal_node:: print(){
	cout<< "(";
	left->print();
	cout<<" <= ";
	right->print();
	cout<<") ";
}
bool lessequal_node::evaluate(){
	float left_val=left->evaluate();
	float right_val=right->evaluate();
	 
	return left_val <= right_val;
}

//Greater than equal to. Evaluate returns bool
greaterequal_node::greaterequal_node(float_exp_node *L, float_exp_node *R) : binaryOp_node(L, R){}
void greaterequal_node:: print(){
	cout<< "(";
	left->print();
	cout<<" >= ";
	right->print();
	cout<<") ";
}
bool greaterequal_node::evaluate(){
	float left_val=left->evaluate();
	float right_val=right->evaluate();
	 
	return left_val <= right_val;
}

//Negation. evaluate returns bool
negation_node::negation_node(bool_exp_node *L) : exp(L) {}
void negation_node:: print() {
  cout << "( ! ";
  exp->print();
  cout << " )";
}
bool negation_node::evaluate() { //Takes in a bool, returns a bool (negation)
  bool expValue = exp->evaluate();
  return  !expValue;
}

// Exponentiation
expo_node::expo_node(float_exp_node *L, float_exp_node *R) : binaryOp_node(L,R) {}
void expo_node:: print() {
  cout << "(";
  left->print();
  cout << " ^ ";
  right->print();
  cout << ")";
}
float expo_node::evaluate() {
	float left_val, right_val;

    left_val = left->evaluate();
    right_val = right->evaluate();

    return pow(left_val, right_val); //Uses pow() from <cmath> library
}

//String concatenation. evaluate returns string
concatenate_node::concatenate_node(string_exp_node *L, string_exp_node *R) : binaryOp_node(L,R) {}
void concatenate_node:: print() {
	cout << "(";
	left->print();
	cout << " + ";
	right->print();
	cout << ")";
}
string concatenate_node::evaluate() {
    string left_str, right_str;

    left_str  = left->evaluate();
    right_str = right->evaluate();
    
    return left_str + right_str;
}

//If-then
if_node::if_node(exp_node *L, exp_node *R) : binaryOp_node(L,R) {}
void if_node:: print() {
  cout << "if (";
  left->print();
  cout << " ) { ";
  right->print();
  cout << " }";
}
void if_node::evaluate() { 
    bool left_val = left->evaluate();
	//right_val?
 
    if (left_val) {
		right->evaluate();
		return;
	}
	return;
}

//If-then-else
if_else_node::if_else_node(exp_node *L, exp_node *M, exp_node *R) : trinaryOp_node(L, M, R) {}
void if_else_node:: print() {
	cout << "if (";
	left->print();
	cout << " ) { ";
	middle->print();
	cout << " } else { ";
	right->print();
	cout << " } ";
}
void if_else_node::evaluate() { 
    bool left_val = left->evaluate();
	//mid_val, right_val?

    if (left_val) { 
		auto middle->evaluate();
		return ;
	} else {
		auto right->evaluate();
		return ;
	}
}

//While loop
loop_node::loop_node(exp_node *L, exp_node *R) : binaryOp_node(L, R){}
void loop_node:: print(){
	cout<< "while ( ";
	left->print();
	cout<< " ) { ";
	right->print();
	cout<< " } ";
}
void loop_node::evaluate(){
	
	while(left->evaluate()){
		right->evaluate();
	}	
	return;
}
/*
//------------------------------------------------------------
//NEED TO FIX

func_dec_node:func_dec_node(string tpe, string name, list<func_params> *params, stmt *states): type(tpe), id(name), parameters(params), statement(states){}
void func_dec_node::print(){
	cout<<type;
	cout<<" ";
	cout<<name;
	cout<<" ( ";
	
	if(!params.empty()){
		cout<<(params.begin());
		for(auto it=++(params.begin()); it!=params.end(); it++){
			cout<<", ";
			print->*it;
		}
	}
	
	cout<<" ) ";
	cout<<" { "<<endl;
	print->statement;
	cout<<" } ";
}
void func_dec_node::evaluate(){
	id=name;
	type=tps;
	*statement=states;
	*expressions=exprs;
}

func_params:func_params(exp_node *L, exp_node*R):binaryOp_node(L, R){} //Need to be able to create a list or parameters to pass to func_dec_node
void func_params::print(){
	left->print();
	cout>>" ";
	right->print();
}
void func_params::evaluate(){
	param_type=left->evaluate();
	param_name=right->evaluate(); 
	
}

//Things needed: name, return type, parameters matched
//Function can be considered like an expression itself

func_call_node:func_dec_node(string name, list<func_param_list> *parameters):func_dec_node(
void func_call_node::print(){
	cout<<name;
	cout<<" ( ";
	
	if(!parameters.empty()){
		cout<<*(expressions.begin());
		for(auto it=++(parametersbegin()); it!=parameters.end(); it++){
			cout<<", ";
			print->*it;
		}
	}
	
	cout<<" ) ";
}
void func_call_node::evaluate(){
	if(type.compare("int")==0){
		int result1;
		result1=statement->evaluate();
		return result1;
		
	}
	
}

func_param_list:func_param_list(  ) //Need to add

//--------------------------------------------------------
*/
var_dec_node::var_dec_node(string tpe, string name) :type(tpe), id(name){}
void var_dec_node::print(){
	cout<<type<<" "<<id;	
}
void var_dec_node::evaluate(){
	switch(type){
		case "int":
			state_i[id]=0;
			break;
		case "bool":
			state_b[id]=0;
			break;
		case "float":
			state_f[id]=0;
			break;
		case "char":
			state_c[id]="";
			break;
		case "string":
			state_s[id]=" ";
			break;
		default:
			cout<<"Type mismatch"<<endl;
	}
	
}

var_dec_assign_node::var_dec_assign_node(string tpe, string name, exp_node *L) :type(tpe), id(name), expr(L){}
void var_dec_assign_node::print(){
	cout<<type<<" "<<id;	
	cout<<" = ";
	expr->print();
}
void var_dec_assign_node::evaluate(){
	switch(type){
		case "int":
			state_i[id]=*expr->evaluate();
			break;
		case "bool":
			state_b[id]=*expr->evaluate();
			break;
		case "float":
			state_f[id]=*expr->evaluate();
			break;
		case "char":
			state_c[id]=*expr->evaluate();
			break;
		case "string":
			state_s[id]=*expr->evaluate();
			break;
		default:
			cout<<"Type mismatch"<<endl;
	}
	
}

//Initializes an array and fills them with default values.
array_dec_node::array_dec_node(string tpe, string nme, int dim=0) : type(tpe), id(nme), dimension(dim){}
void array_dec_node::print(){
	cout<<type<<" "<<id<<" [ "<<dimension<<" ] ";	
}
void array_dec_node::evaluate(){
	if(dimension<0){
		cout<<"Negative array dimension"<<endl;
		return;
	}else{
	
	switch(type){
		case "int":
			for (int i=0; i<=dimension; i++){
				state_i[id][i]=0;
			}
			break;
		case "bool":
			for (int i=0; i<dimension; i++){
				state_b[id][i]=0;
			}
			break;
		case "float":
			for (int i=0; i<dimension; i++){
				state_f[id][i]=0;
			}
			break;
		case "char":
			for (int i=0; i<dimension; i++){
				state_c[id][i]='~';
			}
			break;
		case "string":
			for (int i=0; i<dimension; i++){
				state_s[id][i]='~';
			};
			break;
		default:
			cout<<"Type mismatch"<<endl;		
	}
	}
}

//````````````````````````````````````````````````````````````
assign_node::assign_node(string name, exp_node *expr, int dim=-1) : id(name), expression(expr), dimension(dim) {}
void assign_node::print() {
	if(dimension==-1){ //Checks to see if this is an array
		cout << id << " = ";
		expression->print();
	}else{
		cout<<id<<" [ "<<dimension<<" ] "<<" = ";
		expression->print();
	}
}
void assign_node::evaluate() {
	auto result = *expression->evaluate(); 
	//use typeid to see if the result is a bool, char, int, or float. If its none of those, assume that it is a string
	
	if(dimension==-1){ //If there is no array, just assign normally
		switch(typeid(result).name()){
		case 'i':
			state_i[id]=result;
			break;
		case 'b':
			state_b[id]=result;
			break;
		case 'f':
			state_f[id]=result;
			break;
		case 'c':
			state_c[id]=result;
			break;
		default:
			state_s[id]=result;
			break;
		}
	}else{ //If there is an assocated array dimension, insert results at that array
		switch(typeid(result).name()){
		case 'i':
			state_i[id][dimension]=result;
			break;
		case 'b':
			state_b[id][dimension]=result;
			break;
		case 'f':
			state_f[id][dimension]=result;
			break;
		case 'c':
			state_c[id][dimension]=result;
			break;
		default:
			state_s[id][dimension]=result;
			break;
		
		}
	}
}

print_node::print_node (exp_node *myexp) : exp(myexp) {}
void print_node::print() {
  cout <<  "print ";
  exp->print();
}
void print_node::evaluate() {
  cout << "output: " << exp->evaluate() << endl << endl;
}

skip_node::skip_node ()  {}
void skip_node::evaluate() {}
void skip_node::print() {}


sequence_node::sequence_node(stmt_node* mystmt1, stmt_node* mystmt2): stmt1(mystmt1), stmt2(mystmt2){}
void sequence_node::print() {
  stmt1->print();  cout << " ;" << endl;
  stmt2->print();
}
void sequence_node::evaluate() {
  stmt1->evaluate();
  stmt2->evaluate();
}

map<string, float*> state_f;
map<string, int*> state_i;
map<string, char*> state_c;
map<string, bool*> state_b;
map<string, string*> state_s;