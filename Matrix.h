#ifndef MATRIX_H
#define MATRIX_H

#define PRINT_PLACEHOLDER "%7.2f "
#define MATRIX_TYPE float
#define EPS 1e-5

typedef struct
{
    int matHeight;
    int matWidth;
    MATRIX_TYPE** matData;
} MATRIX;
/** ���º���������е� MATRIX �������� **/
// �ͷž����ڴ�ռ�
void matFree(MATRIX matMatrix);
// ��ӡ����
void matPrint(MATRIX matMatrix);
// ���������
void matMakeRandom(MATRIX matInput, int randMax);

/** ���º����������� MATRIX ��ĳ��ֵ **/
// �жϾ����Ƿ�Ϊ 0 ����
int matIsZeroMatrix(MATRIX matOrigin);
// ����������
int matRank(MATRIX matMatrix);
// ������������ʽ
MATRIX_TYPE matDeterminant(MATRIX matMatrix);

/** ���º��������һ���µ� MATRIX ���� **/
// ��������
MATRIX matCreate(int height, int width);
// ת�þ���
MATRIX matTranspose(MATRIX matOrigin);
// ����˻�
MATRIX matProduct(MATRIX matA, MATRIX matB);
// ������
MATRIX matConvolute(MATRIX matOrigin, MATRIX matConvKernel);
// ���������ʽ��Ӧ�ľ���
MATRIX matCominor(MATRIX matOrigin, int row, int column);
// ��������
MATRIX matAdjugate(MATRIX matOrigin);
// �������ˣ�����
MATRIX matMultiply(MATRIX matOrigin, MATRIX_TYPE operateNumber);
MATRIX matDivide(MATRIX matOrigin, MATRIX_TYPE operateNumber);
// �������
MATRIX matInverse(MATRIX matOrigin);
// ���н����;���
MATRIX matMakeEchelon(MATRIX matOrigin);

#endif