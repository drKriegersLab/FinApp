#ifndef TOOLS_H
#define TOOLS_H

#include <ctime>
#include <stdlib.h>

class tools
{
public:
    tools();
    /// function that generates an unsigned 5 digits random number
    /// it is a sum of two time dependent random number between 10 000 and 50 000
    static uint generateTimeDependentRandomUInt();
};

#endif // TOOLS_H
