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