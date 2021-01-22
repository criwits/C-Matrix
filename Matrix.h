/* matrix.h - C-Matrix ��Ŀͷ�ļ�
 * (C) Hans Wan.
 * ��ѭ Mozilla Public License ������
 */

#ifndef MATRIX_H
#define MATRIX_H

// ʹ�� matPrint() ʱ printf �е�ռλ�����뱣�������� MATRIX_TYPE һ��
#define PRINT_PLACEHOLDER "%7.2f "
// ���������ֵ����ͣ�����ʹ�� float ���� double
#define MATRIX_TYPE float
// ���ȷ�Χ
#define EPS 1e-5

// ����ṹ�壬�������������;�����Ķ�άָ�����
typedef struct
{
    int matHeight;
    int matWidth;
    MATRIX_TYPE** matData;
} MATRIX;

/** ���º���������е� MATRIX �������� **/
// �ͷž����ڴ�ռ�
void matFree(MATRIX* matMatrix);
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