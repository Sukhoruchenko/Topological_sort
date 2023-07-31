#pragma once

using namespace std;

typedef unsigned char UC;

#include "BoolVector.h"

class BoolMatrix
{
	BoolVector *BV;
	int m, n;   //m - кол-во строк матрицы, n - кол-во столбцов
	int Max(char **s, int M);  //вспомогательная ф-я
public:
	BoolMatrix();
	BoolMatrix(int, int);
	BoolMatrix(char **s, int M);
	BoolMatrix(BoolMatrix &);
	BoolMatrix & operator= (BoolMatrix &);
	~BoolMatrix() { delete[]BV; }
	void Scan(int, int);
	void Print();
	BoolVector & operator[] (int);
	bool  operator== (BoolMatrix);
	bool operator!= (BoolMatrix);
	BoolMatrix SetUp1(int i, int j); //установить в 1 эл-т [i][j]
	BoolMatrix SetUp0(int i, int j); //сбросить в 0 эл-т [i][j]
	BoolMatrix SetUp1(int kol, int i, int pos); //установить в 1 kol эл-тов в i-й строке, начиная с позиции pos
	BoolMatrix SetUp0(int kol, int i, int pos); //установить в 0 kol эл-тов в i-й строке, начиная с позиции pos
	BoolMatrix Invert(int i, int j); //инвертировать эл-т [i][j]
	BoolMatrix Invert(int kol, int i, int pos); //инвертировать kol эл-тов в i-й строке, начиная с позиции pos
	BoolMatrix operator & (BoolMatrix &X); //построчная конъюнкция матриц, создается новая матрица  
	BoolMatrix & operator &= (BoolMatrix &X); //построчная конъюнкция матриц, изменяется *this
	BoolMatrix operator | (BoolMatrix &X); //построчная диъюнкция матриц, создается новая матрица  
	BoolMatrix & operator |= (BoolMatrix &X); //построчная дизъюнкция матриц, изменяется *this 
	BoolMatrix operator ^ (BoolMatrix &X); //построчная XOR матриц, создается новая матрица  
	BoolMatrix & operator ^= (BoolMatrix &X); //построчная XOR матриц, изменяется *this
	BoolMatrix operator ~ (); //инверсия матрицы, изменяется *this
	BoolMatrix ShiftRight(int i, int kol); //сдвиг вправо эл-тов i  строки на kol эл-тов, создается новая матрица
	BoolMatrix  & ShiftRightEq(int i, int kol); //сдвиг вправо эл-тов i  строки на kol эл-тов, изменяется *this
	BoolMatrix ShiftLeft(int i, int kol); //сдвиг влево эл-тов i  строки на kol эл-тов, создается новая матрица
	BoolMatrix & ShiftLeftEq(int i, int kol); //сдвиг влево эл-тов i  строки на kol эл-тов, изменяется *this
	BoolVector Conj(); //конъюнкция всех строк матрицы
	BoolVector Disj(); //дизъюнкция всех строк матрицы
	BoolVector Xor(); //XOR всех строк матрицы
	friend ostream &operator << (ostream &r, BoolMatrix & X);
	friend istream &operator >> (istream &r, BoolMatrix & X);
};