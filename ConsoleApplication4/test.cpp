#include<iostream>
#include <memory>
#include"god_ptr.h"
#include<vector>
using namespace std;
struct node
{
	node() = default;
	node(int a,int b):a(a),b(b){}
	int a,  b;
};
int main()
{
	node* p = new node();
	Smart_Ptr<node>sp(p);
	p->a = 10;
	p->b = 20;

	cout << sp->a << endl;
	cout << sp->b << endl;
	cout << (*sp).a << endl;

	return 0;
}