#pragma once
#include <iostream>
#include "DataParser.h"
#include "BigInteger.h"
#include "Socket.h"
#include "Randomizer.h"

using namespace std;;

class Elgamal
{
private:
	Bigint q;
	Bigint alpha;
	Bigint privateKey, publicKey;

	Bigint otherPartyPublicKey;
	Randomizer* randomizer;

	SHA1 checksum;
public:
	Elgamal ( )
	{
		randomizer = new Randomizer ( "out2.txt" );
		FileParser* fileParser = FileParser::getParser ( );

		Bigint temp;
		string tempStr;


		q = Bigint ( fileParser->getValueOf ( "Q_GAMAL" ) );
		alpha = Bigint ( fileParser->getValueOf ( "ALPHA_GAMAL" ) );


		temp = q;
		tempStr = temp.a;
		reverse ( tempStr.begin ( ), tempStr.end ( ) );

		cout << "\n\n___________ Q_GAMAL:     " << tempStr << " ___________\n";

		temp = alpha;
		tempStr = temp.a;
		reverse ( tempStr.begin ( ), tempStr.end ( ) );


		cout << "___________ ALPHA_GAMAL: " << tempStr << " ___________\n";

	    temp = q - 2;
		tempStr = temp.a;
		reverse ( tempStr.begin ( ), tempStr.end ( ) );

		privateKey = randomizer->generateRandomNumber ( "2", tempStr );
		publicKey = pow ( alpha, privateKey, q );
	}


	string getPublicKey ( )
	{
		string s = this->publicKey.a;
		reverse ( s.begin ( ), s.end ( ) );
		return s;
	}

	void setOtherPartyKey ( Bigint key ) { otherPartyPublicKey = key; }

	bool verifySignature ( string message, Bigint s1, Bigint s2 )
	{
		checksum.update ( message );

		Bigint h ( checksum.final ( ) );
		Bigint v1 = (pow ( otherPartyPublicKey, s1, q ) * pow ( s1, s2, q )) % q;
		Bigint v2 = pow ( alpha, h, q );

		return v1 == v2;
	}

	vector<string> signMessage ( string message )
	{
		checksum.update ( message );

		Bigint temp = q - 1;
		string tempStr = temp.a;
		reverse ( tempStr.begin ( ), tempStr.end ( ) );

		Bigint k = randomizer->generateRandomNumber ( "2", tempStr );;
		string s1 = pow ( alpha, k, q ).a;
		reverse ( s1.begin ( ), s1.end ( ) );

		Bigint h = checksum.final ( );
		string s2 = (((h - privateKey * s1) * ModInv ( k, q - 1 )) % (q - 1)).a;
		reverse ( s2.begin ( ), s2.end ( ) );

		// This may cause error so check it later
		return vector<string> ( { s1, s2 } );
	}

};