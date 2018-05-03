#include "tools.h"
#include <stdlib.h>
#include <iostream>


tools::tools()
{

}

uint tools::generateTimeDependentRandomUInt() {
    // initialize random seed with the calendar time converted to int
    int time1 = (int)time(NULL);
    srand(time1);
    int rand1;
    uint cyc = 0;
    do {
        rand1 = rand();
        cyc++;
    } while((cyc < 500) || ((rand1 > 100000) && (rand1 < 500000)));

    // initialize random seed with the ticks what the CPU counted during used by this process
    srand(clock());
    int rand2;
    cyc = 0;
    do {
        rand2 = rand();
        cyc ++;
    } while((cyc < 500) || ((rand2 > 100000) && (rand2 < 500000)));

    return (uint)rand1 + (uint)rand2;
    // note: this solution is more randomly than the usually used rand()%range + swipe, because the probability of linear deviation of the numbers
    // are higher than if you just get the modulo of a number value
}
