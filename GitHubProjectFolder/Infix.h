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
		stack<char> operatorStack;
		stack<int> operandStack;
		stack<char> boolStack;
		int current_precedence = 0, result, lhs, rhs;
		char op;
		const string operators = "*/%+-";
		const int precedence[5] = {6, 6, 6, 5, 5};
		//const string bools = "|&";
		string expression;

		bool isoperator(char opo)
		{
			return operators.find(opo) != std::string::npos;
		}
		/*bool isbool(char boolian)
		{
			return bools.find(boolian) != std::string::npos;
		}*/

		int evaluateOperator(char opo)
		{
			int position = operators.find(opo);
			return precedence[position];
		}
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
			while (tokens >> nextChar)
			{
				if (isdigit(nextChar))
				{
					tokens.putback(nextChar);
					int num;
					tokens >> num;
					operandStack.push(num);
				}
				else if (isoperator(nextChar))
				{
					if (evaluateOperator(nextChar) < current_precedence)
					{
						op = operatorStack.top();
						operatorStack.pop();
						rhs = operandStack.top();
						operandStack.pop();
						lhs = operandStack.top();
						operandStack.pop();
						compute(lhs, rhs, op);
					}
					else
					{
						current_precedence = evaluateOperator(nextChar);
						operatorStack.push(nextChar);
					}
				}
				}
			//after entire string has been processed the stacks are ready to be processed
			while (!operatorStack.empty())
			{
				rhs = operandStack.top();
				operandStack.pop();
				lhs = operandStack.top();
				operandStack.pop();
				op = operatorStack.top();
				compute(lhs, rhs, op);
				
			}
				return operandStack.top();

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

				
		void compute(int lhs, int rhs, char op) 
		{
			switch (op)
			{
			case '+':
				result = lhs + rhs;
				operandStack.push(result);
				operatorStack.pop();
				break;
			case '*':
				result = lhs * rhs;
				operandStack.push(result);
				operatorStack.pop();
				break;
			default:
				break;
			}
			
		}
	};

#endif
//};
