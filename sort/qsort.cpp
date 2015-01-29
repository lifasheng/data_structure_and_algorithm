#include <iostream>
#include <algorithm> // for sort
#include <vector>
#include <stdlib.h> // for srand and rand
#include <time.h> // for time
using namespace std;

#define M3

#ifdef M1
// scan from both sides to center 
int partition( int *a, int low, int high ) {
    int left = low, right = high;
    int pivot = a[low]; // choose first element as pivot
    while ( left < right ) {
        while( a[left] <= pivot) left++;
        while( a[right] > pivot) right--;
        if ( left < right ) swap(a[left],a[right]);
    }
    /* right is final position for the pivot */
    // a[right] <= pivot < a[left]
    swap(a[low], a[right]);
    return right;
}
#endif

#ifdef M2
// scan from both sides to center 
int partition(int *a, int low, int high)
{
    int pivot = a[low];//选第一个元素作为枢纽元
    while(low < high)
    {
        while(low < high && a[high] >= pivot)high--;
        a[low] = a[high];//从后面开始找到第一个小于pivot的元素，放到low位置
        while(low < high && a[low] <= pivot)low++;
        a[high] = a[low];//从前面开始找到第一个大于pivot的元素，放到high位置
    }
    a[low] = pivot;//最后枢纽元放到low的位置
    return low;
}
#endif

#ifdef M3
// scan from left to right, last element as pivot
// http://www.alwayslearn.com/computer%20algorithms/ComputerAlgorithms_QuickSort.html
// 参考算法导论
int partition( int *a, int low, int high ) {
    int pivot = a[high]; // choose last element as pivot
    int location = low-1; //location指向比pivot小的元素段的尾部
    for(int i=low; i<high; ++i) {
        if (a[i] < pivot) {
            ++location;
            swap(a[i], a[location]);
        }
    }
    swap(a[location+1], a[high]);
    return location+1;
}
#endif

#ifdef M4
// scan from left to right, first element as pivot
int partition( int *a, int low, int high ) {
    int pivot = a[low]; // choose first element as pivot
    int location = low; //location指向比pivot小的元素段的尾部
    for(int i=low+1; i<=high; ++i) {
        if (a[i] < pivot) {
            ++location;
            swap(a[i], a[location]);
        }
    }
    swap(a[location], a[low]);
    return location;
}
#endif
/* sort a[low..high] */
void quicksort(int a[], int low, int high)
{ 
    if( high > low ) {
        int p = partition(a, low, high);
        quicksort(a, low, p-1);
        quicksort(a, p+1,  high);
    }
}

int main(int argc, char* argv[])
{
    /* initialize random seed: */
    srand (time(NULL));

    for(int n = 2; n < 200; ++n) {
        vector<int> A(n);
        for(int i=0; i<n; ++i) {
            A[i] = rand() % 101 - 50; // [-50, 50]
        }
        vector<int> B(A);
        vector<int> C(A);

        //for(int j=0;j<n;++j) { cout << A[j] << " "; } cout << endl;
        quicksort(&A[0], 0, A.size()-1);
        //for(int j=0;j<n;++j) { cout << A[j] << " "; } cout << endl;

        //for(int j=0;j<n;++j) { cout << B[j] << " "; } cout << endl;
        sort(B.begin(), B.end());
        //for(int j=0;j<n;++j) { cout << B[j] << " "; } cout << endl; 

        for(int i=0;i<n;++i) {
            if (A[i] != B[i]) {
                cout << "n = " << n << " failed test\n";
                for(int j=0;j<n;++j) { cout << C[j] << " "; } cout << endl; 
                for(int j=0;j<n;++j) { cout << A[j] << " "; } cout << endl; 
                for(int j=0;j<n;++j) { cout << B[j] << " "; } cout << endl; 
                return -1;
            }
        }
    }
    /*
    //int A[] = {2,1,3,0,5,3, 4, -1};
    //int A[] = {49, 17, -18, 33, 20, 12, -27};
    int A[] = {49, 17, -18, 33, 20, 12, -27};
    int N = sizeof(A)/sizeof(int);
    for(int i=0; i<N; ++i) { cout << A[i] << " ";} cout << endl;
    quicksort(A, 0, N-1);
    for(int i=0; i<N; ++i) { cout << A[i] << " ";} cout << endl;
    */
    return 0;
}
