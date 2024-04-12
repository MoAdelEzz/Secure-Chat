#include <Randomizer.h>
#include <DiffieHellman.h>

// Public => Q, alpha, YA
class Elgamal : DiffieHellman
{
protected:
    BigInteger* k;

public:
    Elgamal(int numberOfBits) : DiffieHellman(numberOfBits) 
    {
        //same as diffie hellman constructor but for the k value
        // remember to make k less than or equal to q
        // NOTE: DH constructor is called first so you can use q value without problems to check
    }

    BigInteger* signMessage(BigInteger M)
    {
        // implement Elgamal algorithm here and return both ciphertext elements
        // create the array dynamically please in order not to delete it while returning
    }


    BigInteger generatePublicKey(string privateKey)
    {
        //TODO: generate the public key which is Y = alpha^X % q; 
    }

    BigInteger generateSessionKey(string otherPublicKey, string privateKey)
    {
        // TODO: generate the session key which is S = YB ^ XA % q;
    }

};