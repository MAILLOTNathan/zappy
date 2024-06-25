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

MapVR::MapVR(const EGE::Maths::Vector2<int>& size, std::shared_ptr<EGE::WindowVR> window, std::shared_ptr<EGE::Shader> shader)
{
    this->_size = size;
    this->_window = window;
    this->_modelEgg = std::make_shared<EGE::ModelVR>("models/egg/egg.obj");
    for (int i = 0; i < size.y; i++) {
        for (int j = 0; j < size.x; j++) {
            this->_floor.push_back(std::make_shared<FloorVR>(EGE::Maths::Vector2<int>(j, i), window));
        }
    }
    window->addDrawable("map", shader, [this] (const std::shared_ptr<EGE::Shader>& shader, float view_proj[16]) {
        shader->use();
        shader->setMat("view_proj", EGE::Maths::Matrix<4, 4, float>(view_proj)); // TODO
        this->update(shader);
    });
}

MapVR::~MapVR()
{
}

void MapVR::update(std::shared_ptr<EGE::Shader> shader)
{
    for (const auto &pos : this->_eggPos) {
        __android_log_print(ANDROID_LOG_FATAL, "MYTAG", "draw an egg\n");
        if (this->_modelEgg == nullptr) {
            this->_modelEgg = std::make_shared<EGE::ModelVR>("models/egg/egg.obj");
        }
        this->_modelEgg->setPosition(EGE::Maths::Vector3<float>(pos.x * CELL_SIZE, 1.0f, pos.y * CELL_SIZE));
        this->_modelEgg->draw(*shader);
    }
    for (auto& floor : this->_floor) {
        __android_log_print(ANDROID_LOG_FATAL, "MYTAG", "draw a floor\n");
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

void MapVR::addEgg(EGE::Maths::Vector3<int> pos)
{
    __android_log_print(ANDROID_LOG_FATAL, "MYTAG", "add an egg 1 \n");
    this->_eggPos.push_back(pos);
    __android_log_print(ANDROID_LOG_FATAL, "MYTAG", "add an egg 2 \n");
}

std::vector<EGE::Maths::Vector3<int>>& MapVR::getEggPos()
{
    return this->_eggPos;
}
