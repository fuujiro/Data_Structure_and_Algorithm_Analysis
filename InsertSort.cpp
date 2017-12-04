#include <bits/stdc++.h>
using namespace std;
void print (int a[], int n, int i)
{
	cout << i << ":";
	for (int j = 0; j < 8; j++){
		cout << a[j] << " ";
	} 
	cout << endl;
} 
void ShellInsertSort(int a[], int n, int dk){
	for(int i = dk; i < n; i++){
		if(a[i] < a[i-dk]){
			int j = i - dk;
			int x = a[i];
			a[i] = a[i-dk];
			while(x < a[j]){
				a[j+dk] = a[j];
				j -= dk;
			}
			a[j+dk] = x;
		}
		print(a, n, i);
	}
}
void shellSort(int a[], int n){
	int dk = n / 2;
	while(dk >= 1){
		ShellInsertSort(a, n, dk);
		dk = dk / 2;
	}
}
int main()
{
	int a[8] = {3, 1, 5, 7, 2, 4, 9, 6};
	shellSort(a,8);
	print(a,8,8);
	return 0;
}
