# LU分解

任何非奇异方阵都可以分解成上三角阵与下三角阵之积

$$\begin{bmatrix}a_{11}&a_{12}&\cdots&a_{1n}\\ a_{21}&a_{22}&\cdots&a_{2n}\\\cdots&\cdots&\cdots&\cdots\\a_{n1}&a_{n2}&\cdots&a_{nn}\end{bmatrix} = 
\begin{bmatrix}l_{11}&0&\cdots&0\\ l_{21}&l_{22}&\cdots&0\\\cdots&\cdots&\cdots&\cdots\\l_{n1}&l_{n2}&\cdots&l_{nn}\end{bmatrix}*
\begin{bmatrix}u_{11}&u_{12}&\cdots&u_{1n}\\ 0&u_{22}&\cdots&a_{2n}\\\cdots&\cdots&\cdots&\cdots\\0&0&\cdots&u_{nn}\end{bmatrix}$$  
对比两边矩阵的，可以求得：  
但是编程时，行列都是从0开始时，要注意转换。  
第1行：$$a_{1j} = u_{1j}, j = 1, 2,..,n. => u_{1j} = a_{1j}$$。  
第1列：$$a_{j1} = l_{j1}u_{11}, j = 1, 2,..,n. => l_{j1} = a_{j1}/u_{11}$$。  
...。  
第k行：$$a_{kj} = \sum_{i=1}^{i=k} l_{ki}u_{ij}, => u_{kj} = a_{kj} - \sum_{i=1}^{i=k-1} l_{ki}u_{ij}$$。  
第k列：$$a_{jk} = \sum_{i=1}^{i=k} l_{ji}u_{ik}, => u_{jk} = [a_{jk} - \sum_{i=1}^{i=k-1} l_{ji}u_{ik}]/u_{kk}$$。

因为前k-1行的$$u_{ij}$$都已知，前k-1列的$$l_{ij}$$都已知,因此可以求得第k行$$u_{ij}$$，第k列的$$l_{ij}$$。  
问题：得保证$$a_{11}$$非0，以及矩阵非奇异。

# 利用LU分解求线性方程组的解

求解线性方程组 Ax=b相当于求解LUx=b;  
设Y = UX; 因此LY = b;首先求解LY = b,   
$$\begin{bmatrix}l_{11}&0&\cdots&0\\ l_{21}&l_{22}&\cdots&0\\\cdots&\cdots&\cdots&\cdots\\l_{n1}&l_{n2}&\cdots&l_{nn}\end{bmatrix}\begin{bmatrix}y_{1}\\y_{2}\\\cdots&\\y_{n}\end{bmatrix}= 
\begin{bmatrix}b_{1}\\b_{2}\\\cdots&\\b_{n}\end{bmatrix}$$  
求解上面的方程：  
第1行：$$y_{1} = b_{1}$$  
对于第k行：$$b_{k} = \sum_{i=1}^{i=k}l_{ki}y_{i} =>y_{k} = b_{k} - \sum_{i=1}^{i=k-1}l_{ki}y_{i}$$  
求得Y之后，代入Y=UX求得X:  
$$\begin{bmatrix}u_{11}&u_{12}&\cdots&u_{1n}\\ 0&u_{22}&\cdots&a_{2n}\\\cdots&\cdots&\cdots&\cdots\\0&0&\cdots&u_{nn}\end{bmatrix}\begin{bmatrix}x_{1}\\x_{2}\\\cdots&\\x_{n}\end{bmatrix}= 
\begin{bmatrix}y_{1}\\y_{2}\\\cdots&\\y_{n}\end{bmatrix}$$  
对于上三角矩阵，我们从第n行开始求解  
对第n行：$$y_{n} = u_{nn}x_{n} => x_{n} = y_{n}/u_{nn}$$  
...  
对第k行：$$y_{k} = \sum_{i=k}^{i=n}u_{ki}x_{i} => x_{k} = [y_{n}-\sum_{i=k+1}^{i=n}u_{ki}x_{i}]/u_{kk}$$  
这样通过LU分解矩阵就求得了线性方程组的就X.

算法实现如下。

```cpp
#include "stdafx.h"
#include "matrix.h"
#include <iostream>
#include <math.h>
using namespace std;

template<class T>
CMatrix<T>::CMatrix(int rows, int columns) :
    mRows(rows > 0 ? rows : 0),
    mColumns(columns > 0 ? columns : 0),
    startElement(new double[rows*columns])
{
    if (rows <= 0 || columns <= 0)
    {
        printf("At least one of arguments less than 0!");
    }

    int total = mColumns*mRows;
    for (int i = 0; i < total; i++)
    {
        startElement[i] = 0.0;
    }
}

template<class T>
CMatrix<T>::CMatrix(const CMatrix<T> & mat) :
    mRows(mat.mRows),
    mColumns(mat.mColumns),
    startElement(new double[mat.mRows*mat.mColumns])
{
    int total = mColumns*mRows;
    for (int i = 0; i < total; i++)
    {
        startElement[i] = mat.startElement[i];
    }
}

template<class T>
void CMatrix<T>::Set(int row, int column, T val)
{
    if (row > mRows || column > mColumns || row < 0 || column < 0)
    {
        printf("Wrong matrix index!");
    }
    startElement[(row - 1)*mColumns + column + 1] = val;
}

template<class T>
T CMatrix<T>::Get(int row, int column) const
{
    if (row > mRows || column > mColumns || row < 0 || column < 0)
    {
        printf("Wrong matrix index!");
        return 0.0;
    }
    return startElement[(row - 1)*mColumns + column + 1];
}

template<class T>
CMatrix<T> CMatrix<T>::operator +(const CMatrix &mat2)
{
    if (mRows != mat2.mRows || mColumns != mat2.mLength)
    {
        printf("Two matrix are not match, can't add!");
        return *this;
    }
    CMatrix result = *this;
    for (int i = 0; i < mRows; i++)
    {
        for (int j = 0; j < mColumns; j++)
        {
            result.set(i, j, Get(i, j) + mat2.Get(i, j));
        }
    }
    return result;
}

template<class T>
CMatrix<T> CMatrix<T>::operator -(const CMatrix &mat2)
{
    if (mRows != mat2.mRows || mColumns != mat2.mLength)
    {
        printf("Two matrix are not match, can't add!");
        return *this;
    }
    CMatrix result = *this;
    for (int i = 1; i <= mRows; i++)
    {
        for (int j = 1; j <= mColumns; j++)
        {
            result.set(i, j, Get(i, j) - mat2.Get(i, j));
        }
    }
    return result;
}

template<class T>
CMatrix<T> CMatrix<T>::operator *(const CMatrix &mat2)
{
    if (mColumns != mat2.mRows)
    {
        printf("Two matrix are not match, can't add!");
        return *this;
    }
    CMatrix result(mRows, mat2.mColumns);
    for (int i = 0; i < mRows; i++)
    {
        for (int j = 0; j < mColumns; j++)
        {
            T val = 0;
            for (int k = 0; k < mColumns; k++)
            {
                val += Get(i, k)*mat2.Get(k, j);
            }
            result.set(i, j, val);
        }
    }
    return result;
}

template<class T>
CMatrix<T> CMatrix<T>::operator *(const T div)
{
    CMatrix result = *this;
    for (int i = 0; i < mRows; i++)
    {
        for (int j = 0; j < mColumns; j++)
        {
            result.set(i, j, Get(i, j) * div);
        }
    }
    return result;
}

template<class T>
CMatrix<T> CMatrix<T>::operator /(const T div)
{
    CMatrix result = *this;
    if (abs(div) < 0.0000000001)
    {
        printf("Devisor is 0!");
        return result;
    }
    for (int i = 0; i < mRows; i++)
    {
        for (int j = 0; j < mColumns; j++)
        {
            result.set(i, j, Get(i, j) / div);
        }
    }
    return result;
}

template<class T>
CMatrix<T> CMatrix<T>::I(int n)
{
    if (n>0)
    {
        CMatrix mat(n, n);
    }
    else
    {
        printf("NonValid matrix dimension!");
        CMatrix mat(1, 1);
        return mat;
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)        
        {
            if (i == j)
            {
                mat.set(i, j, 1);
            }
            else
            {
                mat.set(i, j, 0);
            }
        }
    }
    return mat;
}

template<class T>
void CMatrix<T>::LU(CMatrix &mat, int N, CMatrix* L, CMatrix* U)
{

    for (int k = 1; k <=N; k++)
    {
        for (int j = k; j<=N;j++)
        {
            T U_k_j = mat.Get(k, j);
            T L_j_k = mat.Get(j, k);
            for (int i = 1; i <=k-1; i++)
            {
                U_k_j -= L->Get(k, i)*U->Get(i, j);
            }
            U->Set(k, j, U_k_j);

            for (int i = 1; i <=k - 1; i++)
            {
                L_j_k -= L->Get(j, i)*U->Get(i, k);
            }
            U_k_j = U_k_j/U->Get(k,k);
            U->Set(k, j, U_k_j);
        }
    }
}

/*template<class T>
void CMatrix::Solve(CMatrix &mat, int dimensionN, T[] b)
{
    CMatrix<T> L(dimensionN, dimensionN);
    CMatrix<T> U(dimensionN, dimensionN);
    LU(CMatrix &mat, int dimensionN, CMatrix* L, CMatrix* U);
}*/
```



