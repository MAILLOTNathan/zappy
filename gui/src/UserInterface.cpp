/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** UserInterface
*/

#include "UserInterface.hpp"

UserInterface::UserInterface()
{
    this->_menuBar = new EGE::Main();
    this->_soundDevice = new EGE::Sound::Device();
}

void UserInterface::initPlaylist(const std::string &path)
{
    this->_playlist = new EGE::Sound::Playlist(path);
}

EGE::Sound::Playlist *UserInterface::getPlaylist()
{
    return this->_playlist;
}
