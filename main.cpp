#include <iostream>

#include "server.h"

bool isAllDigits(char *c) {
    while (*c != '\0')
    {
        if (!std::isdigit(*c)) {
            return false;
        }
        c++;
    }
    return true;
}

int main(int argc, char** argv)
{
    std::string port;

    if (argc > 2)
    {
        std::cout << "Please enter the port as the first argument" << std::endl;
        return 0;
    }
    else if (argc == 1)
    {
        port = "28888";
    }
    else if (!isAllDigits(argv[1]))
    {
        std::cout << "Invalid port" << std::endl;
        return 0;
    }
    else
    {
        port = argv[1];
    }

    smplServer server("localhost", port);

    server.open();
    server.run();
    server.close();

    return 0;
}
