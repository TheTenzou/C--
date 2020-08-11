// dz4.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>

using namespace std;

struct node
{
	int data;
	node * next;
};
typedef node * pnode;

void create_st(pnode &p)
{
	int x;
	pnode q;
	cin >> x;
	if (x)
	{
		q = new node;
		q->data = x;
		q->next = p;
		p = q;
		create_st(p);
	}
}

void print_l(pnode &p)
{
	pnode top = p;
	while (top)
	{
		cout << top->data << endl;
		top = top->next;
	}
	
}

int main()
{
	pnode st = NULL;
	//cout << st;
	create_st(st);

	pnode st1 = new node;
	st1->next = st;
	st1->data = 500;
	while (st1->next)
	{
		if (st1->next->data < 0)
		{
			pnode tmp = st1->next;
			st1->next = st1->next->next;
			delete tmp;
		}
		st1 = st1->next;
	}
	
	print_l(st);
	
	return 0;
}





// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
