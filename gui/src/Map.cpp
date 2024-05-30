/*
** EPITECH PROJECT, 2024
** gui
** File description:
** Map
*/

#include "Map.hpp"

Onyx::Map::Map(const EGE::Maths::Vector2<int>& size)
{
    std::string shader = Utils::getFileContent("./assets/shaders/map.vert");
    shader = std::regex_replace(shader, std::regex("uniform float offsets\\[\\d+\\]"), "uniform float offsets[" + std::to_string(size.x * size.y) + "]");
    Utils::setFileContent("./assets/shaders/map.vert", shader, false);
    this->_shader = std::make_shared<EGE::Shader>("./assets/shaders/map.vert", "./assets/shaders/fragment.frag");
    for (int i = 0; i < size.x; i++) {
        for (int j = 0; j < size.y; j++) {
            this->_floor.push_back(std::make_shared<Onyx::Floor>(EGE::Maths::Vector3<float>(i * CELL_SIZE, 0, j * CELL_SIZE)));
        }
    }
}

Onyx::Map::~Map()
{
}

void Onyx::Map::update(UNUSED std::shared_ptr<EGE::Shader> shader)
{
    shader->use();
    for (auto& floor : this->_floor) {
        floor->update(this->_shader);
    }
}