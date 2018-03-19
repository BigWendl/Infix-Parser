namespace INF {
	class Infix {

#include <string>
#include <sstream>
#include <Stack.h>
#include <cctype>
#include <exception>		
		
		
		
	private:
		stack<char> operatorStack;
		stack<int> operandStack;
		
		
		const string operators = "!PDR^*/%+-><GLEN&|";
		const string precedence = "888876665543321";
		int rhs, lhs, result;
		
		int charcount;
		bool lhsnum = false;

		int Precedence(char op) {
			for (int i = 0; i < 18; i++) {
				if (op == operators[i])
					return precedence[i];
			}

		}
		
		
	public:

		int buildStacks(string& expression) {
			string temp = "";
			for (string::iterator it = expression.begin(); it != expression.end(); it++) {
				char letter = *it;
				char nextletter = *it++;
				int current_precedence = -1, previous_precedence = -1;
				char op = ' ', tempo = ' ';
				
				if (isdigit(operandStack.top()) && isspace(letter) && isdigit(nextletter)) {
					throw Syntax_Error("Too many spaces between numbers at" + charcount );
				}
				if (isdigit(letter)) {
					
					int n = 1;
					while (isdigit(nextletter)) {
						
						letter += nextletter;
						charcount+=n;
						lhsnum = true;
						it++;
						n++;

					}
					
					operandStack.push(letter);
					
					charcount+= n;
					lhsnum = true;
					
				}
				else if (letter == '(') {
					operatorStack.push('(');

				}
				else if (isspace(letter){
					charcount++;
				}
				else if (letter == ')') {
					while (operatorStack.top() != '(' || operatorStack.empty()) {
						rhs = operandStack.pop();
						lhs = operandStack.pop();
						op = operatorStack.pop();

						operandStack.push(compute(op, lhs, rhs));
					}
					operatorStack.pop();
					op = ' ';
					current_precedence = 0;
					previous_precedence = 0;
				}
				else if (current_precedence == -1 {
					throw Syntax_Error("Invalid character at" + charcount);

				}
				else if (current_precedence < previous_precedence) {
					temp = letter;
					letter = operatorStack.pop();
					rhs = operandStack.pop();

					if (!operandStack.empty()) {
						lhs = operandStack.pop();
					}
					else {
						lhs = 0;

						operandStack.push(compute(letter, lhs, rhs));
						operatorStack.push(temp);
						previous_precedence = current_precedence;
						op = ' ';

					}
						
				}
				else if (!isdigit(letter)) 
				{

					switch(letter) 
					{
						case('&'):
						{
						if (nextletter == '&') 
							{
							operatorStack.push('&');
							charcount += 2;
							lhsnum = false;
							it++;
							current_precedence = Precedence('&');
							}
						else
							throw Syntax_Error("Not enough & operators" + charcount);
						break;
						}
					case('|'):
						{
						if (nextletter == '|') {
							operatorStack.push('|');
							charcount += 2;
							lhsnum = false;
							it++;
							current_precedence = Precedence('|');
							}
							else {
							throw Syntax_Error("Not enough | operators" + charcount);
							}
							break;
						}
					case('!'): {
						if (nextletter == '=') {
							operatorStack.push('N');
							charcount += 2;
							lhsnum = false;
							it++;
							current_precedence = Precedence('N');
						}
						else if (isspace(nextletter) || nextletter == '1' || nextletter == '0') {
							operatorStack.push('!');
							charcount++;
							lhsnum = false;
							current_precedence = Precedence('!');
						}
						else
							throw Syntax_Error("Invalid boolean expression" + charcount);
						break;

					}
					case('>'): {
						if (nextletter == '=') {
							operatorStack.push('G');
							charcount += 2;
							lhsnum = false;
							it++;
							current_precedence = Precedence('G');
						}
						else if (isspace(nextletter) || isdigit(nextletter)) {
							operatorStack.push('>');
							charcount++;
							lhsnum = false;
							current_precedence = Precedence('>');
						}
						else
							throw Syntax_Error("Invalid boolean expression" + charcount);
						break;
					}
					case('<'): {
						if (nextletter == '=') {
							operatorStack.push('L');
							charcount += 2;
							lhsnum = false;
							it++;
							current_precedence = Precedence('L');
						}
						else if (isspace(nextletter) || isdigit(nextletter)) {
							operatorStack.push('<');
							charcount++;
							lhsnum = false;
							current_precedence = Precedence('<');
						}
						else
							throw Syntax_Error("Invalid boolean expression" + charcount);
						break;
						}
					case('='): {
						if (nextletter == '=') {
							operatorStack.push('E');
							charcount += 2;
							lhsnum = false;
							it++;
							current_precedence = Precedence('E');
						}
						
						else
							throw Syntax_Error("Invalid boolean expression" + charcount);
						break;
					}

						
					case('+'): {
						if (nextletter == '+') {
							operatorStack.push('P');
							charcount += 2;
							lhsnum = false;
							it++;
							current_precedence = Precedence('P');
						}
						else if (isspace(nextletter) || isdigit(nextletter)) {
							operatorStack.push('+');
							charcount++;
							lhsnum = false;
							current_precedence = Precedence('+');
						}
						else
							throw Syntax_Error("Invalid addition or increment" + charcount);
						break;

					}
					case('-'): {
						if (nextletter == '-') {
							operatorStack.push('D');
							charcount += 2;
							lhsnum = false;
							it++;
							current_precedence = Precedence('D');

						}

						else if (lhsnum = false) {
							operatorStack.push('R');
							charcount++;
							current_precedence = Precedence('R');

						}

						else if (isspace(nextletter) || isdigit(nextletter)) {
							operatorStack.push('-');
							charcount++;
							lhsnum = false;
							current_precedence = Precedence('-');
						}
						else
							throw Syntax_Error("Invalid subtraction or decrement" + charcount);
						break;
					}
					default: 
						throw Syntax_Error("Invalid character" + charcount);
						break;

					

					}

					
					

				}
				
				while (!operatorStack.empty()) {
					rhs = operandStack.pop();
					if (!operandStack.empty()) {
						lhs = operandStack.pop();
					}
					else
						lhs = 0;

					op = operatorStack.pop();

					int answer = compute(lhs, rhs, op);
					operandStack.push(answer);

				}

				result = operandStack.pop();
				if (!operandStack.empty) {
					throw Syntax_Error("Stack should be empty")
					return 0;
				}
				return result;
				
			}
		}

		int compute(char opo, int left, int right)
		{
			int comp;
			switch (opo)
			{
				case('+'): {
					charcount -=2;
					return comp = left + right;
					
				}
				case('-'): {
					charcount -=2;
					return comp = left - right;
					
				}
				case('*'): {
					charcount -=2;
					return comp = left * right;
					
				}
				case('/'): {
					if (right != 0) {
					charcount -=2;	
					return comp = left / right;
						
					}
					else
						throw Syntax_Error("Cannot divide by 0" + charcount);

				}
				case('%'): {
					return comp = left % right;
					charcount -=2;
				}
				case('^'): {
					int origLeft = left;
					while (rhs != 1) {
						left *= origLeft;
						right--;
					}
					charcount -=2;
					return comp = left;
					
				}
				case('P'): {
					operatorStack.push(left);
					charcount -=2;
					return comp = rhs + 1;
				}
				case('D'): {
					operatorStack.push(left);
					charcount -=2;
					return comp = rhs - 1;
				}
				case('R'): {
					operatorStack.push(left);
					charcount--;
					return comp = -1 * rhs;
				}
				case('!'): {
					if (right = 1) {
						charcount--;
						return 0;
					}
					else{
						charcount--;
						return 1;
					}	
				}
				case('>'): {
					if (left > right) {
						charcount-=2;
						return 1;
					}
					else{
						charcount-=2;
						return 0;
					}
				}
				case('<'): {
					if (left < right) {
						charcount-=2;
						return 1;
					}
					else{
						charcount-=2;
						return 0;
					}
				}
				case('G'): {
					if (left >= right) {
						charcount-=3;
						return 1;
					}
					else{
						charcount-=3;
						return 0;
					}	
				}
				case('L'): {
					if (left <= right) {
						charcount-=3;
						return 1;
					}
					else{
						charcount-=3;
						return 0;
					}	
				}
				case('E'): {
					if (left == right) {
						charcount -=3;
						return 1;
					}
					else{
						charcount -=3;
						return 0;
					}

				}
				case('N'): {
					if (left != right) {
						charcount -=3;
						return 1;
					}
					else{
						charcount -=3;
						return 0;
					}
				}
				case('&'): {
					if (left == 1 && right == 0) {
						charcount -=3;
						return 1;
					}
					else{
						charcount -=3;
						return 0;
					}
				}
				case('|'): {
					if (left == 1 || right == 1) {
						charcount -=3;
						return 1;
					}
					else{
						charcount-=3;
						return 0;
					}

				}

			}





		}
	};
};
