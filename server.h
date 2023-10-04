#ifndef SERVER_H
#define SERVER_H

#include "Poco/Net/ServerSocket.h"
#include "Poco/Net/SocketStream.h"

class iServer
{
    virtual void open()    = 0;
    virtual void run()     = 0;
    virtual void close()   = 0;
};

class smplServer : public iServer
{
private:
    const int MAX_MSG_SIZE = 256;

    Poco::Net::ServerSocket  server;        
    Poco::Net::SocketAddress socketAddress;

    bool running = true;

public:
    smplServer(std::string &);
    smplServer(std::string, std::string);

    ~smplServer();

    void newAddress(Poco::UInt16);                 // Set new socket adress
    void newAddress(std::string&, std::string&);    // Set new socket adress
    

    void listenClient(Poco::Net::StreamSocket);  // Infinite loop waiting for a message from the client

    void open();    // Function to connect to new Socket Address 
    void run();     // Running an infinite server loop
    void close();   // Function to closing server

    void reverseCharArray(char*, int);    // Line reversal
};

#endif
