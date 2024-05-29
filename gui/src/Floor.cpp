/*
** EPITECH PROJECT, 2024
** gui
** File description:
** Floor
*/

#include "Floor.hpp"

Onyx::Floor::Floor(const EGE::Maths::Vector3<float>& position)
{
    this->_position = position;
    this->_model = std::make_shared<EGE::Model>("./assets/models/floor/floor.obj", position, EGE::Maths::Vector3<float>(1.0f, 1.0f, 1.0f), false);
}

Onyx::Floor::~Floor()
{
}

void Onyx::Floor::update(std::shared_ptr<EGE::Shader> shader)
{
    this->_model->draw(*shader.get());
}