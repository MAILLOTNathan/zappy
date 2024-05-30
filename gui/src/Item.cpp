/*
** EPITECH PROJECT, 2024
** gui
** File description:
** Item
*/

#include "Item.hpp"

Onyx::Item::Item(EGE::Maths::Vector2<int> position, Onyx::Item::TYPE type)
{
    this->_position = position;
    this->_type = type;
    switch (type) {
        case Onyx::Item::TYPE::FOOD:
            this->_model = std::make_shared<EGE::Model>("./assets/models/food/steak.obj", EGE::Maths::Vector3<float>(position.x * CELL_SIZE, 3.0f, position.y * CELL_SIZE), EGE::Maths::Vector3<float>(0.1f, 0.1f, 0.1f));
            break;
        case Onyx::Item::TYPE::LINEMATE:
            throw Onyx::Item::ItemError("This item is not implemented yet");
            break;
        case Onyx::Item::TYPE::DERAUMERE:
            throw Onyx::Item::ItemError("This item is not implemented yet");
            break;
        case Onyx::Item::TYPE::SIBUR:
            throw Onyx::Item::ItemError("This item is not implemented yet");
            break;
        case Onyx::Item::TYPE::MENDIANE:
            throw Onyx::Item::ItemError("This item is not implemented yet");
            break;
        case Onyx::Item::TYPE::PHIRAS:
            throw Onyx::Item::ItemError("This item is not implemented yet");
            break;
        case Onyx::Item::TYPE::THYSTAME:
            throw Onyx::Item::ItemError("This item is not implemented yet");
            break;
        default:
            throw Onyx::Item::ItemError("Invalid item type given");
            break;
    }
}

Onyx::Item::~Item()
{
}

void Onyx::Item::update(std::shared_ptr<EGE::Shader> shader)
{
    this->_model->draw(*shader.get());
}

Onyx::Item::TYPE Onyx::Item::getType() const
{
    return this->_type;
}

void Onyx::Item::setType(Onyx::Item::TYPE type)
{
    this->_type = type;
}

EGE::Maths::Vector2<int> Onyx::Item::getPos() const
{
    return this->_position;
}

void Onyx::Item::setPos(EGE::Maths::Vector2<int> position)
{
    this->_position = position;
    Entity::setPosition(EGE::Maths::Vector3<float>(position.x * CELL_SIZE, 3.0f, position.y * CELL_SIZE));
}