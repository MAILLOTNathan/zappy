/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** TcpManagerCmd
*/

#include "TcpManagerCmd.hpp"

net::TcpManagerCmd::TcpManagerCmd()
{
}

net::TcpManagerCmd::~TcpManagerCmd()
{
}

net::TcpCommand *net::TcpManagerCmd::getCommand(std::string command)
{
    if (this->_commands.find(command) == this->_commands.end())
        return nullptr;
    return this->_commands[command];
}


void net::TcpManagerCmd::addCommand(const std::string& command, net::type_command_t type, std::function<void(std::vector<std::string>& args)> callback)
{
    this->_commands[command] = new net::TcpCommand(type, callback);
}
