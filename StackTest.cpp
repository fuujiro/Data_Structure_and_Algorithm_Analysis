#include <iostream>
#include "AnalogStackOperation.cpp"
using namespace std;
int main()
{
	my_stack<int> stk;
	for(int i = 0; i < 50; i++){
		stk.push(i);
	}
	cout << "The size of YourStack is " << stk.size() << endl;
	while(!stk.Empty())
	{
		cout << stk.Top() << endl;
		stk.Pop();
	}
	cout << "The size of YourStack is " << stk.size() << endl;
	return 0;
}
