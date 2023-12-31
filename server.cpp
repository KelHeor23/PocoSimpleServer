#include <iostream>

#include "server.h"

smplServer::smplServer(std::string &_port)
{
    newAddress(std::stoi(_port));
}

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

            // Call poll() and wait 100 sec for it to complete.
            if (clientSocket.poll(Poco::Timespan(100000000), Poco::Net::Socket::SELECT_READ) <= 0)
            {
                std::cout << "There were no messages from the client" << std::endl;
                break;
            }                

            if (clientSocket.available() > MAX_MSG_SIZE)
            {
                std::cout << "Too long msg" << std::endl;
                continue;
            }

            if (clientSocket.available() < (int)sizeof(size))
                break;  

            // Receive size of msg
            clientSocket.receiveBytes(&size, sizeof(size));

            char buffer[size+1];

            if (clientSocket.available() < size)
                break;  

            // Receive msg
            clientSocket.receiveBytes(buffer, size);           

            reverseCharArray(buffer, size);

            buffer[size] = '\0'; // adding the end of line character

            std::cout << "Received message: " << buffer << std::endl;
        }        
    }
    catch (Poco::Exception& exc) {
        std::cerr << "Exception: " << exc.displayText() << std::endl;
    }

    std::cout << "Client socket close" << std::endl; 
    clientSocket.close();
}

void smplServer::newAddress(Poco::UInt16 _port)
{
    try 
    {
        socketAddress = Poco::Net::SocketAddress(_port);   
        std::cout << "Create server socket adress: localhost:" <<  _port << std::endl;
    }
    catch (Poco::Exception& e) 
    {
        std::cerr << "The address is incorrect: " << e.displayText() << std::endl;
    }
}

void smplServer::newAddress(std::string& _adr, std::string& _port)
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
        server.bind(28888); // Connect to a new port
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
    for (int i = 0; i < size / 2; i++) {
        char temp = array[i];
        array[i] = array[size - i - 1];
        array[size - i - 1] = temp;
    }
}
