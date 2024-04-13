#include "../vendor/bigint.h"
using std::string;

class DiffieHellman
{
protected:
    bigint* q, alpha;
public:
    DiffieHellman(int numberOfBits)
    {
        // TODO: file must be decrypted using some sort of encryption we will ignore this for now 
        // 1- create an instance of big integer
        // 2- create a random big integer number from randomizer class
        // 3- make this numbers as a string and pass it to the BigNumber constructor

        // constraints
        // q should be a prime number
        // alpha < q and alpha is a primitive root
    }

    // Destory everything
    ~DiffieHellman();



    bigint generatePublicKey(string privateKey)
    {
        //TODO: generate the public key which is Y = alpha^X % q; 
    }

    bigint generateSessionKey(string otherPublicKey, string privateKey)
    {
        // TODO: generate the session key which is S = YB ^ XA % q;
    }

};