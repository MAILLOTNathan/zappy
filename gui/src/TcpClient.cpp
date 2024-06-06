/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** TcpClient
*/

#include "TcpClient.hpp"


net::TcpClient::TcpClient(const std::string& ip, int port)
{
    this->_ip = ip;
    this->_port = port;
    this->_fd = 0;
    FD_ZERO(&this->_readfds);
}

net::TcpClient::~TcpClient()
{
}

void net::TcpClient::connection()
{
    this->_initSocket();
    struct sockaddr_in serv_addr = {0};
    socklen_t len = sizeof(serv_addr);

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(this->_port);
    serv_addr.sin_addr.s_addr = inet_addr(this->_ip.c_str());
    if (connect(this->_fd, (struct sockaddr *)&serv_addr, len) < 0)
        throw net::TcpClientError("Connection failed");
    this->_getheader();
    this->_sendTeamName();
}

void net::TcpClient::_getheader()
{
    std::string header;
    char buffer[1024] = {0};

    recv(this->_fd, buffer, 1024, 0);
    header = buffer;
    if (header.find("WELCOME") == std::string::npos)
        throw net::TcpClientError("Connection failed");
    std::cout << header << std::endl;
}

void net::TcpClient::_sendTeamName()
{
    std::string teamName = "GRAPHIC\n";

    send(this->_fd, teamName.c_str(), teamName.size(), 0);
}

void net::TcpClient::_initSocket()
{
    this->_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (this->_fd < 0)
        throw net::TcpClientError("Socket creation failed");
}


void net::TcpClient::disconnect()
{
    close(this->_fd);
}

void net::TcpClient::sendRequest(const std::string& request)
{
    send(this->_fd, request.c_str(), request.size(), 0);
}

void net::TcpClient::waitEvent()
{
    this->_initFdSet();
    select(this->_fd + 1, &this->_readfds, &this->_writefds, NULL, NULL);
    if (FD_ISSET(this->_fd, &this->_readfds)) {
        this->_readAll();
        this->_evalCommand();
    }
}


void net::TcpClient::addCommand(const std::string& command, net::type_command_t type, std::function<void(std::vector<std::string>& args)> callback)
{
    this->_manager.addCommand(command, type, callback);
}

void net::TcpClient::_readAll()
{
    char buffer[1000000] = {0};
    std::string response;
    ssize_t valread;

    do {
        valread = recv(this->_fd, buffer, 1000000, 0);
        if (valread == 0)
            break;
        response += buffer;
        std::memset(buffer, 0, 1000000);
    } while (valread == 1000000);

    this->_buffer += response;
}

void net::TcpClient::_evalCommand()
{
    std::string command;
    std::vector<std::string> args;
    size_t pos = 0;

    while ((pos = this->_buffer.find("\n")) != std::string::npos) {
        command = this->_buffer.substr(0, pos);
        this->_buffer.erase(0, pos + 1);

        if (command == "dead") {
            this->disconnect();
            throw net::TcpClientError("Dead");
        }
        args = Utils::split(command, ' ');
        this->_manager.getCommand(args[0]) ? this->_manager.getCommand(args[0])->exec(args) : void();
    }
}

void net::TcpClient::_initFdSet()
{
    FD_ZERO(&this->_readfds);
    FD_ZERO(&this->_writefds);
    FD_SET(this->_fd, &this->_readfds);
    FD_SET(this->_fd, &this->_writefds);
    FD_SET(0, &this->_readfds);
}
