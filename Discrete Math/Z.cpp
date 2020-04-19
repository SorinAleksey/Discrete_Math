#include "Z.h"
#include "NN.h"
#include <iostream>
#include <vector>
#include <conio.h>
using namespace std;

constexpr unsigned char Enter = 13, Backspace = 8, Esc = 27;

/*
	структура данных
	n - номер младшей позиции
	a - массив символов с чилом
*/
struct NN {
	int n = 0;
	vector<char> a = { '0' };
};

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

//Z-1 автор: Макарова Ольга
/*
	абсолютная величина числа, результат - натуральное

	принимает на вход целое число
*/
NN* ABS_Z_N(Z* n) {
	NN* res = new NN();
	if (n->n == 0) return res;
	res->a.erase(res->a.cbegin());
	res->n = n->n;
	for (int i = 0; i < n->n; ++i) res->a.push_back(n->a[i]);
	return res;
}

//Z-2 автор: Цой Алина
/*
	Определение положительности числа (2 - положительное, 0 — равное нулю, 1 - отрицательное)

	принимает целое число
*/
int POZ_Z_D(Z* n) {
	if (n->n == 0) return 0;
	return n->sign ? 2 : 1;
}

//Z-3 автор: Цой Алина
/*
	Умножение целого на (-1)

	принимает на вход целое число
*/
Z* MUL_ZM_Z(Z* n) {
	Z* res = new Z();
	if (n->n == 0) return res;
	res->a.erase(res->a.cbegin());
	res->n = n->n;
	for (int i = 0; i < n->n; ++i) res->a.push_back(n->a[i]);
	res->sign = n->sign ? false : true;
	return res;
}

//Z-4 автор: Макарова Ольга
/*
	Преобразование натурального в целое

	принимает натуральное число
*/
Z* TRANS_N_Z(NN* n) {
	Z* res = new Z();
	if (n->n == 0) return res;
	res->a.erase(res->a.cbegin());
	res->n = n->n;
	for (int i = 0; i < n->n; ++i) res->a.push_back(n->a[i]);
	return res;
}

//Z-5 автор: Макарова Ольга
/*
	Преобразование целого неотрицательного в натуральное

	получает на вход целое число и возвращает натуральное
*/
NN* TRANS_Z_N(Z* n) {
	if (n->sign) {
		NN* res = new NN();
		if (n->n == 0) return res;
		res->a.erase(res->a.cbegin());
		res->n = n->n;
		for (int i = 0; i < n->n; ++i) res->a.push_back(n->a[i]);
		return res;
	}
	else return nullptr;
}

//Z-6 автор: Цой Алина
/*
	Сложение целых чисел
	используемые функции:
		POZ_Z_D - определение положительности числа (2 - положительное, 0 — равное нулю, 1 - отрицательное)
		ABS_Z_N - абсолютная величина числа, результат - натуральное
		COM_NN_D - сравнение натуральных чисел: 2 - если первое больше второго, 0, если равно, 1 иначе
		ADD_NN_N - сложение натуральных чисел
		SUB_NN_N - вычитание из первого большего натурального числа второго меньшего или равного
		MUL_ZM_Z - Умножение целого на (-1)
		TRANS_N_Z - Преобразование натурального в целое

	принимает на вход 2 целых числа
*/
Z* ADD_ZZ_Z(Z* n, Z* m) {
	Z* res;
	NN* nNN = ABS_Z_N(n), * mNN = ABS_Z_N(m), * resNN;
	//если первое число не отрицательно
	if (POZ_Z_D(n) != 1) {
		//если второе число не отрицательно
		if (POZ_Z_D(m) != 1) {
			resNN = ADD_NN_N(nNN, mNN);
			res = TRANS_N_Z(resNN);
		}
		//ессли второе число отрицательно
		else {
			//если первое число не меньше второго
			if (COM_NN_D(nNN, mNN) != 1) {
				resNN = SUB_NN_N(nNN, mNN);
				res = TRANS_N_Z(resNN);
			}
			//если первое число меньше второго
			else {
				resNN = SUB_NN_N(mNN, nNN);
				res = TRANS_N_Z(resNN);
				res->sign = false;
			}
		}
	}
	//если первое число отрицательно
	else {
		//если второе число не отрицательно
		if (POZ_Z_D(m) != 1) {
			//если второе число по модулю не меньше первого 
			if (COM_NN_D(mNN, nNN) != 1) {
				resNN = SUB_NN_N(mNN, nNN);
				res = TRANS_N_Z(resNN);
			}
			//если второе число по модулю меньше первого 
			else {
				resNN = SUB_NN_N(nNN, mNN);
				res = TRANS_N_Z(resNN);
				res->sign = false;
			}
		}
		//если второе число отрицательно
		else {
			resNN = ADD_NN_N(nNN, mNN);
			res = TRANS_N_Z(resNN);
			res->sign = false;
		}
	}

	delNN(nNN);
	delNN(mNN);
	delNN(resNN);
	return res;
}

//Z-7 автор: Богданова Екатерина
/*
	Вычитание целых чисел
	используемые функции:
		POZ_Z_D - определение положительности числа (2 - положительное, 0 — равное нулю, 1 - отрицательное)
		ABS_Z_N - абсолютная величина числа, результат - натуральное
		COM_NN_D - сравнение натуральных чисел: 2 - если первое больше второго, 0, если равно, 1 иначе
		ADD_NN_N - сложение натуральных чисел
		SUB_NN_N - вычитание из первого большего натурального числа второго меньшего или равного
		MUL_ZM_Z - умножение целого на (-1)
		TRANS_N_Z - преобразование натурального в целое

	принимает на вход 2 целых числа
*/
Z* SUB_ZZ_Z(Z* n, Z* m) {
	Z* res;
	NN* nNN = ABS_Z_N(n), * mNN = ABS_Z_N(m), * resNN;
	//если первое число не отрицательно
	if (POZ_Z_D(n) != 1) {
		//если второе число не отрицательно
		if (POZ_Z_D(m) != 1) {
			//если перове число не меньше второго
			if (COM_NN_D(nNN, mNN) != 1) {
				resNN = SUB_NN_N(nNN, mNN);
				res = TRANS_N_Z(resNN);
			}
			//если перове число меньше второго
			else {
				resNN = SUB_NN_N(mNN, nNN);
				res = TRANS_N_Z(resNN);
				res->sign = false;
			}
		}
		//если второе число отрицательно
		else {
			resNN = ADD_NN_N(nNN, mNN);
			res = TRANS_N_Z(resNN);
		}
	}
	//если первое число отрицательно
	else {
		//если второе число не отрицательно
		if (POZ_Z_D(m) != 1) {
			resNN = ADD_NN_N(nNN, mNN);
			res = TRANS_N_Z(resNN);
			res->sign = false;
		}
		//если второе число отрицательно
		else {
			//если перове число не меньше второго
			if (COM_NN_D(nNN, mNN) != 1) {
				resNN = SUB_NN_N(nNN, mNN);
				res = TRANS_N_Z(resNN);
				res->sign = false;
			}
			//если перове число меньше второго
			else {
				resNN = SUB_NN_N(mNN, nNN);
				res = TRANS_N_Z(resNN);
			}
		}
	}

	delNN(nNN);
	delNN(mNN);
	delNN(resNN);
	return res;
}

//Z-8 автор: Богданова Екатерина
/*
	Умножение целых чисел
	используемые функции:
		POZ_Z_D - определение положительности числа (2 - положительное, 0 — равное нулю, 1 - отрицательное)
		ABS_Z_N - абсолютная величина числа, результат - натуральное
		MUL_NN_N - умножение натуральных чисел
		MUL_ZM_Z - умножение целого на (-1)
		TRANS_N_Z - преобразование натурального в целое

	принимает 2 целых числа
*/
Z* MUL_ZZ_Z(Z* n, Z* m) {
	NN* nNN = ABS_Z_N(n), * mNN = ABS_Z_N(m), * resNN;
	resNN = MUL_NN_N(nNN, mNN);
	Z* res = TRANS_N_Z(resNN);
	res->sign = ((POZ_Z_D(n) != 1 && POZ_Z_D(m) != 1) || (POZ_Z_D(n) == 1 && POZ_Z_D(m) == 1)) ? true : false;
	delNN(nNN);
	delNN(mNN);
	delNN(resNN);
	return res;
}

//Z-9 автор: Иванова Яна
/*
	Частное от деления большего целого числа на меньшее или равное натуральное с остатком
	(делитель отличен от нуля)
	используемые функции:
		ABS_Z_N - абсолютная величина числа, результат - натуральное
		POZ_Z_D - определение положительности числа (2 - положительное, 0 — равное нулю, 1 - отрицательное)
		DIV_NN_N - частное от деления большего натурального числа на меньшее или равное 
		MUL_ZM_Z - умножение целого на (-1)

	принимает 2 целых числа
*/
Z* DIV_ZZ_Z(Z* n, Z* m) {
	NN* nNN = ABS_Z_N(n), * mNN = ABS_Z_N(m), * resNN;
	resNN = DIV_NN_N(nNN, mNN);
	Z* res = TRANS_N_Z(resNN);
	res->sign = ((POZ_Z_D(n) != 1 && POZ_Z_D(m) != 1) || (POZ_Z_D(n) == 1 && POZ_Z_D(m) == 1)) ? true : false;
	delNN(nNN);
	delNN(mNN);
	delNN(resNN);
	return res;
}

//Z-10 автор: Иванова Яна
/*
	Остаток от деления большего целого числа на меньшее или равное натуральное с остатком
	(делитель отличен от нуля)
	используемые функции:
		DIV_ZZ_Z - частное от деления большего целого числа на меньшее
		MUL_ZZ_Z - умножение целых чисел
		SUB_ZZ_Z - вычитание целых чисел
		MUL_ZM_Z - умножение целого на (-1)

	принимает 2 целых числа
*/
Z* MOD_ZZ_Z(Z* n, Z* m) {
	Z* copN = new Z(), * copM = new Z();
	copN->a.erase(copN->a.cbegin());
	copM->a.erase(copM->a.cbegin());
	copN->n = n->n;
	copM->n = m->n;
	for (int i = 0; i < n->n; ++i) copN->a.push_back(n->a[i]);
	for (int i = 0; i < m->n; ++i) copM->a.push_back(m->a[i]);
	//частное от деления
	Z* temp = DIV_ZZ_Z(copN, copM);
	//целая часть
	Z* temp2 = MUL_ZZ_Z(temp, copM);
	delZ(temp);
	//остаток
	temp = SUB_ZZ_Z(n, temp2);
	delZ(temp2);
	if (!temp->sign) {
		temp2 = ADD_ZZ_Z(temp, copM);
		delZ(temp);
		temp = temp2;
	}
	delZ(copN);
	delZ(copM);
	return temp;
}