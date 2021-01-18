#include "Matrix.h"
#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FLOAT_PLACEHOLDER "%5.2f"


MATRIX matCreate(int height, int width)
{
	MATRIX matMatrix;
	matMatrix.matHeight = height;
	matMatrix.matWidth = width;
	matMatrix.matData = (float**)malloc(height * sizeof(float*));
	for (int i = 0; i < height; i++)
	{
		matMatrix.matData[i] = (float*)malloc(width * sizeof(float));
		memset(matMatrix.matData[i], 0, width * sizeof(float));
	}
	errno = 0;
	return matMatrix;
}

void matFree(MATRIX matMatrix)
{
	for (int i = 0; i < matMatrix.matHeight; i++)
	{
		free(matMatrix.matData[i]);
	}
	free(matMatrix.matData);
	errno = 0;
}

void matPrint(MATRIX matMatrix)
{
	for (int i = 0; i < matMatrix.matHeight; i++)
	{
		printf("[ ");
		for (int j = 0; j < matMatrix.matWidth; j++)
		{
			printf(FLOAT_PLACEHOLDER, matMatrix.matData[i][j]);
		}
		printf(" ]\n");
	}
	errno = 0;
}

MATRIX matTranspose(MATRIX matOrigin)
{
	MATRIX matTrans = matCreate(matOrigin.matWidth, matOrigin.matHeight);
	for (int i = 0; i < matOrigin.matHeight; i++)
	{
		for (int j = 0; j < matOrigin.matWidth; j++)
		{
			matTrans.matData[j][i] = matOrigin.matData[i][j];
		}
	}
	errno = 0;
	return matTrans;
}

MATRIX matMultiply(MATRIX matA, MATRIX matB)
{
	if (matA.matWidth != matB.matHeight)
	{
		MATRIX matNull;
		matNull.matHeight = 0;
		matNull.matWidth = 0;
		matNull.matData = NULL;
		errno = 1;
		return matNull;
	}
	MATRIX matAnswer = matCreate(matA.matHeight, matB.matWidth);
	for (int i = 0; i < matAnswer.matHeight; i++)
	{
		for (int j = 0; j < matAnswer.matWidth; j++)
		{
			for (int k = 0; k < matA.matWidth; k++)
			{
				matAnswer.matData[i][j] += matA.matData[i][k] * matB.matData[k][j];
			}
		}
	}
	errno = 0;
	return matAnswer;
}

MATRIX matConvolute(MATRIX matOrigin, MATRIX matConvKernel)
{
	if (!(matConvKernel.matHeight % 2 == 1 && matConvKernel.matWidth % 2 == 1))
	{
		MATRIX matNull;
		matNull.matHeight = 0;
		matNull.matWidth = 0;
		matNull.matData = NULL;
		errno = 1;
		return matNull;
	}
	MATRIX matConvoluted = matCreate(matOrigin.matHeight, matOrigin.matWidth);
	int tempRow, tempColumn;
	for (int i = 0; i < matConvoluted.matHeight; i++)
	{
		for (int j = 0; j < matConvoluted.matWidth; j++)
		{
			for (int k = 0; k < matConvKernel.matHeight; k++)
			{
				for (int l = 0; l < matConvKernel.matWidth; l++)
				{
					tempRow = i - matConvKernel.matHeight / 2 + k;
					tempColumn = j - matConvKernel.matWidth / 2 + l;
					matConvoluted.matData[i][j] += matConvKernel.matData[k][l] * 
						((tempRow >= 0 && tempRow < matOrigin.matHeight && tempColumn >= 0 && tempColumn < matOrigin.matWidth) ? 
						matOrigin.matData[tempRow][tempColumn] : 0);
				}
			}
		}
	}
	errno = 0;
	return matConvoluted;
}

void matMakeRandom(MATRIX* matInput, int randMax)
{
	for (int i = 0; i < matInput->matHeight; i++)
	{
		for (int j = 0; j < matInput->matWidth; j++)
		{
			matInput->matData[i][j] = rand() % randMax;
		}
	}
	errno = 0;
}