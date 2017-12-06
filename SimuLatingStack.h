#include <iostream>
#include <stdlib.h>
using namespace std;

#define MAXSIZE 0xffff

//Write the stack with the template class (template) of c++
template<class type>
class my_stack
{
	int top;
	type *my_s;
	int MAXSIZE;
	
public:
	my_stack():top(-1),maxsize(MAXSIZE)
	{
		my_s = new type[maxsize];
		if(my_s == NULL)
		{
			cerr << "Dynamic storage allocation failed. " << endl;
			exit(1); 
		}
	} 
	~my_stack()
	{
		delete[] my_s;
	}
	//Determine whether or not it is empty
	bool Empty();
	// pushed on the stack
	void Push(type tp);	
	//Return the top element of the stack
	type Top();
	//poped out the stack
	void Pop();
	//Return the size of the stack
	int Size();
};

template <class type>
bool my_stack<type>::Empty()
{
	if(top == -1){
		return true;
	} else{
		return false;
	} 
} 

template <class type>
type my_stack<type>::Top()
{
	if(top != -1){
		return my_s[top];
	}else{
		cout << "Empty Stack!" << endl;
		exit(1);
	} 
}

template <class type>
void my_stack<type>::Push(type tp)
{
	if(top + 1 < maxsize){
		my_s[++top] = tp;
	}else{
		cout << "Full Stack!" << endl;
		exit(1); 
	}
}

template <class type>
void my_stack<type>::Pop()
{
	if(top >= 0){
		top --;
	}else{
		cout << "Empty Stack!" << endl;
		exit(1);
	}
}

template <class type>
int my_stack<type>::Size()
{
	return top+1;
}
