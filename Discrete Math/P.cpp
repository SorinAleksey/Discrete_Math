#include "Z.h"
#include "NN.h"
#include "Q.h"
#include "P.h"
#include <iostream>
#include <vector>
#include <conio.h>
using namespace std;

constexpr unsigned char Enter = 13, Backspace = 8, Esc = 27;

/*
	структура данных - натуральные числа и ноль
	n - номер младшей позиции
	a - массив символов с чилом
*/
struct NN {
	int n = 0;
	vector<char> a = { '0' };
};

/*
	структура данных - целые числа
	sign - логическая переменная, отвечающая за знак числа: + = true, - = false
	n - номер младшей позиции позиции
	a - массив символов с чилом
*/
struct Z {
	bool sign = true;
	int n = 0;
	vector<char> a = { '0' };
};

/*
	структура данных - рациональные числа
	numerator - числитель - целое число
	denominator - знаменатель - натуральное число
*/
struct Q {
	Z* numerator = new Z();
	NN* denominator = new NN();
};