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
    this->_panels.push_back(new EGE::Panel("Test"));
}