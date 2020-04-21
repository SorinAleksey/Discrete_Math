#include <iostream>
#include "NN.h"
#include "Z.h"
#include "Q.h"
#include "P.h"
using namespace std;

int main() {
	setlocale(LC_ALL, "ru");
	cout << "Discrete Math" << endl;

	Q* a = readQ(), * b = readQ();
	printQ(DIV_QQ_Q(a, b));

	return 0;
}