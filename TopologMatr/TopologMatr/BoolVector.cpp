#include "BoolVector.h"

using namespace std;

int BoolVector::Input(char *s, int i_s, int i_bv, int N)
{
	//формированием эл-та bv[i_bv]
	//i_s -индекс символа в s
	//N -кол-во значащих цифр в bv[i_bv]
	{UC mask = 1;
	int j = 0;
	mask <<= (N - 1);
	bv[i_bv] = 0;
	for (int i = i_s; j < N; j++, i++, i_s++, mask >>= 1)
		if (s[i] == '1') bv[i_bv] |= mask;
	return i_s;
	}
}

BoolVector::BoolVector()
{
	n = 0;
	m = 1;
	bv = new UC[m];
	bv[0] = 0;
}

BoolVector::BoolVector(int N)
{
	n = N;
	m = N / 8;
	int k = N % 8;
	if (k) m++;
	bv = new UC[m];
	for (int i = 0; i < m; i++)
		bv[i] = 0;
}

BoolVector::BoolVector(char* s)
{
	n = strlen(s);
	m = (n - 1) / 8 + 1;
	bv = new UC[m];
	for (int i = 0; i < m; i++)
		bv[i] = 0;
	UC mask = 1;
	int i = strlen(s) - 1;
	for (int x = n, p = m - 1; x > 0 && i >= 0; x--, i--, mask <<= 1)
	{
		if (!mask)
		{
			mask = 1;
			p--;
		}
		if (s[i] == '1')
			bv[p] |= mask; // |= логическое сложение
	}
}

BoolVector::BoolVector(char *s, int N)
{
	if (strlen(s))
	{
		if (N == -1)
		{
			n = strlen(s);
		}
		else {
			n = N;
		}
		if (n)
		{
			m = (n - 1) / 8 + 1;
			bv = new UC[m];
			for (int i = 0; i < m; i++)
				bv[i] = 0;
			UC mask = 1;
			int i = strlen(s) - 1;
			for (int i1 = n, i2 = m - 1; i1 > 0 && i >= 0; i1--, i--, mask <<= 1)
			{
				if (!mask)
				{
					mask = 1;
					i2--;
				}
				if (s[i] == '1')
					bv[i2] |= mask;
			}
		}
	}
	else
	{
		m = 0;
		n = 0;
		bv = NULL;
	}

}
BoolVector::BoolVector(BoolVector &V)
{
	n = V.n;
	m = V.m;
	bv = new UC[m];
	for (int i = 0; i < m; i++)
		bv[i] = V.bv[i];
}

BoolVector::~BoolVector()
{
	delete[]bv;
}

BoolVector & BoolVector::operator = (BoolVector &V)
{
	if (this != &V)
	{
		delete[]bv;
		n = V.n;
		m = V.m;
		bv = new UC[m];
		for (int i = 0; i < m; i++)
			bv[i] = V.bv[i];
	}
	return *this;
}

void BoolVector::Print()
{
	UC mask = 1;
	if (n % 8 == 0)
		mask <<= 7;
	else
		mask <<= (n % 8 - 1);

	for (int i = 0; i < m; i++, mask = 1 << 7)
	{
		for (; mask; mask >>= 1)
		{
			if (bv[i] & mask)
				cout << '1';
			else
				cout << '0';
		}
	}
	cout << endl;
}
void BoolVector::Scan(int N)
{
	cout << "enter bool vector, lenght " << N << ": ";
	char *s;
	s = new char[N + 1];
	//cin.getline(s, N + 1);
	getchar();
	fgets(s, N + 1, stdin);
	BoolVector T(s);
	*this = T;
	delete[]s;
}

BoolVector BoolVector::operator & (BoolVector V) //создаетс€ новый вектор
{
	int n1 = n; // длина рез. вектора
	int i_res = m - 1; // индекс массива рез. вектора
	if (n1 > V.n) { n1 = V.n; i_res = V.m - 1; }
	int i, i_V;
	BoolVector Res(n1);
	for (i = m - 1, i_V = V.m - 1; i_res >= 0; i--, i_V--, i_res--)
		Res.bv[i_res] = bv[i] & V.bv[i_V];
	return Res;
}

BoolVector & BoolVector::operator &= (BoolVector V) //измен€етс€ *this
{
	BoolVector T = (*this) & V;
	*this = T;
	return *this;
}

BoolVector BoolVector::operator|(BoolVector V)
{
	int n1 = n;
	int i_res = m - 1;
	if (n1 < V.n) { n1 = V.n; i_res = V.m - 1; }
	int i, i_V;
	BoolVector Res(n1);
	for (i = m - 1, i_V = V.m - 1; i_V >= 0 && i >= 0; i--, i_V--, i_res--)
		Res.bv[i_res] = bv[i] | V.bv[i_V];
	if (i >= 0) for (; i >= 0; i--, i_res--)Res.bv[i_res] = bv[i];
	if (i_V >= 0) for (; i_V >= 0; i_V--, i_res--)Res.bv[i_res] = V.bv[i_V];
	return Res;
}

BoolVector & BoolVector::operator|=(BoolVector V)
{
	return *this = *this | V;
}

BoolVector BoolVector::operator^(BoolVector V)
{
	int n1 = n;
	int i_res = m - 1;
	if (n1 < V.n) { n1 = V.n; i_res = V.m - 1; }
	int i, i_V;
	BoolVector Res(n1);
	for (i = m - 1, i_V = V.m - 1; i_V >= 0 && i >= 0; i--, i_V--, i_res--)
		Res.bv[i_res] = bv[i] ^ V.bv[i_V];
	if (i >= 0) for (; i >= 0; i--, i_res--)Res.bv[i_res] = bv[i];
	if (i_V >= 0) for (; i_V >= 0; i_V--, i_res--)Res.bv[i_res] = V.bv[i_V];
	return Res;
}

BoolVector & BoolVector::operator ^= (BoolVector V)
{
	return *this = *this ^ V;
}

BoolVector & BoolVector::operator ~ ()
{
	for (int i = 0; i < m; i++)
		bv[i] = ~bv[i];
	return *this;
}

BoolVector BoolVector::operator >> (int k) //сдвиг вправо
{
	BoolVector Res(n);
	if (k < n)
	{
		int i;
		for (i = 0; i < n - k; i++)
			if (this->operator[](i + k) == '1') Res.SetUp1(i);
			else Res.SetUp0(i);
	}
	return Res;
}

BoolVector & BoolVector::operator >>= (int k) //измен€етс€ *this сдвиг
{
	BoolVector T;
	T = (*this) >> k;
	*this = T;
	return *this;
}

BoolVector BoolVector::operator << (int k)
{
	BoolVector Res(n);
	if (k < n)
	{
		int i;
		for (i = 0; i < n - k; i++)
			if ((*this)[i] == '1')
				Res.SetUp1(k + i);
			else
				Res.SetUp0(k + i);
	}
	return Res;
}

BoolVector & BoolVector::operator <<= (int k)
{
	BoolVector T;
	T = (*this) << k;
	*this = T;
	return *this;
}

BoolVector BoolVector::SetUp1(int pos)
{
	if (pos >= n) cout << "incorrect position";
	else
	{
		int m1 = pos / 8, k1 = pos % 8;
		UC mask = 1 << k1;
		bv[m - 1 - m1] |= mask;
	}
	return *this;
}

BoolVector BoolVector::SetUp0(int pos)
{
	if (pos >= n)
		cout << "incorrect position" << endl;
	else
	{
		int m1 = pos / 8, k1 = pos % 8;
		UC mask = (1 << k1);
		mask = ~mask;
		bv[m - 1 - m1] &= mask;
	}
	return *this;
}

BoolVector BoolVector::SetUp1(int kol, int pos)
{
	if (pos >= n || pos + kol > n)
		cout << "incorrect position" << endl;
	else
	{
		for (int i = pos; i < pos + kol; i++)
			SetUp1(i);
	}
	return *this;
}

BoolVector BoolVector::SetUp0(int kol, int pos)
{
	if (n - pos >= kol)
	{
		int k1 = pos % 8;
		UC mask = 1 << k1;
		int m1 = m - pos / 8 - 1;
		for (int i = 0; i < kol; i++, mask <<= 1) {
			if (!mask) {
				mask = 1;
				m1--;
			}
			bv[m1] &= ~mask;
		}
	}
	else
	{
		cout << "incorrect position" << endl;
	}
	return *this;
}

BoolVector BoolVector::Invert(int pos)
{
	if (pos >= n) cout << "incorrect position" << endl;
	else
		if ((*this)[pos] == '0') (*this).SetUp1(pos);
		else (*this).SetUp0(pos);
	return *this;
}

BoolVector BoolVector::Invert(int kol, int pos)
{
	if (pos >= n || pos + kol >= n) cout << "incorrect position" << endl;
	else
		for (int i = 0; i < kol; i++)
			if ((*this)[pos + i] == '0') (*this).SetUp1(pos + i);
			else (*this).SetUp0(pos + i);
	return *this;
}

UC BoolVector::operator [] (int pos)
{
	if (pos >= n) { cout << "incorrect position"; return '0'; }
	else
	{
		int m1 = pos / 8, k1 = pos % 8;
		UC mask = 1 << k1;
		if (bv[m - 1 - m1] & mask) return '1';
		else return '0';
	}
}

bool BoolVector::operator == (BoolVector V)
{
	for (int i = 0; i < m; i++)
		if (bv[i] != V.bv[i])
			return false;
	return true;
}

bool BoolVector::operator != (BoolVector V)
{
	for (int i = 0; i < n; i++)
		if (bv[i] != V.bv[i])
			return true;
	return false;
}

bool BoolVector::operator < (BoolVector V)
{
	for (int i = 0; i < n; i++)
		if (bv[i] > V.bv[i])
			return false;
	return true;
}

bool BoolVector::operator > (BoolVector V)
{
	for (int i = 0; i < n; i++)
		if (bv[i] < V.bv[i])
			return false;
	return true;
}

int BoolVector::Weight()
{
	int count = 0;
	UC mask = 1;
	for (int j = 0; j < m; j++)
	{
		mask <<= 7;
		for (int i = 0; i < 8; i++)
		{
			if (bv[j] & mask) count++;
			if (i < 7) mask >>= 1;
		}
	}
	return count;
}
istream & operator>>(std::istream &r, BoolVector &V)
{
	cout << "enter length:" << endl;
	int N;
	cin >> N;
	V.Scan(N);
	return r;
}
ostream & operator<<(std::ostream& r, BoolVector &V)
{
	UC mask = 1;
	if (V.n % 8 == 0)
		mask <<= 7;
	else
		mask <<= (V.n % 8 - 1);

	for (int i = 0; i < V.m; i++, mask = 1 << 7)
	{
		for (; mask; mask >>= 1)
		{
			if (V.bv[i] & mask)
				r << '1';
			else
				r << '0';
		}
	}
	r << endl;
	return r;
}
