
#include "ExpressionConverter.h"
#include <stack>
#include <queue>
#include <deque>
#include <array>
#include <map>
#include <list>
#include <sstream>
#include <iostream>

string out;
stringstream ss;

string Infix2RPN(string infix)
{
	const int MAX_SIZE = 127;
	myData myArray[MAX_SIZE];
	stack<char> opStack;
	string temp;
	istringstream iss;
	stringstream output;
	iss.str(infix);

	//Converting input string to list of tokens
	for (int i = 0; i < MAX_SIZE; i++)
	{
		if (iss >> temp)
		{
			if (temp == "(")
			{
				myArray[i].stat = '(';
				myArray[i].isOperand = false;
			}
			else if (temp == ")")
			{
				myArray[i].stat = ')';
				myArray[i].isOperand = false;
			}
			else if (temp == "+")
			{
				myArray[i].stat = '+';
				myArray[i].isOperand = false;
			}
			else if (temp == "-")
			{
				myArray[i].stat = '-';
				myArray[i].isOperand = false;
			}
			else if (temp == "/")
			{
				myArray[i].stat = '/';
				myArray[i].isOperand = false;
			}
			else if (temp == "*")
			{
				myArray[i].stat = '*';
				myArray[i].isOperand = false;
			}
			else
			{
				myArray[i].stat = stol(temp);
				myArray[i].isOperand = true;
			}
		}
		else
			break;
	}


	for (int i = 0; i < MAX_SIZE; ++i)
	{
		if (myArray[i].isOperand == true)
		{
			output << to_string(myArray[i].stat) << " ";
		}
		else if (myArray[i].stat == '(')
		{
			opStack.push((char)myArray[i].stat);
		}
		else if (myArray[i].stat == ')')
		{
			while (!opStack.empty())
			{
				if (opStack.top() == '(')
				{
					opStack.pop();
					break;
				}
				else
				{
					output << opStack.top() << " ";
					opStack.pop();
				}
			}
		}

		//token is an operator, *, /, +, or -
		if (myArray[i].stat == '+' || myArray[i].stat == '-' || myArray[i].stat == '*' || myArray[i].stat == '/')
		{
			while (!opStack.empty())
			{
				if (opStack.top() != '(')
				{
					if ((int)myArray[i].stat >= (int)opStack.top())
					{
						output << myArray[i].stat << " ";
						opStack.pop();
					}
					else
					{
						opStack.push((char)myArray[i].stat);
						break;
					}
				}
				else
				{
					opStack.push((char)myArray[i].stat);
					break;
				}
			}
			if (opStack.empty())
			{
				opStack.push((char)myArray[i].stat);
			}
		}
	}

	while (!opStack.empty())
	{
		output << opStack.top();
		opStack.pop();
	}

	return output.str();
}

string RPN2Infix(string rpn)
{
	ArithNode* root = RPN2ExpressionTree(rpn);
	out.clear();
	ss.str("");
	inorder(root);
	return out;
}

void inorder(ArithNode* node)
{

	if (node == nullptr)
	{
		return;
	}

	if (!(node->left == nullptr && node->right == nullptr))
	{
		ss << "(";
	}
	if (node->left != nullptr)
	{
		inorder(node->left);
	}

	if (node->isOperator)
	{
		ss << node->binaryOperator;
	}
	else
	{
		ss << node->operand;
	}

	if (node->right != nullptr)
	{
		inorder(node->right);
	}
	if (!(node->left == nullptr && node->right == nullptr))
	{
		ss << ")";
	}

	out = ss.str();
	ss.clear();
}


ArithNode *RPN2ExpressionTree(string rpn)
{
	const int MAX_SIZE = 127;
	myData myArray[MAX_SIZE];
	stack<ArithNode> exp_stack;
	unsigned int count = 0;
	istringstream iss;
	iss.str(rpn);
	string token;

	for (int i = 0; i < MAX_SIZE; i++)
	{
		if (iss >> token)
		{
			if (token == "(")
			{
				myArray[i].stat = '(';
				myArray[i].isOperand = false;
			}
			else if (token == ")")
			{
				myArray[i].stat = ')';
				myArray[i].isOperand = false;
			}
			else if (token == "+")
			{
				myArray[i].stat = '+';
				myArray[i].isOperand = false;
			}
			else if (token == "-")
			{
				myArray[i].stat = '-';
				myArray[i].isOperand = false;
			}
			else if (token == "/")
			{
				myArray[i].stat = '/';
				myArray[i].isOperand = false;
			}
			else if (token == "*")
			{
				myArray[i].stat = '*';
				myArray[i].isOperand = false;
			}
			else
			{
				myArray[i].stat = stol(token);
				myArray[i].isOperand = true;
			}
		}
		else
			break;
	}

	for (int i = 0; i < MAX_SIZE; i++)
	{
		if (myArray[i].isOperand == true)
		{
			ArithNode* temp = new ArithNode((int)myArray[i].stat);
			exp_stack.push(*temp);
		}
		else
		{
			if (exp_stack.size() == 1)
			{
				break;
			}
			ArithNode* temp2 = new ArithNode((char)myArray[i].stat);
			temp2->right = new ArithNode(exp_stack.top());
			exp_stack.pop();
			temp2->left = new ArithNode(exp_stack.top());
			exp_stack.pop();
			exp_stack.push(*temp2);
		}
	}
	ArithNode* root = new ArithNode(exp_stack.top());

	return root;
}

ArithNode *Infix2ExpressionTree(string infix)
{
	return RPN2ExpressionTree(Infix2RPN(infix));
}
int EvaluateInfix(string infix)
{
	return EvaluateRPN(Infix2RPN(infix));
}

int EvaluateRPN(string expr)
{
	const int MAX_SIZE = 127;
	myData myArray[MAX_SIZE];
	stack<int> operandStack;
	istringstream iss;
	iss.str(expr);
	string token;
	int result;

	for (int i = 0; i < MAX_SIZE; i++)
	{
		if (iss >> token)
		{
			if (token == "(")
			{
				myArray[i].stat = '(';
				myArray[i].isOperand = false;
			}
			else if (token == ")")
			{
				myArray[i].stat = ')';
				myArray[i].isOperand = false;
			}
			else if (token == "+")
			{
				myArray[i].stat = '+';
				myArray[i].isOperand = false;
			}
			else if (token == "-")
			{
				myArray[i].stat = '-';
				myArray[i].isOperand = false;
			}
			else if (token == "/")
			{
				myArray[i].stat = '/';
				myArray[i].isOperand = false;
			}
			else if (token == "*")
			{
				myArray[i].stat = '*';
				myArray[i].isOperand = false;
			}
			else
			{
				myArray[i].stat = stol(token);
				myArray[i].isOperand = true;
			}
		}
		else
			break;
	}

	for (int i = 0; i < MAX_SIZE; ++i)
	{
		if (myArray[i].isOperand == true)
		{
			operandStack.push(myArray[i].stat);
		}
		else
		{
			if (operandStack.size() == 1)
			{
				break;
			}
			int secondOperand = operandStack.top();
			operandStack.pop();
			int firstOperand = operandStack.top();
			operandStack.pop();

			if (myArray[i].stat == '+')
			{
				operandStack.push(firstOperand + secondOperand);
			}
			else if (myArray[i].stat == '-')
			{
				operandStack.push(firstOperand - secondOperand);
			}
			else if (myArray[i].stat == '*')
			{
				operandStack.push(firstOperand * secondOperand);
			}
			else
			{
				operandStack.push(firstOperand / secondOperand);
			}
		}

	}

	result = operandStack.top();
	operandStack.pop();
	return result;
}