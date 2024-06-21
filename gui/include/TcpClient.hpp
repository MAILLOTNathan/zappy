/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** TcpClient
*/

#ifndef TCPCLIENT_HPP_
    #define TCPCLIENT_HPP_

    #include <iostream>
    #include <sys/socket.h>
    #include <arpa/inet.h>
    #include <unistd.h>
    #include <string>
    #include <queue>
    #include <array>
    #include <cstring>
    #include "Error.hpp"
    #include "TcpManagerCmd.hpp"

    #define COMMAND_VALIDE

namespace net {
    /**
     * @brief An exception class for TCP client errors.
     *
     * This class is used to represent errors that occur during TCP client operations.
     * It inherits from the EGE::Error class.
     */
    class TcpClientError : public EGE::Error {
        public:
            /**
             * @brief Constructs a TcpClientError object with the given error message.
             *
             * @param message The error message associated with the exception.
             */
            TcpClientError(const std::string& message) : Error(message) {}
    };

    /**
     * @class TcpClient
     * @brief Represents a TCP client that connects to a server and sends/receives data.
     */
    class TcpClient {
        public:
            /**
             * @brief Constructs a TcpClient object with the specified IP address and port number.
             *
             * @param ip The IP address of the server to connect to.
             * @param port The port number of the server to connect to.
             */
            TcpClient(const std::string& ip, int port);

            /**
             * @brief Destroys the TcpClient object.
             */
            ~TcpClient();

            /**
             * @brief Connects to the server.
             *
             * Establishes a connection with the server.
             * Initializes the socket, sets up the server address, and connects to the server.
             * Throws a net::TcpClientError exception if the connection fails.
             * Retrieves the header from the server and sends the team name.
             */
            void connection();

            /**
             * @brief Disconnects the TCP client.
             *
             * This function closes the file descriptor associated with the TCP client.
             */
            void disconnect();

            /**
             * @brief Sends a request over the TCP connection.
             *
             * @param request The request to send.
             */
            void sendRequest(const std::string& request);

            /**
             * @brief Waits for an event on the TCP client socket.
             *
             * Waits for an event on the TCP client socket.
             * This function initializes the file descriptor set, performs a select operation,
             * and checks if the socket is ready for reading. If the socket is ready, it reads
             * all available data and evaluates the received command.
             *
             * @throws net::TcpClientError if the select operation fails.
             */
            void waitEvent();

            /**
             * @brief Adds a command to the TCP client.
             *
             * This function adds a command to the TCP client's command manager. The command is identified by a string `command`,
             * and its type is specified by the `type` parameter. The `callback` parameter is a function that will be called when
             * the command is executed, and it takes a vector of strings as its argument.
             *
             * @param command The command to be added.
             * @param type The type of the command.
             * @param callback The callback function to be called when the command is executed.
             */
            void addCommand(const std::string& command, net::type_command_t type, std::function<void(std::vector<std::string>& args)> callback);

            /**
             * @brief Gets the IP address of the server.
             *
             * @return The IP address of the server.
             */
            std::string getIP() const;

            /**
             * @brief Gets the port number of the server.
             *
             * @return The port number of the server.
             */
            int getPort() const;

        protected:
            std::string _ip;                    /**< The IP address of the server. */
            int _port;                          /**< The port number of the server. */
            int _fd;                            /**< The file descriptor associated with the TCP client. */
            struct sockaddr_in _serv_addr;      /**< The server address structure. */
            TcpManagerCmd _manager;             /**< The command manager for the TCP client. */
            fd_set _readfds;                    /**< The file descriptor set for the select operation. */
            std::string _buffer;                /**< The buffer for storing received data. */
            fd_set _writefds;                   /**< The file descriptor set for the select operation. */

        private:
            /**
             * @brief Initializes the socket.
             */
            void _initSocket();

            /**
             * @brief Initializes the file descriptor set.
             */
            void _initFdSet();

            /**
             * @brief Retrieves the header from the server.
             */
            void _getheader();

            /**
             * @brief Sends the team name to the server.
             */
            void _sendTeamName();

            /**
             * @brief Reads all available data from the socket.
             */
            void _readAll();

            /**
             * @brief Evaluates the received command.
             */
            void _evalCommand();
        };
} // namespace net


#endif /* !TCPCLIENT_HPP_ */
