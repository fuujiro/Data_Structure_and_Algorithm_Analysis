#include <bits/stdc++.h>
using namespace std;
void print(int a[], int n){  
    for(int j= 0; j<n; j++){  
        cout<<a[j] <<"  ";  
    }  
    cout<<endl;  
}  
  
void swap(int *a, int *b)  
{  
    int tmp = *a;  
    *a = *b;  
    *b = tmp;  
}  
  
int partition(int a[], int low, int high)  
{  
    int privotKey = a[low];                 //基准元素  
    while(low < high){                   //从表的两端交替地向中间扫描  
        while(low < high  && a[high] >= privotKey) --high; //从high 所指位置向前搜索，至多到low+1 位置。将比基准元素小的交换到低端  
        swap(&a[low], &a[high]);  
        while(low < high  && a[low] <= privotKey ) ++low;  
        swap(&a[low], &a[high]);  
    }  
    print(a,10);  
    return low;  
}  
  
  
void qsort_improve(int r[ ],int low,int high, int k){  
    if( high -low > k ) { //长度大于k时递归, k为指定的数  
        int pivot = partition(r, low, high); // 调用的Partition算法保持不变  
        qsort_improve(r, low, pivot - 1,k);  
        qsort_improve(r, pivot + 1, high,k);  
    }   
}   
void quickSort(int r[], int n, int k){  
    qsort_improve(r,0,n,k);//先调用改进算法Qsort使之基本有序  
  
    //再用插入排序对基本有序序列排序  
    for(int i=1; i<=n;i ++){  
        int tmp = r[i];   
        int j=i-1;  
        while(tmp < r[j]){  
            r[j+1]=r[j]; j=j-1;   
        }  
        r[j+1] = tmp;  
    }   
  
}   
  
  
  
int main(){  
    int a[10] = {3,1,5,7,2,4,9,6,10,8};  
    cout<<"初始值：";  
    print(a,10);  
    quickSort(a,9,4);  
    cout<<"结果：";  
    print(a,10);  
  
}  
