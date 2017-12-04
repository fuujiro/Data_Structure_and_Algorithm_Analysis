#include <bits/stdc++.h>
using namespace std;
void print(int a[], int n, int i){
	cout << ":";
	for(int j = 0; j < 8; j++){
		cout << a[j] << " ";
	}
	cout << endl;
} 
void InsertSort(int a[], int n)
{
	for(int i = 1; i < n; i++){
		if(a[i] < a[i-1]){
			int j = i-1;
			int x = a[i];
			a[i] = a[i-1];
			while(x < a[j]){
				a[j+1] = a[j];
				j--;
			}
			a[j+1] = x;
		}
		print(a, n, i);
	}
}
int main()
{
	 int a[8] = {3, 1, 5, 7, 2, 4, 9, 6};
	 InsertSort(a,8);
	 print(a,8,8); 
}
