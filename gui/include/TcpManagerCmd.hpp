/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** TcpManagerCmd
*/

#ifndef TCPMANAGERCMD_HPP_
    #define TCPMANAGERCMD_HPP_

    #include <map>
    #include "TcpCommand.hpp"

namespace net {
    class TcpManagerCmd {
        public:
            TcpManagerCmd();
            ~TcpManagerCmd();

            /**
             * @brief Retrieves a TcpCommand object based on the given command string.
             *
             * This function searches for a TcpCommand object that matches the provided command string.
             * If a matching command is found, a pointer to the TcpCommand object is returned.
             * If no matching command is found, nullptr is returned.
             *
             * @param command The command string to search for.
             * @return A pointer to the TcpCommand object if found, nullptr otherwise.
             */
            TcpCommand *getCommand(std::string command);

            /**
             * @brief Adds a command to the TcpManagerCmd object.
             *
             * This function adds a command to the TcpManagerCmd object. The command is associated with a type and a callback function.
             *
             * @param command The command string.
             * @param type The type of the command.
             * @param callback The callback function to be executed when the command is received.
            */
            void addCommand(const std::string& command, net::type_command_t type, std::function<void(std::vector<std::string>& args)> callback);

        protected:
            /**
             * @brief A map that associates strings with TcpCommand pointers.
             *
             * This map is used to store and retrieve TcpCommand objects based on their associated strings.
             * The keys of the map are strings, and the values are pointers to TcpCommand objects.
             */
            std::map<std::string, TcpCommand *> _commands;
        private:
    };
}

#endif /* !TCPMANAGERCMD_HPP_ */
