#ifndef MATRIX_H
#define MATRIX_H

#define PRINT_PLACEHOLDER "%7.2f "
#define MATRIX_TYPE float
#define EPS 1e-5

typedef struct
{
    int matHeight;
    int matWidth;
    MATRIX_TYPE** matData;
} MATRIX;
/** 以下函数针对现有的 MATRIX 变量操作 **/
// 释放矩阵内存空间
void matFree(MATRIX matMatrix);
// 打印矩阵
void matPrint(MATRIX matMatrix);
// 随机化矩阵
void matMakeRandom(MATRIX matInput, int randMax);

/** 以下函数计算现有 MATRIX 的某种值 **/
// 判断矩阵是否为 0 矩阵
int matIsZeroMatrix(MATRIX matOrigin);
// 计算矩阵的秩
int matRank(MATRIX matMatrix);
// 计算矩阵的行列式
MATRIX_TYPE matDeterminant(MATRIX matMatrix);

/** 以下函数计算出一个新的 MATRIX 变量 **/
// 创建矩阵
MATRIX matCreate(int height, int width);
// 转置矩阵
MATRIX matTranspose(MATRIX matOrigin);
// 矩阵乘积
MATRIX matProduct(MATRIX matA, MATRIX matB);
// 矩阵卷积
MATRIX matConvolute(MATRIX matOrigin, MATRIX matConvKernel);
// 求矩阵余子式对应的矩阵
MATRIX matCominor(MATRIX matOrigin, int row, int column);
// 求伴随矩阵
MATRIX matAdjugate(MATRIX matOrigin);
// 矩阵数乘（除）
MATRIX matMultiply(MATRIX matOrigin, MATRIX_TYPE operateNumber);
MATRIX matDivide(MATRIX matOrigin, MATRIX_TYPE operateNumber);
// 求逆矩阵
MATRIX matInverse(MATRIX matOrigin);
// 求行阶梯型矩阵
MATRIX matMakeEchelon(MATRIX matOrigin);

#endif