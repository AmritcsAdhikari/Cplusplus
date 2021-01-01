
/*
Author: Amrit Adhikari
CSCE 3110 
Data Structures (Fall 2020)
Project 2
Date : 9/29/2020
Description : This program is a calcualtor that takes input as an infix expression, which is evaluated after converting into a post fix expresssion. In summary, this program would take in infix expression and then output post fix expression as well as the result.
*/

#include "PostfixEvaluation.h"
#include <iostream>
using namespace std;

int main()
{
	string infix; // hoolds the infix expression from the user
	cout << "Enter a valid infix expression: ";
	getline(cin, infix);  // read whole string entered by the user

	get_postfix_and_evaluate(infix); // calling function that converts infix expression to post fix and then evaluating to display the result
	return 0;
}
