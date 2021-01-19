#ifndef MATRIX_H
#define MATRIX_H

#define PRINT_PLACEHOLDER "%5.2f "
#define MATRIX_TYPE float

typedef struct
{
	int matHeight;
	int matWidth;
	MATRIX_TYPE** matData;
} MATRIX;

void matFree(MATRIX matMatrix);
void matPrint(MATRIX matMatrix);
void matMakeRandom(MATRIX* matInput, int randMax);

MATRIX matCreate(int height, int width);
MATRIX matTranspose(MATRIX matOrigin);
MATRIX matMultiply(MATRIX matA, MATRIX matB);
MATRIX matConvolute(MATRIX matOrigin, MATRIX matConvKernel);
MATRIX_TYPE matDeterminant(MATRIX matMatrix);
MATRIX matCominor(MATRIX matOrigin, int row, int column);

#endif