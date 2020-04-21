#ifndef Q_H
#define Q_H

struct NN;
struct Z;
struct Q;

//Данил Ламов
Q* readQ();
void printQ(Q* n);
Q* delQ(Q* n);

//Кравчук Наталья
Q* RED_Q_Q(Q* n);
bool INT_Q_B(Q* n);
Q* TRANS_Z_Q(Z* n);

//Шапарь Илья
Z* TRANS_Q_Z(Q* drob);
Q* ADD_QQ_Q(Q* first, Q* second);
Q* SUB_QQ_Q(Q* first, Q* second);

//Карасов Эмиль
Q* MUL_QQ_Q(Q* first, Q* second);
Q* DIV_QQ_Q(Q* first, Q* second);

#endif