/*
** EPITECH PROJECT, 2024
** gui
** File description:
** main
*/

#include "MainMenu.hpp"
#include "TcpClient.hpp"

bool isHelp(char *str)
{
    if (std::string(str) == "--help")
        return true;
    if (std::string(str) == "-h")
        return true;
    if (std::string(str) == "--aled")
        return true;
    return false;
}

void launchGame(const std::string &ip, int port)
{
    net::TcpClient client(ip, port);
    std::shared_ptr<Onyx::Gui> gui = std::make_shared<Onyx::Gui>(client);
    gui->loop();
    exit(0);
}

void launchMenu()
{
    Onyx::MainMenu *mainMenu = new Onyx::MainMenu();

    mainMenu->loop();
    launchGame(mainMenu->getClient()->getIP(), mainMenu->getClient()->getPort());
}

int main(int argc, char **argv)
{
    try {
        if (argc == 1) {
            launchMenu();
        } else if (argc == 3) {
            if (std::stoi(argv[2]) < 0 || std::stoi(argv[2]) > 65535)
                throw EGE::Error("Invalid port number: " + std::string(argv[2]));
            launchGame(argv[1], std::stoi(argv[2]));
        } else {
            if (argc > 3) {
                throw EGE::Error("Too many arguments");
            } else if (argc == 2 && isHelp(argv[1])) {
                std::cout << "USAGE: ./onyx [ip] [port]" << std::endl;
                std::cout << "          OR" << std::endl;
                std::cout << "       ./onyx" << std::endl;
                std::cout << "ip: The IP address of the server to connect to." << std::endl;
                std::cout << "port: The port number of the server to connect to." << std::endl;
                exit(0);
            } else {
                throw EGE::Error("Invalid argument: " + std::string(argv[1]));
            }
        }
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return 84;
    }
}
