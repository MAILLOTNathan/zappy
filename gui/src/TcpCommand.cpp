/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** TcpCommand
*/

#include "TcpCommand.hpp"

net::TcpCommand::TcpCommand(type_command_t type, std::function<void(std::vector<std::string>& args)> callback)
    : _type(type), _callback(callback)
{
}

net::TcpCommand::~TcpCommand()
{
}

void net::TcpCommand::exec(std::vector<std::string>& args)
{
    this->_callback(args);
}
