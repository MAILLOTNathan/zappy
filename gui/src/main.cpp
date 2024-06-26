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
    if (std::string(str) == "-help")
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
}

void launchMenu(const std::string &ip, int port)
{

    while (true) {
        Onyx::MainMenu *mainMenu = new Onyx::MainMenu(ip, port);
        mainMenu->loop();
        std::string localIP = mainMenu->getClient()->getIP();
        int localPort = mainMenu->getClient()->getPort();
        delete mainMenu;
        launchGame(localIP, localPort);
    }
}

// dinf the port after the -p flag
int getPort(char **argv)
{
    for (int i = 1; argv[i] != NULL; i++) {
        if (std::string(argv[i]) == "-p") {
            return std::stoi(argv[i + 1]);
        }
    }
    return 0;
}

std::string getIp(char **argv)
{
    for (int i = 1; argv[i] != NULL; i++) {
        if (std::string(argv[i]) == "-h") {
            return std::string(argv[i + 1]);
        }
    }
    return "127.0.0.1";
}

int main(int argc, char **argv)
{
    try {
        if (argc == 1) {
            launchMenu("", 0);
        } else if (argc == 5 || argc == 3) {
            int port = getPort(argv);
            if (port < 0 || port > 65535)
                throw EGE::Error("Invalid port number: " + std::string(argv[2]));
            launchMenu(getIp(argv), port);
        } else {
            if (argc > 5) {
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
