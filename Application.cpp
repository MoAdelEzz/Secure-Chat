#include <iostream>
#include "BigInteger.h"
using namespace std;

int main()
{
    BigInteger A("5651231861216165165");
    BigInteger B("6313252351");

    BigInteger C = A / B;

    C.print();
    return 0;
}