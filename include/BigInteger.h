#include <vector>
#include <string>

using std::vector, std::string;

// this class is used to support very large number - scale of 1000 bit numbers - 
// this will be used to support large key lengths

// @MOA will make it isa
class BigInteger
{
    vector<int> number;
public:
    BigInteger(const BigInteger& B)
    {
       for (auto& x : B.number) this->number.push_back(x);
    }

    BigInteger()
    {
        // empty Instance
    }

    BigInteger(string bigString)
    {
        // each character will represent a number, each number will take 4 bits out of 32 bits so we can store every 8 numbers in one 
        // integer entry

    }


    BigInteger operator + (const BigInteger& B)
    {
        //TODO: implement this
    } 

    
    BigInteger operator - (const BigInteger& B)
    {
        //TODO: implement this
    } 

    
    BigInteger operator * (const BigInteger& B)
    {
        //TODO: implement this
    } 

    
    BigInteger operator / (const BigInteger& B)
    {
        //TODO: implement this
    } 

    
    BigInteger operator % (const BigInteger& B)
    {
        //TODO: implement this
    } 

    bool operator < (const BigInteger& B)
    {
        // TODO: implement this
    }

    bool operator <= (const BigInteger& B)
    {
        // TODO: implement this
    }

    bool operator > (const BigInteger& B)
    {
        // TODO: implement this
    }

    bool operator >= (const BigInteger& B)
    {
        // TODO: implement this
    }

    bool operator == (const BigInteger& B)
    {
        // TODO: implement this
    }
};