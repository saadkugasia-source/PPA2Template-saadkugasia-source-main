#include <stdio.h>
#include <stdlib.h> // to use many functions like calloc or malloc or randome number generation
#include <time.h>   // to seed the rand by time in srand
#include "MacUILib.h"

typedef struct
{
    float coeff;
    int power;
    char symbol[4];
} Monom; // if u use typedef then semi-collon is needed

int main(void)
{
    Monom mono1 = {-3.1, 12}; // Monom is only needed when initializing
    printf("Coeff: %.2f\n", mono1.coeff);
    printf("Power: %d\n", ++mono1.power);

    printf("\n");

    Monom *mptr = &mono1; // Monom is only needed when initializing

    printf("Coeff: %.2f\n", mptr->coeff);
    printf("Power: %d\n", mptr->power);

    // printf('\n'); // u can't do this, have to use double quoates

    printf("\n");

    mono1.coeff = 3.5;
    mptr->power = 3;

    printf("Coeff: %.2f\n", mptr->coeff);
    printf("Power: %d\n", mptr->power);

    printf("\n");

    mptr->symbol[0] = '<';
    mptr->symbol[1] = 'H';
    mptr->symbol[2] = '>';
    mptr->symbol[3] = '\0'; // every string has this in the back or end of it, afterall string is a array of characters!!

    printf("Symbol: %s\n", mptr->symbol); // remember to use %s instean of %c for strings!!
}
