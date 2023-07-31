#include"Header.h"
using namespace std;

void Lider::AddTrailer(Lider *p) 
{
	if (tr == 0) 
	{
		tr = new Trailer;
		tr->pointer = p;
	}
	else 
	{
		Trailer *tr1;
		tr1 = new Trailer;
		tr1->pointer = p;
		tr1->next = tr->next;
		tr->next = tr1;
	}
}

void Lider::DelTrailer(Lider *q) 
{
	while (q->tr) 
	{
		Trailer *t = q->tr;
		q->tr->pointer->count--;
		q->tr = q->tr->next;
		delete t;
	}
}

Graf::Graf() 
{
	head = new Lider;
}

Graf:: ~Graf() 
{
	Lider *t;
	t = head->next;
	while (t) 
	{
		t->DelTrailer(t);
		Del(t);
		t = t->next;
	}
	delete head;
}

void Graf::AddToHead(int k) 
{
	Lider *t;
	t = new Lider;
	t->key = k;
	t->next = head->next;
	head->next = t;
}

void Graf::AddToTail(Lider *q) 
{
	Lider *p = head;
	for (; p->next != NULL; p = p->next);
	p->next = q;
	q->next = 0;
}

void Graf::Del(Lider *q)
{
	Lider *p = head;
	for (; p->next != q; p = p->next);
	{
		while (q->tr)
		{
			Trailer *t = q->tr;
			q->tr = q->tr->next;
			delete t;
		}
		p->next = q->next;
		delete q;
	}
}

void Graf::Exclude(Lider *q) 
{
	Lider *p = head;
	if (!Empty())
	{
		for (p; p->next != q; p = p->next);
		p->next = q->next;
	}
}

Lider* Graf::FindKey(int k) 
{
	Lider *v = head;
	if (!Empty()) 
	{
		for (v = v->next; (v->key != k) && (v->next != NULL); v = v->next);
		if (v->key != k)
			return 0;
		else return v;
	}
	else {
		return 0;
	}

}

Lider* Graf::FindCount(int x) 
{
	Lider *v = head;
	if (!Empty()) 
	{
		for (v = v->next; v->count != x && v->next != NULL; v = v->next);
		if (v->count != x)
			return 0;
		else return v;

	}
	else return 0;
}

void Graf::Clear() 
{
	while (!Empty())
		Del(head->next);
}

bool Graf::Empty() 
{
	if (head->next == NULL)
		return true;
	else
		return false;
}

void Lider::ReduceCount() 
{
	if (tr != 0) {
		Trailer *run;
		tr->pointer->count--;
		run = tr;
		while (run->next != 0) 
		{
			run = run->next;
			run->pointer->count--;
		}
	}
}

void Lider::IncreaseCount() 
{
	if (tr != 0) {
		Trailer *run = tr;
		run->pointer->count++;
		while (run->next != 0) 
		{
			run = run->next;
			run->pointer->count++;
		}
	}
}

int Graf::FormGraf()
{
	int n = 0, x, y;
	Lider *px, *py;

	cout << "enter x and y: ";
	cin >> x >> y;
	while (x && y)
	{
		if (FindKey(x) == 0)
		{
			AddToHead(x);
			px = head->next;
			n++;
		}
		else px = FindKey(x);
		if (FindKey(y) == 0)
		{
			AddToHead(y);
			py = head->next;
			n++;
		}
		else py = FindKey(y);
		py->count++;
		px->AddTrailer(py);
		cout << "enter x and y: ";
		cin >> x >> y;
	}
	return n;
}

void Graf::SortGraf(Graf &newLD)
{
	Lider *p, *q;
	while (!Empty())
	{
		p = FindCount(0);
		if (p == 0 && !Empty())
		{
			cout << "cycle"; 
			return;
		}
		Exclude(p);
		newLD.AddToTail(p);
		p->ReduceCount();
	}
	q = newLD.head->next;
	while (q != 0)
	{
		q->IncreaseCount(); q = q->next;
	}
}

void Graf::Print(int n) 
{
	Lider *run = head;
	if (n != 0)
		for (run = run->next; n > 0; run = run->next, n--)
			cout << run->key;
	else
		cout << "graf empty";
}