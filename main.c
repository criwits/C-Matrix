/* һ����ʾ����
 * ������һ�� 6x6 ��������󣬴�ӡ����������������ʽ����ӡ�����н��ݾ��󣬼��������ȡ�
 */
#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include "matrix.h"
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <time.h>

int main(void)
{
    srand(time(0));

    MATRIX mat;
    mat = matCreate(6,6);
    matMakeRandom(mat, 5);

    matPrint(mat);
    printf(PRINT_PLACEHOLDER, matDeterminant(mat));
    puts("");

    MATRIX matE = matMakeEchelon(mat);
    matPrint(matE);
    printf("%d", matRank(mat));

    matFree(&mat);
    matFree(&matE);

    return 0;
}