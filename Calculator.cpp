// Calculator.cpp: ���������� ����� ����� ��� ����������� ����������.
//

#include "stdafx.h"
#include "Parser.h"
#include "CalcExpr.h"
#include <iostream>
#include <list>

using namespace std;

int main()
{
	setlocale(LC_ALL, "Russian");
	Parser p;
	CalcExpr ce;
	while (1) {
		p.getOPZ();
		cout << "�����: " << ce.calcOPZ(&(p.output)) << endl;
		p.output.clear();
	}
	system("pause");
	
    return 0;
}

