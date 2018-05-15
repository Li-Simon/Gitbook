#ifndef CMATRIX_H
#define  CMATRIX_H
#pragma once
#include <iostream>
using namespace std;

class CMatrix
{
public:
	CMatrix();
	CMatrix(int rows, int columns); //constructor a zero matrix
	CMatrix(const CMatrix&);
	
	~CMatrix();  //Destructor
	int Rows() const { return mRows; }
	int Columns() const { return mColumns; }
	int Length() { return mColumns*mRows; }
	//double* Data() { return mData; }
	double get(int i, int j) const;
	double set(int i, int j, double val);

	CMatrix operator +(const CMatrix &mat);
	CMatrix operator -(const CMatrix &mat);
	CMatrix operator *(const CMatrix &mat);
	CMatrix operator *(const double div);
	CMatrix operator /(const double div);

	void operator =(const CMatrix &mat);
private:
	int mRows;
	int mColumns;
	int mLength;
	double* startElement;
};

ostream & operator <<(ostream &, const CMatrix &);
#endif
