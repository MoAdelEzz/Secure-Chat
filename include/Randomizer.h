#include "Utils.h"
#include "../vendor/bigint.h"

class Randomizer
{
    Randomizer(int seed);

    bigint generateRandomNumber(uint numberOfBits, int st = 0, int en = inf)
    {
        if (st > en) 
            throw "INVALID RANGE: start must be less than or equal end";

        // TODO: create Multiple random integer values which is 32 bits each till you reach the target number of bits and return it
        // optionally will pass some limits for the number
        // inf is just -1 not max as there will be no max :)

        return bigint("");
    }
};