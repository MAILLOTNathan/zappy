/*
** EPITECH PROJECT, 2024
** gui
** File description:
** Map
*/

#include "Map.hpp"

Onyx::Map::Map()
{
    std::cout << "Empty map created" << std::endl;
}

Onyx::Map::Map(const EGE::Maths::Vector2<int>& size)
{
    std::cout << "Map constructor" << std::endl;
    std::string shader = Utils::getFileContent("./assets/shaders/map.vert");
    shader = std::regex_replace(shader, std::regex("uniform float offsets\\[\\d+\\]"), "uniform float offsets[" + std::to_string(size.x * size.y) + "]");
    Utils::setFileContent("./assets/shaders/map.vert", shader, false);
    // this->_shader = std::make_shared<EGE::Shader>("./assets/shaders/map.vert", "./assets/shaders/fragment.frag");
    for (int i = 0; i < size.x; i++) {
        for (int j = 0; j < size.y; j++) {
            std::shared_ptr<Onyx::Floor> floor = std::make_shared<Onyx::Floor>(EGE::Maths::Vector2<int>(i, j));
            this->_floor.push_back(floor);
        }
    }
    this->_size = size;
}

Onyx::Map::~Map()
{
    std::cout << "Map destroyed" << std::endl;
}

void Onyx::Map::update(std::shared_ptr<EGE::Shader> shader)
{
    shader->use();
    for (auto& floor : this->_floor) {
        floor->update(shader);
    }
}

void Onyx::Map::addItem(const EGE::Maths::Vector2<int>& position, Onyx::Item::TYPE type, int number)
{
    std::cout << "Adding item at " << this->_size.x * position.y + position.x << std::endl;
    std::cout << "Size: " << this->_floor.size() << std::endl;
    this->_floor[this->_size.x * position.y + position.x]->addItem(type, number);
}

void Onyx::Map::removeItem(const EGE::Maths::Vector2<int>& position, Onyx::Item::TYPE type)
{
    for (auto& floor : this->_floor) {
        if (floor->getPos() == position) {
            floor->removeItem(type);
            break;
        }
    }
}

EGE::Maths::Vector2<int> Onyx::Map::getSize() const
{
    return this->_size;
}


std::vector<std::shared_ptr<Onyx::Floor>> Onyx::Map::getFloor() const
{
    return this->_floor;
}
