// dz5.cpp : This file contains the 'main' function. Program execution begins and ends there.
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

void create_cr(pnode &top)
{
	int x;
	cin >> x;
	if (x) 
	{
		top = new node;
		top->data = x;
		pnode p;
		p = top;
		cin >> x;
		while (x)
		{
			pnode q = new node;
			q->data = x;
			p->next = q;
			p = q;
			cin >> x;
		}
		p->next = top;
	}
	
};

void print_l(pnode &p)
{
	pnode top = p;
	do
	{
		cout << top->data << endl;
		top = top->next;
	} while (top != p);
}

int main()
{
	pnode circle = NULL;
	cout << "k=";
	int k;
	cin >> k;
	create_cr(circle);
	
	while (circle->next != circle)
	{
		for (int i = 0; i < k - 2; i++)
		{
			circle = circle->next;
		}
		//cout << circle->next->data<<'#';
		circle->next = circle->next->next;
		circle = circle->next;
	}
	cout << circle->data;
	//print_l(curcle);
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
