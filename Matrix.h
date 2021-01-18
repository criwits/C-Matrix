#ifndef MATRIX_H
#define MATRIX_H

typedef struct
{
	int matHeight;
	int matWidth;
	float** matData;
} MATRIX;

MATRIX matCreate(int height, int width);
void matFree(MATRIX matMatrix);
void matPrint(MATRIX matMatrix);
MATRIX matTranspose(MATRIX matOrigin);
MATRIX matMultiply(MATRIX matA, MATRIX matB);
MATRIX matConvolute(MATRIX matOrigin, MATRIX matConvKernel);
void matMakeRandom(MATRIX* matInput, int randMax);
float matDeterminant(MATRIX matMatrix);

#endif