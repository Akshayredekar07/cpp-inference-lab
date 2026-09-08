// bad_as_cpp.c
#include <stdlib.h>
int main(void) {
    int* p = ((int*)malloc(4 * sizeof(int)));   // C: implicit void* -> int* OK
    
    for (int i = 0; i < 4; ++i) p[i] = i;
    free(p);
    return 0;
}