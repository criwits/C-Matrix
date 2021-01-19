#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include "Matrix.h"
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <time.h>

extern int errno;

int main(void)
{
    srand(time(0));
    //MATRIX matA, matB;
    //matA = matCreate(9, 7);
    //matB = matCreate(3, 3);
    //matMakeRandom(&matA, 5);
    //matMakeRandom(&matB, 4);
    //matPrint(matA);
    //matPrint(matB);

    //MATRIX matM;
    //matM = matConvolute(matA, matB);
    //matPrint(matM);

    //matFree(matA);
    //matFree(matB);
    //matFree(matM);

    MATRIX mat;
    mat = matCreate(3, 3);
    matMakeRandom(&mat, 5);
    matPrint(mat);

    puts("");

    MATRIX matC;
    matC = matInverse(mat);
    matPrint(matC);

    puts("");

    MATRIX matX;
    matX = matProduct(mat, matC);
    matPrint(matX);
    puts("");

    printf(PRINT_PLACEHOLDER, matDeterminant(mat));
    //printf(PRINT_PLACEHOLDER, matDeterminant(matC));
    matFree(mat);
    matFree(matC);
    matFree(matX);

    return 0;
}