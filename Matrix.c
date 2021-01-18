#include "Matrix.h"
#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FLOAT_PLACEHOLDER "%5.2f "


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

void mergeArray(int* a, int first, int mid, int last, int* count)
{
	int* temp = (int*)malloc((last - first + 1) * sizeof(int));
	int i = first, j = mid + 1, m = mid, n = last, k = 0;
	while (i <= m && j <= n)
	{
		if (a[i] <= a[j])
			temp[k++] = a[i++];
		else
		{
			temp[k++] = a[j++];
			*count += mid - i + 1;
		}
	}
	while (i <= m)
		temp[k++] = a[i++];
	while (j <= n)
		temp[k++] = a[j++];
	for (i = 0; i < k; ++i)
		a[first + i] = temp[i];
	free(temp);
}

void mergeSort(int* a, int first, int last, int* count)
{
	if (first < last)
	{
		int mid = (first + last) / 2;
		mergeSort(a, first, mid, count);
		mergeSort(a, mid + 1, last, count);
		mergeArray(a, first, mid, last, count);
	}
}

int getReversedNumber(const int* numList, int num)
{
	int* tempList = (int*)malloc(num * sizeof(int));
	int reversedNumber = 0;
	for (int i = 0; i < num; i++)
	{
		tempList[i] = numList[i];
	}
	mergeSort(tempList, 0, num - 1, &reversedNumber);
	free(tempList);
	return reversedNumber;
}

void makePermutation(int* numList, int first, int last, float* tempAnswer, MATRIX matMatrix)
{
	if (first == last)
	{
		float singleAnswer = 1.00;
		singleAnswer *= (getReversedNumber(numList, matMatrix.matWidth) % 2 == 1) ? -1.0 : 1.0;
		for (int j = 0; j < matMatrix.matWidth; j++)
		{
			singleAnswer *= matMatrix.matData[j][numList[j]];
		}
		*tempAnswer += singleAnswer;
		return;
	}

	int tempExchange;
	for (int i = first; i <= last; i++)
	{
		tempExchange = numList[first];
		numList[first] = numList[i];
		numList[i] = tempExchange;

		makePermutation(numList, first + 1, last, tempAnswer, matMatrix);

		tempExchange = numList[first];
		numList[first] = numList[i];
		numList[i] = tempExchange;
	}
}

float matDeterminant(MATRIX matMatrix)
{
	if (matMatrix.matHeight != matMatrix.matWidth)
	{
		errno = 1;
		return 0.00;
	}
	int* indexList = (int*)malloc(matMatrix.matHeight * sizeof(int));
	for (int i = 0; i < matMatrix.matHeight; i++)
	{
		indexList[i] = i;
	}
	float answer = 0;
	makePermutation(indexList, 0, matMatrix.matHeight - 1, &answer, matMatrix);
	free(indexList);
	errno = 0;
	return answer;
}