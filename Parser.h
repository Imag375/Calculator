#pragma once
#include <list>

using namespace std;

class Parser
{
	char input[256];	//������� ������
	
	
public:
	Parser();
	~Parser();
	void getOPZ();
	list<char> output;	//������� ������
};

