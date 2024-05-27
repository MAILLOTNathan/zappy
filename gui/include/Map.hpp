/*
** EPITECH PROJECT, 2024
** gui
** File description:
** Map
*/

#pragma once

#include "Floor.hpp"
#include "Maths/Vector2.hpp"

#define CELL_SIZE 4

namespace Onyx {
    class Map {
        public:
            Map(const EGE::Maths::Vector2<int>& size);
            ~Map();

            void update(EGE::Shader& shader);
        private:
            std::vector<std::shared_ptr<Floor>> _floor;
    };
}