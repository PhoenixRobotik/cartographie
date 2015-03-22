#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#include "geometrie.h"
#include "obstacles.h"

// À initialiser


int main() {
    coord a,b;
    a.x=0;
    a.y=1;
    b.x=1;
    b.y=1;

    printf("%f\n", distance(a,b));

    return 0;
}
