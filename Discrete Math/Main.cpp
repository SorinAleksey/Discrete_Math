#include <iostream>
#include <vector>
#include "NN.h"
using namespace std;

int main() {
	setlocale(LC_ALL, "ru");
	cout << "Discrete Math" << endl;
	NN* a = readNN(), * b = readNN();
	printNN(a);
	printNN(b);
	printNN(SUB_NDN_N(a, b, '2'));
	//printNN(SUB_NN_N(a, b));

	return 0;
}