/*
** EPITECH PROJECT, 2024
** gui
** File description:
** Map
*/

#include "Map.hpp"

Onyx::Map::Map()
{
}

Onyx::Map::Map(const EGE::Maths::Vector2<int>& size)
{
    std::string shader = Utils::getFileContent("./assets/shaders/map.vert");
    shader = std::regex_replace(shader, std::regex("uniform float offsets\\[\\d+\\]"), "uniform float offsets[" + std::to_string(size.x * size.y) + "]");
    Utils::setFileContent("./assets/shaders/map.vert", shader, false);
    // this->_shader = std::make_shared<EGE::Shader>("./assets/shaders/map.vert", "./assets/shaders/fragment.frag");
    this->_egg = std::make_shared<EGE::Model>("./assets/models/egg/egg.obj");
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
}

void Onyx::Map::update(std::shared_ptr<EGE::Shader> shader)
{
    shader->use();
    for (const auto& pos : this->_eggPos) {
        this->_egg->setPosition(EGE::Maths::Vector3<float>(pos.x * CELL_SIZE, 5.0f, pos.y * CELL_SIZE));
        this->_egg->draw(*shader.get());
    }
    for (auto& floor : this->_floor) {
        // instancing for the floor
        floor->update(shader);
    }
}

void Onyx::Map::createMap(const EGE::Maths::Vector2<int>& size)
{
    std::string shader = Utils::getFileContent("./assets/shaders/map.vert");
    shader = std::regex_replace(shader, std::regex("uniform float offsets\\[\\d+\\]"), "uniform float offsets[" + std::to_string(size.x * size.y) + "]");
    Utils::setFileContent("./assets/shaders/map.vert", shader, false);
    // this->_shader = std::make_shared<EGE::Shader>("./assets/shaders/map.vert", "./assets/shaders/fragment.frag");
    this->_egg = std::make_shared<EGE::Model>("./assets/models/egg/egg.obj");
    for (int i = 0; i < size.x; i++) {
        for (int j = 0; j < size.y; j++) {
            std::shared_ptr<Onyx::Floor> floor = std::make_shared<Onyx::Floor>(EGE::Maths::Vector2<int>(i, j));
            this->_floor.push_back(floor);
        }
    }
    this->_size = size;
}

void Onyx::Map::addItem(const EGE::Maths::Vector2<int>& position, Onyx::Item::TYPE type, int number)
{
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

int Onyx::Map::getTileSelected(const EGE::Maths::Vector3<float>& cameraPosition, const EGE::Maths::Matrix<4, 4, float>& projection, const EGE::Maths::Matrix<4, 4, float>& view)
{
    int tileSelected = -1;
    float t, u, v;
    glm::vec4 rayClip = glm::vec4(0.0f, 0.0f, -1.0f, 1.0f);
    glm::vec4 rayEye = glm::inverse(projection.toGlm()) * rayClip;
    rayEye = glm::vec4(rayEye.x, rayEye.y, -1.0f, 0.0f);
    glm::vec3 rayWorld = glm::normalize(glm::vec3(glm::inverse(view.toGlm()) * rayEye));

    for (int i = 0; i < this->_floor.size(); i++) {
        if (this->_floor[i]->intersects(cameraPosition.toGlmVec3(), rayWorld, t, u, v)) {
            tileSelected = i;
            break;
        }
    }
    return tileSelected;
}

void Onyx::Map::addEgg(EGE::Maths::Vector3<int> pos)
{
    this->_eggPos.push_back(pos);
}

std::vector<EGE::Maths::Vector3<int>>& Onyx::Map::getEggPos()
{
    return this->_eggPos;
}