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
    /**
     * @brief Enumeration of the supported TCP command types.
     */
    typedef enum type_command_s {
        MSZ,    ///< Get the size of the map
        BCT,    ///< Get the content of a tile
        MCT,    ///< Get the content of the whole map
        TNA,    ///< Get the names of all the teams
        PNW,    ///< Get the information of a new player
        PPO,    ///< Get the position of a player
        PLV,    ///< Get the level of a player
        PIN,    ///< Get the inventory of a player
        PEX,    ///< Get the player's expulsion
        PBC,    ///< Get the player's broadcast
        PIC,    ///< Get the start of an incantation
        PIE,    ///< Get the end of an incantation
        PFK,    ///< Get the player's fork
        PDR,    ///< Get the player's drop
        PGT,    ///< Get the player's take
        PDI,    ///< Get the player's death
        ENW,    ///< Get the notification of a new player
        EHT,    ///< Get the notification of an egg hatching
        EBO,    ///< Get the notification of an egg being laid
        EDI,    ///< Get the notification of an egg dying
        SGT,    ///< Get the time unit value
        SST,    ///< Set the time unit value
        SEG,    ///< Get the end of the game
        SMG,    ///< Get a server message
        SUC,   ///< Get the response to an unknown command
        SBP,    ///< Get the response to a bad parameter
        IDM,    ///< Get the id of the player that moves or rotates
    } type_command_t;

    /**
     * @brief Class representing a TCP command.
     */
    class TcpCommand {
        public:
            /**
             * @brief Default constructor.
             */
            TcpCommand() = default;

            /**
             * @brief Constructor with type and callback function.
             *
             * @param type The type of the command.
             * @param callback The callback function to be executed when the command is executed.
             */
            TcpCommand(type_command_t type, std::function<void(std::vector<std::string>& args)> callback);

            /**
             * @brief Destructor.
             */
            ~TcpCommand();

            /**
             * @brief Executes the TCP command with the given arguments.
             *
             * @param args The vector of strings containing the command arguments.
             */
            void exec(std::vector<std::string>& args);

        protected:
            /**
             * @brief The type of the command.
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
