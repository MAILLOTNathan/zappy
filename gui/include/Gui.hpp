/*
** EPITECH PROJECT, 2024
** gui
** File description:
** Gui
*/

#pragma once

#include "Entity.hpp"
#include "Window.hpp"

namespace Onyx {
    class Gui {
        public:
            Gui();
            ~Gui();

            void update(bool& running);
        private:
            void _bindEvents();
            std::shared_ptr<EGE::Window> _window;
            std::vector<std::shared_ptr<Entity>> _entities;
    };
}