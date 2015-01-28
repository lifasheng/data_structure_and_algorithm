#include <stdio.h>

// ok for positive interger, fail for negative integer.
int numOf1_v1 (int n) {
    int count = 0;
    while(n) {
        if(n & 1) ++count;
        n = n >> 1;
    }

    return count;
}

int numOf1_v2(int n) {
    int count = 0;
    unsigned int flag = 1;

    while(flag) {
        if (n & flag) ++count;
        flag <<= 1;
    }

    return count;
}

int numOf1_v3(int n) {
    int ret = 0;
    while(n) {
        ++ret;
        n &= (n-1);
    }
    return ret;
}

int main()
{
    for(int i=0; i<10; ++i) {
        printf("%d: ones:%d, ones:%d\n", i, numOf1_v2(i), numOf1_v3(i));
    }

    for(int i=-10; i<1; ++i) {
        printf("%d: ones:%d, ones:%d\n", i, numOf1_v2(i), numOf1_v3(i));
    }

    return 0;
}
