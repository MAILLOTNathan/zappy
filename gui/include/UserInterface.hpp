/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** UserInterface
*/

#include "Sound/Device.hpp"
#include "Sound/Playlist.hpp"
#include "GUI/GUIManager.hpp"

class UserInterface : public EGE::GUIManager {
    public:
        UserInterface();
        ~UserInterface(){};

        void initPlaylist(const std::string &path);

        EGE::Sound::Playlist *getPlaylist();

    protected:
        EGE::Sound::Device *_soundDevice;
        EGE::Sound::Playlist *_playlist;
};