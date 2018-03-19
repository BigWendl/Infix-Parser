namespace INF {
	class Infix {

#include <string>
#include <sstream>
#include <stack>
#include <cctype>
#include <exception>		
		
		
		
	private:
		stack<char> operatorStack;
		stack<int> operandStack;
		
		
		const string operators = "!PDR^*/%+-><GLEN&|";
		const string precedence = "888876665543321";
		int parencount = 0;
		int digitcount = 0;
		int charcount;
		bool lhsnum = false;
		
		
		void buildStacks(string& expression) {
			string temp = "";
			for (string::iterator it = expression.begin(); it != expression.end(); it++) {
				char letter = *it;

				char nextletter = *it++;
				// checks if there's a space between numbers
				if (isdigit(operandStack.top()) && isspace(letter) && isdigit(nextletter)) {
					throw Syntax_Error("Too many spaces between numbers" + charcount);
				}
				//checks for number
				if (isdigit(letter)) {
					
					//checks for entire number before moving on
					while (isdigit(nextletter)) {
						
						letter += nextletter;
						charcount++;
						lhsnum = true;

					}
					operandStack.push(letter);
					
					charcount++;
					lhsnum = true;
					
				}
				//checks for parentheses
				else if (letter == '(' || letter == ')') {
					if (letter == '(') {
						parencount++;
						charcount++;
						
					}
					else {
						parencount--;
						charcount--;
					}
				}
				//checks for operator
				else if (isoperator(letter)) {

					switch(letter) {
					//checks for &&		
					case('&'):{
						if (nextletter == '&') {
							operatorStack.push('&');
							charcount += 2;
							lhsnum = false;
							it++;
						}
						else
							throw Syntax_Error("Not enough & operators" + charcount);
						break;
					}
					//checks for ||
					case('|'): {
						if (nextletter == '|') {
							operatorStack.push('|');
							charcount += 2;
							lhsnum = false;
							it++;
						}
						else
							throw Syntax_Error("Not enough | operators" + charcount);
						break;
					}
					//checks for !, !=		
					case('!'): {
						if (nextletter == '=') {
							operatorStack.push('N');
							charcount += 2;
							lhsnum = false;
							it++;
						}
						else if (isspace(nextletter) || nextletter == '1' || nextletter == '0') {
							operatorStack.push('!');
							charcount++;
							lhsnum = false;
						}
						else
							throw Syntax_Error("Invalid boolean expression" + charcount);
						break;

					}
					//checks for >, >=		
					case('>'): {
						if (nextletter == '=') {
							operatorStack.push('G');
							charcount += 2;
							lhsnum = false;
							it++;
						}
						else if (isspace(nextletter) || isdigit(nextletter)) {
							operatorStack.push('>');
							charcount++;
							lhsnum = false;
						}
						else
							throw Syntax_Error("Invalid boolean expression" + charcount);
						break;
					}
					//checks for <, <=
					case('<'): {
						if (nextletter == '=') {
							operatorStack.push('L');
							charcount += 2;
							lhsnum = false;
							it++;
						}
						else if (isspace(nextletter) || isdigit(nextletter)) {
							operatorStack.push('<');
							charcount++;
							lhsnum = false;
						}
						else
							throw Syntax_Error("Invalid boolean expression" + charcount);
						break;
						}
					//checks for ==		
					case('='): {
						if (nextletter == '=') {
							operatorStack.push('E');
							charcount += 2;
							lhsnum = false;
							it++;
						}
						
						else
							throw Syntax_Error("Invalid boolean expression" + charcount);
						break;
					}

					//checks for +, ++	
					case('+'): {
						if (nextletter == '+') {
							operatorStack.push('P');
							charcount += 2;
							lhsnum = false;
							it++;
						}
						else if (isspace(nextletter) || isdigit(nextletter)) {
							operatorStack.push('+');
							charcount++;
							lhsnum = false;
						}
						else
							throw Syntax_Error("Invalid addition or increment" + charcount);
						break;

					}
					//checks for -,--, or negative expression		
					case('-'): {
						if (nextletter == '-') {
							operatorStack.push('D');
							charcount += 2;
							lhsnum = false;
							it++;
						}

						else if (lhsnum = false) {
							operatorStack.push('R');
							charcount++;
						
						}
						
						else if (isspace(nextletter) || isdigit(nextletter)) {
							operatorStack.push('-');
								charcount++;
								lhsnum = false;
						}
						else
							throw Syntax_Error("Invalid subtraction or decrement" + charcount);
						break;
					}

					}

					
					

				}
				
			}
		}


		bool isoperator(char opo)
		{
			return operators.find(opo) != std::string::npos;
		}
		

		int evaluateOperator(char opo)
		{	
			
		}
		

	public:
		int count = 0;

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
					count++;
				}
				else if (isoperator(nextChar))
				{
					operandStack.push(evaluateOperator(nextChar));
				}
				else if (isbool(nextChar))
				{						
					char boolian;
					tokens >> boolian;

					if (!boolStack.empty())
					{
						boolStack.push(boolian);
						count++;
					}
					else
					{
						if (boolian == boolStack.top())
						{
							evaluateBool(boolian);
						}
						else
							throw("Must have consecutive boolean values at character" + count);
					}





				}
				else if (nextChar == ' ')
				{
					if (tokens >> 

				}
					
			}
		}
		


	};
};
