#include "stdafx.h"
#include "Parser.h"
#include <iostream>
#include <list>

using namespace std;


Parser::Parser()
{
}


Parser::~Parser()
{
}

void Parser::getOPZ() {

	cout << "���������: \n";
	cin >> input;
	
	list<char> stack;	//����
	//output.push_back(':');
	int flag = 0;		//���� � ������� ����� �����
	int flagE = 0;
	int i = 0;			//������� ��� ������� ������
	while (i < 256) {
		if (flag == 1)	//���� ���������� ���� "=",
			break;		//�� ��������� �����������
		switch (input[i]) {
		case '+': {		//���� ���������� ����
			if (stack.size() == 0) {
				stack.push_back(input[i]);
			}
			else {
				while (stack.back() == '^') {		//�������� � ����� �������
					output.push_back(stack.back());	//��� ������ ����������� ����������
					stack.pop_back();				//� �������� ������
					if (stack.size() == 0) {
						break;
					}
				}
				if (stack.size() > 0) {
					if ((stack.back() == '*') || (stack.back() == '/')) {
						output.push_back(stack.back());
						stack.pop_back();
					}
				}
				if (stack.size() > 0) {
					if ((stack.back() == '-') || (stack.back() == '+')) {
						output.push_back(stack.back());
						stack.pop_back();
					}
				}
				if (stack.size() > 0) {
					if (stack.back() == '.') {
						output.push_back(stack.back());
						stack.pop_back();
					}
				}
				stack.push_back(input[i]);
			}
			i++;
			break;
		}
		case '-': { //���� ���������� �����
			if ((i == 0) || (input[i-1] == '(')) {	//���� ����� �������
				output.push_back('0');
				output.push_back(' ');
			}
			if (stack.size() == 0) {
				stack.push_back(input[i]);
			}
			else {
				while (stack.back() == '^') {		//�������� � ����� ������� �����������
					output.push_back(stack.back());	//� �������� ������
					stack.pop_back();
					if (stack.size() == 0) {
						break;
					}
				}
				if (stack.size() > 0) {
					if ((stack.back() == '*') || (stack.back() == '/')) {
						output.push_back(stack.back());
						stack.pop_back();
					}
				}
				if (stack.size() > 0) {
					if ((stack.back() == '-') || (stack.back() == '+')) {
						output.push_back(stack.back());
						stack.pop_back();
					}
				}
				if (stack.size() > 0) {
					if (stack.back() == '.') {
						output.push_back(stack.back());
						stack.pop_back();
					}
				}
				stack.push_back(input[i]);
			}
			i++;
			break;
		}
		case '*': { //���� ����������� ���������
			if (stack.size() == 0) {
				stack.push_back(input[i]);
			}
			else {
				while (stack.back() == '^') {   //���� � ����� ���� �������,
					output.push_back(stack.back());
					stack.pop_back();
					if (stack.size() == 0) {
						break;
					}
				}
				if (stack.size() > 0) {
					if ((stack.back() == '*') || (stack.back() == '/')) {	//���� � ����� ���� ��������
						output.push_back(stack.back());						//� �������� ������
						stack.pop_back();
					}
				}
				if (stack.size() > 0) {
					if (stack.back() == '.') {
						output.push_back(stack.back());
						stack.pop_back();
					}
				}
				stack.push_back(input[i]);
			}
			i++;
			break;
		}
		case '/': { //���� ����������� �������
			if (stack.size() == 0) {
				stack.push_back(input[i]);
			}
			else {
				while (stack.back() == '^') {   //���� � ����� ���� �������,
					output.push_back(stack.back());
					stack.pop_back();
					if (stack.size() == 0) {
						break;
					}
				}
				if (stack.size() > 0) {
					if ((stack.back() == '*') || (stack.back() == '/')) { //���� � ����� ���� ��������
						output.push_back(stack.back());                    //� �������� ������
						stack.pop_back();
					}
				}
				if (stack.size() > 0) {
					if (stack.back() == '.') {
						output.push_back(stack.back());
						stack.pop_back();
					}
				}
				stack.push_back(input[i]);
			}
			i++;
			break;
		}
		case '^': { //������ ������� �� � ����
			if (stack.size() > 0) {
				if (stack.back() == '.') {
					output.push_back(stack.back());
					stack.pop_back();
				}
			}
			stack.push_back(input[i]);
			i++;
			break;
		}
		case '(': { //������ ������� �� � ����
			stack.push_back(input[i]);
			i++;
			break;
		}
		case ')': { //���� ����������� ����������� ������,
			while (stack.back() != '(') {    //������������ ���������� �����, ���� �� �������� ����������� ������
				output.push_back(stack.back());
				stack.pop_back();
			}
			stack.pop_back();
			if (stack.size() > 0) {
				if (stack.back() == 's' || stack.back() == 'c' || stack.back() == 't' || stack.back() == 'g' || stack.back() == 'n' || stack.back() == 'x') {
					output.push_back(stack.back());
					stack.pop_back();
				}
			}
			i++;
			break;
		}
		case '.': { //���� ����������� �����
			stack.push_back(input[i]);
			i++;
			break;
		}
		case 'e': {
			if (stack.size() > 0) {
				if (stack.back() == '.') {
					output.push_back(stack.back());
					stack.pop_back();
				}
			}
			if (input[i + 1] == '-' || input[i + 1] == '+') {
				i++;
				stack.push_back('e');
				output.push_back('0');
				output.push_back(' ');
				stack.push_back(input[i]);
				flagE = 1;
			}
			else {
				stack.push_back('x');
				i += 2;
			}
			i++;
			break;
		}
		case 's': { //���� ����������� sin,
			stack.push_back('s');
			i += 3;
			break;
		}
		case 'c': { //���� ����������� cos,
			stack.push_back('c');
			i += 3;
			break;
		}
		case 't': { //���� ����������� tan,
			stack.push_back('t');
			i += 3;
			break;
		}
		case 'l': {	//���� ����������� log/ln,
			if (input[i + 1] == 'o') {
				stack.push_back('g');
				i += 3;
			}
			else {
				stack.push_back('n');
				i += 2;
			}
			break;
		}
		case '=': {		//���� ���������� ���� '='
			flag = 1;	//����������� ���� � �������� ������
			while (stack.size() > 0) {
				output.push_back(stack.back());
				stack.pop_back();
			}
			i++;
			break;
		}
		default: {
			output.push_back(input[i]);
			if ((input[i + 1] == '*') || (input[i + 1] == '/') || (input[i + 1] == '^') || (input[i + 1] == '+') || (input[i + 1] == '-') || (input[i + 1] == 'e') || (input[i + 1] == '=') || (input[i + 1] == '.') || (input[i + 1] == ')') || (input[i + 1] == '(')) {
				output.push_back(' '); //���� ����� �����������, ������ ������
				if (flagE == 1) {
					output.push_back(stack.back());
					stack.pop_back();
					output.push_back(stack.back());
					stack.pop_back();
					flagE = 0;
				}
			}
			i++;
		}
		}
	}
}
