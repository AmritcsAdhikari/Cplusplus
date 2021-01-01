#include "PostfixEvaluation.h"


/*Method for mismatched Parentheses */
bool mismatched_Parentheses(string expression)
{
	int open_p = 0, close_p = 0;
	for (int i = 0; i < expression.size(); ++i)

	{
		if (expression[i] == '(')
			open_p++;
		if (expression[i] == ')')
			close_p++;
		if (close_p > open_p)
			return true;
	}
	if (open_p - close_p != 0)
		return true;
	return false;
}

/* validating the operands */
bool is_operand(string tok)
{
	if (tok.empty())
		return false;
	string nums = "-.0123456789";
	for (char c : tok)
	{
		if (nums.find(c) == std::string::npos)
			return false;
	}
	return true;
}

/* This function checks for the operators(if valid or invalid) */
bool is_operator(string tok)
{
	vector<string> operators = { "+" , "-", "*","/" , "^", "%" };

	return find(operators.begin(), operators.end(), tok) != operators.end();
}


/* This function returns the value as per the precendence of the operator passsed into */
int get_weight(string operation)
{
	int ret = 0;

	if (operation == "+" || operation == "-")
		ret = 1;
	else if (operation == "*" || operation == "/" || operation == "%")
		ret = 2;
	else if (operation == "^")
		ret = 3;

	return ret;
}

/*Coding for the right to left associativity of ^ operator as it has higher precendence over other operators */
bool has_higher_w8(const string& op1, string& op2)
{
	const int op1W = get_weight(op1);
	int op2_w = get_weight(op2);

	if (op1W == op2_w)
	{
		if (op1 == "^")
		{
			return false;
		}
		return true;
	}
	if (op1W > op2_w)
		return true;

	return   false;
}


/*This method converts the infix to postfix expression using stack */
void  infix_to_postfix(string expression, queue<string>& postfix)
{
	stack<string> stack1;
	string tok;
	vector<string> expression_splitted;
	for (int i = 0; i < expression.size(); ++i)

	{
		if (expression[i] == ' ')
		{
			expression_splitted.push_back(tok), tok.clear();
			continue;
		}
		tok.push_back(expression[i]);
	}
	if (tok.size())
		expression_splitted.push_back(tok);

	for (int i = 0; i < expression_splitted.size(); ++i)
	{
		string tok = expression_splitted[i];
		if (is_operator(tok))
		{
			while (stack1.size() && stack1.top() != "(" && has_higher_w8(stack1.top(), tok))
			{
				postfix.push(stack1.top());
				stack1.pop();
			}
			stack1.push(tok);
		}
		else if (is_operand(tok))
		{
			postfix.push(tok);
		}
		else if (tok == "(")
		{
			stack1.push(tok);
		}
		else if (tok == ")")
		{
			while (!stack1.empty() && stack1.top() != "(")
			{
				postfix.push(stack1.top());
				stack1.pop();
			}
			if (!stack1.empty())
				stack1.pop();
		}
		else
		{
			// the user entered something strange
			//terminate the code
			puts("You entered invalid characters, Terminating.....");
			exit(0);
		}
	}

	while (!stack1.empty())
	{
		if (stack1.top() != "(" && stack1.top() != ")")
			postfix.push(stack1.top());
		stack1.pop();
	}


}



double do_operation(double op1, double op2, string operation)
{
	//Perform do_operation
	if (operation == "^")
		return pow(op2, op1);
	if (operation == "%")
		return ((int)(op2) % (int)(op1));
	if (operation == "-")
		return op2 - op1;
	if (operation == "+")
		return op2 + op1;
	if (operation == "*")
		return op2 * op1;
	if (operation == "/")
		return op2 / op1;
	//return nothing
	return -1;
}

/* This method evaluates the post fix expression that is passed into as a queue  */
double postfix_eval(queue<string> postfix)
{
	stack<double> stk;

	while (postfix.size() > 0)
	{
		string val = postfix.front();
		postfix.pop();
		// checks if the token is operator
		if (is_operator(val))
		{
			double op1 = stk.top();
			stk.pop();
			double op2 = stk.top();
			stk.pop();
			double result = do_operation(op1, op2, val);
			stk.push(result);
		}
		// checks if the token is operand (i.e a number)
		else if (is_operand(val))
		{

			stk.push(stod(val));
		}
	}
	return stk.top();
}

/* Final evaluation and result displaying */
void get_postfix_and_evaluate(string infix)
{
	queue<string> postfix;
	const bool is_mismatched_parentheses = mismatched_Parentheses(infix);
	infix_to_postfix(infix, postfix);
	cout << "The resulting postfix expression is: ";
	queue<string> to_print = postfix;
	while (!to_print.empty())
	{
		cout << to_print.front() << " ";
		to_print.pop();
	}
	cout << endl;

	if (is_mismatched_parentheses)
	{
		cout << "Error: Mismatched Parentheses! Program Terminated.\n";
		return;
	}

	cout << "The result is: " << postfix_eval(postfix) << endl;
}