#include "BM.h"

using namespace std;

int BoolMatrix::Max(char **s, int M)
{
	int n = strlen(s[0]);
	for (int i = 1; i < M; i++)
		if (strlen(s[i]) > n) n = strlen(s[i]);
	return n;
}

BoolMatrix::BoolMatrix()
{
	m = n = 1;
	BV = new BoolVector[m];
	BV[0] = BoolVector();
}

BoolMatrix::BoolMatrix(int M, int N)
{
	m = M; n = N;
	BV = new BoolVector[m];
	for (int i = 0; i < m; i++)
		BV[i] = BoolVector(n);
}

BoolMatrix::BoolMatrix(char **s, int M)
{
	m = M;
	n = Max(s, M);
	BV = new BoolVector[m];
	for (int i = 0; i < m; i++)
		BV[i] = BoolVector(s[i], n);
}

BoolMatrix::BoolMatrix(BoolMatrix &X)
{
	m = X.m; n = X.n;
	BV = new BoolVector[m];
	for (int i = 0; i < m; i++)
		BV[i] = X.BV[i];
}

BoolMatrix & BoolMatrix::operator = (BoolMatrix &X)
{
	if (this != &X)
	{
		if (m != X.m)
		{
			delete[]BV;
			m = X.m;
			BV = new BoolVector[m];
		}
		n = X.n;
		for (int i = 0; i < m; i++)
			BV[i] = X.BV[i];
	}
	return *this;
}

BoolVector & BoolMatrix::operator[] (int i)
{
	if (i < 0 || i >= m) { cout << "incorrect i"; return BV[0]; }
	else return BV[i];
}

BoolMatrix BoolMatrix::SetUp1(int i, int j) //установить в 1 эл-т [i][j]
{
	if (i < 0 || i >= m)
	{
		cout << "incorrect index i" << endl;
		return *this;
	}
	if (j < 0 || j >= n)
	{
		cout << "incorrect index j" << endl;
		return *this;
	}
	BV[i].SetUp1(j);
	return *this;
}

BoolMatrix BoolMatrix::SetUp0(int i, int j)
{
	if (i < 0 || i >= m)
	{
		cout << "incorrect index i" << endl;
		return *this;
	}
	if (j < 0 || j >= n)
	{
		cout << "incorrect index j" << endl;
		return *this;
	}
	BV[i].SetUp0(j);
	return *this;
}

BoolMatrix BoolMatrix::SetUp1(int kol, int i, int pos)
{
	if (i < 0 || i >= m)
	{
		cout << "incorrect index i" << endl;
		return *this;
	}
	BV[i].SetUp1(kol, pos);
	return *this;
}

BoolMatrix BoolMatrix::SetUp0(int kol, int i, int pos)
{
	if (i < 0 || i >= m)
	{
		cout << "incorrect index i" << endl;
		return *this;
	}
	BV[i].SetUp0(kol, pos);
	return *this;

	if (pos < 0 || pos + kol - 1 >= n)
	{
		cout << "incorrect index j" << endl;
		return *this;
	}
	for (int k = 0; k < kol; k++)
		BV[i].SetUp0(pos + k);
	return *this;
}


BoolMatrix BoolMatrix::Invert(int i, int j)
{
	if (i < 0 || i >= m)
	{
		cout << "incorrect index i";
		return *this;
	}
	if (j < 0 || j >= n)
	{
		cout << "incorrect index j";
		return *this;
	}
	BV[i].Invert(j);
	return *this;
}

BoolMatrix BoolMatrix::Invert(int kol, int i, int pos)
{
	if (i < 0 || i >= m)
	{
		cout << "incorrect index i";
		return *this;
	}
	if (pos < 0 || pos >= n)
	{
		cout << "incorrect index pos";
		return *this;
	}
	BV[i].Invert(kol, pos);
	return *this;
}

BoolMatrix BoolMatrix::operator & (BoolMatrix &X) //построчная конъюнкция матриц, создается новая матрица  
{
	BoolMatrix Res(m, n);
	if (m != X.m || n != X.n)
	{
		cout << "incorrect dimension";
		return *this;
	}
	else for (int i = 0; i < m; i++)
		Res.BV[i] = BV[i] & X.BV[i];
	return Res;
}

BoolMatrix & BoolMatrix::operator &= (BoolMatrix &X) //построчная конъюнкция матриц, изменяется *this
{
	return *this = *this & X;
}

BoolMatrix BoolMatrix::operator | (BoolMatrix & X)
{
	BoolMatrix Res(m, n);
	if (m != X.m || n != X.n)
	{
		cout << "incorrect dimension";
		return *this;
	}
	else for (int i = 0; i < m; i++)
		Res.BV[i] = BV[i] | X.BV[i];
	return Res;
}

BoolMatrix & BoolMatrix::operator |= (BoolMatrix & X)
{
	return *this = *this | X;
}

BoolMatrix BoolMatrix::operator ^ (BoolMatrix & X)
{
	BoolMatrix Res(m, n);
	if (m != X.m || n != X.n)
	{
		cout << "incorrect dimension" << endl;
		return *this;
	}
	else
	{
		for (int i = 0; i < m; i++)
			Res.BV[i] = BV[i] ^ X.BV[i];
	}
	return Res;
}

BoolMatrix & BoolMatrix::operator ^= (BoolMatrix & X)
{
	return *this = *this ^ X;
}

BoolMatrix BoolMatrix::operator ~ ()
{
	for (int i = 0; i < m; i++) BV[i] = ~BV[i];
	return *this;
}

BoolMatrix BoolMatrix::ShiftRight(int i, int kol)
//сдвиг вправо эл-тов i  строки на kol эл-тов, 
//создается новая матрица
{
	BoolMatrix Res = *this;
	Res.BV[i] >> kol;
	return Res;
}

BoolMatrix  & BoolMatrix::ShiftRightEq(int i, int kol) //сдвиг вправо эл-тов i  строки на kol эл-тов, изменяется *this
{
	BV[i] >>= kol;
	return *this;
}

BoolMatrix BoolMatrix::ShiftLeft(int i, int kol)
{
	BoolMatrix Res = *this;
	Res.BV[i] << kol;
	return Res;
}

BoolMatrix & BoolMatrix::ShiftLeftEq(int i, int kol)
{
	BV[i] <<= kol;
	return *this;
}

bool BoolMatrix::operator == (BoolMatrix X)
{
	if (n != X.n || m != X.m) return false;
	for (int i = 0; i < m; i++)
		if (BV[i] != X.BV[i]) return false;
	return true;
}

bool BoolMatrix::operator != (BoolMatrix X)
{
	if (n != X.n || m != X.m) return true;
	for (int i = 0; i < m; i++)
		if (BV[i] != X.BV[i]) return true;
	return false;
}

BoolVector BoolMatrix::Conj() //конъюнкция всех строк матрицы
{
	BoolVector B = BV[0];
	for (int i = 1; i < m; i++)
		B &= BV[i];
	return B;
}

BoolVector BoolMatrix::Disj()
{
	BoolVector B = BV[0];
	for (int i = 1; i < m; i++)
		B |= BV[i];
	return B;
}

BoolVector BoolMatrix::Xor()
{
	BoolVector B = BV[0];
	for (int i = 1; i < m; i++)
		B ^= BV[i];
	return B;
}

ostream & operator << (ostream& os, BoolMatrix & X)
{
	for (int i = 0; i < X.m; i++)
		os << X.BV[i];
	return os;
}

istream & operator >> (istream &r, BoolMatrix & X)
{
	int m, n;
	cout << "enter m and n: ";
	cin >> m >> n;
	X.Scan(m, n);
	return r;
}

void BoolMatrix::Scan(int M, int N)
{
	if (m != M || n != N)
	{
		delete[] BV;
		m = M; n = N;
		BV = new BoolVector[m];
		for (int i = 0; i < m; i++)
			BV[i] = BoolVector(n);
	}
	cout << "Enter BoolMatrix, size " << M << " x " << N << " : " << endl;
	for (int i = 0; i < m; i++)
		cin >> BV[i];
}

void BoolMatrix::Print()
{
	for (int i = 0; i < m; i++)
	{
		cout << BV[i];
	}
}

