#include "infix.h"
#include <iostream>
#include <string>

using namespace std;

void main()
{
	Infix eval;
	string expression = "1+2*3";
	int eval_result = eval.evaluate(expression);
	cout << "RESULT = " << eval_result << endl;
	system("pause");
	//return 0;
}
