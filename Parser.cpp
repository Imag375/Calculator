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

	cout << "Выражение: \n";
	cin >> input;
	
	list<char> stack;	//стек
	//output.push_back(':');
	int flag = 0;		//флаг о встрече знака равно
	int flagE = 0;
	int i = 0;			//счетчик для входной строки
	while (i < 256) {
		if (flag == 1)	//если встретился знак "=",
			break;		//то выражение закончилось
		switch (input[i]) {
		case '+': {		//если встретился плюс
			if (stack.size() == 0) {
				stack.push_back(input[i]);
			}
			else {
				while (stack.back() == '^') {		//операции с более высоким
					output.push_back(stack.back());	//или равным приоритетом отправляем
					stack.pop_back();				//в выходную строку
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
		case '-': { //если встретился минус
			if ((i == 0) || (input[i-1] == '(')) {	//если минус унарный
				output.push_back('0');
				output.push_back(' ');
			}
			if (stack.size() == 0) {
				stack.push_back(input[i]);
			}
			else {
				while (stack.back() == '^') {		//операции с более высоким приоритетом
					output.push_back(stack.back());	//в выходную строку
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
		case '*': { //если встретилось умножение
			if (stack.size() == 0) {
				stack.push_back(input[i]);
			}
			else {
				while (stack.back() == '^') {   //если в стеке есть степень,
					output.push_back(stack.back());
					stack.pop_back();
					if (stack.size() == 0) {
						break;
					}
				}
				if (stack.size() > 0) {
					if ((stack.back() == '*') || (stack.back() == '/')) {	//если в стеке есть операции
						output.push_back(stack.back());						//в выходную строку
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
		case '/': { //если встретилось деление
			if (stack.size() == 0) {
				stack.push_back(input[i]);
			}
			else {
				while (stack.back() == '^') {   //если в стеке есть степень,
					output.push_back(stack.back());
					stack.pop_back();
					if (stack.size() == 0) {
						break;
					}
				}
				if (stack.size() > 0) {
					if ((stack.back() == '*') || (stack.back() == '/')) { //если в стеке есть операции
						output.push_back(stack.back());                    //в выходную строку
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
		case '^': { //просто заносим ее в стек
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
		case '(': { //просто заносим ее в стек
			stack.push_back(input[i]);
			i++;
			break;
		}
		case ')': { //если встретилась закрывающая скобка,
			while (stack.back() != '(') {    //высвобождаем содержимое стека, пока не встретим открывающую скобку
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
		case '.': { //если встретилась точка
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
		case 's': { //если встретилась sin,
			stack.push_back('s');
			i += 3;
			break;
		}
		case 'c': { //если встретилась cos,
			stack.push_back('c');
			i += 3;
			break;
		}
		case 't': { //если встретилась tan,
			stack.push_back('t');
			i += 3;
			break;
		}
		case 'l': {	//если встретилась log/ln,
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
		case '=': {		//если встретился знак '='
			flag = 1;	//освобождаем стек в выходную строку
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
				output.push_back(' '); //если число закончилось, ставим пробел
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
