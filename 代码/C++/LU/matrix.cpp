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
	startElement[(row)*mColumns + column] = val;
}

template<class T>
T CMatrix<T>::Get(int row, int column) const
{
	if (row > mRows || column > mColumns || row < 0 || column < 0)
	{
		printf("Wrong matrix index!");
		return 0.0;
	}
	return startElement[(row)*mColumns + column];
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
	for (int i = 0; i < mRows; i++)
	{
		for (int j = 0; j < mColumns; j++)
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
			result.Set(i, j, val);
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
CVector CMatrix<T>::operator *(const CVector vec)
{
	CMatrix result = *this;
	CVector vecResult(vec.Size());
	for (int i = 0; i < mRows; i++)
	{
		double multiRes = 0;
		for (int j = 0; j < mColumns; j++)
		{
			multiRes += result.Get(i, j)*vec.Get(j);
		}
		vecResult.Set(i, multiRes);
	}
	return vecResult;
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
	/*for (int k = 0; k< N;k++)
	{
		L->Set(k, k, 1);
	}*/

	for (int k = 0; k <N; k++)
	{
		for (int j = k; j<N;j++)
		{
			T U_k_j = mat.Get(k, j);
			T L_j_k = mat.Get(j, k);
			for (int i = 0; i <k; i++)
			{
				U_k_j -= L->Get(k, i)*U->Get(i, j);
			}
			U->Set(k, j, U_k_j);

			for (int i = 0; i < k; i++)
			{
				L_j_k -= L->Get(j, i)*U->Get(i, k);
			}
			L_j_k = L_j_k / U->Get(k, k);
			L->Set(j, k, L_j_k);
			
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


