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
            this->_model = std::make_shared<EGE::Model>("./assets/models/food/steak.obj", foodPosition, EGE::Maths::Vector3<float>(90.0f, 0.0f, 0.0f), EGE::Maths::Vector3<float>(0.1f, 0.1f, 0.1f));
            break;
        case Onyx::Item::TYPE::LINEMATE:
            this->_model = std::make_shared<EGE::Model>("./assets/models/items/1.obj", EGE::Maths::Vector3<float>(position.x * CELL_SIZE, 3.0f, position.y * CELL_SIZE), EGE::Maths::Vector3<float>(0.0f, 0.0f, 0.0f), EGE::Maths::Vector3<float>(CELL_SIZE / 9.0f, CELL_SIZE / 9.0f, CELL_SIZE / 9.0f));
            break;
        case Onyx::Item::TYPE::DERAUMERE:
            this->_model = std::make_shared<EGE::Model>("./assets/models/items/2.obj", EGE::Maths::Vector3<float>(position.x * CELL_SIZE, 3.0f, position.y * CELL_SIZE), EGE::Maths::Vector3<float>(0.0f, 0.0f, 0.0f), EGE::Maths::Vector3<float>(CELL_SIZE / 9.0f, CELL_SIZE / 9.0f, CELL_SIZE / 9.0f));
            break;
        case Onyx::Item::TYPE::SIBUR:
            this->_model = std::make_shared<EGE::Model>("./assets/models/items/3.obj", EGE::Maths::Vector3<float>(position.x * CELL_SIZE, 3.0f, position.y * CELL_SIZE), EGE::Maths::Vector3<float>(0.0f, 0.0f, 0.0f), EGE::Maths::Vector3<float>(CELL_SIZE / 9.0f, CELL_SIZE / 9.0f, CELL_SIZE / 9.0f));
            break;
        case Onyx::Item::TYPE::MENDIANE:
            this->_model = std::make_shared<EGE::Model>("./assets/models/items/4.obj", EGE::Maths::Vector3<float>(position.x * CELL_SIZE, 3.0f, position.y * CELL_SIZE), EGE::Maths::Vector3<float>(0.0f, 0.0f, 0.0f), EGE::Maths::Vector3<float>(CELL_SIZE / 9.0f, CELL_SIZE / 9.0f, CELL_SIZE / 9.0f));
            break;
        case Onyx::Item::TYPE::PHIRAS:
            this->_model = std::make_shared<EGE::Model>("./assets/models/items/5.obj", EGE::Maths::Vector3<float>(position.x * CELL_SIZE, 3.0f, position.y * CELL_SIZE), EGE::Maths::Vector3<float>(0.0f, 0.0f, 0.0f), EGE::Maths::Vector3<float>(CELL_SIZE / 9.0f, CELL_SIZE / 9.0f, CELL_SIZE / 9.0f));
            break;
        case Onyx::Item::TYPE::THYSTAME:
            this->_model = std::make_shared<EGE::Model>("./assets/models/items/6.obj", EGE::Maths::Vector3<float>(position.x * CELL_SIZE, 3.0f, position.y * CELL_SIZE), EGE::Maths::Vector3<float>(0.0f, 0.0f, 0.0f), EGE::Maths::Vector3<float>(CELL_SIZE / 9.0f, CELL_SIZE / 9.0f, CELL_SIZE / 9.0f));
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
    switch (this->_type) {
        case Onyx::Item::TYPE::FOOD:
            Entity::setPosition(foodPosition);
            break;
        case Onyx::Item::TYPE::LINEMATE:
            Entity::setPosition(linematePosition);
            break;
        case Onyx::Item::TYPE::DERAUMERE:
            Entity::setPosition(deraumerePosition);
            break;
        case Onyx::Item::TYPE::SIBUR:
            Entity::setPosition(siburPosition);
            break;
        case Onyx::Item::TYPE::MENDIANE:
            Entity::setPosition(mendianePosition);
            break;
        case Onyx::Item::TYPE::PHIRAS:
            Entity::setPosition(phirasPosition);
            break;
        case Onyx::Item::TYPE::THYSTAME:
            Entity::setPosition(thystamePosition);
            break;
        default:
            break;
    }
    // Entity::setPosition(EGE::Maths::Vector3<float>(position.x * CELL_SIZE, 3.0f, position.y * CELL_SIZE));
}