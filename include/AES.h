#include <BigInteger.h>

class AES
{
    AES();

    BigInteger encrypt(BigInteger M, BigInteger K);
    BigInteger decrypt(BigInteger C, BigInteger K);
};