#include "stdafx.h"
#include "CalcExpr.h"
#include <iostream>
#include <list>

using namespace std;

CalcExpr::CalcExpr()
{
}


CalcExpr::~CalcExpr()
{
}

float CalcExpr::calcOPZ(list<char>* listOPZ) { //метод, вычисляющий значение арифметической
	switch ((*listOPZ).back()) {				//формулы, используя обратную польскую запись
		case '+': { //если встретился плюс
			(*listOPZ).pop_back();
			float a2 = calcOPZ(listOPZ);
			float a1 = calcOPZ(listOPZ);
			float tmp = a1 + a2;
			return a1 + a2;
		}
		case '-': { //если встретился минус
			(*listOPZ).pop_back();
			float a2 = calcOPZ(listOPZ);
			float a1 = calcOPZ(listOPZ);
			float tmp = a1 - a2;
			return a1 - a2;
		}
		case '*': { //если встретилось умножение
			(*listOPZ).pop_back();
			float a2 = calcOPZ(listOPZ);
			float a1 = calcOPZ(listOPZ);
			float tmp = a1*a2;
			return a1*a2;
		}
		case '/': { //если встретилось деление
			(*listOPZ).pop_back();
			float a2 = calcOPZ(listOPZ);
			float a1 = calcOPZ(listOPZ);
			float tmp = a1 / a2;
			return a1 / a2;
		}
		case '^': { //если встретилась степень
			(*listOPZ).pop_back();
			float a2 = calcOPZ(listOPZ);
			float a1 = calcOPZ(listOPZ);
			float tmp = pow(a1, a2);
			return pow(a1, a2);
		}
		case '.': { //если встретилась точка
			(*listOPZ).pop_back();
			float a2; //= calcOPZ(listOPZ);
			int i = getFloat(listOPZ, &a2);
			float a1 = calcOPZ(listOPZ);
			
			/*while (a2 > i) {
				i *= 10;
			}*/
			return a1 + a2 / pow(10.0f, i/1.0f);
		}
		case 'e': { //если встретилось 'e'
			(*listOPZ).pop_back();
			float a2 = calcOPZ(listOPZ);
			float a1 = calcOPZ(listOPZ);
			return a1 * pow(10.0f, a2);
		}
		case 's': { //если встретилось 's'
			(*listOPZ).pop_back();
			float a1 = calcOPZ(listOPZ);
			return sin(a1);
		}
		case 'c': { //если встретилось 'c'
			(*listOPZ).pop_back();
			float a1 = calcOPZ(listOPZ);
			return cos(a1);
		}
		case 't': { //если встретилось 't'
			(*listOPZ).pop_back();
			float a1 = calcOPZ(listOPZ);
			return tan(a1);
		}
		case 'g': { //если встретилось 'g'
			(*listOPZ).pop_back();
			float a2 = calcOPZ(listOPZ);
			float a1 = calcOPZ(listOPZ);
			return log(a2) / log(a1);
		}
		case 'n': { //если встретилось деление
			(*listOPZ).pop_back();
			float a1 = calcOPZ(listOPZ);
			return log(a1);
		}
		case 'x': { //если встретилось деление
			(*listOPZ).pop_back();
			float a1 = calcOPZ(listOPZ);
			return exp(a1);
		}
		default: { //если встретился разделитель
			(*listOPZ).pop_back();
			int x = static_cast<int>((*listOPZ).back()) - 48; //переводим символ в число
			(*listOPZ).pop_back();
			if ((*listOPZ).size() > 0) {
				while (((*listOPZ).back() != ' ') && ((*listOPZ).back() != '*') && ((*listOPZ).back() != '/') && ((*listOPZ).back() != '^') && ((*listOPZ).back() != '+') && ((*listOPZ).back() != '-') && ((*listOPZ).back() != '.') && ((*listOPZ).back() != 'e') && ((*listOPZ).back() != 's') && ((*listOPZ).back() != 'c') && ((*listOPZ).back() != 't') && ((*listOPZ).back() != 'g') && ((*listOPZ).back() != 'n') && ((*listOPZ).back() != 'x')) {
					x = x + (static_cast<int>((*listOPZ).back()) - 48) * 10; //если число не закончилось, склеиваем его схемой Горнера
					(*listOPZ).pop_back();
					if ((*listOPZ).size() == 0) {
						break;
					}
				}
			}
			float tmp = x / 1.0f;
			return tmp;
		}
	}
}

int CalcExpr::getFloat(list<char>* l, float* a) {
	(*l).pop_back();
	int i = 0;
	int x = static_cast<int>((*l).back()) - 48; //переводим символ в число
	i++;
	(*l).pop_back();
	if ((*l).size() > 0) {
		while (((*l).back() == '0') || ((*l).back() == '1') || ((*l).back() == '2') || ((*l).back() == '3') || ((*l).back() == '4') || ((*l).back() == '5') || ((*l).back() == '6') || ((*l).back() == '7') || ((*l).back() == '8') || ((*l).back() == '9')) {
			x = x + (static_cast<int>((*l).back()) - 48) * 10; //если число не закончилось, склеиваем его схемой Горнера
			i++;
			(*l).pop_back();
			if ((*l).size() == 0) {
				break;
			}
		}
	}
	*a = x / 1.0f;
	return i;
}
