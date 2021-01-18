#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include "Matrix.h"
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

extern int errno;

int main(void)
{
	MATRIX matA, matB;
	matA = matCreate(7, 6);
	matB = matCreate(3, 3);
	matMakeRandom(&matA, 5);
	matMakeRandom(&matB, 4);
	matPrint(matA);
	matPrint(matB);

	MATRIX matM;
	matM = matConvolute(matA, matB);
	matPrint(matM);

	matFree(matA);
	matFree(matB);
	matFree(matM);

	return 0;
}