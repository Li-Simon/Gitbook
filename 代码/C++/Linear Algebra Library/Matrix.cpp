#include "stdafx.h"
#include "Matrix.h"
#include <iostream>
#include <math.h>


CMatrix::CMatrix()
{
}


CMatrix::~CMatrix()
{
	delete[] startElement;
}

CMatrix::CMatrix(int rows, int columns):
	mRows(rows>0?rows:0),
	mColumns(columns>0 ? columns : 0),
	startElement(new double[rows*columns])
{
	if (rows <= 0 || columns <= 0)
	{
		printf("At least one of arguments less than 0!");
	}

	int total = mColumns*mRows;
	for (int i = 0; i < total; i++)
	{
		startElement[i] =0.0;
	}
}


CMatrix::CMatrix(const CMatrix & mat) :
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

double CMatrix::get(int row, int col) const
{
	if (row > mRows || col > mColumns || row < 0 || col < 0)
	{
		printf("Wrong matrix index!");
		return 0.0;
	}
	return startElement[(row - 1)*mColumns + col + 1];
}

double CMatrix::set(int row, int col, double val)
{
	if (row > mRows || col > mColumns || row < 0 || col < 0)
	{
		printf("Wrong matrix index!");
		return 0.0;
	}
	startElement[(row - 1)*mColumns + col + 1] = val;
}

CMatrix CMatrix::operator +(const CMatrix &mat2)
{
	if (mRows != mat2.mRows || mColumns!=mat2.mLength)
	{
		printf("Two matrix are not match, can't add!");
		return *this;
	}
	CMatrix result = *this;
	for (int i = 0; i< mRows; i++)
	{
		for (int j = 0; j< mColumns; j++)
		{
			result.set(i, j, get(i, j) + mat2.get(i, j));
		}
	}
	return result;
}

CMatrix CMatrix::operator -(const CMatrix &mat2)
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
			result.set(i, j, get(i, j) - mat2.get(i, j));
		}
	}
	return result;
}

CMatrix CMatrix::operator *(const CMatrix &mat2)
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
			double val = 0;
			for (int k = 0; k < mColumns; k++)
			{
				val += get(i, k)*mat2.get(k, j);
			}
			result.set(i, j, val);
		}
	}
	return result;
}

CMatrix CMatrix::operator *(const double div)
{
	CMatrix result = *this;
	for (int i = 0; i < mRows; i++)
	{
		for (int j = 0; j < mColumns; j++)
		{
			result.set(i, j, get(i, j) * div);
		}
	}
	return result;
}

CMatrix CMatrix::operator /(const double div)
{
	CMatrix result = *this;
	for (int i = 0; i < mRows; i++)
	{
		for (int j = 0; j < mColumns; j++)
		{
			result.set(i, j, get(i, j)/div);
		}
	}
	return result;
}


/*void CMatrix::operator =(const CMatrix &mat)
{
	CMatrix mat(mRows, mColumns);
	for (int i = 0; i < mRows; i++)
	{
		for (int j = 0; j < mColumns; j++)
		{
			mat.set(i, j, get(i, j));
		}
	}
	return;
}*/


ostream &operator <<(ostream &os, const CMatrix &mat)
{
	int row = mat.Rows();
	int col = mat.Columns();

	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j<col; j++)
		{
			os << fixed << mat.get(i, j) << '\t';
		}
		if (i < row)
		{
			os << "\n";
		}
	}
	os << "\n";
	return os;
}

