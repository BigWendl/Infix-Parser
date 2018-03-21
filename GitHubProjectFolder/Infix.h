#ifndef INFIX_H_
#define INFIX_H_

#include <string>
#include <sstream>
#include <stack>
#include <iostream>

using namespace std;

class Infix {
private:

	stack<string> operatorStack;//changed to stack of strings so it could handle two character operators
	stack<int> operandStack;
	int result, lhs, rhs, charCount;
	string operators[17] = { "!", "++", "--", "^", "*", "/", "%", "+", "-", ">", ">=", "<", "<=", "==", "!=", "&&", "||" };//only operator not included is negative (-)
	int precedence[17] = { 8, 8, 8, 7, 6, 6, 6, 5, 5, 4, 4, 4, 4, 3, 3, 2, 1 };
	bool error, neg;

	int isoperator(string operators[], int precedence[], string op)
	{
		for (int i = 0; i < 17; i++)
		{
			if (operators[i] == op)//search for operator
			{
				return precedence[i];//if found return the precedence of the operator
			}
		}
		return -1; //if not found return -1
	}

public:
	int evaluate(const string& expression)
	{
		istringstream tokens(expression);
		char nextChar;
		int current_precedence = -1, previous_precedence = -1;
		string op = "", temp = "";
		charCount = 0;
		error = false, neg = false;
		while (!operandStack.empty())
			operandStack.pop();
		while (!operatorStack.empty())
			operatorStack.pop();

		while (tokens >> nextChar)
		{
			if (isdigit(nextChar))//if character is a number read the value as an integer
			{
				charCount++;
				tokens.putback(nextChar);
				int num;
				tokens >> num;
				if (num >= 10)
				{
					charCount++;
					if (num >= 100)
					{
						charCount++;
						if (num >= 1000)
						{
							charCount++;
							if (num >= 10000)
								charCount++;
						}

					}
				}
				if (neg == true)
				{
					num *= -1;
					neg = false;
				}
				operandStack.push(num);
			}
			else if (nextChar == '(' || nextChar == ')')
			{
				charCount++;
				if ((operandStack.empty() && operatorStack.empty()) && nextChar == ')')
				{
					cout << "Expression can't start with a closing parenthesis @ char: " << charCount << endl;
					return 0;
				}
				else if (nextChar == '(')//checks for open parentheses
				{
					operatorStack.push("(");
				}
				else if (nextChar == ')')//checks for closing parentheses
				{
					while (operatorStack.top() != "(" || operatorStack.empty())
					{
						rhs = operandStack.top();
						operandStack.pop();
						lhs = operandStack.top();
						operandStack.pop();
						op = operatorStack.top();
						operatorStack.pop();

						operandStack.push(compute(lhs, rhs, op));
					}
					operatorStack.pop();
					op = "";
					current_precedence = 0;
					previous_precedence = 0;
				}
			}
			else if (nextChar == '-' && neg == false && (operatorStack.empty() || operatorStack.top() == "("))//neg at begin
			{
				neg = true;
				charCount++;
			}
			else
			{
				charCount++;
				op += nextChar;//if the next character is not a number add it to the operator string
				tokens >> nextChar;//read the next character to see if it should be included in the operator	
				if ((operandStack.empty() && operatorStack.empty()) && (op == ">" || op == "<" || op == "=" || (op == "!" && nextChar == '=') || op == "&" || op == "|"))
				{
					cout << "Expression can't start with a binary operator @ char: " << charCount << endl;
					return 0;
				}
				if ((op == ">" || op == "<" || op == "=" || op == "!" || op == "&" || op == "|") && (current_precedence <= 4 && current_precedence > 0))
				{
					cout << "Two binary operators in a row @ char: " << charCount << endl;
					return 0;
				}
				if ((op == ">" || op == "<" || op == "=" || op == "!" || op == "&" || op == "|") && current_precedence == 8)
				{
					cout << "A unary operand can't be followed by a binary operator @ char: " << charCount << endl;
					return 0;
				}
				if (isdigit(nextChar))
				{
					tokens.putback(nextChar);//if the next character is a number, put it back to be added to the operand stack
					current_precedence = isoperator(operators, precedence, op);
				}
				else if (op == ">" || op == "<" || op == "=" || op == "!" || op == "&" || op == "|" || (op == "-" && nextChar == '-') || (op == "+" && nextChar == '+'))
				{
					if (nextChar != '!')
					{
						op += nextChar;//if it isn't a number add it to the operator string
					}
					if (op == "++" || op == "--" || op == ">=" || op == "<=" || op == "==" || op == "!=" || op == "&&" || op == "||")
						charCount++;
					current_precedence = isoperator(operators, precedence, op);
				}
				else if (nextChar == '(')
				{
					charCount++;
					operatorStack.push("(");
					previous_precedence = 0;
					current_precedence = 0;
				}
				else
				{
					tokens.putback(nextChar);//if the next character is a number, put it back to be added to the operand stack
					current_precedence = isoperator(operators, precedence, op);
				}
				if (current_precedence == -1)//if it can't find the precedence it is because the operator is not included in the list of operators
				{
					cout << "Invalid Character @ Char: " << charCount << endl;
					return 0;
				}
				else if (current_precedence < previous_precedence)//if the precedence of the current operator is lower than the operator previous put on the stack
				{
					temp = op;//assign the newest operator to a temp variable and process the previous operator and previous two operands
					op = operatorStack.top();
					operatorStack.pop();
					rhs = operandStack.top();
					operandStack.pop();

					if (!operandStack.empty())
					{
						lhs = operandStack.top();
						operandStack.pop();
					}
					else
						lhs = 0;

					operandStack.push(compute(lhs, rhs, op));//push the value of the operation back to the operand stack
					operatorStack.push(temp);//push the newest operator to the stack
					previous_precedence = current_precedence;//set the previous precedence value to that of the operator at the top of the stack
					op = "";//clear the operator string for further processing
				}
				else
				{
					previous_precedence = current_precedence;//if the precedence of the new operator is not less then push it to the stack
					operatorStack.push(op);
					op = "";//clear the operator string for further processing
				}
			}
		}
		while (!operatorStack.empty())//after entire string has been processed the stacks are ready to be processed
		{
			rhs = operandStack.top();
			operandStack.pop();
			if (!operandStack.empty())
			{
				lhs = operandStack.top();
				operandStack.pop();
			}
			else
				lhs = 0;

			op = operatorStack.top();
			int answer = compute(lhs, rhs, op);

			operandStack.push(answer);
			operatorStack.pop();
		}

		result = operandStack.top();
		while (!operandStack.empty())//once expression is finished, make sure to empty stack for next expression
			operandStack.pop();
		if (error == false)
			cout << expression << " = " << result << endl;
		return 0;//once operator stack has been cleared, end the function
	}



	int compute(int lhs, int rhs, string op)//I made this if\else if instead of switch because c++ does not allow you to switch on string values
	{
		if (op == "+")
		{
			return result = lhs + rhs;
		}
		else if (op == "*")
		{
			return result = lhs * rhs;
		}
		else if (op == "-")
		{
			return result = lhs - rhs;
		}
		else if (op == "/")
		{
			if (rhs == 0)
			{
				if (error == false)
				{
					cout << "Division by zero @ Char: " << charCount << endl;
					error = true;
				}
				return result;
			}
			else
			{
				return result = lhs / rhs;
			}
		}
		else if (op == "%")
		{
			return result = lhs % rhs;
		}
		else if (op == "^")
		{
			int origLeft = lhs;
			while (rhs != 1)
			{
				lhs *= origLeft;
				rhs--;
			}
			result = lhs;
			return result;
		}
		else if (op == ">")
		{
			if (lhs > rhs)
				return 1;
			else
				return 0;
		}
		else if (op == "<")
		{
			if (lhs < rhs)
				return 1;
			else
				return 0;
		}
		else if (op == ">=")
		{
			if (lhs >= rhs)
				return 1;
			else
				return 0;
		}
		else if (op == "<=")
		{
			if (lhs <= rhs)
				return 1;
			else
				return 0;
		}
		else if (op == "==")
		{
			if (lhs == rhs)
				return 1;
			else
				return 0;
		}
		else if (op == "!=")
		{
			if (lhs != rhs)
				return 1;
			else
				return 0;
		}
		else if (op == "&&")
		{
			if ((lhs >= 1) && (rhs >= 1))
				return 1;
			else
				return 0;
		}
		else if (op == "||")
		{
			if ((lhs == 1) || (rhs == 1))
				return 1;
			else
				return 0;
		}
		else if (op == "!")
		{
			if (rhs >= 1)
				return 0;
			else if (rhs == 0)
				return 1;
		}
		else if (op == "++")
		{
			while (operatorStack.top() == "++")
			{
				rhs++;
				operatorStack.pop();
				if (operatorStack.empty())
					return ++rhs;
			}
			return ++rhs;
		}
		else if (op == "--")
		{
			while (operatorStack.top() == "--")
			{
				rhs--;
				operatorStack.pop();
				if (operatorStack.empty())
					return --rhs;
			}
			return --rhs;
		}
		return result;
	}
};
#endif
