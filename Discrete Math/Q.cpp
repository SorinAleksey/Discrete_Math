#include "Z.h"
#include "NN.h"
#include "Q.h"
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

//автор: Данил Ламов
/*
	считывание рационального числа

	возврщает прочитанное целое число
*/
Q* readQ() {
	char ch;
	Q* num = new Q();

	//считывание числителя
	do {
		cout << "Введите числитель: " << (num->numerator->n > 0 ? (num->numerator->sign ? "+" : "-") : "");
		for (int i = num->numerator->a.size() - 1; i >= 0; --i) cout << num->numerator->a[i];
		cout << endl << "Количество символов: " << num->numerator->n << endl;

		ch = _getch();

		//добавление цифры в числo
		if (ch >= '0' && ch <= '9') {
			if (num->numerator->n == 0 && ch != '0') {
				num->numerator->a[0] = ch;
				++num->numerator->n;
			}
			else if (num->numerator->n != 0) {
				num->numerator->a.emplace(num->numerator->a.cbegin(), ch);
				++num->numerator->n;
			}
		}

		//изменение знака числа
		if (ch == '+' && !num->numerator->sign) num->numerator->sign = true;
		if (ch == '-' && num->numerator->sign) num->numerator->sign = false;

		//удаление цифры из числа
		if (ch == Backspace && num->numerator->n > 0) {
			if (num->numerator->n == 1) num->numerator->a[0] = '0';
			else num->numerator->a.erase(num->numerator->a.cbegin());
			--num->numerator->n;
		}

		system("cls");
	} while (ch != Enter && ch != Esc);

	//если числитель не 0
	if (num->numerator->n != 0) {
		//считывание знаменателя
		do {
			cout << "Введите знаменатель: ";
			for (int i = num->denominator->a.size() - 1; i >= 0; --i) cout << num->denominator->a[i];
			cout << endl << "Количество символов: " << num->denominator->n << endl;

			ch = _getch();

			//добавление цифры в числo
			if (ch >= '0' && ch <= '9') {
				if (num->denominator->n == 0 && ch != '0') {
					num->denominator->a[0] = ch;
					++num->denominator->n;
				}
				else if (num->denominator->n != 0) {
					num->denominator->a.emplace(num->denominator->a.cbegin(), ch);
					++num->denominator->n;
				}
			}

			//удаление цифры из числа
			if (ch == Backspace && num->denominator->n > 0) {
				if (num->denominator->n == 1) num->denominator->a[0] = '0';
				else num->denominator->a.erase(num->denominator->a.cbegin());
				--num->denominator->n;
			}

			if ((ch == Enter || ch == Esc) && num->denominator->n == 0) ch = 0;

			system("cls");
		} while (ch != Enter && ch != Esc);
	}

	return num;
}

//автор: Данил Ламов
/*
	вывод рационального число на экран
*/
void printQ(Q* n) {
	if (n != nullptr) {
		cout << "Ваше число: " << (n->numerator->n > 0 ? (n->numerator->sign ? "+" : "-") : "");
		for (int i = n->numerator->a.size() - 1; i >= 0; --i) cout << n->numerator->a[i];
		cout << '/';
		for (int i = n->denominator->a.size() - 1; i >= 0; --i) cout << n->denominator->a[i];
		cout << endl << "Количество символов в числителе: " << n->numerator->n << endl
			<< "Количество символов в знаменателе: " << n->denominator->n << endl;
	}
	else cout << "Числа не существует" << endl;
}

//автор: Данил Ламов
/*
	удаление натурального числа из динамической памяти
*/
Q* delQ(Q* n) {
	if (n != nullptr) {
		delZ(n->numerator);
		delNN(n->denominator);
		delete n;
	}
	else cout << "Числа не существует." << endl;
	return nullptr;
}