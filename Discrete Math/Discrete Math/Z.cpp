#include "Z.h"
#include "NN.h"
#include <iostream>
#include <vector>
#include <conio.h>
using namespace std;

constexpr unsigned char Enter = 13, Backspace = 8, Esc = 27;

/*
	��������� ������
	n - ����� ������� �������
	a - ������ �������� � �����
*/
struct NN {
	int n = 0;
	vector<char> a = { '0' };
};

/*
	��������� ������
	sign - ���������� ����������, ���������� �� ���� �����: + = true, - = false
	n - ����� ������� ������� �������
	a - ������ �������� � �����
*/
struct Z {
	bool sign = true;
	int n = 0;
	vector<char> a = { '0' };
};

//�����: ����� �����
/*
	���������� ������ �����

	��������� ����������� ����� �����
*/
Z* readZ() {
	char ch;
	Z* num = new Z();
	do {
		cout << "���� �����: " << (num->n > 0 ? (num->sign ? "+" : "-") : "");
		for (int i = num->a.size() - 1; i >= 0; --i) cout << num->a[i];
		cout << endl << "���������� ��������: " << num->n << endl;

		ch = _getch();

		//���������� ����� � ����o
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

		//��������� ����� �����
		if (ch == '+' && !num->sign) num->sign = true;
		if (ch == '-' && num->sign) num->sign = false;

		//�������� ����� �� �����
		if (ch == Backspace && num->n > 0) {
			if (num->n == 1) num->a[0] = '0';
			else num->a.erase(num->a.cbegin());
			--num->n;
		}

		system("cls");
	} while (ch != Enter && ch != Esc);
	return num;
}

//�����: ����� �����
/*
	������� ������������ ����� �� �����
*/
void printZ(Z* n) {
	if (n != nullptr) {
		cout << "���� �����: " << (n->n > 0 ? (n->sign ? "+" : "-") : "");
		for (int i = n->a.size() - 1; i >= 0; --i) cout << n->a[i];
		cout << endl << "���������� ��������: " << n->n << endl;
	}
	else cout << "����� �� ����������" << endl;
}

//�����: ����� �����
/*
	�������� ������������ ����� �� ������������ ������
*/
Z* delZ(Z* n) {
	if (n != nullptr) {
		n->a.clear();
		delete n;
		return nullptr;
	}
	else cout << "����� �� ����������." << endl;
}

//Z-1 �����: �������� �����
/*
	���������� �������� �����, ��������� - �����������

	��������� �� ���� ����� �����
*/
NN* ABS_Z_N(Z* n) {
	NN* res = new NN();
	if (n->n == 0) return res;
	res->n = n->n;
	res->a.clear();
	for (int i = 0; i < n->n; ++i) res->a.push_back(n->a[i]);
	return res;
}

//Z-2 �����: ��� �����
/*
	����������� ��������������� ����� (2 - �������������, 0 � ������ ����, 1 - �������������)

	��������� ����� �����
*/
int POZ_Z_D(Z* n) {
	if (n->n == 0) return 0;
	return n->sign ? 2 : 1;
}

//Z-3 �����: ��� �����
/*
	��������� ������ �� (-1)

	��������� �� ���� ����� �����
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

//Z-4 �����: �������� �����
/*
	�������������� ������������ � �����

	��������� ����������� �����
*/
Z* TRANS_N_Z(NN* n) {
	Z* res = new Z();
	if (n->n == 0) return res;
	res->n = n->n;
	res->a.clear();
	for (int i = 0; i < n->n; ++i) res->a.push_back(n->a[i]);
	return res;
}

//Z-5 �����: �������� �����
/*
	�������������� ������ ���������������� � �����������

	�������� �� ���� ����� ����� � ���������� �����������
*/
NN* TRANS_Z_N(Z* n) {
	if (!n->sign) return nullptr;
	NN* res = new NN();
	if (n->n == 0) return res;
	res->n = n->n;
	res->a.clear();
	for (int i = 0; i < n->n; ++i) res->a.push_back(n->a[i]);
	return res;
}

//Z-6 �����: ��� �����
/*
	�������� ����� �����
	������������ �������:
		POZ_Z_D - ����������� ��������������� ����� (2 - �������������, 0 � ������ ����, 1 - �������������)
		ABS_Z_N - ���������� �������� �����, ��������� - �����������
		COM_NN_D - ��������� ����������� �����: 2 - ���� ������ ������ �������, 0, ���� �����, 1 �����
		ADD_NN_N - �������� ����������� �����
		SUB_NN_N - ��������� �� ������� �������� ������������ ����� ������� �������� ��� �������
		MUL_ZM_Z - ��������� ������ �� (-1)
		TRANS_N_Z - �������������� ������������ � �����

	��������� �� ���� 2 ����� �����
*/
Z* ADD_ZZ_Z(Z* n, Z* m) {
	Z* res;
	NN* nNN = ABS_Z_N(n), * mNN = ABS_Z_N(m), * resNN;
	//���� ������ ����� �� ������������
	if (POZ_Z_D(n) != 1) {
		//���� ������ ����� �� ������������
		if (POZ_Z_D(m) != 1) {
			resNN = ADD_NN_N(nNN, mNN);
			res = TRANS_N_Z(resNN);
		}
		//����� ������ ����� ������������
		else {
			//���� ������ ����� �� ������ �������
			if (COM_NN_D(nNN, mNN) != 1) {
				resNN = SUB_NN_N(nNN, mNN);
				res = TRANS_N_Z(resNN);
			}
			//���� ������ ����� ������ �������
			else {
				resNN = SUB_NN_N(mNN, nNN);
				res = TRANS_N_Z(resNN);
				res->sign = false;
			}
		}
	}
	//���� ������ ����� ������������
	else {
		//���� ������ ����� �� ������������
		if (POZ_Z_D(m) != 1) {
			//���� ������ ����� �� ������ �� ������ ������� 
			if (COM_NN_D(mNN, nNN) != 1) {
				resNN = SUB_NN_N(mNN, nNN);
				res = TRANS_N_Z(resNN);
			}
			//���� ������ ����� �� ������ ������ ������� 
			else {
				resNN = SUB_NN_N(nNN, mNN);
				res = TRANS_N_Z(resNN);
				res->sign = false;
			}
		}
		//���� ������ ����� ������������
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

//Z-7 �����: ��������� ���������
/*
	��������� ����� �����
	������������ �������:
		POZ_Z_D - ����������� ��������������� ����� (2 - �������������, 0 � ������ ����, 1 - �������������)
		ABS_Z_N - ���������� �������� �����, ��������� - �����������
		COM_NN_D - ��������� ����������� �����: 2 - ���� ������ ������ �������, 0, ���� �����, 1 �����
		ADD_NN_N - �������� ����������� �����
		SUB_NN_N - ��������� �� ������� �������� ������������ ����� ������� �������� ��� �������
		MUL_ZM_Z - ��������� ������ �� (-1)
		TRANS_N_Z - �������������� ������������ � �����

	��������� �� ���� 2 ����� �����
*/
Z* SUB_ZZ_Z(Z* n, Z* m) {
	Z* res;
	NN* nNN = ABS_Z_N(n), * mNN = ABS_Z_N(m), * resNN;
	//���� ������ ����� �� ������������
	if (POZ_Z_D(n) != 1) {
		//���� ������ ����� �� ������������
		if (POZ_Z_D(m) != 1) {
			//���� ������ ����� �� ������ �������
			if (COM_NN_D(nNN, mNN) != 1) {
				resNN = SUB_NN_N(nNN, mNN);
				res = TRANS_N_Z(resNN);
			}
			//���� ������ ����� ������ �������
			else {
				resNN = SUB_NN_N(mNN, nNN);
				res = TRANS_N_Z(resNN);
				res->sign = false;
			}
		}
		//���� ������ ����� ������������
		else {
			resNN = ADD_NN_N(nNN, mNN);
			res = TRANS_N_Z(resNN);
		}
	}
	//���� ������ ����� ������������
	else {
		//���� ������ ����� �� ������������
		if (POZ_Z_D(m) != 1) {
			resNN = ADD_NN_N(nNN, mNN);
			res = TRANS_N_Z(resNN);
			res->sign = false;
		}
		//���� ������ ����� ������������
		else {
			//���� ������ ����� �� ������ �������
			if (COM_NN_D(nNN, mNN) != 1) {
				resNN = SUB_NN_N(nNN, mNN);
				res = TRANS_N_Z(resNN);
				res->sign = false;
			}
			//���� ������ ����� ������ �������
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

//Z-8 �����: ��������� ���������
/*
	��������� ����� �����
	������������ �������:
		POZ_Z_D - ����������� ��������������� ����� (2 - �������������, 0 � ������ ����, 1 - �������������)
		ABS_Z_N - ���������� �������� �����, ��������� - �����������
		MUL_NN_N - ��������� ����������� �����
		MUL_ZM_Z - ��������� ������ �� (-1)
		TRANS_N_Z - �������������� ������������ � �����

	��������� 2 ����� �����
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

//Z-9 �����: ������� ���
/*
	������� �� ������� �������� ������ ����� �� ������� ��� ������ ����������� � ��������
	(�������� ������� �� ����)
	������������ �������:
		ABS_Z_N - ���������� �������� �����, ��������� - �����������
		POZ_Z_D - ����������� ��������������� ����� (2 - �������������, 0 � ������ ����, 1 - �������������)
		DIV_NN_N - ������� �� ������� �������� ������������ ����� �� ������� ��� ������ 
		MUL_ZM_Z - ��������� ������ �� (-1)

	��������� 2 ����� �����
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

//Z-10 �����: ������� ���
/*
	������� �� ������� �������� ������ ����� �� ������� ��� ������ ����������� � ��������
	(�������� ������� �� ����)
	������������ �������:
		DIV_ZZ_Z - ������� �� ������� �������� ������ ����� �� �������
		MUL_ZZ_Z - ��������� ����� �����
		SUB_ZZ_Z - ��������� ����� �����
		MUL_ZM_Z - ��������� ������ �� (-1)

	��������� 2 ����� �����
*/
Z* MOD_ZZ_Z(Z* n, Z* m) {
	Z* copN = new Z(), * copM = new Z();
	copN->a.erase(copN->a.cbegin());
	copM->a.erase(copM->a.cbegin());
	copN->n = n->n;
	copM->n = m->n;
	for (int i = 0; i < n->n; ++i) copN->a.push_back(n->a[i]);
	for (int i = 0; i < m->n; ++i) copM->a.push_back(m->a[i]);
	//������� �� �������
	Z* temp = DIV_ZZ_Z(copN, copM);
	//����� �����
	Z* temp2 = MUL_ZZ_Z(temp, copM);
	delZ(temp);
	//�������
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