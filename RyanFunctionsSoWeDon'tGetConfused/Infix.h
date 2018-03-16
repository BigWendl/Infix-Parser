namespace INF {
	class Infix {

#include <string>
#include <sstream>
#include <stack>

		using namespace std;
	private:
		stack<char> operatorStack;
		stack<int> operandStack;
		stack<char> boolStack;
		const string operators = "*/%+-";
		const string bools = "|&";

		bool isoperator(char opo)
		{
			return operators.find(opo) != std::string::npos;
		}
		bool isbool(char boolian)
		{
			return bools.find(boolian) != std::string::npos;
		}

		int evaluateOpperator(char opo)
		{
		
		}
		int evaluateBool(char boolian)
		{
		
			//pop bool stack
		}

	public:

		int evaluate(string& expression)
		{
			while (operandStack.empty())
				operandStack.pop();

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
					operandStack.push(evaluateOpperator(nextChar));
				}
				else if (isbool(nextChar))
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
					}





				}
			}
		}


	};
};
