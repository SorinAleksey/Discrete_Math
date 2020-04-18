#include <iostream>
#include <vector>
#include <conio.h>
#include "NN.h"
using namespace std;

constexpr unsigned char Enter = 13, Backspace = 8, Esc = 27;

/*
	структура данных
	sign - логическая переменная, отвечающая за знак числа: + = true, - = false
	n - номер младшей позиции позиции
	a - массив символов с чилом
*/
struct Z {
	bool sign = true;
	int n = 0;
	vector<char> a = { '0' };
};

//автор: Данил Ламов
/*
	считывание целого числа

	возврщает прочитанное целое число
*/
Z* readZ() {
	char ch;
	Z* num = new Z();
	do {
		cout << "Ваше число: " << (num->n > 0 ? (num->sign ? "+" : "-") : "");
		for (int i = num->a.size() - 1; i >= 0; --i) cout << num->a[i];
		cout << endl << "Количество символов: " << num->n << endl;

		ch = _getch();

		//добавление цифры в числo
		if (ch >= '0' && ch <= '9') {
			if (num->n == 0 && ch != '0') {
				num->a[0] = ch;
				++num->n;
			}
			else if (num->n != 0) {
				num->a.emplace(num->a.cbegin(), ch);
				++num->n;
			}
		}

		//изменение знака числа
		if (ch == '+' && !num->sign) num->sign = true;
		if (ch == '-' && num->sign) num->sign = false;

		//удаление цифры из числа
		if (ch == Backspace && num->n > 0) {
			if (num->n == 1) num->a[0] = '0';
			else num->a.erase(num->a.cbegin());
			--num->n;
		}

		system("cls");
	} while (ch != Enter && ch != Esc);
	return num;
}

//автор: Данил Ламов
/*
	выводит натурального число на экран
*/
void printZ(Z* n) {
	if (n != nullptr) {
		cout << "Ваше число: " << (n->n > 0 ? (n->sign ? "+" : "-") : "");
		for (int i = n->a.size() - 1; i >= 0; --i) cout << n->a[i];
		cout << endl << "Количество символов: " << n->n << endl;
	}
	else cout << "Числа не существует" << endl;
}

//автор: Данил Ламов
/*
	удаление натурального числа из динамической памяти
*/
Z* delZ(Z* n) {
	if (n != nullptr) {
		n->a.clear();
		delete n;
		return nullptr;
	}
	else cout << "Числа не существует." << endl;
}