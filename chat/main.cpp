#define WIN32_LEAN_AND_MEAN

#include "AES.h"
#include "sha1.h"
#include "BigInteger.h"
#include "DataParser.h"
#include "Elgamal.h"
#include "DiffieHellman.h"


#include <algorithm>
#include <sys/stat.h>

ByteArray stringToByteArray(string s)
{
    ByteArray arr;
    for (int i = 0; i < s.size(); i++)arr.push_back(s[i]);
    return arr;
}

string byteArrayToString(ByteArray arr, int length)
{
    string s = "";
    for (auto& x : arr)
    {
        s += x;
    }
    return s;
}


void test(SocketConnection socket)
{
    while (1)
    {
        string message;
        if (FileParser::getParser()->getValueOf("USER_TYPE") == "server")
        {
            cout << "Trying To Send Message" << endl;
            message = "testing connection";
            socket.sendMessage(message.c_str(), message.size());


            cout << "Trying To Recieve Message" << endl;
            message = "testing connection";
            cout << socket.recieveMessage() << endl;
        }

        else
        {
            cout << "Trying To Recieve Message" << endl;
            message = "testing connection";
            cout << socket.recieveMessage() << endl;


            cout << "Trying To Send Message" << endl;
            message = "testing connection";
            socket.sendMessage(message.c_str(), message.size());
        }
    }
}


int clientProcedure(FileParser* fileParser, DiffieHellman diffieHellman, Elgamal elgamalDS, SocketConnection& socket, std::string name )
{
    // exchange elgamal public key
    // wait for the other elgamal public key which is signed by elgamal ds
    string otherResponse = socket.recieveMessage();
    elgamalDS.setOtherPartyKey(Bigint(otherResponse));

    cout << "\n\n_____ Recieving Elgamal public key: " << otherResponse << " _____\n";


    // send the endpoint elgamal public key
    string message = elgamalDS.getPublicKey();
    socket.sendMessage(message.c_str(), message.size());

    cout << "\n\n_____ Sending Elgamal public key: " << message << " _____\n";


    // wait for the other DH public key
    otherResponse = socket.recieveMessage();
    vector<string> splittedResponse = fileParser->splitByDelim(otherResponse, ' ');

    cout << "\n\n_____ Recieving Diffie Hellman with Digital Signature" << " _____\n";

    // now we send DH public key after signing it using Elgamal digital signature
    string publicDHString = diffieHellman.getPublicKey();
    vector<string> elgamalSign = elgamalDS.signMessage(publicDHString);

    message = diffieHellman.getPublicKey() + " " + elgamalSign[0] + " " + elgamalSign[1];
    socket.sendMessage(message.c_str(), message.size());

    cout << "\n\n_____ Sending Diffie Hellman with Digital Signature" << " _____\n";


    // checking signature
    Bigint publicDHOther(splittedResponse[0]);
    Bigint s1(splittedResponse[1]);
    Bigint s2(splittedResponse[2]);

    if (!elgamalDS.verifySignature(splittedResponse[0], s1, s2))
    {
        // Do Smth to imply a bad signature
        return 255;
    }
    else
    {
        cout << "\n\n_____ Digital Signature Verified, Generating AES Key..." << " _____\n";

        diffieHellman.generateSharedKey ( publicDHOther );

        ByteArray tempArr = diffieHellman.getSharedKey ( );
        std::string tempStr;
        for ( int i = 0; i < tempArr.size ( ); i++ ) {
            tempStr.push_back ( tempArr[i] );
        }


        cout << "\n\n_____ AES Shared Key: " << tempStr << " _____\n\n\n";
    }


    string otherName = socket.recieveMessage ( );
    socket.sendMessage ( name.c_str ( ), name.size ( ) );
   

    SetConsoleTextAttribute ( hConsole, 9 );
    cout << "####################################################\n";
    cout << "                 Say Hi to " << otherName << "                  " << endl;
    cout << "####################################################\n\n\n";


    return 0;
}


int serverProcedure(FileParser* fileParser, DiffieHellman diffieHellman, Elgamal elgamalDS, SocketConnection& socket, std::string name)
{
    // exchange elgamal public key
    // send the endpoint elgamal public key
    string message = elgamalDS.getPublicKey();
    socket.sendMessage(message.c_str(), message.size());

    cout << "\n\n_____ Sending Elgamal public key: " << message << " _____\n";

    // wait for the other elgamal public key which is signed by elgamal ds
    string otherResponse = socket.recieveMessage();
    elgamalDS.setOtherPartyKey(Bigint(otherResponse));

    cout << "\n\n_____ Recieving Elgamal public key: " << otherResponse << " _____\n";



    // now we send DH public key after signing it using Elgamal digital signature
    string publicDHString = diffieHellman.getPublicKey();
    vector<string> elgamalSign = elgamalDS.signMessage(publicDHString);

    message = diffieHellman.getPublicKey() + " " + elgamalSign[0] + " " + elgamalSign[1];
    socket.sendMessage(message.c_str(), message.size());

    cout << "\n\n_____ Sending Diffie Hellman with Digital Signature" << " _____\n";

    
    // wait for the other DH public key
    otherResponse = socket.recieveMessage();
    vector<string> splittedResponse = fileParser->splitByDelim(otherResponse, ' ');

    cout << "\n\n_____ Recieving Diffie Hellman with Digital Signature" << " _____\n";

    // checking signature
    Bigint publicDHOther(splittedResponse[0]);
    Bigint s1(splittedResponse[1]);
    Bigint s2(splittedResponse[2]);

    if (!elgamalDS.verifySignature(splittedResponse[0], s1, s2))
    {
        // Do Smth to imply a bad signature
        return 255;
    }
    else
    {

        cout << "\n\n_____ Digital Signature Verified, Generating AES Key..." << " _____\n";
        
        diffieHellman.generateSharedKey(publicDHOther);

        ByteArray tempArr = diffieHellman.getSharedKey ( );
        std::string tempStr;
        for ( int i = 0; i < tempArr.size ( ); i++ ) {
            tempStr.push_back ( tempArr[i] );
        }


        cout << "\n\n_____ AES Shared Key: " << tempStr << " _____\n\n\n";
    }


    socket.sendMessage ( name.c_str ( ), name.size ( ) );
    string otherName = socket.recieveMessage ( );

    SetConsoleTextAttribute ( hConsole, 9 );

    cout << "####################################################\n";
    cout << "                 Say Hi to " << otherName << "                  " << endl;
    cout << "####################################################\n\n\n";


    return 0;
}

int __cdecl main ( int argc, char** argv )
{
    if (argc < 3)
    {
        cout << "Please Provide A Config File" << endl;
        return 400;
    }

    struct stat sb;

    if (stat(argv[2], &sb) != 0)
    {
        cout << "No Such File Exists...";
        return 404;
    }
   
    std::string name;
    cout << "please enter your name: ";
    cin >> name;
    system ( "cls" );
    FileParser* fileParser = FileParser::getParser();
    fileParser->parseFile(argv[2]);
    
    string processType = fileParser->getValueOf("USER_TYPE");
    if (processType.empty())
    {
        cout << "U Should Provide the process type in the config";
        return 402;
    }

    cout << "####################################################\n";
    cout << "                 Hello " << name << "                  " << endl;
    cout << "####################################################\n";

    HANDLE hThread;
    DWORD dwThreadID;

    DiffieHellman diffieHellman;
    Elgamal elgamalDS;
    SocketConnection socket = SocketConnection();


    int exchange_status;

    if (processType == "client")
    {
        exchange_status = clientProcedure(fileParser, diffieHellman, elgamalDS, socket, name);
    }
    else
    {
        exchange_status = serverProcedure(fileParser, diffieHellman, elgamalDS, socket, name);
    }

    if (exchange_status != 0)
    {
        cout << "Something went wrong while exchanging keys ....";
        return 403;
    }






    // Receive until the peer closes the connection


    ByteArray keyArray = diffieHellman.getSharedKey ( );
    
    Aes256 aes = Aes256 ( keyArray );

    socket.createReadingThread ( keyArray );
    SetConsoleTextAttribute ( hConsole, 14 );

    do
    {

        SetConsoleTextAttribute ( hConsole, 14 );

        string originalMessageString;
        string encryptedMessageString;


        if (!std::getline(std::cin, originalMessageString))
            break;

        cout << "\n";

        ByteArray originalMessageArray = stringToByteArray(originalMessageString);
        ByteArray encryptedMessageArray;
        

        int encryptedMessageSize = aes.encrypt ( keyArray, originalMessageArray, encryptedMessageArray );


        encryptedMessageString = byteArrayToString(encryptedMessageArray, encryptedMessageSize);

        if ( originalMessageString != "" )
            socket.sendMessage ( encryptedMessageString.c_str ( ), encryptedMessageString.size ( ) );
      
    } while ( true );


    delete fileParser;
    return 0;
}