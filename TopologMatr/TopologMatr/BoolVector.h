#pragma once

#include <iostream>
#include <string.h>
#include <stdio.h>
#include <conio.h>

using namespace std;

typedef unsigned char UC;

class BoolVector
{
private:
	UC *bv;
	int n; //длина булева вектора
	int m; //размер масссива bv
	int Input(char*, int, int, int); //формированием эл-та массива bv
public:
	BoolVector();
	BoolVector(int N);
	BoolVector(char*s);
	BoolVector(char *s, int N); //strlen(s)!=N
	BoolVector(BoolVector &);
	~BoolVector();
	BoolVector & operator = (BoolVector&);
	void Output(int); //вывод эл-та массива bv
	void Print();
	void Scan(int);
	int Weight();
	BoolVector  operator & (BoolVector); //создается новый вектор
	BoolVector & operator &= (BoolVector); //изменяется *this
	BoolVector  operator | (BoolVector); //создается новый вектор
	BoolVector & operator |= (BoolVector); //изменяется *this
	BoolVector  operator ^ (BoolVector); //создается новый вектор
	BoolVector & operator ^= (BoolVector); //изменяется *this
	BoolVector & operator ~ ();
	BoolVector  operator >> (int); //создается новый вектор
	BoolVector & operator >>= (int); //изменяется *this
	BoolVector operator << (int); //создается новый вектор
	BoolVector & operator <<= (int); //изменяется *this
	BoolVector  SetUp1(int);
	BoolVector  SetUp0(int);
	BoolVector SetUp1(int kol, int pos);
	BoolVector SetUp0(int kol, int pos);
	BoolVector Invert(int);
	BoolVector Invert(int kol, int pos);
	UC operator [] (int);
	bool operator == (BoolVector);
	bool operator != (BoolVector);
	bool operator < (BoolVector);  //x<y если x[i]<=y[i] для всех i
	bool operator > (BoolVector);  //x>y если x[i]>=y[i] для всех i
	friend ostream & operator << (ostream &r, BoolVector &V);
	friend istream & operator >> (istream &r, BoolVector &V);
};
