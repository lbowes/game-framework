#include <stdio.h>
#include "factorial.h"

int main() {
    const int result = factorial(4);
    if(result != 24) {
        printf("Test failed\n");
    }
    else {
        printf("Test passed\n");
    }

    return 0;
}