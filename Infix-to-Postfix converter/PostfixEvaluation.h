#ifndef POSTFIX_EVALUATION
#define POSTFIX_EVALUATION

#include <string>
#include <string>
#include <vector>
#include <stack>    // including STL stack
#include <queue>  // // including STL queue
#include <iostream>
#include <algorithm>
#include<cmath>
#include <sstream>
using namespace std;


bool is_operand(string tok);

bool is_operator(string tok);


int get_weight(string operation);

bool has_higher_w8(const string& op1, string& op2); // const ref to operands as they are not going to be changed throughout the program


double do_operation(double op1, double op2, string operation);


double postfix_eval(queue<string> postfix); // passing queue as an argument for evaluation

void infix_to_postfix(string expression, queue<string>& postfix);

void get_postfix_and_evaluate(string infix);  // cout result

#endif