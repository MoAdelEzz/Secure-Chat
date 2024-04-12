
// i will struct this later but it should work as following
// sender will ping the reciever and wait for him to answer
// reciever will ping sender as acknowledge process
// sending process will start will reciever will listen to him
class Socket
{
    Socket();

    void connect();
    void disconnect();
    void send();
    void recieve();
    void ping();
};