#include <stdio.h>

template <typename T>
void num2bits(T t)
{
    const int n = sizeof(T) * 8;
    char buf[n];
    for(int i=0; i<n; ++i) {
        buf[i] = t & 0x01;
        t >>= 1;
    }
    for(int i=n-1;i>=0;--i) {
        printf("%d", buf[i]);
        if(i%4==0)printf(" ");
    }
    printf("\n");
}

int main(int argc, char* argv[])
{
    num2bits(10);
    return 0;
}
