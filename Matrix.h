#ifndef MATRIX_H
#define MATRIX_H

#define PRINT_PLACEHOLDER "%7.2f "
#define MATRIX_TYPE float

//#define PRINT_PLACEHOLDER "%2d "
//#define MATRIX_TYPE int

typedef struct
{
    int matHeight;
    int matWidth;
    MATRIX_TYPE** matData;
} MATRIX;

void matFree(MATRIX matMatrix);
void matPrint(MATRIX matMatrix);
void matMakeRandom(MATRIX* matInput, int randMax);

MATRIX_TYPE matDeterminant(MATRIX matMatrix);

MATRIX matCreate(int height, int width);
MATRIX matTranspose(MATRIX matOrigin);
MATRIX matProduct(MATRIX matA, MATRIX matB);
MATRIX matConvolute(MATRIX matOrigin, MATRIX matConvKernel);
MATRIX matCominor(MATRIX matOrigin, int row, int column);
MATRIX matAdjugate(MATRIX matOrigin);
MATRIX matMultiply(MATRIX matOrigin, MATRIX_TYPE operateNumber);
MATRIX matDivide(MATRIX matOrigin, MATRIX_TYPE operateNumber);
MATRIX matInverse(MATRIX matOrigin);

#endif