// LinearAlgebraLibrary.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Matrix.h"


int main()
{
	CMatrix mt = CMatrix(2, 2);
	for (int row = 0; row < mt.Rows(); row++)
	{
		for (int col = 0; col < mt.Columns(); col++)
		{
			mt.set(row, col, row + col);
			//printf("row = %d, col = %d, val = %f\n", row, col, mt->get(row, col));
		}
	}
	//mt = mt*2;
	cout << mt;
}

