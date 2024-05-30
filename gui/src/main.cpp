/*
** EPITECH PROJECT, 2024
** gui
** File description:
** main
*/

#include "Gui.hpp"

int main()
{
    try {
        bool running = true;
        std::shared_ptr<Onyx::Gui> gui = std::make_shared<Onyx::Gui>();

        while (running) {
            gui->update(running);
        }
    } catch (const EGE::Error& e) {
        std::cerr << e.what() << std::endl;
        return 84;
    }
}