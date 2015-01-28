#include <stdio.h>

typedef unsigned char* byte_pointer;
void show_bytes(byte_pointer start, int len) 
{
    for(int i=0; i<len;++i) {
            printf(" %x", start[i]);
    }
    printf("\n");
}

int main(int argc, char* argv[])
{
    int a = 125;
    show_bytes((byte_pointer)&a, sizeof(int));

    return 0;
}
