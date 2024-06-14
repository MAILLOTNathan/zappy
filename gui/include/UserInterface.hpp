/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** UserInterface
*/

#include "Sound/Device.hpp"
#include "Sound/Playlist.hpp"
#include "GUI/GUIManager.hpp"

/**
 * @class UserInterface
 * @brief Represents the user interface for the zappy game.
 * @details This class inherits from the EGE::GUIManager class and provides functionality for managing the graphical user interface of the game.
 */
class UserInterface : public EGE::GUIManager {
    public:
        /**
         * @brief Default constructor for the UserInterface class.
         */
        UserInterface();

        /**
         * @brief Destructor for the UserInterface class.
         */
        ~UserInterface(){};

        void initPlaylist(const std::string &path);

        EGE::Sound::Playlist *getPlaylist();

    protected:
        EGE::Sound::Device *_soundDevice;
        EGE::Sound::Playlist *_playlist;
};