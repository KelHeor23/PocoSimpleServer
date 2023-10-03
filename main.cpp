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
    if (argc != 2)
    {
        std::cout << "Please enter the port as the first argument" << std::endl;
        return 0;
    }
    if (!isAllDigits(argv[1]))
    {
        std::cout << "Invalid port" << std::endl;
        return 0;
    }

    smplServer server("localhost", argv[1]);

    server.open();
    server.run();
    server.close();

    return 0;
}