#include "../vendor/bigint.h"

class AES
{
    AES();

    bigint encrypt(bigint M, bigint K);
    bigint decrypt(bigint C, bigint K);
};