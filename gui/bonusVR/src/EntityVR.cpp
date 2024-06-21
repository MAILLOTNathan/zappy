/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** EntityVR
*/

#include "EntityVR.hpp"


void EntityVR::update(std::shared_ptr<EGE::Shader> shader)
{
}

void  EntityVR::setPosition(const EGE::Maths::Vector3<float>& position)
{
    this->_position = position;
    this->_model->setPosition(position);
}

EGE::Maths::Vector3<float>  EntityVR::getPosition()
{
    return this->_position;
}

std::shared_ptr<EGE::ModelVR> EntityVR::getModel()
{
    return this->_model;
}
