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

//�����: ����� �����
/*
	���������� ������������ �����

	��������� ����������� ����������� �����
*/
NN* readNN() {
	char ch;
	NN* num = new NN();
	do {
		cout << "���� �����: ";
		for (int i = num->a.size() - 1; i >= 0; --i) cout << num->a[i];
		cout << endl << "���������� ��������: " << num->n << endl;

		ch = _getch();

		//���������� ����� � ����o
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
void printNN(NN* n){
	if (n != nullptr) {
		cout << "���� �����: ";
		for (int i = n->a.size() - 1; i >= 0; --i) cout << n->a[i];
		cout << endl << "���������� ��������: " << n->n << endl;
	}
	else cout << "����� �� ����������" << endl;
}

//�����: ����� �����
/*
	�������� ������������ ����� �� ������������ ������
*/
NN* delNN(NN* n) {
	if (n != nullptr) {
		n->a.clear();
		delete n;
	}
	else cout << "����� �� ����������." << endl;
	return nullptr;
}

//N-1 �����: ������� ��������
/*
    ��������� ����������� �����: 2 - ���� ������ ������ �������, 0, ���� �����, 1 �����

    ��������� �� ���� 2 ����������� �����
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

//N-2 �����: ��������� ����������
/*
	�������� �� ����: ���� ����� �� ����� ����, �� ��� ����� ����

	��������� �� ���� ����������� �����
*/
void NZER_N_B(NN* n) {
	cout << (n->n != 0 ? "��" : "���") << endl;
}

//N-3 �����: ���� ���������
/*
	���������� 1 � ������������ �����

	��������� �� ���� ���������� �����
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

//N-4 �����: ������� ��������
/*
	�������� ����������� �����
	��� �������� �������������� ������� COM_NN_D

	��������� �� ���� 2 ����������� �����
*/
NN* ADD_NN_N(NN* n, NN* m) {
	NN* res = new NN();
	res->a.erase(res->a.begin());
	for (int i = 0; i < (COM_NN_D(n, m) == 2 ? n->n : m->n); ++i) {
		//���� ���������� ������� � ���� 3 ���������
		if (n->n > i && m->n > i && res->n > i)
			//���� ����� ����� �������� ������ 10
			if (n->a[i] + m->a[i] + res->a[i] - 3 * '0' < 10) res->a[i] += n->a[i] + m->a[i] - 2 * '0';
			else {
				++res->n;
				res->a[i] = res->a[i] + n->a[i] + m->a[i] - 2 * '0' - 10;
				res->a.push_back('1');
			}
		//���� ���������� ������� ������ � ���������
		else if (n->n > i && m->n > i) 
			//���� ����� �������� ��������� ������ 10
			if (n->a[i] + m->a[i] - 2 * '0' < 10) {
				++res->n;
				res->a.push_back(n->a[i] + m->a[i] - '0');
			}
			else {
				res->n += 2;
				res->a.push_back(n->a[i] + m->a[i] - '9' - 1);
				res->a.push_back('1');
			}
		//���� ���������� ������� � ������ �� ���� ���������
		else
			//���� ���������� ������ ����������
			if (res->n > i)
				//���� ����� �������� ������ 10
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

//N-5 �����: ��������� ����������
/*
	��������� �� ������� �������� ������������ ����� ������� �������� ��� �������
	���������� COM_NN_D - ��������� ����������� �����: 2 - ���� ������ ������ �������, 0, ���� �����, 1 �����

	��������� �� ���� 2 ����������� �����
*/
NN* SUB_NN_N(NN* n, NN* m) {
	NN* res = new NN();
	if (COM_NN_D(n, m) == 0) return res;
	if (COM_NN_D(n, m) == 1) return nullptr;

	res->a.erase(res->a.begin());

	/*
	bool swap = false;
	if (COM_NN_D(n, m) == 1) {
		NN* temp = n;
		n = m;
		m = temp;
		swap = true;
	}
	*/

	for (int i = 0; i < n->n; ++i) {
		//���� ���������� ������� �����������
		if (m->n > i) {
			//���� ���������� ������� � ������
			if (res->n > i) {
				//���� �������� ������ ������������ ������ ��� ����� �������� ������� �����������
				if (n->a[i] + (n->a[i] == '0' ? 10 : 0) + res->a[i] >= m->a[i]) {
					//res->a[i] += n->a[i] - m->a[i] + '0';
					res->a[i] += n->a[i] + '9' + 1 - m->a[i];
					if (res->a[i] > '9') res->a[i] -= 10;
				}
				//���� �������� ������ ������������ ������ �������� ������� �����������
				else {
					res->a[i] += n->a[i] + 10 - m->a[i] + '0';
					//if (res->a[i] > '0') res->a[i] -= 10;
					//��������
					int ind = i + 1;
					if (n->n  > ind) {
						do {
							//���� ���������� ������� � ������
							if (res->n > ind) {
								--res->a[ind];
							}
							//���� � ������ ��� ��������
							else {
								++res->n;
								res->a.push_back(-1);
							}
						} while (n->n - 1 > ind && n->a[++ind] == '0');
					}
				}
			}
			//���� �������� � ������ ���
			else {
				//���� �������� ������ ������������ ������ ��� ����� �������� ������� �����������
				if (n->a[i] >= m->a[i]) {
					++res->n;
					res->a.push_back(n->a[i] - m->a[i] + '0');
				}
				//���� �������� ������ ������������ ������ �������� ������� �����������
				else {
					++res->n;
					res->a.push_back(n->a[i] + 10 - m->a[i] + '0');
					//�������� ���������
					int ind = i;
					do {
						++res->n;
						res->a.push_back(-1);
					} while (n->a[++ind] == '0');
				}
			}
		}
		//���� �������� ����������� �� ���������� 
		else {
			//���� ���������� ������� � ������
			if (res->n > i) {
				//res->a[i] = '9' + 1 + res->a[i] + n->a[i] -'0';
				//res->a[i] += n->a[i];
				res->a[i] += n->a[i];
				if (res->a[i] < '0') res->a[i] += 10;
			}
			//���� �������� � ������ �� ����������
			else {
				++res->n;
				res->a.push_back(n->a[i]);
			}
		}
	}

	//�������� ����� ������� �����
	while (res->a[res->n - 1] == '0') {
		--res->n;
		res->a.erase(res->a.end() - 1);
	}

	/*
	if (swap) {
		NN* temp = n;
		n = m;
		m = temp;
	}
	*/

	return res;
}

//N-6 �����: ���� ���������
/*
	��������� ������������ ����� �� �����

	��������� �� ���� ����������� ����� � �����
*/
NN* MUL_ND_N(NN* n, const char& num) {
	NN* res = new NN;
	if (n->n == 0 || num == '0') return res;
	res->a.erase(res->a.begin());

	for (int i = 0; i < n->n; ++i) {
		//���� ������ ������ ����������
		if (res->n > i) {
			//���� ������������ ������ 8
			if ((n->a[i] - '0') * (num - '0') < 8) {
				res->a[i] += (n->a[i] - '0') * (num - '0') + '0';
			}
			//���� ������������ ������ 8
			else {
				++res->n;
				res->a.push_back(((n->a[i] - '0') * (num - '0') + res->a[i]) / 10);
				res->a[i] = ((n->a[i] - '0') * (num - '0') + res->a[i]) % 10 + '0';
			}
		}
		//���� ������ ������ �� ����������
		else {
			//���� ������������ ������ 10
			if ((n->a[i] - '0') * (num - '0') < 10) {
				++res->n;
				res->a.push_back((n->a[i] - '0') * (num - '0') + '0');
			}
			//���� ������������ ������ 10
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

//N-7 �����: ������� ��������
/*
	��������� ������������ ����� �� 10^k

	��������� �� ���� ���������� ����� � ������� � ������� ��� ����� ���������
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

//N-8 �����: ��������� ����������
/*
	��������� ����������� �����
	����������� �������: 
		MUL_ND_N - ��������� ������������ ����� �� �����
		MUL_Nk_N - ��������� ������������ ����� �� 10^k
		ADD_NN_N - �������� ����������� �����

	��������� �� ���� 2 ����������� �����
*/
NN* MUL_NN_N(NN* n, NN* m) {
	NN* res = new NN();
	if (n->n == 0 || m->n == 0) return res;
	res->a.erase(res->a.begin());

	for (int i = 0; i < n->n; ++i) {
		//��������� ������������ ����� �� �����
		NN* temp = MUL_ND_N(m, n->a[i]);
		//��������� ������������ ����� �� 10 ^ k
		NN* temp2 = MUL_Nk_N(temp, i);
		delNN(temp);
		//�������� ����������� �����
		temp = ADD_NN_N(res, temp2);
		delNN(temp2);
		delNN(res);
		res = temp;
	}

	return res;
}

//N-9 �����: ���� ���������
/*
	��������� �� ������������ ������� ������������, ����������� �� ����� ��� ������
	� ��������������� �����������
	� ������, ���� ��������� ���������� ����������, ���������� ������� ���������
	����������� �������:
		SUB_NN_N - ��������� �� ������� �������� ������������ ����� ������� �������� ��� �������
		MUL_ND_N - ��������� ������������ ����� �� �����
		COM_NN_D - ��������� ����������� �����: 2 - ���� ������ ������ �������, 0, ���� �����, 1 �����

	��������� �� ����:
		1. ����������� ����� �� �������� ��������
		2. ����������� ����� ������� ��������
		3. ����������� ��� ������� ������������ �����
*/
NN* SUB_NDN_N(NN* n, NN* m, const char& k) {
	NN* res, * m2;
	m2 = MUL_ND_N(m, k);
	//���� ��������� ��������� �� �����������
	if (COM_NN_D(n, m2) != 1) {
		res = SUB_NN_N(n, m2);
		delNN(m2);
		return res;
	}
	return nullptr;
}

//N-10 �����: ������� ��������
/*
	���������� ������ ����� ������� �������� ������������ �� �������, ����������� �� 10^k,
	��� k - ����� ������� ���� ����� (����� ��������� � ����)
	����������� �������:
		MUL_Nk_N - ��������� ������������ ����� �� 10^k
		COM_NN_D - ��������� ����������� �����: 2 - ���� ������ ������ �������, 0, ���� �����, 1 �����
		SUB_NN_N - ��������� �� ������� �������� ������������ ����� ������� �������� ��� �������

	�� ���� ����������� 2 ����������� ����� � ������������� �������
*/
NN* DIV_NN_Dk(NN* n, NN* m, const unsigned int& k) {
	NN* res = new NN();
	++res->n;

	/*
	bool swap = false;
	if (COM_NN_D(n, m) == 1) {
		swap = true;
		NN* temp = n;
		n = m;
		m = temp;
	}
	*/

	//��������� ���������� ������ ����� �� �������
	bool ud = true;
	for (int i = 1; i < m->n + 1; ++i)
		if (n->a[n->n - i] < m->a[m->n - i]) {
			ud = false;
			break;
		}
		else if (n->a[n->n - i] > m->a[m->n - i]) {
			break;
		}

	NN* temp = new NN();
	temp->a.erase(temp->a.begin());
	//���� ����� �������� �� ���������� ��������
	if (ud) {
		for (int i = 1; i < m->n + 1; ++i) {
			++temp->n;
			temp->a.emplace(temp->a.begin(), n->a[n->n - i]);
		}
	}
	//���� ����� �� �������� �� ���������� ��������
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

	/*
	if (swap) {
		NN* temp = n;
		n = m;
		m = temp;
	}
	*/

	temp = MUL_Nk_N(res, k);
	delNN(res);
	res = temp;
	return res;
}

//N-11 �����: ���������� ���������
/*
	������� �� ������� �������� ������������ ����� �� ������� ��� ������ 
	����������� � ��������(�������� ������� �� ����)
	����������� �������:
		DIV_NN_Dk - ���������� ������ ����� ������� �������� ������������ �� �������, ����������� �� 10^k
		SUB_NDN_N - ��������� �� ������������ ������� ������������, ����������� �� �����
		MUL_Nk_N - ��������� ������������ ����� �� 10^k

	��������� �� ���� 2 �����������  �����
*/
NN* DIV_NN_N(NN* n, NN* m) {
	if (m->n == 0) return nullptr;
	//temp - ����� n
	NN* res = new NN(), * temp = new NN();
	temp->a.erase(temp->a.cbegin());
	temp->n = n->n;
	for (int i = 0; i < n->n; ++i)
		temp->a.push_back(n->a[i]);
	
	bool ud = true;
	for (int i = 1; i < m->n + 1; ++i)
		if (n->a[n->n - i] < m->a[m->n - i]) {
			ud = false;
			break;
		}
		else if (n->a[n->n - i] > m->a[m->n - i]) break;

	//�������� ���������� �������
	int ind = n->n - m->n - (ud ? 0 : 1);
	while (COM_NN_D(temp, m) != 1) {
		//���������� ������ ����� �� ������� ����������� �� ����������� ������
		NN* temp2 = DIV_NN_Dk(temp, m, ind);
		//�������� ������� � �����
		NN* temp3 = ADD_NN_N(res, temp2);
		delNN(res);
		res = temp3;
		//���������� temp
		delNN(temp2);
		//��������� ������������ ����� �� 10^k
		temp2 = MUL_Nk_N(m, ind);
		//��������� ������������ ����� �� ����� � ��������� �� temp
		temp3 = SUB_NDN_N(temp, temp2, res->a[ind]);
		delNN(temp2);
		delNN(temp);
		temp = temp3;
		--ind;
	}

	return res;
}

//N-12 �����: ���� ���������
/*
	������� �� ������� �������� ������������ ����� �� ������� ��� ������ ����������� �
	��������(�������� ������� �� ����)
	������������ �������:
		DIV_NN_N - ������� �� ������� �������� ������������ ����� �� ������� ��� ������
		SUB_NN_N - ��������� �� ������� �������� ������������ ����� ������� �������� ��� �������
		MUL_NN_N - ��������� ����������� �����

	��������� �� ���� 2 ����������� �����:
		n - �������
		m - ��������
*/
NN* MOD_NN_N(NN* n, NN* m) {
	//����� ����� �� ������� 
	NN* temp = DIV_NN_N(n, m);
	//����� ����� �� ������� * ��������
	NN* temp2 = MUL_NN_N(temp, m);
	delNN(temp);
	NN* res = SUB_NN_N(n, temp2);
	delNN(temp2);
	return res;
}

//N-13 �����: ������� ��������
/*
	��� ����������� �����
	������������ �������:
		MOD_NN_N - ������� �� ������� �������� ������������ ����� �� �������
		COM_NN_D - ��������� ����������� �����: 2 - ���� ������ ������ �������, 0, ���� �����, 1 �����
		NZER_N_B - �������� �� ����: ���� ����� �� ����� ����, �� ��� ����� ����

	��������� �� ���� 2 ����������� �����
*/
NN* GCF_NN_N(NN* n, NN* m) {
	NN* copN = new NN(), * copM = new NN();
	copN->a.erase(copN->a.cbegin());
	copM->a.erase(copM->a.cbegin());
	copN->n = n->n;
	copM->n = m->n;
	for (int i = 0; i < n->n; ++i) copN->a.push_back(n->a[i]);
	for (int i = 0; i < m->n; ++i) copM->a.push_back(m->a[i]);

	//�������� ������� 
	while (copN->n > 0 && copM->n > 0) {
		if (COM_NN_D(copN, copM) == 2) {
			NN* temp = MOD_NN_N(copN, copM);
			delNN(copN);
			copN = temp;
		}
		else {
			NN* temp = MOD_NN_N(copM, copN);
			delNN(copM);
			copM = temp;
		}
	}

	NN* res = ADD_NN_N(copN, copM);
	delNN(copN);
	delNN(copM);
	return res;
}

//N-14 �����: ���� ���������
/*
	��� ����������� �����
	������������ �������:
		GCF_NN_N - ��� ����������� �����
		MUL_NN_N - ��������� ����������� �����

	����������� ���� 2 ����������� �����
*/
NN* LCM_NN_N(NN* n, NN* m) {
	//��� (�, b) ��������� �� �������: (a,b)=a*b / ��� (�, b)
	NN* temp = MUL_NN_N(n, m);
	NN* temp2 = GCF_NN_N(n, m);
	NN* res = DIV_NN_N(temp, temp2);
	delNN(temp);
	delNN(temp2);
	return res;
}