#pragma once
#ifndef _MATRIX_H
#define _MATRIX_H
#include <iostream>
#include <algorithm>
#include "Vector.h"
using namespace std;

template<class T>
class CMatrix
{
public:
	CMatrix() {};
	CMatrix(int rows, int columns);
	CMatrix(const CMatrix&);
	~CMatrix() {};
public:
	void Set(int row, int column, T val);
    T Get(int row, int column) const;
	CMatrix operator +(const CMatrix &mat2);
	CMatrix operator -(const CMatrix &mat2);
	CMatrix operator *(const CMatrix &mat2);
	CMatrix operator *(const T div);
	CVector operator *(const CVector vec);
	CMatrix operator /(const T div);
public:
	CMatrix I(int n);
	void LU(CMatrix &mat, int dimensionN, CMatrix* L, CMatrix* U);
	//void Solve(CMatrix &mat, int dimensionN, T[] b);
	//T[] SolveLow(CMatrix &mat, int dimensionN, T[] b);
	//void SolveUpper(CMatrix &mat, int dimensionN, T[] b);
	int Rows() const{ return mRows; }
	int Columns() const{ return mColumns; }
	int Length() { return mRows*mColumns; }
	friend ostream &operator<<(ostream &os, const CMatrix &mat)
	{
		int row = mat.Rows();
		int col = mat.Columns();

		for (int i = 0; i < row; i++)
		{
			for (int j = 0; j < col; j++)
			{
				os << fixed << mat.Get(i, j) << '\t';
			}
			if (i < row)
			{
				os << "\n";
			}
		}
		os << "\n";
		return os;
	};
	
private:
	int mRows;
	int mColumns;
	T* startElement;
	
};
#endif