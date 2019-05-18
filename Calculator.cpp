// Calculator.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "Parser.h"
#include <iostream>
#include <list>

using namespace std;

int main()
{
	setlocale(LC_ALL, "Russian");
	Parser p;// = new Parser();
	p.getOPZ();
	while (!p.output.empty()) {
		cout << p.output.front();
		p.output.pop_front();
	}
	system("pause");
	
    return 0;
}

