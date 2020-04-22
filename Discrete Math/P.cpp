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

/*
	структура данных - многочлен с рациональными коэффициентами
	m - степень многочлена - натуральное число или 0
	с - массив коэффициентов - рациональные числа
*/
struct P {
	unsigned int m = 0;
	vector<Q*> c;
};

//автор: Сорин Алексей
/*
	считывание многочлена с рациональными коэффициентами

	возвращает прочитанный многочлен
*/
P* readP() {
	char ch;
	unsigned int deg;
	P* num = new P();

	(num->c).push_back(new Q());
	//считывание многочлена
	do {
		//добавление элемента в многочлен
		cout << "Введите степень добавляемого элемента: ";
		cin >> deg;
		if (deg > num->m)
		{
			for (unsigned int i = 0; i < deg - num->m - 1; i++)
				(num->c).push_back(new Q());
			num->m = deg;
			//считывание рационального коэффициента
			cout << endl <<  "Введите рациональный коэффициент элемента: " << endl;
			(num->c).push_back(readQ());
		
		}
		else
		{
			//замена элемента
			cout << endl << "Введите рациональный коэффициент элемента: " << endl;
			num->c[deg] = readQ();
		}

		printP(num);

		cout << endl << "Нажмите \'space\', чтобы продолжить";

		ch = _getch();

		system("cls");
	} while (ch != Enter && ch != Esc);
	return num;
}

//автор: Сорин Алексей
/*
	вывод многочлена с рациональными коэффициентами на экран
*/
void printP(P* n) {
	if (n != nullptr)
	{
		cout << "Ваш многочлен: ";
		for (unsigned int i = 0; i <= n->m; i++)
		{
			cout << (n->c[i]->numerator->n > 0 ? (n->c[i]->numerator->sign ? "+" : "-") : "");
			for (int j = n->c[i]->numerator->a.size() - 1; j >= 0; --j)
				if (n->c[i]->numerator->n != 0)
					cout << n->c[i]->numerator->a[j];
			if (n->c[i]->numerator->n != 0)
				cout << '/';
			for (int j = n->c[i]->denominator->a.size() - 1; j >= 0; --j)
				if (n->c[i]->denominator->n != 0)
					cout << n->c[i]->denominator->a[j];
			if (n->c[i]->numerator->n != 0)
			{
				cout << ' ';
				if (i != 0)
					cout << "x^" << i << ' ';
			}
		}
		cout << endl << "Степень многочлена: " << n->m;
	}
	else cout << "Многочлена не существует" << endl;
}

//автор: Сорин Алексей
/*
	удаление многочлена с рациональными коэффициентами из динамической памяти
*/
P* delP(P* n) {
	if (n != nullptr) {
		for (int i = n->m; i >= 0; i--)
		{
			delZ(n->c[i]->numerator);
			delNN(n->c[i]->denominator);
		}
		delete n;
	}
	else cout << "Многочлена не существует." << endl;
	return nullptr;
}
