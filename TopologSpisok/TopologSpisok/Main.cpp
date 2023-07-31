#include "Header.h"
#include <iostream>
#include <string.h>
#include <stdio.h>
#include <conio.h>
using namespace std;
void main()
{
	Graf G, G1;
	int n = G.FormGraf(); 
	G.Print(n);
	cout << endl;
	G.SortGraf(G1);
	G1.Print(n);
	_getch();
}
// (2,1) (4,5) (5,1) (5,3) (6,2) (6,3) (6,5) (7,1) (0,0)
