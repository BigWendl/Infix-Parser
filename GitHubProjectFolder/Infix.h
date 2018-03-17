#ifndef INFIX_H_
#define INFIX_H_

#include <string>
#include <sstream>
#include <stack>
#include <iostream>

//namespace INF {
using namespace std;
	
class Infix {

	private:
		stack<string> operatorStack;//changed to stack of strings so it could handle two character operators
		stack<int> operandStack;
		stack<char> boolStack;//do we need this?
		int result, lhs, rhs, position;
		string operators[17] = { "!", "++", "--", "^", "*", "/", "%", "+", "-", ">", ">=", "<", "<=", "==", "!=", "&&", "||"};//only operator not included is negative (-)
		int precedence[17] = {8, 8, 8, 7, 6, 6, 6, 5, 5, 4, 4, 4, 4, 3, 3, 2, 1};
		//const string bools = "|&";
		string expression;

		int isoperator(string operators[], int precedence[], string op)
		{
			for (int i = 0; i < 17; i++)
			{
				if (operators[i] == op)//search for operator
				{
					return precedence[i];//if found return the precedence of the operator
				}
				
			}
			return 0; //if not found return 0

			//return operators.find(opo) != std::string::npos;
		}
		/*bool isbool(char boolian)
		{
			return bools.find(boolian) != std::string::npos;
		}*/

		/*int evaluateOperator(string op)
		{
			return precedence[position];
		}*/
		//int evaluateBool(char boolian)
		//{
		//	//pop bool stack
		//}

	public:

		int evaluate(const string& expression)
		{
			/*while (operandStack.empty())
				operandStack.pop();*/

			istringstream tokens(expression);
			char nextChar;
			int current_precedence = 0, previous_precedence = 0; 
			string op = "", temp="";
			while (tokens >> nextChar)
			{
				if (isdigit(nextChar))//if character is a number read the value as an integer
				{
					tokens.putback(nextChar);
					int num;
					tokens >> num;
					operandStack.push(num);
				}
				else
				{
					op += nextChar;//if the next character is not a number add it to the operator string
					tokens >> nextChar;//read the next character to see if it should be included in the operator

					if (isdigit(nextChar))
					{
						tokens.putback(nextChar);//if the next character is a number, put it back to be added to the operand stack
					}
					else
					{
						op += nextChar;//if it isn't a number add it to the operator string
					}

					current_precedence = isoperator(operators, precedence, op);//find the precedence of the operator 
					if (current_precedence == 0)//if it can't find the precedence it is because the operator is not included in the list of operators
					{
						cout << "Invalid Character";//output error that the operator is invalid
						system("pause");
					}
					else if (current_precedence < previous_precedence)//if the precedence of the current operator is lower than the operator previous put on the stack
					{
						
						temp = op;//assign the newest operator to a temp variable and process the previous operator and previous two operands
						op = operatorStack.top();
						operatorStack.pop();
						rhs = operandStack.top();
						operandStack.pop();
						lhs = operandStack.top();
						operandStack.pop();
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
				lhs = operandStack.top();
				operandStack.pop();
				op = operatorStack.top();
				int answer = compute(lhs, rhs, op);
				operandStack.push(answer);
				operatorStack.pop();
			}
			return operandStack.top();//once operator stack has been cleared, return the last value in the operand stack
		}


			/*else if (isbool(nextChar))
			{
				char boolian;
				tokens >> boolian;

				if (!boolStack.empty())
				{
					boolStack.push(boolian);
				}
				else
				{
					if (boolian == boolStack.top())
					{
						evaluateBool(boolian);
					}
					else
						throw("Must have consecutive boolian values");
				}*/


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
						cout << "Division by Zero Error";
						system("pause");
						EXIT_FAILURE;
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
					return result = pow(lhs, rhs);
				}
				//more operators need to be added and the logic applied
				//function needs to be passed 0 for the lhs if the operator only takes one operand
		}
	};

#endif
