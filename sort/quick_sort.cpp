#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

//template <class ForwardIt>
 //void quicksort(ForwardIt first, ForwardIt last)
 void quicksort(vector<int>::iterator first, vector<int>::iterator last)
 {
    if(first == last) return;
 
    int pivot = *first;//choose_pivot(first,last);
 
    vector<int>::iterator middle1 = std::partition(first, last, 
                         [&pivot](const int& em){ return em < pivot; });
     std::cout << middle1-first << ", middle1: " << *middle1 << std::endl;
    for_each(first, last, [](const int v){cout << v << " ";});
    cout << endl;
    vector<int>::iterator middle2 = std::partition(middle1, last, 
                         [&pivot](const int& em){ return !(pivot < em); });
     std::cout << middle2-first << ", middle2: "  < *middle2<<std::endl;
    for_each(first, last, [](const int v){cout << v << " ";});
    cout << endl<<endl;
 
    quicksort(first, middle1);
    quicksort(middle2, last);
 }
 

int main(int argc, char* argv[])
{
    //vector<int> vi = {2,1,5,4,3,7,9,8, 1};
    vector<int> vi = {1, 2,1,5,4,3, 1};
/*
    for_each(vi.begin(), vi.end(), [](const int v){cout << v << " ";});
    cout << endl;
    auto p = partition(vi.begin(), vi.end(), bind2nd(less<int>(), 2));
    cout << p-vi.begin() << " : " << *p << endl;
    for_each(vi.begin(), vi.end(), [](const int v){cout << v << " ";});
    cout << endl;
*/
    for_each(vi.begin(), vi.end(), [](const int v){cout << v << " ";});
    cout << endl;
quicksort(vi.begin(), vi.end());
    for_each(vi.begin(), vi.end(), [](const int v){cout << v << " ";});
    cout << endl;

    return 0;
}
