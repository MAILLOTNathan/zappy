/*
** EPITECH PROJECT, 2024
** gui
** File description:
** main
*/

#include "Gui.hpp"

int main()
{
    bool running = true;
    std::shared_ptr<Onyx::Gui> gui = std::make_shared<Onyx::Gui>();

    while (running) {
        gui->update(running);
    }
}