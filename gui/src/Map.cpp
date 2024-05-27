/*
** EPITECH PROJECT, 2024
** gui
** File description:
** Map
*/

#include "Map.hpp"

Onyx::Map::Map(const EGE::Maths::Vector2<int>& size)
{
    for (int i = 0; i < size.x; i++) {
        for (int j = 0; j < size.y; j++) {
            this->_floor.push_back(std::make_shared<Onyx::Floor>(EGE::Maths::Vector3<float>(i * CELL_SIZE, 0, j * CELL_SIZE)));
        }
    }
}