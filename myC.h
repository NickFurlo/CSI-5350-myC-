#include <iostream>
#include <stdlib.h>
#include <string>
#include <map>
#include <list>
#include <vector>

using namespace std;


class exp_node{
	public:
		virtual void print();
		//virtual void evaluate();
};

class int_exp_node {
	public:

    // print function for pretty printing an expression
    virtual void print() = 0;

    // evaluation function for a leaf, replaced for interior nodes
    virtual int evaluate();
};


class float_exp_node:public exp_node{
	public:
		virtual void print() = 0;
		virtual float evaluate();
};
class string_exp_node: public exp_node{
	public:
		virtual void print() = 0;
		virtual string evaluate();
};
class bool_exp_node:public exp_node{
	public:
		virtual void print() = 0;
		virtual bool evaluate();
};
class int_exp_node:public exp_node{
	public:
		virtual void print() = 0;
		virtual int evaluate();
};
class char_exp_node:public exp_node{
	public:
		virtual void print() = 0;
		virtual char evaluate();
};


class binaryOp_node : public exp_node {
public:
    exp_node *left;
    exp_node *right;

  // the constructor for node links the node to its children,
  // and stores the character representation of the operator.
    binaryOp_node(exp_node *L, exp_node *R);
};
/*
class string_binaryOp_node : public string_exp_node {
public:
    string_exp_node *left;
    string_exp_node *right;

  // the constructor for node links the node to its children,
  // and stores the character representation of the operator.
    string_binaryOp_node(exp_node *L, exp_node *R);
};
class bool_binaryOp_node : public bool_exp_node {
public:
    bool_exp_node *left;
    bool_exp_node *right;

  // the constructor for node links the node to its children,
  // and stores the character representation of the operator.
    bool_binaryOp_node(exp_node *L, exp_node *R);
};
*/

class int_node : public int_exp_node{
	private:
		 int num;
	public:
		int_node(int value);
		void print();
		int evaluate();
};

class char_node : public char_exp_node{
	private:
		char c;
		
	public:
		char_node(char val);
		void print();
		char evaluate();
};

class float_node : public float_exp_node {
	private:
		float num;

	public:
		float_node(float value);
		void print();
		float evaluate();
};

class string_node : public string_exp_node{ //NEW. Defining string
	private:
		string str;
		
	public:
		string_node(string val);
		void print();
		string evaluate();
};

class bool_node : public bool_exp_node{
	private:
		bool bl;
		
	public:
		bool_node(bool val);
		void print();
		bool evaluate();
};

class variable_node : public string_exp_node {
protected:
  string id;

public:
  variable_node(string value);
  void print();
  string evaluate();
};

class neg_node : public float_exp_node {
 protected:
  float_exp_node *exp;
 public:
  neg_node(float_exp_node *exp);
  void print();
  float evaluate();
};

// add_node inherits the characteristics of node and adds its own evaluate function
class add_node : public binaryOp_node {
  public:

  // add_node's constructor just uses node's constructor
  add_node(float_exp_node *L, float_exp_node *R);
  void print();
  float evaluate();
};


// subtract_node inherits the characteristics of node and adds its own evaluate function
class subtract_node : public binaryOp_node {
  public:

  subtract_node(float_exp_node *L, float_exp_node *R);
  void print();
  float evaluate();
};


// multiply_node inherits the characteristics of node and adds its own evaluate function
class multiply_node : public binaryOp_node {
  public:

  multiply_node(float_exp_node *L, float_exp_node *R);
  void print();
  float evaluate();
};


// divide_node inherits the characteristics of node and adds its own evaluate function
class divide_node : public binaryOp_node {
  public:

  divide_node(float_exp_node *L, float_exp_node *R);
  void print();
  float evaluate();
};

//`````````````````````````````````````

//OR
class or_node : public binaryOp_node{
	public:
	
	or_node(bool_exp_node *L, bool_exp_node *R);
	void print();
	bool evaluate();
};

//AND
class and_node : public binaryOp_node{
	public:
	
	and_node(bool_exp_node *L, bool_exp_node *R);
	void print();
	bool evaluate();
};

//equal
class equal_node : public binaryOp_node{
	public:
	
	equal_node(exp_node *L, exp_node *R);
	void print();
	bool evaluate();
};

//not equal
class notequal_node : public binaryOp_node{
	public:
	
	notequal_node(exp_node *L, exp_node *R);
	void print();
	bool evaluate();
};

//less than
class less_node : public binaryOp_node{
	public:
	
	less_node(float_exp_node *L, float_exp_node *R);
	void print();
	bool evaluate();
};

//greater than
class greater_node : public binaryOp_node{
	public:
	
	greater_node(float_exp_node *L, float_exp_node *R);
	void print();
	bool evaluate();
};

//less than equal
class lessequal_node : public binaryOp_node{
	public:
	
	lessequal_node(float_exp_node *L, float_exp_node *R);
	void print();
	bool evaluate();
};

//greater than equal
class greaterequal_node : public binaryOp_node{
	public:
	
	greaterequal_node(float_exp_node *L, float_exp_node *R);
	void print();
	bool evaluate();
};

//negation
class negation_node : public bool_exp_node {
 protected:
  exp_node *exp;
 public:
  negation_node(bool_exp_node *exp);
  void print();
  bool evaluate();
};

//exponentiation
class expo_node : public binaryOp_node{
	public:
	
	expo_node(float_exp_node *L, float_exp_node *R);
	void print();
	float evaluate();
};
//string concatenation
class concatenate_node : public binaryOp_node{
	public:
	
	concatenate_node(string_exp_node *L, string_exp_node *R);
	void print();
	string evaluate();
};

//if-then
class if_node : public binaryOp_node{  //If-then-else is not a binary node, its actually trinary. Modify?
	public:
	
	if_node(exp_node *L, exp_node *R);
	void print();
	void evaluate();
};

//Used to define if-then-else
class trinaryOp_node : public exp_node {
	public:
		exp_node *left;
		exp_node *middle;
		exp_node *right;

  // the constructor for node links the node to its children,
  // and stores the character representation of the operator.
    trinaryOp_node(exp_node *L, exp_node *M, exp_node *R);
};
//if-then-else. This is like the matched if stmt in the grammar.
class if_else_node : public trinaryOp_node{  //If-then-else is not a binary node, its actually trinary. Modify?
	public:
	
	if_else_node(exp_node *L, exp_node *M,  exp_node *R);
	void print();
	void evaluate();
};

//loop
class loop_node : public binaryOp_node{
	public:
		loop_node(exp_node *L, exp_node *R);
		void print();
		void evaluate();
};
/*
//--------------------------------------------------
class func_dec_node : public stmt_node{
	protected:
		string type;
		string id;
		stmt *statement;
		list<func_params> *parameters;
	public:
		func_dec_node(string type, string name, list<func_params> *params,  stmt_node *statement);
		void print();
		void evaluate();
};


class func_params : public binaryOp_node{
	protected:
		string param_type;
		string param_name;
	public:
		func_params(exp_node *L, exp_node *R);
		void print();
		void evaluate();
}


class func_call_node : public func_dec_node{
		
	public:
		func_dec_node(string name, list<func_param_list> *parameters);
		void print();
		void evaluate();
};

class func_param_list : 
*/
//-----------------------------------------------------

class var_dec_node : public stmt_node {
	protected:
		string type;
		string id;
	public:
		
		var_dec_node(string tpe, string nme);
		void print();
		void evaluate();
};

class var_dec_assign_node : public stmt_node {
	protected:
		string type;
		string id;
		exp_node *expr; 
	public:
		
		var_dec_assign_node(string tpe, string nme, exp_node *exp);
		void print();
		void evaluate();
};


class array_dec_node: public stmt_node {
	protected:
		string type;
		string id;
		int dimension;
	public:
		array_dec_node(string tpe, string nme, int dim);
		void print();
		void evaluate();
	
};

//`````````````````````````````````````

class stmt_node {
 public:
  virtual void print();
  virtual void evaluate() = 0;
};

class assign_node : public stmt_node {
 protected:
  string id;
  exp_node *expression;
  int dimension;
 public:
  assign_node(string name, exp_node *expr, int dim);
  void print();
  void evaluate();
};

class print_node: public stmt_node {
 protected:
  exp_node *exp;
 public:
  print_node(exp_node *myexp);
  void print();
  void evaluate();
};

class skip_node: public stmt_node {
 public:
  skip_node();
  void print();
  void evaluate();
};


class sequence_node: public stmt_node {
 protected:
  stmt_node *stmt1, *stmt2;
 public:
  sequence_node(stmt_node *mystmt1, stmt_node *mystmt2);
  void print();
  void evaluate();
};

// the object at the base of our tree
//extern map<string, float> state;
extern map<string, float*> state_f;
extern map<string, int*> state_i;
extern map<string, char*> state_c;
extern map<string, bool*> state_b;
extern map<string, string*> state_s;
