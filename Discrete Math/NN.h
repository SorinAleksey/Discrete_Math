#ifndef NN_H
#define NN_H

struct NN;

//Данил Ламов
NN* readNN();
void printNN(NN* n);
NN* delNN(NN* n);

//Валерия Веревина
int COM_NN_D(NN* n, NN* m);
NN* ADD_NN_N(NN* n, NN* m);
NN* MUL_Nk_N(NN* n, const unsigned int& k);
NN* DIV_NN_Dk(NN* n, NN* m, const unsigned int& k);

//Анастасия Данченкова
void NZER_N_B(NN* n);
NN* SUB_NN_N(NN* n, NN* m);
NN* MUL_NN_N(NN* n, NN* m);

//Юлия Веселкова
NN* ADD_1N_N(NN* n);
NN* MUL_ND_N(NN* n, const char& num);
NN* SUB_NDN_N(NN* n, NN* m, const char& k);

#endif