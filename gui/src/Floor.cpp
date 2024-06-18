/*
** EPITECH PROJECT, 2024
** gui
** File description:
** Floor
*/

#include "Floor.hpp"

std::vector<std::shared_ptr<Onyx::Item>> Onyx::Floor::_items = {};

Onyx::Floor::Floor(const EGE::Maths::Vector2<int>& position)
{
    this->_pos = position;
    this->_position = EGE::Maths::Vector3<float>(position.x * CELL_SIZE, 0, position.y * CELL_SIZE);
    this->_model = std::make_shared<EGE::Model>("./assets/models/floor/floor.obj", this->_position, EGE::Maths::Vector3<float>(0.0f, 0.0f, 0.0f), EGE::Maths::Vector3<float>(CELL_SIZE / 3.0f, 1.0f, CELL_SIZE / 3.0f));
    memset(this->_quantity, 0, sizeof(this->_quantity));
    if (Onyx::Floor::_items.empty()) {
        Onyx::Floor::_items.push_back(std::make_shared<Onyx::Item>(EGE::Maths::Vector2<int>(0, 0), Onyx::Item::TYPE::FOOD));
        Onyx::Floor::_items.push_back(std::make_shared<Onyx::Item>(EGE::Maths::Vector2<int>(0, 0), Onyx::Item::TYPE::LINEMATE));
        Onyx::Floor::_items.push_back(std::make_shared<Onyx::Item>(EGE::Maths::Vector2<int>(0, 0), Onyx::Item::TYPE::DERAUMERE));
        Onyx::Floor::_items.push_back(std::make_shared<Onyx::Item>(EGE::Maths::Vector2<int>(0, 0), Onyx::Item::TYPE::SIBUR));
        Onyx::Floor::_items.push_back(std::make_shared<Onyx::Item>(EGE::Maths::Vector2<int>(0, 0), Onyx::Item::TYPE::MENDIANE));
        Onyx::Floor::_items.push_back(std::make_shared<Onyx::Item>(EGE::Maths::Vector2<int>(0, 0), Onyx::Item::TYPE::PHIRAS));
        Onyx::Floor::_items.push_back(std::make_shared<Onyx::Item>(EGE::Maths::Vector2<int>(0, 0), Onyx::Item::TYPE::THYSTAME));
    }
}

Onyx::Floor::~Floor()
{
}

void Onyx::Floor::update(std::shared_ptr<EGE::Shader> shader)
{
    this->_model->draw(*shader.get());
    for (int i = 0; i < Onyx::Item::TYPE::MAX; i++) {
        if (this->_quantity[i] > 0) {
            Onyx::Floor::_items[i]->setPos(EGE::Maths::Vector2<int>(this->_pos.x, this->_pos.y));
            Onyx::Floor::_items[i]->update(shader);
            // draw the quantity of the item
        }
    }
}

void Onyx::Floor::addItem(Onyx::Item::TYPE type, int number)
{
    this->_quantity[type] = number;
}

void Onyx::Floor::removeItem(Onyx::Item::TYPE type)
{
    this->_quantity[type]--;
}

int Onyx::Floor::getQuantity(Onyx::Item::TYPE type) const
{
    return this->_quantity[type];
}

float Onyx::Floor::getDistance(const EGE::Maths::Vector3<float>& cameraPositon, const EGE::Maths::Vector3<float>& cameraFront) const
{
    return EGE::Maths::Vector3<float>(this->_position.x - cameraPositon.x, this->_position.y - cameraPositon.y, this->_position.z - cameraPositon.z).length();
}

EGE::Maths::Vector2<int> Onyx::Floor::getPos() const
{
    return this->_pos;
}