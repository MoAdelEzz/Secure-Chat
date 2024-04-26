#pragma once
#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>

#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <cstring>
#include<iostream>
#include <fstream>
#include<cmath>
#include<math.h>

#define DEFAULT_BUFLEN 512
#define DEFAULT_PORT "1010"

// Need to link with Ws2_32.lib, Mswsock.lib, and Advapi32.lib
#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")

ByteArray keyArray;
HANDLE hConsole = GetStdHandle ( STD_OUTPUT_HANDLE );



DWORD WINAPI ReadingThread ( LPVOID param );

class SocketConnection
{
public:
    WSADATA wsaData;
    SOCKET mySocket = INVALID_SOCKET;
    SOCKET otherSocket = INVALID_SOCKET;
    
    char sendbuf[DEFAULT_BUFLEN];

    char recvbuf[DEFAULT_BUFLEN];

    string ack = "MoAWasHere";



    void dllInit()
    {
        int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
        if (iResult != 0) 
        {
            printf("WSAStartup failed with error: %d\n", iResult);
            exit(400);
        }
    }

    void createSocket()
    {
        mySocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
        if (mySocket == INVALID_SOCKET)
        {
            printf("Socket Initialization Failed, Try Again...\n");
            exit(400);
        }
        else
        {
            SetConsoleTextAttribute ( hConsole,FOREGROUND_GREEN  );
            printf("\n\n____________ Socket Created Successfully ____________\n");
        }

    }

    addrinfo* getAddressInfo(string address, string port)
    {
        struct addrinfo* result = NULL;
        struct addrinfo hints;

        ZeroMemory(&hints, sizeof(hints));
        hints.ai_family = AF_INET;
        hints.ai_socktype = SOCK_STREAM;
        hints.ai_protocol = IPPROTO_TCP;
        hints.ai_flags = AI_PASSIVE;


        // Resolve the server address and port
        int iResult = getaddrinfo(address.c_str(), port.c_str(), &hints, &result);
        if (iResult != 0) {
            printf("Failed To Get Information Of The Address Please Try Again....\n");
            exit(400);
        }

        return result;
    }

    // Each Socket Will Have It's Own IP:Port address so in this function
    // We Assign The Socket To An Address
    void bindSocket(string address, string port)
    {
        struct addrinfo* result = getAddressInfo(address, port);

        // Setup the TCP listening socket
        int iResult = bind(mySocket, result->ai_addr, (int)result->ai_addrlen);
        if (iResult == SOCKET_ERROR) {
            printf("bind failed with error: %d\n", WSAGetLastError());
            freeaddrinfo(result);
            closesocket(mySocket);
            WSACleanup();
            exit(400);
        }


        freeaddrinfo(result);
    }
   
    void listenToSocket() // 10 trials untill failure
    {
        if (listen(mySocket, 1) == SOCKET_ERROR)
        {
            printf("error listening to the socket....\n");
            WSACleanup();
            exit(400);
        }

        //printf("Listening To Connections execution will be paused now...\n");

        int trials = 10;
        do
        {
            otherSocket = accept(mySocket, nullptr, nullptr);
            if (otherSocket == INVALID_SOCKET)
            {
                printf("Connection Failed, trying again (%d trials left) ...", --trials);
            }
        } while (trials && otherSocket == INVALID_SOCKET);

        if (!trials)
        {
            cout << "Failed To Connect Shutting Down\n";
            WSACleanup();
            exit(400);
        }
    }

    // address and port of the server
    void connectToSocket(string address, string port)
    {
        struct addrinfo* result = getAddressInfo(address, port);

        int trials = 10;
        int iResult;
        do
        {
            iResult = connect(mySocket, result->ai_addr, (int)result->ai_addrlen);
            if (iResult == INVALID_SOCKET)
            {
                printf("Connection Failed, trying again (%d trials left) ...", --trials);
            }
        } while (trials && iResult);

        if (!trials)
        {
            cout << "Failed To Connect Shutting Down\n";
            WSACleanup();
            exit(400);
        }
    }




    void destroySocket()
    {
        closesocket(mySocket);
    }

    
    void clientConstructor()
    {
        FileParser* fileParser = FileParser::getParser();
        dllInit();
        createSocket();
        connectToSocket(fileParser->getValueOf("ADDRESS"), fileParser->getValueOf("SERVER_PORT"));
        otherSocket = mySocket;
    }

    void serverConstructor()
    {
        FileParser* fileParser = FileParser::getParser();
        dllInit();
        createSocket();
        bindSocket(fileParser->getValueOf("ADDRESS"), fileParser->getValueOf("PORT"));
        listenToSocket();
    }

    bool isClient()
    {
       FileParser* fileParser = FileParser::getParser();
       return fileParser->getValueOf("USER_TYPE") == "client";
    }



    SocketConnection()
	{
        memset(sendbuf, '\0', DEFAULT_BUFLEN);
        memset(recvbuf, '\0', DEFAULT_BUFLEN);
        if (isClient()) clientConstructor();
        else serverConstructor();
	}

    ~SocketConnection()
    {
        WSACleanup();
        destroySocket();
    }

 

    void createReadingThread ( ByteArray keyArray ) {


        HANDLE hThread;
        DWORD dwThreadID;
        keyArray = keyArray;
        hThread = CreateThread ( NULL, 0, &ReadingThread, (void*)this, 0, &dwThreadID );
        if ( !hThread )
        {
            printf ( "Error at CreateThread ( )\n" );
            WSACleanup ( );
            exit ( 400 );
        }

    }

    bool sendMessage(const char* message, int length )
    {
        memcpy(sendbuf, message, length);
        sendbuf[length] = '\0';

        int iResult = send(otherSocket, sendbuf, DEFAULT_BUFLEN, 0);

        if (iResult == SOCKET_ERROR) {
            printf("send failed with error: %d\n", WSAGetLastError());
            return false;
        }

        memset(sendbuf, '\0', length);
    
        return true;
    }

    string recieveMessage( )
    {
        int iResult = recv(otherSocket, recvbuf, DEFAULT_BUFLEN, 0);

        recvbuf[DEFAULT_BUFLEN - 1] = '\0';

        if (recvbuf[0] == '\0')
        {
            cout << "Other EndPoint Has Terminated\n";
            exit(0);
        }


        string originalMessageString;
        for (auto c : recvbuf)
        {
            if (c == '\0') break;
            originalMessageString.push_back(c);
        }
        memset(recvbuf, '\0', originalMessageString.size());
        return originalMessageString;
    }

};



DWORD WINAPI ReadingThread ( LPVOID param )
{
    SocketConnection s = *static_cast<SocketConnection*>(param);

    Aes256 aes = Aes256 ( keyArray );

    do
    {


        std::string receivedMessageString = s.recieveMessage ( );
        ByteArray receivedMessageArray;

        for ( int i = 0; i < receivedMessageString.size ( ); i++ )receivedMessageArray.push_back ( receivedMessageString[i] );

        std::string originalMessageString;
        ByteArray originalMessageArray;



        int originalMessageSize = aes.decrypt ( keyArray, receivedMessageArray, originalMessageArray );


        for ( int i = 0; i < originalMessageSize; i++ )originalMessageString.push_back ( originalMessageArray[i] );




        SetConsoleTextAttribute ( hConsole, BACKGROUND_GREEN );

        cout << setw ( 70 ) << setiosflags ( ios::right ) << originalMessageString;

        SetConsoleTextAttribute ( hConsole, 14 );

        cout << '\n';

        cout << endl;




    } while ( true );

    return 0;
}
