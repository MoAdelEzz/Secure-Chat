#include "BigInteger.h"
#include <cstdlib>
#include <string>
#include <fstream>

#define SUCCESSFUL_GENERATION 200

using std::string, std::to_string, std::ifstream;

class Randomizer
{
    const string filename;
    
    bool requestPrimeGeneration(string bits, string start, string end)
    {
        string query = "python ./Randomizer.py " + bits + " " + this->filename + " " + start + " " + end;


        std::cout << query << std::endl;

        int returnCode = std::system(query.c_str());
        
        return returnCode == SUCCESSFUL_GENERATION;
    }

    BigInteger readValue()
    {
        ifstream primeFile(this->filename);
        
        string line;
        while (std::getline(primeFile,line))
        {
            //TODO: check for the text if it's really a number

            if (line.empty()) continue;
            BigInteger bigInt(line);
            return bigInt;
        }
    }

public:

    Randomizer(string filename): filename(filename){}

    BigInteger generateRandomNumber(unsigned long long numberOfBits, int st = 0, int en = -1)
    {
        if (st > en && en != -1) 
            throw "INVALID RANGE: start must be less than or equal end";

        string start = to_string(st);
        string end = to_string(en);
        string bits = to_string(numberOfBits);

        return requestPrimeGeneration(bits, start, end) ? readValue() : BigInteger();
    }
};