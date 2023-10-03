#include <iostream>

#include "server.h"

smplServer::smplServer(std::string _adr, std::string _port)
{
    newAddress(_adr, _port);
}

smplServer::~smplServer()
{}


void smplServer::run()
{
    while (running)
    {      
        try {
            Poco::Net::StreamSocket clientSocket = server.acceptConnection(); // Waiting for the client to connect

            std::cout << "Client connected with IP: " << clientSocket.peerAddress().toString() << std::endl;
            std::cout << "Welcome to POCO TCP server. Enter you string:" << std::endl;

            listenClient(clientSocket); // Start listening
        }
        catch (Poco::Exception& exc)
        {
            std::cerr << "Exception: " << exc.displayText() << std::endl;
        }  
    }
}

void smplServer::listenClient(Poco::Net::StreamSocket clientSocket)
{
     try {   
        while (true) {

            Poco::UInt8  size;
            // Receive size of msg
            if (clientSocket.receiveBytes(&size, sizeof(size)) <= 0)
                break;

            char buffer[size+1];

            // Receive msg
            if (clientSocket.receiveBytes(buffer, size) <= 0)
                break;

            reverseCharArray(buffer, size);

            buffer[size] = '\0'; // adding the end of line character

            std::cout << "Received message: " << buffer << std::endl;
        }

        std::cout << "Client socket close" << std::endl; 
        clientSocket.close();
    }
    catch (Poco::Exception& exc) {
        std::cerr << "Exception: " << exc.displayText() << std::endl;
    }
}

void smplServer::newAddress(std::string& _adr, std::string _port)
{
    try 
    {
        socketAddress = Poco::Net::SocketAddress(_adr, _port);   
        std::cout << "Create server socket adress: " <<  _adr <<  ":" <<  _port << std::endl;
    }
    catch (Poco::Exception& e) 
    {
        std::cerr << "The address is incorrect: " << e.displayText() << std::endl;
    }
}

void smplServer::open()
{    
    try 
    {
        server.bind(socketAddress); // Connect to a new port
        server.listen();            // Start to listen a new port
        std::cout << "Server opened" << std::endl;
    }
    catch (Poco::Exception& e) 
    {
        std::cerr << "Connection failed: " << e.displayText() << std::endl;
    }
}

void smplServer::close()
{
    server.close();
    std::cout << "Server closed" << std::endl;
}

void smplServer::reverseCharArray(char* array, int size)
{
    std::reverse(array, array + size);
}
