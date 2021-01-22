/* matrix.c - C-Matrix 项目源文件
 * (C) Hans Wan.
 * 遵循 Mozilla Public License 发布。
 */

#include "matrix.h"
#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

// 创建矩阵函数，返回一个指定行数和列数，并且值为 0 的矩阵变量。
MATRIX matCreate(int height, int width)
{
    MATRIX matMatrix;
    matMatrix.matHeight = height;
    matMatrix.matWidth = width;
    matMatrix.matData = (MATRIX_TYPE**)malloc(height * sizeof(MATRIX_TYPE*));
    for (int i = 0; i < height; i++)
    {
        matMatrix.matData[i] = (MATRIX_TYPE*)malloc(width * sizeof(MATRIX_TYPE));
        memset(matMatrix.matData[i], 0, width * sizeof(MATRIX_TYPE));
    }
    errno = 0;
    return matMatrix;
}

// 释放矩阵内存空间函数，会释放指定的矩阵变量中动态数组占用的内存空间，并将原本指向它的指针变成空指针。
void matFree(MATRIX* matMatrix)
{
    for (int i = 0; i < matMatrix->matHeight; i++)
    {
        free(matMatrix->matData[i]);
    }
    free(matMatrix->matData);
    matMatrix->matData = NULL;
    errno = 0;
}

// 打印矩阵函数，以一种可读的方式打印指定的矩阵。
void matPrint(MATRIX matMatrix)
{
    for (int i = 0; i < matMatrix.matHeight; i++)
    {
        printf("[ ");
        for (int j = 0; j < matMatrix.matWidth; j++)
        {
            printf(PRINT_PLACEHOLDER, matMatrix.matData[i][j]);
        }
        printf(" ]\n");
    }
    errno = 0;
}

// 判断一个矩阵是否为 0 矩阵。
int matIsZeroMatrix(MATRIX matOrigin)
{
    for (int i = 0; i < matOrigin.matHeight; i++)
    {
        for (int j = 0; j < matOrigin.matWidth; j++)
        {
            if (fabs(matOrigin.matData[i][j]) > EPS)
            {
                errno = 0;
                return 0;
            }
        }
    }
    errno = 0;
    return 1;
}

// 转置矩阵函数，输入一个矩阵，返回它的转置矩阵。
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

// 矩阵乘积函数，返回 matA 和 matB 的乘积。如果不可乘，返回长宽为 0 的空矩阵。
MATRIX matProduct(MATRIX matA, MATRIX matB)
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

// 矩阵卷积函数，输入原矩阵和卷积核，返回卷积之后的矩阵。其中，对于边界，采取扩展边界用 0 填充的策略。如果卷积核行数或列数非奇数，返回空矩阵。
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
                        ((tempRow >= 0 && tempRow < matOrigin.matHeight&& tempColumn >= 0 && tempColumn < matOrigin.matWidth) ?
                            matOrigin.matData[tempRow][tempColumn] : 0);
                }
            }
        }
    }
    errno = 0;
    return matConvoluted;
}

// 随机化矩阵函数，指定一个矩阵，将它用小于 randMax 的整数填充。仅供测试用。
void matMakeRandom(MATRIX matInput, int randMax)
{
    for (int i = 0; i < matInput.matHeight; i++)
    {
        for (int j = 0; j < matInput.matWidth; j++)
        {
            matInput.matData[i][j] = rand() % randMax;
        }
    }
    errno = 0;
}

// 归并数组函数，配合 mergeSort() 使用，实现归并排序的同时计算数列的逆序数。
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

// 归并排序函数，目的并不是排序，而是算逆序数。
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

// 算数列逆序数的函数，配合上面两个函数使用，实现“求逆序数”过程的封装。
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

// 生成全排列的函数，这是一个递归函数，通过递归方式逐级获得一个数列的每一种排列。
void makePermutation(int* numList, int first, int last, MATRIX_TYPE* tempAnswer, MATRIX matMatrix)
{
    if (first == last)
    {
        MATRIX_TYPE singleAnswer = 1.00;
        singleAnswer *= (getReversedNumber(numList, matMatrix.matWidth) % 2 == 1) ? -1 : 1;
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

// 求行列式的函数，是上面 4 个函数的功能性封装。如果输入的矩阵行列数不相等，返回 0。
MATRIX_TYPE matDeterminant(MATRIX matMatrix)
{
    if (matMatrix.matHeight != matMatrix.matWidth)
    {
        errno = 1;
        return 0;
    }
    int* indexList = (int*)malloc(matMatrix.matHeight * sizeof(int));
    for (int i = 0; i < matMatrix.matHeight; i++)
    {
        indexList[i] = i;
    }
    MATRIX_TYPE answer = 0;
    makePermutation(indexList, 0, matMatrix.matHeight - 1, &answer, matMatrix);
    free(indexList);
    errno = 0;
    return answer;
}

// 求余子式对应矩阵的函数，也就是求一个矩阵去掉某行某列之后的矩阵。如果那一行或者那一列不存在，返回空矩阵。
MATRIX matCominor(MATRIX matOrigin, int row, int column)
{
    if (row < 0 || column < 0 || row >= matOrigin.matHeight || column >= matOrigin.matWidth)
    {
        MATRIX matNull;
        matNull.matHeight = 0;
        matNull.matWidth = 0;
        matNull.matData = NULL;
        errno = 1;
        return matNull;
    }
    MATRIX matCominorMatrix = matCreate(matOrigin.matHeight - 1, matOrigin.matWidth - 1);
    for (int i = 0, k = 0; i < matOrigin.matHeight; i++)
    {
        if (i == row)
        {
            continue;
        }
        for (int j = 0, l = 0; j < matOrigin.matWidth; j++)
        {
            if (j == column)
            {
                continue;
            }
            matCominorMatrix.matData[k][l] = matOrigin.matData[i][j];
            l++;
        }
        k++;
    }
    errno = 0;
    return matCominorMatrix;
}

// 求伴随矩阵的函数。
MATRIX matAdjugate(MATRIX matOrigin)
{
    MATRIX matAdjugateT = matCreate(matOrigin.matHeight, matOrigin.matWidth);
    for (int i = 0; i < matOrigin.matHeight; i++)
    {
        for (int j = 0; j < matOrigin.matWidth; j++)
        {
            MATRIX matTempCominor = matCominor(matOrigin, i, j);
            matAdjugateT.matData[i][j] = ((i + j) % 2 == 1 ? -1 : 1) * matDeterminant(matTempCominor);
            matFree(&matTempCominor);
        }
    }
    errno = 0;
    MATRIX matAdjugate = matTranspose(matAdjugateT);
    matFree(&matAdjugateT);
    return matAdjugate;
}

// 求矩阵数乘。
MATRIX matMultiply(MATRIX matOrigin, MATRIX_TYPE operateNumber)
{
    MATRIX matAnswer = matCreate(matOrigin.matHeight, matOrigin.matWidth);
    for (int i = 0; i < matOrigin.matHeight; i++)
    {
        for (int j = 0; j < matOrigin.matWidth; j++)
        {
            matAnswer.matData[i][j] = matOrigin.matData[i][j] * operateNumber;
        }
    }
    errno = 0;
    return matAnswer;
}

// 求矩阵“数除”。
MATRIX matDivide(MATRIX matOrigin, MATRIX_TYPE operateNumber)
{
    MATRIX matAnswer = matCreate(matOrigin.matHeight, matOrigin.matWidth);
    for (int i = 0; i < matOrigin.matHeight; i++)
    {
        for (int j = 0; j < matOrigin.matWidth; j++)
        {
            matAnswer.matData[i][j] = matOrigin.matData[i][j] / operateNumber;
        }
    }
    errno = 0;
    return matAnswer;
}

// 求逆矩阵，如果行列式为 0，或者矩阵不是方阵，返回空矩阵。
MATRIX matInverse(MATRIX matOrigin)
{
    int det = matDeterminant(matOrigin);
    if (!det)
    {
        MATRIX matNull;
        matNull.matHeight = 0;
        matNull.matWidth = 0;
        matNull.matData = NULL;
        errno = 1;
        return matNull;
    }
    MATRIX matAdjugated = matAdjugate(matOrigin);
    MATRIX matInversed = matDivide(matAdjugated, det);
    matFree(&matAdjugated);
    errno = 0;
    return matInversed;
}

// 求行阶梯型矩阵的辅助函数，是一个递归函数。
void matEchelon(MATRIX matOrigin, int startRow, int startColumn)
{
    if (startRow == matOrigin.matHeight || startColumn == matOrigin.matWidth)
    {
        return;
    }
    int initColumn = startColumn;
    for (int i = startColumn; i < matOrigin.matWidth; i++)
    {
        _Bool flagIsZeroColumn = 1;
        for (int j = startRow; j < matOrigin.matHeight; j++)
        {
            if (fabs(matOrigin.matData[j][i]) > EPS)
            {
                flagIsZeroColumn = 0;
                break;
            }
        }
        if (!flagIsZeroColumn)
        {
            break;
        }
        initColumn++;
    }

    int initRow;
    for (int i = startRow; i < matOrigin.matHeight; i++)
    {
        if (fabs(matOrigin.matData[i][initColumn]) > EPS)
        {
            initRow = i;
            break;
        }
    }

    if (initRow != startRow)
    {
        MATRIX_TYPE exchangeTemp;

        for (int i = initColumn; i < matOrigin.matWidth; i++)
        {
            exchangeTemp = matOrigin.matData[initRow][i];
            matOrigin.matData[initRow][i] = matOrigin.matData[startRow][i];
            matOrigin.matData[startRow][i] = exchangeTemp;
        }
    }

    MATRIX_TYPE ratioTemp;

    for (int i = startRow + 1; i < matOrigin.matHeight; i++)
    {
        ratioTemp = matOrigin.matData[i][initColumn] / matOrigin.matData[startRow][initColumn];
        for (int j = initColumn; j < matOrigin.matWidth; j++)
        {
            matOrigin.matData[i][j] -= matOrigin.matData[startRow][j] * ratioTemp;
        }
    }

    matEchelon(matOrigin, startRow + 1, initColumn + 1);
}

// 求一个矩阵变换成的行阶梯型矩阵的函数。
MATRIX matMakeEchelon(MATRIX matOrigin)
{
    MATRIX matE = matCreate(matOrigin.matHeight, matOrigin.matWidth);
    if (matIsZeroMatrix(matOrigin))
    {
        return matE;
    }
    for (int i = 0; i < matOrigin.matHeight; i++)
    {
        for (int j = 0; j < matOrigin.matWidth; j++)
        {
            matE.matData[i][j] = matOrigin.matData[i][j];
        }
    }

    matEchelon(matE, 0, 0);

    errno = 0;
    return matE;
}

// 求矩阵的秩的函数。
int matRank(MATRIX matMatrix)
{
    MATRIX matE = matMakeEchelon(matMatrix);
    _Bool flagIsZeroRow;
    int i;
    for (i = 0; i < matE.matHeight; i++)
    {
        flagIsZeroRow = 1;
        for (int j = 0; j < matE.matWidth; j++)
        {
            if (fabs(matE.matData[i][j]) > EPS)
            {
                flagIsZeroRow = 0;
                break;
            }
        }
        if (flagIsZeroRow)
        {
            break;
        }
    }
    matFree(&matE);
    errno = 0;
    return i;
}
