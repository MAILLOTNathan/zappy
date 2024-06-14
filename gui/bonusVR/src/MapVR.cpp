/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** MapVR
*/

#include "MapVR.hpp"

MapVR::MapVR()
{
}

MapVR::MapVR(const EGE::Maths::Vector2<int>& size, std::shared_ptr<EGE::WindowVR> window)
{
    this->_size = size;
    this->_window = window;
    for (int i = 0; i < size.y; i++) {
        for (int j = 0; j < size.x; j++) {
            this->_floor.push_back(std::make_shared<FloorVR>(EGE::Maths::Vector2<int>(j, i), window));
        }
    }
}

MapVR::~MapVR()
{
}

void MapVR::update(std::shared_ptr<EGE::Shader> shader)
{
    for (auto& floor : this->_floor) {
        floor->update(shader);
    }
}

void MapVR::addItem(const EGE::Maths::Vector2<int>& position, ItemVR::TYPE type, int number)
{
    this->_floor[this->_size.x * position.y + position.x]->addItem(type, number);
}

void MapVR::removeItem(const EGE::Maths::Vector2<int>& position, ItemVR::TYPE type)
{
    this->_floor[this->_size.x * position.y + position.x]->removeItem(type);
}

EGE::Maths::Vector2<int> MapVR::getSize() const
{
    return this->_size;
}

std::vector<std::shared_ptr<FloorVR>> MapVR::getFloor() const
{
    return this->_floor;
}


