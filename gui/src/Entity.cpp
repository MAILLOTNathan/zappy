/*
** EPITECH PROJECT, 2024
** gui
** File description:
** Entity
*/

#include "Entity.hpp"

void Onyx::Entity::update(std::shared_ptr<EGE::Shader> shader)
{
}

void Onyx::Entity::setPosition(const EGE::Maths::Vector3<float>& position)
{
    this->_position = position;
    this->_model->setPosition(position);
    this->_model->setOriginalModelMatrix();
}

EGE::Maths::Vector3<float> Onyx::Entity::getPosition()
{
    return this->_position;
}