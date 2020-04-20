#ifndef Z_H
#define Z_H

struct NN;
struct Z;

//Данил Ламов
Z* readZ();
void printZ(Z* n);
Z* delZ(Z* n);

//Макарова Ольга
NN* ABS_Z_N(Z* n);
Z* TRANS_N_Z(NN* n);
NN* TRANS_Z_N(Z* n);

//Цой Алина
int POZ_Z_D(Z* n);
Z* MUL_ZM_Z(Z* n);
Z* ADD_ZZ_Z(Z* n, Z* m);

//Богданова Екатерина
Z* SUB_ZZ_Z(Z* n, Z* m);
Z* MUL_ZZ_Z(Z* n, Z* m);

//Иванова Яна
Z* DIV_ZZ_Z(Z* n, Z* m);
Z* MOD_ZZ_Z(Z* n, Z* m);

#endif