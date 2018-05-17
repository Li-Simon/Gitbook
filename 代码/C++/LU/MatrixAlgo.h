#pragma once
#include "matrix.h"
#include "Vector.h"

CVector SolveLow(CMatrix<double>& mat, CVector& vec);
CVector SolveUpper(CMatrix<double>& mat, CVector& vec);
CVector Solve(CMatrix<double>& mat, CVector& vec);

CVector Solve(CMatrix<double>& mat, CVector& vec)
{
	CVector X(vec.Size());
	CVector Y(vec.Size());
	if (mat.Columns() != mat.Rows() && mat.Rows() != vec.Size())
	{
		printf("Dimension not match!");
		return X;
	}
	CMatrix<double> L(vec.Size(), vec.Size());
	CMatrix<double> U(vec.Size(), vec.Size());
	mat.LU(mat, vec.Size(), &L, &U);
	Y = SolveLow(L, vec);
	cout << "Y\n" << Y;
	X = SolveUpper(U, Y);
	cout << "X\n" << X;
	return X;
}

CVector SolveLow(CMatrix<double>& mat, CVector& vec)
{
	CVector vecRes(vec.Size());
	if (mat.Columns() != mat.Rows() && mat.Rows() != vec.Size())
	{
		printf("Dimension not match!");
		return vecRes;
	}
	double mRes = 0;
	for (int k = 0; k < vec.Size(); k++)
	{
		mRes = vec.Get(k);
		for (int i = 0; i < k - 1; i++)
		{
			mRes -= mat.Get(k, i)*vecRes.Get(i);
		}
		vecRes.Set(k, mRes);
	}
	return vecRes;
}

CVector SolveUpper(CMatrix<double>& mat, CVector& vec)
{
	CVector vecRes(vec.Size());
	if (mat.Columns() != mat.Rows() && mat.Rows() != vec.Size())
	{
		printf("Dimension not match!");
		return vecRes;
	}
	double mRes = 0;
	for (int k = vec.Size() -1; k >=0 ; k--)
	{
		mRes = vec.Get(k);
		for (int i = k+1; i <  vec.Size(); i++)
		{
			mRes -= mat.Get(k, i)*vecRes.Get(i);
		}
		mRes = mRes / mat.Get(k, k);
		vecRes.Set(k, mRes);
	}
	return vecRes;
}