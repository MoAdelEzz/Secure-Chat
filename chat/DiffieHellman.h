#include <iostream>
#include <string>
#include "BigInteger.h"
#include "Randomizer.h"

using namespace std;

class DiffieHellman
{
	Bigint q;
	Bigint alpha;
	Bigint privateKey, publicKey;
	Randomizer *randomizer;
	Bigint sharedKey;

public:
	DiffieHellman()
	{
		HANDLE hConsole = GetStdHandle ( STD_OUTPUT_HANDLE );
		SetConsoleTextAttribute ( hConsole, FOREGROUND_RED );

		randomizer = new Randomizer ( "out.txt" );
		FileParser* fileParser = FileParser::getParser();
		Bigint temp;
		string tempStr;

		q = Bigint(fileParser->getValueOf("Q_DH"));
		alpha = Bigint(fileParser->getValueOf("ALPHA_DH"));

		temp = q;
		tempStr = temp.a;
		reverse ( tempStr.begin ( ), tempStr.end ( ) );

		cout << "\n\n____________ Q_DH:      " << tempStr <<" ____________\n";

		temp = alpha;
		tempStr = temp.a;
		reverse ( tempStr.begin ( ), tempStr.end ( ) );
		

		cout << "____________ ALPHA_DH:  " << tempStr << " ____________\n";



		temp = q - 1;
		tempStr = temp.a;
		reverse ( tempStr.begin ( ), tempStr.end ( ) ); 
	    privateKey = randomizer->generateRandomNumber ( "2", tempStr );
		publicKey = pow(alpha, privateKey, q);
	}

	string getPublicKey() 
	{
		string s = publicKey.a;
		reverse(s.begin(), s.end());
		return s; 
	}

	void generateSharedKey(Bigint otherPartyKey)
	{
		sharedKey = pow(otherPartyKey, privateKey, q);
	}

	ByteArray getSharedKey()
	{
		string shared = sharedKey.a;
		reverse(shared.begin(), shared.end());

		ByteArray keyArray;
		for (int i = 0; i < shared.size(); i++) keyArray.push_back(shared[i]);

		return keyArray;
	}
	~DiffieHellman ( ) {
		delete randomizer;
	}
};