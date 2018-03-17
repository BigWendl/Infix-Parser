#include "infix.h"
#include <iostream>
#include <string>

using namespace std;

void main()
{	
	Infix eval;
	string expression;
	int eval_result;

	expression = "1+2*3";
	eval_result = eval.evaluate(expression);
	cout << "1+2*3 = " << eval_result << endl;

	expression = "2+2^2*3";
	eval_result = eval.evaluate(expression);
	cout << "2+2^2*3 = " << eval_result << endl;

	expression = "1==2";
	eval_result = eval.evaluate(expression);
	cout << "1==2 = " << eval_result << endl;

	expression = "1+3 > 2";
	eval_result = eval.evaluate(expression);
	cout << "1+3 > 2 = " << eval_result << endl;
	
	system("pause");
	//return 0;
}
