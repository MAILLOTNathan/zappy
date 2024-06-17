/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** FloorVR
*/

#include "FloorVR.hpp"

std::vector<std::shared_ptr<ItemVR>> FloorVR::_items = {};

FloorVR::FloorVR(const EGE::Maths::Vector2<int>& position, std::shared_ptr<EGE::WindowVR> window)
{
    this->_pos = position;
    this->_position = EGE::Maths::Vector3<float>(position.x * CELL_SIZE, -0.9, position.y * CELL_SIZE);
    this->_model = std::make_shared<EGE::ModelVR>("models/floor/floor.obj", this->_position, EGE::Maths::Vector3<float>(0.0f, 0.0f, 0.0f), EGE::Maths::Vector3<float>(CELL_SIZE / 3.0f, CELL_SIZE / 3.0f, CELL_SIZE / 3.0f));
    window->addModel("Map", this->_model);
    memset(this->_quantity, 0, sizeof(this->_quantity));
    if (FloorVR::_items.empty()) {
        FloorVR::_items.push_back(std::make_shared<ItemVR>(EGE::Maths::Vector2<int>(0, 0), ItemVR::FOOD, window));
        FloorVR::_items.push_back(std::make_shared<ItemVR>(EGE::Maths::Vector2<int>(0, 0), ItemVR::LINEMATE, window));
        FloorVR::_items.push_back(std::make_shared<ItemVR>(EGE::Maths::Vector2<int>(0, 0), ItemVR::DERAUMERE, window));
        FloorVR::_items.push_back(std::make_shared<ItemVR>(EGE::Maths::Vector2<int>(0, 0), ItemVR::SIBUR, window));
        FloorVR::_items.push_back(std::make_shared<ItemVR>(EGE::Maths::Vector2<int>(0, 0), ItemVR::MENDIANE, window));
        FloorVR::_items.push_back(std::make_shared<ItemVR>(EGE::Maths::Vector2<int>(0, 0), ItemVR::PHIRAS, window));
        FloorVR::_items.push_back(std::make_shared<ItemVR>(EGE::Maths::Vector2<int>(0, 0), ItemVR::THYSTAME, window));
    }
}

FloorVR::~FloorVR()
{
}

void FloorVR::update(std::shared_ptr<EGE::Shader> shader)
{
    this->_model->draw(*shader.get());
    for (int i = 0; i < ItemVR::TYPE::MAX; i++) {
        if (this->_quantity[i] > 0) {
            FloorVR::_items[i]->setPos(EGE::Maths::Vector2<int>(this->_position.x, this->_position.y));
            FloorVR::_items[i]->update(shader);
            // draw the quantity of the item
        }
    }
}

void FloorVR::addItem(ItemVR::TYPE type, int number)
{
    this->_quantity[type] = number;
}

void FloorVR::removeItem(ItemVR::TYPE type)
{
    this->_quantity[type]--;
}

int FloorVR::getQuantity(ItemVR::TYPE type) const
{
    return this->_quantity[type];
}

EGE::Maths::Vector2<int> FloorVR::getPosition() const
{
    return this->_pos;
}
