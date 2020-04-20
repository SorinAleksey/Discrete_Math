#ifndef NN_H
#define NN_H

struct NN;

//����� �����
NN* readNN();
void printNN(NN* n);
NN* delNN(NN* n);

//������� ��������
int COM_NN_D(NN* n, NN* m);
NN* ADD_NN_N(NN* n, NN* m);
NN* MUL_Nk_N(NN* n, const unsigned int& k);
NN* DIV_NN_Dk(NN* n, NN* m, const unsigned int& k);
NN* GCF_NN_N(NN* n, NN* m);

//��������� ����������
void NZER_N_B(NN* n);
NN* SUB_NN_N(NN* n, NN* m);
NN* MUL_NN_N(NN* n, NN* m);
NN* DIV_NN_N(NN* n, NN* m);

//���� ���������
NN* ADD_1N_N(NN* n);
NN* MUL_ND_N(NN* n, const char& num);
NN* SUB_NDN_N(NN* n, NN* m, const char& k);
NN* MOD_NN_N(NN* n, NN* m);
NN* LCM_NN_N(NN* n, NN* m);

#endif