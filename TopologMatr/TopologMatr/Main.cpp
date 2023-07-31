#include "BM.h"
#include <conio.h>
#include <string.h>
using namespace std;
const int n = 7;
int main() 
{
	int *Res = new int[n];
	const char *m[7]
	{"0000000",	"1000000","0000000","0000100","1010000","0110100","1000000"};
	char** a = new char*[7];
	for (int i = 0; i < 7; i++)
		a[i] = new char[7];
	for (int i = 0; i < 7; i++)
		strcpy_s(a[i], 8, m[i]);
	BoolMatrix G(a, n);
	cout << G;
	BoolVector V0, V1, w, d;
	int count = 0;
	while (count < n)
	{
		w = G.Disj();
		d = ~w;
		V1 = V0 ^ d;
		for (int i = n - 1; i >= 0; i--)
		{
			if (V1[i] == '1')
			{
				G.SetUp0(n,n - i - 1,0);
				Res[count] = n - i;
				count++;
			}
		}
		V0 = w;
	}
	cout << "Res: " ;
	for (int i = 0; i < n; i++)
		cout << Res[i] << " ";
	_getch();
}