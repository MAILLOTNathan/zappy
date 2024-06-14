/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** ItemVR
*/

#include "ItemVR.hpp"

ItemVR::ItemVR(const EGE::Maths::Vector2<int> &position, std::shared_ptr<EGE::WindowVR> window)
{
    this->_position = position;
    this->_type = static_cast<TYPE>(rand() % 7);
    __android_log_print(ANDROID_LOG_INFO, "MYTAG", "Creating item %d\n", this->_type);
    switch (this->_type) {
        case FOOD:
            this->_model = std::make_shared<EGE::ModelVR>("models/food/steak.obj", EGE::Maths::Vector3<float>(position.x * CELL_SIZE, 3.0f, position.y * CELL_SIZE), EGE::Maths::Vector3<float>(0.1f, 0.1f, 0.1f));
            break;
        case LINEMATE:
            this->_model = std::make_shared<EGE::ModelVR>("models/items/1.obj", EGE::Maths::Vector3<float>(position.x * CELL_SIZE, 3.0f, position.y * CELL_SIZE), EGE::Maths::Vector3<float>(0.5f, 0.5f, 0.5f));
            break;
        case DERAUMERE:
            this->_model = std::make_shared<EGE::ModelVR>("models/items/2.obj", EGE::Maths::Vector3<float>(position.x * CELL_SIZE, 3.0f, position.y * CELL_SIZE), EGE::Maths::Vector3<float>(0.5f, 0.5f, 0.5f));
            break;
        case SIBUR:
            this->_model = std::make_shared<EGE::ModelVR>("models/items/3.obj", EGE::Maths::Vector3<float>(position.x * CELL_SIZE, 3.0f, position.y * CELL_SIZE), EGE::Maths::Vector3<float>(0.5f, 0.5f, 0.5f));
            break;
        case MENDIANE:
            this->_model = std::make_shared<EGE::ModelVR>("models/items/4.obj", EGE::Maths::Vector3<float>(position.x * CELL_SIZE, 3.0f, position.y * CELL_SIZE), EGE::Maths::Vector3<float>(0.5f, 0.5f, 0.5f));
            break;
        case PHIRAS:
            this->_model = std::make_shared<EGE::ModelVR>("models/items/5.obj", EGE::Maths::Vector3<float>(position.x * CELL_SIZE, 3.0f, position.y * CELL_SIZE), EGE::Maths::Vector3<float>(0.5f, 0.5f, 0.5f));
            break;
        case THYSTAME:
            this->_model = std::make_shared<EGE::ModelVR>("models/items/6.obj", EGE::Maths::Vector3<float>(position.x * CELL_SIZE, 3.0f, position.y * CELL_SIZE), EGE::Maths::Vector3<float>(0.5f, 0.5f, 0.5f));
            break;
        default:
            break;
    }
    __android_log_print(ANDROID_LOG_INFO, "MYTAG", "Adding model item");
    window->addModel("Map", this->_model);
}

ItemVR::~ItemVR()
{
}

void ItemVR::update(std::shared_ptr<EGE::Shader> shader)
{
    this->_model->draw(*shader.get());
}

void ItemVR::setType(TYPE type)
{
    this->_type = type;
}

ItemVR::TYPE ItemVR::getType() const
{
    return this->_type;
}

void ItemVR::setPos(EGE::Maths::Vector2<int> position)
{
    this->_position = position;
    this->_model->setPosition(EGE::Maths::Vector3<float>(position.x * CELL_SIZE, 3.0f, position.y * CELL_SIZE));
}

EGE::Maths::Vector2<int> ItemVR::getPos() const
{
    return this->_position;
}


