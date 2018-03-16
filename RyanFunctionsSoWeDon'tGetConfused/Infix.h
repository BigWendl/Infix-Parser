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
		
		
		const string operators = "+-*/%^";
		const string booleans = "|&=><!";
		int parencount = 0;
		int digitcount = 0;
		int charcount;
		
		void buildStacks(string expression) {
			string temp = "";
			for (string::iterator it = expression.begin(); it != expression.end(); it++) {
				char letter = *it;

				char nextletter = *it++;
				
				if (isdigit(operandStack.top()) && isspace(letter) && isdigit(nextletter)) {
					throw Syntax_Error("Too many spaces between numbers" + charcount);
				}
				if (isdigit(letter)) {
					if (isdigit(nextletter)) {
						int x = 0;
						temp = letter + nextletter;
						stringstream tem(temp);
						tem >> x;
						operandStack.push(x);
						digitcount++;
						charcount++;
						

					}
					operandStack.push(letter);
					digitcount++;
					charcount++;
					
				}
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
				else if (isoperator(letter) || isbool(letter)) {

					switch(letter) {
					case('&'):{
						if (nextletter == '&') {
							operatorStack.push('&');
							charcount += 2;
						}
						else
							throw Syntax_Error("Not enough & operators" + charcount);
						break;
					}
					case('|'): {
						if (nextletter == '|') {
							operatorStack.push('|');
							charcount += 2;
						}
						else
							throw Syntax_Error("Not enough | operators" + charcount);
						break;
					}
					case('!'): {
						if (nextletter == '=') {
							operatorStack.push('n');
							charcount += 2;
						}
						else if (isspace(nextletter) || nextletter == '1' || nextletter == '0') {
							operatorStack.push('!');
							charcount++;
						}
						else
							throw Syntax_Error("Invalid boolean expression" + charcount);
						break;

					}
					case('>'): {
						if (nextletter == '=') {
							operatorStack.push('G');
							charcount += 2;
						}
						else if (isspace(nextletter) || isdigit(nextletter)) {
							operatorStack.push('>');
							charcount++;
						}
						else
							throw Syntax_Error("Invalid boolean expression" + charcount);
						break;
					}
					case('<'): {
						if (nextletter == '=') {
							operatorStack.push('L');
							charcount += 2;
						}
						else if (isspace(nextletter) || isdigit(nextletter)) {
							operatorStack.push('<');
							charcount++;
						}
						else
							throw Syntax_Error("Invalid boolean expression" + charcount);
						break;
						}
					case('='): {
						if (nextletter == '=') {
							operatorStack.push('E');
							charcount += 2;
						}
						else if (isspace(nextletter) || isdigit(nextletter)) {
							operatorStack.push('=');
							charcount++;
						}
						else
							throw Syntax_Error("Invalid boolean expression" + charcount);
						break;
					}

						
					case('+'): {
						if (nextletter == '+') {
							operatorStack.push('P');
							charcount += 2;
						}
						else if (isspace(nextletter) || isdigit(nextletter)) {
							operatorStack.push('+');
								charcount++;
						}
						else
							throw Syntax_Error("Invalid addition or increment" + charcount);
						break;

					}
					case('-'): {
						if (nextletter == '-') {
							operatorStack.push('D');
							charcount += 2;
						}
						else if (isspace(nextletter) || isdigit(nextletter)) {
							operatorStack.push('-');
								charcount++;
						}
						else
							throw Syntax_Error("Invalid addition or increment" + charcount);
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
		bool isbool(char boolean)
		{
			return booleans.find(boolean) != std::string::npos;
		}

		int evaluateOperator(char opo)
		{	
			
		}
		int evaluateBool(char boolean)
		{
			
			//pop bool stack
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
