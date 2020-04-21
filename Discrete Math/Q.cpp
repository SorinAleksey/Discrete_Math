#include "Z.h"
#include "NN.h"
#include "Q.h"
#include <iostream>
#include <vector>
#include <conio.h>
using namespace std;

constexpr unsigned char Enter = 13, Backspace = 8, Esc = 27;

/*
	��������� ������ - ����������� ����� � ����
	n - ����� ������� �������
	a - ������ �������� � �����
*/
struct NN {
	int n = 0;
	vector<char> a = { '0' };
};

/*
	��������� ������ - ����� �����
	sign - ���������� ����������, ���������� �� ���� �����: + = true, - = false
	n - ����� ������� ������� �������
	a - ������ �������� � �����
*/
struct Z {
	bool sign = true;
	int n = 0;
	vector<char> a = { '0' };
};

/*
	��������� ������ - ������������ �����
	numerator - ��������� - ����� �����
	denominator - ����������� - ����������� �����
*/
struct Q {
	Z* numerator = new Z();
	NN* denominator = new NN();
};

//�����: ����� �����
/*
	���������� ������������� �����

	��������� ����������� ����� �����
*/
Q* readQ() {
	char ch;
	Q* num = new Q();

	//���������� ���������
	do {
		cout << "������� ���������: " << (num->numerator->n > 0 ? (num->numerator->sign ? "+" : "-") : "");
		for (int i = num->numerator->a.size() - 1; i >= 0; --i) cout << num->numerator->a[i];
		cout << endl << "���������� ��������: " << num->numerator->n << endl;

		ch = _getch();

		//���������� ����� � ����o
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

		//��������� ����� �����
		if (ch == '+' && !num->numerator->sign) num->numerator->sign = true;
		if (ch == '-' && num->numerator->sign) num->numerator->sign = false;

		//�������� ����� �� �����
		if (ch == Backspace && num->numerator->n > 0) {
			if (num->numerator->n == 1) num->numerator->a[0] = '0';
			else num->numerator->a.erase(num->numerator->a.cbegin());
			--num->numerator->n;
		}

		system("cls");
	} while (ch != Enter && ch != Esc);

	//���� ��������� �� 0
	if (num->numerator->n != 0) {
		//���������� �����������
		do {
			cout << "������� �����������: ";
			for (int i = num->denominator->a.size() - 1; i >= 0; --i) cout << num->denominator->a[i];
			cout << endl << "���������� ��������: " << num->denominator->n << endl;

			ch = _getch();

			//���������� ����� � ����o
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

			//�������� ����� �� �����
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

//�����: ����� �����
/*
	����� ������������� ����� �� �����
*/
void printQ(Q* n) {
	if (n != nullptr) {
		cout << "���� �����: " << (n->numerator->n > 0 ? (n->numerator->sign ? "+" : "-") : "");
		for (int i = n->numerator->a.size() - 1; i >= 0; --i) cout << n->numerator->a[i];
		cout << '/';
		for (int i = n->denominator->a.size() - 1; i >= 0; --i) cout << n->denominator->a[i];
		cout << endl << "���������� �������� � ���������: " << n->numerator->n << endl
			<< "���������� �������� � �����������: " << n->denominator->n << endl;
	}
	else cout << "����� �� ����������" << endl;
}

//�����: ����� �����
/*
	�������� ������������� ����� �� ������������ ������
*/
Q* delQ(Q* n) {
	if (n != nullptr) {
		delZ(n->numerator);
		delNN(n->denominator);
		delete n;
	}
	else cout << "����� �� ����������." << endl;
	return nullptr;
}

//Q-1 �����: ������� �������
/*
	���������� �����
	������������ �������:
		ABS_Z_N - ���������� �������� �����, ��������� - �����������
		GCF_NN_N - ��� ����������� �����
		DIV_ZZ_Z - ������� �� ������� �������� ������ ����� �� ������� ��� ������
		DIV_NN_N - ������� �� ������� �������� ������������ ����� �� ������� ��� ������ 

	��������� �� ���� ������������ �����
*/
Q* RED_Q_Q(Q* n) {
	NN* numNN = ABS_Z_N(n->numerator);
	NN* nodNN = GCF_NN_N(numNN, n->denominator);
	Q* res = new Q();
	res->numerator->a.clear();
	Z* nodZ = TRANS_N_Z(nodNN);
	res->numerator = DIV_ZZ_Z(n->numerator, nodZ);
	res->denominator->a.clear();
	res->denominator = DIV_NN_N(n->denominator, nodNN);

	delNN(numNN);
	delNN(nodNN);
	delZ(nodZ);

	return res;
}

//Q-2 �����: ������� �������
/*
	�������� �� �����, ���� ������������ ����� �������� �����, �� ���, ����� ����

	��������� �� ���� ������������ �����
*/
bool INT_Q_B(Q* n){
		Q* m = new Q();

		m->numerator->a.clear();
		m->numerator->sign = n->numerator->sign;
		m->numerator->n = n->numerator->n;
		for (int i = 0; i < n->numerator->n; ++i) m->numerator->a.push_back(n->numerator->a[i]);

		m->denominator->n = n->denominator->n;
		m->denominator->a.clear();
		for (int i = 0; i < n->denominator->n; ++i) m->denominator->a.push_back(n->denominator->a[i]);

		Q* newM = RED_Q_Q(m);
		delQ(m);
		bool f = ((newM->denominator->n == 1) && (newM->denominator->a[0] == '1')) ? true : false;
		delQ(newM);
		return f;
}

//Q-3 �����: ������� �������
/*
	�������������� ������ � �������

	��������� �� ���� ����� �����
*/
Q* TRANS_Z_Q(Z* n) {
	Q* res = new Q;
	
	res->numerator->sign = n->sign;
	res->numerator->n = n->n;
	res->numerator->a.clear();
	for (int i = 0; i < n->n; ++i) res->numerator->a.push_back(n->a[i]);

	res->denominator->n = 1;
	res->denominator->a[0] = '1';

	return res;
}

//Q-4 �����: ������ ����
/*
	�������������� ����� � ����� �����

	��������� �� ���� ������������ �����
*/
Z* TRANS_Q_Z(Q* drob) {
	if (drob->denominator->n == 1 && drob->denominator->a[0] == '1') {
		Z* res = new Z();

		res->sign = drob->numerator->sign;
		res->n = drob->numerator->n;
		res->a.clear();
		for (int i = 0; i < drob->numerator->n; ++i) res->a.push_back(drob->numerator->a[i]);

		return res;
	}
	else return nullptr;
}

//Q-5 �����: ������ ����
/*
	c������� ���� ������
	������������ �������:
		LCM_NN_N - ��� ����������� �����
		MUL_ZZ_Z - ��������� ����� �����
		ADD_ZZ_Z - �������� ����� �����
		DIV_NN_N - ������� �� ������� �������� ������������ ����� �� ������� ��� ������
		TRANS_N_Z - �������������� ������������ � �����

	�� ���� ��� ��������� �� �����
*/
Q* ADD_QQ_Q(Q* first, Q* second) {
	Q* res = new Q();
	res->denominator->a.clear();
	NN* nok = LCM_NN_N(first->denominator, second->denominator);

	res->denominator->n = nok->n;
	res->denominator->a.clear();
	for (int i = 0; i < nok->n; ++i) res->denominator->a.push_back(nok->a[i]);

	NN* temp1 = DIV_NN_N(nok, first->denominator);
	Z* temp1Z = TRANS_N_Z(temp1);
	delNN(temp1);
	Z* temp2 = MUL_ZZ_Z(temp1Z, first->numerator);
	delZ(temp1Z);

	temp1 = DIV_NN_N(nok, second->denominator);
	temp1Z = TRANS_N_Z(temp1);
	delNN(temp1);
	Z* temp3 = MUL_ZZ_Z(temp1Z, second->numerator);
	delZ(temp1Z);

	res->numerator->a.clear();
	res->numerator = ADD_ZZ_Z(temp2, temp3);

	delZ(temp2);
	delZ(temp3);

	return res;
}

//Q-6 �����: ������ ����
/*
	��������� ������ ����� �� ������
	������������ �������:
		LCM_NN_N - ��� ����������� �����
		MUL_ZZ_Z - ��������� ����� �����
		SUB_ZZ_Z - ��������� ����� �����
		DIV_NN_N - ������� �� ������� �������� ������������ ����� �� ������� ��� ������
		TRANS_N_Z - �������������� ������������ � �����

	�� ���� ��� ��������� �� �����
*/
Q* SUB_QQ_Q(Q* first, Q* second) {
	Q* res = new Q();
	res->denominator->a.clear();
	NN* nok = LCM_NN_N(first->denominator, second->denominator);

	res->denominator->n = nok->n;
	res->denominator->a.clear();
	for (int i = 0; i < nok->n; ++i) res->denominator->a.push_back(nok->a[i]);

	NN* temp1 = DIV_NN_N(nok, first->denominator);
	Z* temp1Z = TRANS_N_Z(temp1);
	delNN(temp1);
	Z* temp2 = MUL_ZZ_Z(temp1Z, first->numerator);
	delZ(temp1Z);

	temp1 = DIV_NN_N(nok, second->denominator);
	temp1Z = TRANS_N_Z(temp1);
	delNN(temp1);
	Z* temp3 = MUL_ZZ_Z(temp1Z, second->numerator);
	delZ(temp1Z);

	res->numerator->a.clear();
	res->numerator = SUB_ZZ_Z(temp2, temp3);

	delZ(temp2);
	delZ(temp3);

	return res;
}

//Q-7 �����: ������� �����
/*
	��������� ������
	������������ �������:
		MUL_ZZ_Z - ��������� ����� �����
		MUL_NN_N - ��������� ����������� �����

	�� ���� ��� ��������� �� �����
*/
Q* MUL_QQ_Q(Q* first, Q* second) {
	Q* res = new Q();
	res->numerator->a.clear();
	res->denominator->a.clear();
	res->numerator = MUL_ZZ_Z(first->numerator, second->numerator);
	res->denominator = MUL_NN_N(first->denominator, second->denominator);
	return res;
}

//Q-8 �����: ������� �����
/*
	������� ������ (�������� ������� �� ����)
	������������ �������:
		MUL_ZZ_Z - ��������� ����� �����
		TRANS_N_Z - �������������� ������������ � �����
		MUL_NN_N - ��������� ����������� �����
		TRANS_Z_N - �������������� ������ ���������������� � �����������

	�� ���� ��� ��������� �� �����
*/
Q* DIV_QQ_Q(Q* first, Q* second) {
	Q* res = new Q();
	Z* temp = TRANS_N_Z(second->denominator);
	res->numerator->a.clear();
	res->numerator = MUL_ZZ_Z(first->numerator, temp);
	delZ(temp);
	
	res->numerator->sign = first->numerator->sign == second->numerator->sign ? true : false;
	second->numerator->sign = true;

	NN* temp2 = TRANS_Z_N(second->numerator);
	res->denominator->a.clear();
	res->denominator = MUL_NN_N(first->denominator, temp2);
	delNN(temp2);

	return res;
}