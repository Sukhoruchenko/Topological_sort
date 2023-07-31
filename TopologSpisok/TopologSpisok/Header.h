#include <iostream>
using namespace std;
#pragma once


struct Trailer;

struct Lider
{
	int key, count;//count -количество входящих ребер
	Lider *next;//указатель на следующий элемент
	Trailer *tr;//указатель на список  вершин, из которых исходят дуги
	Lider() { key = count = 0; next = 0; tr = 0; };
	void AddTrailer(Lider *p);//добавление узла в список трейлеров узла *p (в начало)
	void DelTrailer(Lider *p);//удаляет весь список трейлеров узла *p
	void ReduceCount();//убавляет нужный каунт 
	void IncreaseCount();//прибавляет 
};

struct Trailer
{
	Lider *pointer;//указатель на вершину в списке Лидер, к к-ой ведет исходящая дуга из вершины, к к-ой прикреплен Трейлер
	Trailer *next;//указатель на следующий элемент
	Trailer() { pointer = 0; next = 0; };
};


struct Graf //список с фиктивной головой
{
	Lider *head;
	Graf();
	~Graf();
	void AddToHead(int k);
	void AddToTail(Lider *q);
	void Del(Lider *q);  //физическое удаление узла, для Clear()
	void Exclude(Lider *q); //исключение узла из списка, для формирования упорядоченного списка
	Lider *FindKey(int k);
	Lider *FindCount(int x);
	int FormGraf();
	void SortGraf(Graf &);
	void Clear();
	bool Empty();
	void Print(int n);
};