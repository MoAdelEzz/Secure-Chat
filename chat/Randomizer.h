#pragma once


#include <cstdlib>
#include <string>
#include <fstream>
#include "BigInteger.h"

#define SUCCESSFUL_GENERATION 200

using std::string;
using std::to_string;
using std::ifstream;

class Randomizer
{
    const string filename;

    bool requestPrimeGeneration (  string start, string end )
    {
        string query = "python ./Randomizer.py " + this->filename + " " + start + " " + end;

        int returnCode = std::system ( query.c_str ( ) );

        return returnCode == SUCCESSFUL_GENERATION;
    }

    Bigint readValue ( )
    {
        ifstream primeFile ( this->filename );

        string line;
        while ( std::getline ( primeFile, line ) )
        {
            //TODO: check for the text if it's really a number

            if ( line.empty ( ) ) continue;
            Bigint bigInt ( line );
            return bigInt;
        }
    }

public:

    Randomizer ( string filename ) : filename ( filename ) {}

    Bigint generateRandomNumber (  string st , string en  )
    {

        string start =  st;
        string end =  en;

        return requestPrimeGeneration ( start, end ) ? readValue ( ) : Bigint ( );
    }
};