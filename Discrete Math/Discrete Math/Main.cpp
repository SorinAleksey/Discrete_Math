#include <iostream>
#include "NN.h"
#include "Z.h"
#include "Q.h"
using namespace std;

int main() {
	setlocale(LC_ALL, "ru");
	cout << "Discrete Math" << endl;

	Q* a = readQ(), * b = readQ();
	printQ(SUB_QQ_Q(a, b));

	return 0;
}