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
    this->_model = std::make_shared<EGE::Model>("./assets/floor/floor.obj");
}

Onyx::Floor::~Floor()
{
}

void Onyx::Floor::update(EGE::Shader& shader)
{
    this->_model->draw(shader);
}