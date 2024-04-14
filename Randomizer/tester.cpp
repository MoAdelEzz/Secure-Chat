#include <iostream>
#include "Randomizer.h"
#include <cstdlib> // For std::system
using namespace std;

int main()
{
    Randomizer R("key.txt");
    
    R.generateRandomNumber(500).print();
    R.generateRandomNumber(500).print();
    R.generateRandomNumber(500).print();

}