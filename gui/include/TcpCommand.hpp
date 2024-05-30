/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** TcpCommand
*/

#ifndef TCPCOMMAND_HPP_
    #define TCPCOMMAND_HPP_

    #include <vector>
    #include <string>
    #include "Utils.hpp"
    #include <functional>

namespace net {
    typedef enum type_command_s {
        MSZ,
        BCT,
        TNA,
        PNW,
        PPO,
        PLV,
        PIN,
        PEX,
        PBC,
        PIC,
        PIE,
        PFK,
        PDR,
        PGT,
        PDI,
        ENW,
        EHT,
        EBO,
        EDI,
        SGT,
        SEG,
        SMG,
    } type_command_t;

    class TcpCommand {
        public:
            TcpCommand() = default;
            TcpCommand(type_command_t type, std::function<void(std::vector<std::string>& args)> callback);
            ~TcpCommand();

            /**
             * Executes the TCP command with the given arguments.
             *
             * @param args The vector of strings containing the command arguments.
             */
            void exec(std::vector<std::string>& args);

        protected:
            /**
             * The type of the command.
             */
            type_command_t _type;
            /**
             * @brief A callable object that can hold and invoke a function with the signature:
             *        void(std::vector<std::string>& args)
             *
             * This type is used to store a callback function that takes a reference to a vector
             * of strings as an argument and returns void.
             */
            std::function<void(std::vector<std::string>& args)> _callback;
        private:
    };
} // namespace net

#endif /* !TCPCOMMAND_HPP_ */
