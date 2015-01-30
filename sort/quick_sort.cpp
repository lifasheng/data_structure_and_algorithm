//g++ quick_sort.cpp -std=c++11; ./a.out
#include <iostream>
#include <iterator>
#include <vector>
#include <algorithm>
using namespace std;

// 这个和firstHigh的思路有点类似。
// firstHigh: http://www.alwayslearn.com/computer%20algorithms/ComputerAlgorithms_QuickSort.html
// 细想一下，你会发现差别：
// 以前学的partition，都是将数组或链表按某个数分成三段，[<pivot>[pivot][>=pivot], 返回pivot的位置;
// 而这里的mypartition, 是std::partition的一种可能的实现。它就数组或链表按照一个判定方法分成两段[true][false], 返回[false]区域的第一个位置。
// 对于排序来说，第一种方法一遍就能完成就地(in-place)划分，而第二种方法要两边才能完成，见下面的quicksort实现。
// 但是第二种方法的通用非常好，能适合很多需要划分的问题，包括排序。
template <class ForwardIterator, class UnaryPredicate>
ForwardIterator mypartition(ForwardIterator first, ForwardIterator last, UnaryPredicate pred) {
    ForwardIterator pos = first;
    for(; first != last; ++first) {
        if (pred(*first)) {
            std::swap(*pos, *first);
            ++pos;
        }
    }

    return pos;
}

template <class ForwardIterator>
void quicksort(ForwardIterator first, ForwardIterator last)
{
    if(first == last) return;

    typedef typename iterator_traits<ForwardIterator>::value_type ValueType;
    ValueType pivot = *first;//choose_pivot(first,last);

    // partition将符合条件的元素放在前面，不符合的放在后面,并返回第一个不符合的位置。
    // 第一次调用，将小于pivot的划分到middle1的前面了，
    // 第二次调用将小于等于pivot的放在middle2的前面，但是在middle1的后面。
    // 第二次调用相当于把等于pivot的放在了中间位置，最终的顺序是：[<pivot] [=pivot] [>pivot]
    // 这里的!(pivot<em)是要求ValueType实现<就行。
#if 0
    ForwardIterator middle1 = std::partition(first, last, [&pivot](const int& em){ return em < pivot; });
    ForwardIterator middle2 = std::partition(middle1, last, [&pivot](const int& em){ return !(pivot < em); });
#else
    ForwardIterator middle1 = mypartition(first, last, [&pivot](const ValueType& em){ return em < pivot; });
    ForwardIterator middle2 = mypartition(middle1, last, [&pivot](const ValueType& em){ return !(pivot < em); });
#endif

    quicksort(first, middle1);
    quicksort(middle2, last);
}
 

int main(int argc, char* argv[])
{
    /* initialize random seed: */
    srand (time(NULL));

    for(int n = 2; n < 2000; ++n) {
        vector<int> A(n);
        for(int i=0; i<n; ++i) {
            A[i] = rand() % 101 - 50; // [-50, 50]
        }
        vector<int> B(A);
        vector<int> C(A);

        //for(int j=0;j<n;++j) { cout << A[j] << " "; } cout << endl;
        quicksort(A.begin(), A.end());
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

    return 0;
}
