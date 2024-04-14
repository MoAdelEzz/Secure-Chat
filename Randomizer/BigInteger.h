#include <iostream>
#include <vector>
#include <string>

using std::vector, std::string, std::max;


#define MAX_DIGITS 1000

// this class is used to support very large number - scale of 1000 bit numbers - 
// this will be used to support large key lengths

// @MOA will make it isa
class BigInteger
{
    vector<int> number;
    int count = 0;
    bool sign = false; // false => positive, true => negative

    BigInteger shiftByTen(BigInteger A, int amount)
    {
        BigInteger result;
        result.count = A.count + amount;

        for (int i = amount; i < A.count + amount; i++)
        {
            result.number[i] = A.number[i - amount];
        }
        return result;
    }

    string intToString(int x)
    {
        string s = "";
        while(x)
        {
            int digit = x % 10;
            x /= 10;
            s += digit + '0';
        }
        return s;
    }
public:
    BigInteger(const BigInteger& B)
    {
       number.resize(MAX_DIGITS, 0);
       for (auto& x : B.number) this->number[count++] = x;
       count = B.count;
       sign = B.sign;
    }

    BigInteger(int x) : BigInteger(intToString(x)){}

    BigInteger()
    {
        // empty Instance
        number.resize(MAX_DIGITS, 0);
        count = 0;
        sign = false;
    }

    BigInteger(string bigString)
    {
        // each character will represent a number, each number will take 4 bits out of 32 bits so we can store every 8 numbers in one 
        // integer entry

        number.resize(MAX_DIGITS, 0);
        for (auto it = bigString.end(); it != bigString.begin(); it--)
        {
            char c = *(it - 1);
            
            bool isSign = c == '-' || c == '+';
            if (isSign) {
                this->sign = (c == '-');
                continue;
            }

            bool isDigit = c >= '0' && c <= '9'; 
            if (!isDigit) throw "invalid argument: string must all consist of digits";

            this->number[count++] = c - '0';
        }
    }


    bool operator < (const BigInteger& B)
    {
        if (this->count > B.count)
            return false;

        if (this->count < B.count)
            return true;
        
        for (int i = this->count - 1; i >= 0; i--)
        {
            if (this->number[i] < B.number[i]) return true;
            if (this->number[i] > B.number[i]) return false;
        }

        return false;
    }

    bool operator <= (const BigInteger& B)
    {
        return *this < B || *this == B;
    }

    bool operator > (const BigInteger& B)
    {
        bool notLess = !(*this < B);
        bool notEqual = !(*this == B);
        return notLess && notEqual;
    }

    bool operator >= (const BigInteger& B)
    {
        return !(*this < B);
    }

    bool operator == (const BigInteger& B)
    {
        if (this->count != B.count) return false;

        for (int i = 0; i < count; i++) 
            if (this->number[i] != B.number[i]) return false;

        return true;
    }

    // ======================================================================================================
    void print()
    {
        if (count == 0)
        {
            std::cout << "0";
            return;
        }
        if (sign) std::cout << "-";
        for (int i = count - 1; i >= 0 ; i--)
        {
            std::cout << number[i];
        }
        std::cout << std::endl;
    }
    // ======================================================================================================
    BigInteger operator + (const BigInteger& B)
    {
        //TODO: implement this
        int n = max(this->count, B.count);
        int carry = 0;
        BigInteger result;

        if (this->sign != B.sign)
        {
            return *this - B;
        }

        result.sign = this->sign;

        for (int i = 0; i < n || carry; i++)
        {   
            result.number[i] = (this->number[i] + B.number[i] + carry) % 10;
            carry = (this->number[i] + B.number[i] + carry) / 10;
            result.count++;
        }

        return result;
    } 
    
    BigInteger operator +(int x)
    {
        BigInteger X(x);
        return *this + X;
    }
    
    BigInteger operator - (const BigInteger& B)
    {
        //TODO: implement this

        BigInteger result;

        if (this->sign != B.sign)
        {
            BigInteger C(B);
            C.sign = !B.sign;
            return *this + C;
        }

        if (*this == B)
            return result; // zero 

        // sign decision
        if (*this < B)
        {
            result.sign = !B.sign;
        }
        else 
        {
            result.sign = this->sign;
        }

        // subtracting smaller from larger now => result = x - y; where x > y
        auto x = (*this > B) ? this->number.begin() : B.number.begin();
        auto y = (x == B.number.begin()) ? this->number.begin() : B.number.begin();

        int n = max(B.count, this->count);
        int borrow = 0;

        int lst = 0;

        for (int i = 0; i < n; i++)
        {
            int xn = *x, yn = *y;
            
            if (yn > xn - borrow)
            {
                result.number[i] = (xn - borrow + 10) - yn;
                borrow = 1;
            }
            else 
            {
                result.number[i] = (xn - borrow) - yn;
                borrow = 0;
            }
            

            if (result.number[i] != 0) lst = i;
            x++, y++;
        }

        result.count = lst + 1;

        return result;
    } 

    
    BigInteger operator * (const BigInteger& B)
    {
        //TODO: implement this
        BigInteger result;
        for (int i = 0; i < B.count; i++)
        {
            int x = B.number[i];
            result = result + shiftByTen((*this) * x, i);
        }

        int mx = this->count + B.count;
        for (int i = mx - 1 ; i >= 0; i--)
        {
            if (result.number[i] != 0)
            {
                result.count = i + 1;
                break;
            }
        }

        return result;
    } 

    BigInteger operator * (const int& x)
    {
        BigInteger result;
        int carry = 0;
        int mx = this->count;

        for (int i = 0; ; i++)
        {
            int dummy = (x * this->number[i]);
            if (dummy + carry == 0 && i >= mx) break;

            result.number[i] = (dummy + carry) % 10;
            carry = (dummy + carry) / 10;
            result.count++;
        }
        return result;
    }

    // 0 will return the quotient while anything else will return the remainder
    BigInteger longDivision(const BigInteger& B, bool mood = 0)
    {
        //TODO: implement this
        if (*this < B) return BigInteger();
        if (*this == B) return BigInteger("1");

        BigInteger Q = B;
        BigInteger C;
        BigInteger result;
        int it = 0;
        
        int last = this->count - 1;
        bool flag = false;
        
        for (int i = 0; i < this->count; i++)
        {
            C = shiftByTen(C,1) + this->number[last - i];
            if (C < Q) 
            {
                if (flag) result.number[it++] = 0;
                continue;
            }

            flag = true;

            for (int quotient = 9; quotient >= 1; quotient--)
            {
                BigInteger Z = Q * quotient;
                if (C >= Z)
                {
                    C = C - Z;
                    result.number[it++] = quotient;
                    break;
                }
            }
        }

        if (mood) return C;
        
        BigInteger rev;
        rev.count = it;
        for (int i = it - 1; i >= 0; i--)
        {
            rev.number[it - 1 - i] = result.number[i];
        }
        return rev;
    }


    BigInteger operator / (const BigInteger& B)
    {
        return longDivision(B);
    } 

    
    BigInteger operator % (const BigInteger& B)
    {
        return longDivision(B,1);
    } 


};
