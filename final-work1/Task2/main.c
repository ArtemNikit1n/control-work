#include "testForStack.h"

#include <stdio.h>
#include <stdbool.h>

void testTask2(bool* errorCode) {
    return;
}

int main(void) {
    bool errorCode = false;
    runStackTest(&errorCode);

    testTask2(&errorCode);
    if (errorCode) {
        printf("Tests failed");
    }
    else {
        printf("Tests passed");
    }

    return errorCode;
}