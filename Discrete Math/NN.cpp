#include <iostream>
#include <vector>
#include <conio.h>
using namespace std;

constexpr unsigned char Enter = 13, Backspace = 8, Esc = 27, Delete = 83, Up = 72, Down = 80, Left = 75, Right = 77;
char ch;

/*
	структура данных
	n - номер младшей позиции позиции
	a - массив символов с чилом
*/
struct NN {
	int n = 0;
	vector<char> a = { '0' };
};

//автор: Данил Ламов
/*
	считывание натурального числа

	возврщает прочитанное натуральное число
*/
NN* readNN() {
	NN* num = new NN();
	do {
		cout << "Ваше число: ";
		for (int i = num->a.size() - 1; i >= 0; --i) cout << num->a[i];
		cout << endl << "Количество символов: " << num->n << endl;

		ch = _getch();

		//добавление цифры в числo
		if (ch >= '0' && ch <= '9') {
			if (num->n == 0 && ch != '0') {
				num->a[0] = ch;
				++num->n;
			}
			else if (num->n != 0){
				num->a.emplace(num->a.cbegin(), ch);
				++num->n;
			}
		}

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
void printNN(NN* n){
	if (n != nullptr) {
		cout << "Ваше число: ";
		for (int i = n->a.size() - 1; i >= 0; --i) cout << n->a[i];
		cout << endl << "Количество символов: " << n->n << endl;
	}
	else cout << "Числа не существует" << endl;
}

//автор: Данил Ламов
/*
	удаление натурального числа из динамической памяти
*/
NN* delNN(NN* n) {
	if (n != nullptr) {
		n->a.clear();
		delete n;
		return nullptr;
	}
	else cout << "Числа не существует." << endl;
}

//N-1 автор: Валерия Веревина
/*
    сравнение натуральных чисел: 2 - если первое больше второго, 0, если равно, 1 иначе

    принимает на вход 2 натуральных числа
*/
int COM_NN_D(NN* n, NN* m) {
	if (n->a.size() > m->a.size()) return 2;
	else if (n->a.size() < m->a.size()) return 1;

	for (int i = n->a.size() - 1; i >= 0; --i) {
		if (n->a[i] > m->a[i]) return 2;
		else if (n->a[i] < m->a[i]) return 1;
	}

	return 0;
}

//N-2 автор: Анастасия Данченкова
/*
	Проверка на ноль: если число не равно нулю, то «да» иначе «нет»

	принимает на вход натуральное число
*/
void NZER_N_B(NN* n) {
	cout << (n->n != 0 ? "Да" : "Нет") << endl;
}

//N-3 автор: Юлия Веселкова
/*
	добавление 1 к натуральному числу

	принимает на вход натурально число
*/
NN* ADD_1N_N(NN* n) {
	for (int i = 0; i < n->a.size(); ++i)
		if (n->a[i] < '9') {
			++n->a[i];
			break;
		}
		else {
			n->a[i] = '0';
			if (i < n->a.size() - 1) {
				++n->a[i + 1];
				if (n->a[i + 1] < '9') break;
			}
			else {
				n->a.push_back('1');
				++n->n;
			}
		}

	return n;
}

//N-4 автор: Валерия Веревина
/*
	сложение натуральных чисел
	при создании использовалась функция COM_NN_D

	принимает на вход 2 натуральных числа
*/
NN* ADD_NN_N(NN* n, NN* m) {
	NN* res = new NN();
	res->a.erase(res->a.begin());
	for (int i = 0; i < (COM_NN_D(n, m) == 2 ? n->n : m->n); ++i) {
		//если существуют разряды у всех 3 элементов
		if (n->n > i && m->n > i && res->n > i)
			//если сумма вссех разрядов меньше 10
			if (n->a[i] + m->a[i] + res->a[i] - 3 * '0' < 10) res->a[i] += n->a[i] + m->a[i] - 2 * '0';
			else {
				++res->n;
				res->a[i] = res->a[i] + n->a[i] + m->a[i] - 2 * '0' - 10;
				res->a.push_back('1');
			}
		//если существуют разряды только у слогаемых
		else if (n->n > i && m->n > i) 
			//если сумма разрядов слогаемых меньше 10
			if (n->a[i] + m->a[i] - 2 * '0' < 10) {
				++res->n;
				res->a.push_back(n->a[i] + m->a[i] - '0');
			}
			else {
				res->n += 2;
				res->a.push_back(n->a[i] + m->a[i] - '9' - 1);
				res->a.push_back('1');
			}
		//если существуют разряды у одного из двух слогаемых
		else
			//если существует разряд результата
			if (res->n > i)
				//если сумма разрядов меньше 10
				if (res->a[i] + (n->n > m->n ? n->a[i] : m->a[i]) - 2 * '0' < 10) res->a[i] += (n->n > m->n ? n->a[i] : m->a[i]) - '0';
				else {
					++res->n;
					res->a[i] += (n->n > m->n ? n->a[i] : m->a[i]) - '0' - 10;
					res->a.push_back('1');
				}
			else {
				++res->n;
				res->a.push_back(n->n > m->n ? n->a[i] : m->a[i]);
			}
	}

	if (res->a.size() == 0) res->a.push_back('0');

	return res;
}

//N-5 автор: Анастасия Данченкова
/*
	вычитание из первого большего натурального числа второго меньшего или равного
	использует COM_NN_D - сравнение натуральных чисел: 2 - если первое больше второго, 0, если равно, 1 иначе

	принимает на вход 2 натуральных числа
*/
NN* SUB_NN_N(NN* n, NN* m) {
	NN* res = new NN();
	if (COM_NN_D(n, m) == 0) return res;

	res->a.erase(res->a.begin());
	bool swap = false;
	if (COM_NN_D(n, m) == 1) {
		NN* temp = n;
		n = m;
		m = temp;
		swap = true;
	}

	for (int i = 0; i < n->n; ++i) {
		//если существуют разряды вычитаемого
		if (m->n > i) {
			//если существуют разряды в ответе
			if (res->n > i) {
				//если значение разряд уменьшаемого больше значения разряда вычитаемого
				if (n->a[i] > m->a[i]) {
					res->a[i] += n->a[i] - m->a[i] + '0';
				}
				//если значение разряд уменьшаемого меньше или равно значения разряда вычитаемого
				else {
					res->a[i] += n->a[i] + 10 - m->a[i] + '0';
					//занимаем
					int ind = i;
					do {
						//если существуют разряды в ответе
						if (res->n - 1 > ind) {
							--res->a[i];
						}
						//если в ответе нет разрядов
						else {
							++res->n;
							res->a.push_back(-1);
						}
					} while (n->a[++ind] == '0');
				}
			}
			//если разрядов в ответе нет
			else {
				//если значение разряд уменьшаемого больше или равно значения разряда вычитаемого
				if (n->a[i] >= m->a[i]) {
					++res->n;
					res->a.push_back(n->a[i] - m->a[i] + '0');
				}
				//если значение разряд уменьшаемого меньше значения разряда вычитаемого
				else {
					++res->n;
					res->a.push_back(n->a[i] + 10 - m->a[i] + '0');
					//алгоритм занимания
					int ind = i;
					do {
						++res->n;
						res->a.push_back(-1);
					} while (n->a[++ind] == '0');
				}
			}
		}
		//если разрядов вычитаемого не существует 
		else {
			//если существуют разряды в ответе
			if (res->n > i) {
				//res->a[i] = '9' + 1 + res->a[i] + n->a[i] -'0';
				res->a[i] += n->a[i];
				if (res->a[i] == '9' + 1) res->a[i] = '0';
			}
			//если разрядов в ответе не существует
			else {
				++res->n;
				res->a.push_back(n->a[i]);
			}
		}
	}

	//удаление нолей спереди числа
	while (res->a[res->n - 1] == '0') {
		--res->n;
		res->a.erase(res->a.end() - 1);
	}

	if (swap) {
		NN* temp = n;
		n = m;
		m = temp;
	}

	return res;
}

//N-6 автор: Юлия Веселкова
/*
	умножение натурального числа на цифру

	принимает на вход натуральное число и цифру
*/
NN* MUL_ND_N(NN* n, const char& num) {
	NN* res = new NN;
	if (n->n == 0 || num == '0') return res;
	res->a.erase(res->a.begin());

	for (int i = 0; i < n->n; ++i) {
		//если разряд ответа существует
		if (res->n > i) {
			//если произведение меньше 8
			if ((n->a[i] - '0') * (num - '0') < 8) {
				res->a[i] += (n->a[i] - '0') * (num - '0') + '0';
			}
			//если произведение больше 8
			else {
				++res->n;
				res->a.push_back(((n->a[i] - '0') * (num - '0') + res->a[i]) / 10);
				res->a[i] = ((n->a[i] - '0') * (num - '0') + res->a[i]) % 10 + '0';
			}
		}
		//если разряд ответа не существует
		else {
			//если произведение меньше 10
			if ((n->a[i] - '0') * (num - '0') < 10) {
				++res->n;
				res->a.push_back((n->a[i] - '0') * (num - '0') + '0');
			}
			//если произведение больше 10
			else {
				res->n += 2;
				res->a.push_back((n->a[i] - '0') * (num - '0') % 10 + '0');
				res->a.push_back((n->a[i] - '0') * (num - '0') / 10);
			}
		}
	}

	if (res->a[res->n - 1] < '0') res->a[res->n - 1] += '0';

	return res;
}

//N-7 автор: Валерия Веревина
/*
	умножение натурального числа на 10^k

	принимает на вход натурально число и степень в которую оно будет возведено
*/
NN* MUL_Nk_N(NN* n, const unsigned int& k) {
	NN* res = new NN();
	if (n->n == 0) return res;
	res->a.erase(res->a.begin());
	res->n = n->n + k;
	for (int i = 0; i < n->n; ++i) res->a.push_back(n->a[i]);
	for (int i = 0; i < k; ++i) res->a.emplace(res->a.cbegin(), '0');
	return res;
}

//N-8 автор: Анастасия Данченкова
/*
	умножение натуральных чисел
	используеме функции: 
		MUL_ND_N - умножение натурального числа на цифру
		MUL_Nk_N - умножение натурального числа на 10^k
		ADD_NN_N - сложение натуральных чисел

	принимает на вход 2 натуральных числа
*/
NN* MUL_NN_N(NN* n, NN* m) {
	NN* res = new NN();
	if (n->n == 0 || m->n == 0) return res;
	res->a.erase(res->a.begin());

	for (int i = 0; i < n->n; ++i) {
		//умножение натурального числа на цифру
		NN* temp = MUL_ND_N(m, n->a[i]);
		//умножение натурального числа на 10 ^ k
		NN* temp2 = MUL_Nk_N(temp, i);
		delNN(temp);
		//сложение натуральных чисел
		temp = ADD_NN_N(res, temp2);
		delNN(temp2);
		delNN(res);
		res = temp;
	}

	return res;
}

//N-9 автор: Юлия Веселкова
/*
	вычитание из натурального другого натурального, умноженного на цифру для случая
	с неотрицательным результатом
	в случае, если результат выполнения отрицаелен, возвращает нулевой указатель
	используеме функции:
		SUB_NN_N - вычитание из первого большего натурального числа второго меньшего или равного
		MUL_ND_N - умножение натурального числа на цифру
		COM_NN_D - сравнение натуральных чисел: 2 - если первое больше второго, 0, если равно, 1 иначе

	принимает на вход:
		1. натуральное число из которого вычитаем
		2. натуральное число которое вычитаем
		3. коэффициент для второго натурального числа
*/
NN* SUB_NDN_N(NN* n, NN* m, const char& k) {
	NN* res, * m2;
	m2 = MUL_ND_N(m, k);
	//если результат вычитания не отрицателен
	if (COM_NN_D(n, m2) != 1) {
		res = SUB_NN_N(n, m2);
		delNN(m2);
		return res;
	}
	return nullptr;
}

//N-10 автор: Валерия Веревина
/*
	Вычисление первой цифры деления большего натурального на меньшее, домноженное на 10^k,
	где k - номер позиции этой цифры (номер считается с нуля)
	используеме функции:
		MUL_Nk_N - умножение натурального числа на 10^k
		COM_NN_D - сравнение натуральных чисел: 2 - если первое больше второго, 0, если равно, 1 иначе
		SUB_NN_N - вычитание из первого большего натурального числа второго меньшего или равного

	на вход принимаются 2 натуральных числа и положительную степень
*/
NN* DIV_NN_Dk(NN* n, NN* m, const unsigned int& k) {
	NN* res = new NN();
	++res->n;
	bool swap = false;
	if (COM_NN_D(n, m) == 1) {
		swap = true;
		NN* temp = n;
		n = m;
		m = temp;
	}

	//алгоритма нахождения первой цифры от деления
	bool ud = true;
	for (int i = 1; i < m->n + 1; ++i)
		if (n->a[n->n - i] < m->a[m->n - i]) {
			ud = false;
			break;
		}

	NN* temp = new NN();
	temp->a.erase(temp->a.begin());
	//если число подходит по количеству символов
	if (ud) {
		for (int i = 1; i < m->n + 1; ++i) {
			++temp->n;
			temp->a.emplace(temp->a.begin(), n->a[n->n - i]);
		}
	}
	//если число не подходит по количеству символов
	else {
		for (int i = 1; i < m->n + 2; ++i) {
			++temp->n;
			temp->a.emplace(temp->a.begin(), n->a[n->n - i]);
		}
	}

	do {
		++res->a[0];
		NN* temp2 = SUB_NN_N(temp, m);
		delNN(temp);
		temp = temp2;
	} while (COM_NN_D(temp, m) != 1);

	if (swap) {
		NN* temp = n;
		n = m;
		m = temp;
	}

	temp = MUL_Nk_N(res, k);
	delNN(res);
	res = temp;
	return res;
}