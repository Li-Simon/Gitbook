#pragma once
#include <iostream>
using namespace std;
class CVector
{
public:
	CVector() {}
	CVector(int n):
		mSize(n),
		startElement(new double[n])
	{
		mSize = n;
		for (int i =0 ; i < n; i++)
		{
			startElement[i] = 0;
		}
	}
	CVector(int n, bool unit):
		mSize(n),
		startElement(new double[n])
	{
		if (unit == true)
		{
			for (int i = 0; i < n; i++)
			{
				startElement[i] = 1;
			}
		}
		else
		{
			for (int i = 0; i < n; i++)
			{
				startElement[i] = 0;
			}
		}
		
	}
	CVector(const CVector & vec) :
		mSize(vec.mSize),
		startElement(new double[vec.mSize])
	{
		int total = mSize;
		for (int i = 0; i < total; i++)
		{
			startElement[i] = vec.startElement[i];
		}
	}
	~CVector() {}
public:
	static CVector UnitVector(int n, int length)
	{
		CVector V(length);
		V.startElement[n] = 1;
		return V;
	}
	void Set(int n, double val)
	{
		startElement[n] = val;
	}
	double Get(int n) const
	{
		return startElement[n];
	}
	int Size() const
	{
		return mSize;
	}
	friend ostream &operator<<(ostream &os, const CVector &vec)
	{
		int size = vec.Size();
		for (int i = 0; i < size; i++)
		{
		 os << fixed << vec.Get(i) << '\n';
		}
		os << "\n";
		return os;
	};
private:
	double* startElement;
	int mSize;

};

