#include "stdafx.h"
#include "Infix.h"
#include <iostream>
#include <string>
#include <stack>

using namespace std;

int main()
{
	Infix eval;

	eval.evaluate("1+2*3");

	eval.evaluate("2+2^2*3");

	eval.evaluate("1==2");

	eval.evaluate("1+3 > 2");

	eval.evaluate("(4>=4) && 0");

	eval.evaluate("(1+2)*3");

	eval.evaluate("++++2-5*(3^2)");

	cout << endl;
	system("pause");
	return 0;
}
