#pragma once

#include <list>

using namespace std;

class CalcExpr
{
public:
	CalcExpr();
	~CalcExpr();
	float calcOPZ(list<char>* opz);
private:
	int getFloat(list<char>* l, float* a);
};

