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
    this->_position = EGE::Maths::Vector3<float>(position.x * CELL_SIZE, 0, position.y * CELL_SIZE);
    this->_model = std::make_shared<EGE::ModelVR>("models/floor/floor.obj", this->_position, EGE::Maths::Vector3<float>(0.5, 0.5, 0.5));
    window->addModel("Map", this->_model);
    memset(this->_quantity, 0, sizeof(this->_quantity));
    __android_log_print(ANDROID_LOG_INFO, "MYTAG", "Adding model floor");
    if (FloorVR::_items.empty()) {
        FloorVR::_items.push_back(std::make_shared<ItemVR>(EGE::Maths::Vector2<int>(0, 0), window));
        FloorVR::_items.push_back(std::make_shared<ItemVR>(EGE::Maths::Vector2<int>(0, 0), window));
        FloorVR::_items.push_back(std::make_shared<ItemVR>(EGE::Maths::Vector2<int>(0, 0), window));
        FloorVR::_items.push_back(std::make_shared<ItemVR>(EGE::Maths::Vector2<int>(0, 0), window));
        FloorVR::_items.push_back(std::make_shared<ItemVR>(EGE::Maths::Vector2<int>(0, 0), window));
        FloorVR::_items.push_back(std::make_shared<ItemVR>(EGE::Maths::Vector2<int>(0, 0), window));
        FloorVR::_items.push_back(std::make_shared<ItemVR>(EGE::Maths::Vector2<int>(0, 0), window));
    }
    __android_log_print(ANDROID_LOG_INFO, "MYTAG", "Adding items");
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
