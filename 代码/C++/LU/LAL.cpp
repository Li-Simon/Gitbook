// LAL.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "matrix.h"
#include "matrix.cpp"
#include <iostream>
#include <math.h>
#include "Vector.h"
#include "MatrixAlgo.h"
using namespace std;

int main()
{
	//CMatrix<double>* mt = new CMatrix<double>(2,2);
	int mdemension = 2;
	CMatrix<double> mt(mdemension, mdemension);
	CMatrix<double> L(mdemension, mdemension);
	CMatrix<double> U(mdemension, mdemension);
	CVector vec(mdemension, true);
	for (int row = 0; row < mt.Rows(); row++)
	{
		for (int col = 0; col < mt.Columns(); col++)
		{
			mt.Set(row, col, row +col + 1);
			//mt.Set(row, col, row + col*col + 1 + rand()%100);
		}
	}
	//mt->LU(*mt, 2, &L, &U);
	mt.LU(mt, mdemension, &L, &U);
	cout << "mt\n" << mt;
	cout << "vec\n" << vec;
	cout << "L\n" << L;
	cout << "U\n" << U;
	cout << "L*U\n" << L*U;
	//cout << "mt*Vec\n" << mt*vec;
	cout << "Solve(mt,vec)\n" << Solve(mt,vec);
    return 0;
}

