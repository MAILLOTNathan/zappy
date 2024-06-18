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

std::shared_ptr<EGE::Model> Onyx::Entity::getModel()
{
    return this->_model;
}

bool Onyx::Entity::intersects(const glm::vec3& rayOrigin, const glm::vec3& rayPosition, float& t, float& u, float& v)
{
    const float EPSILON = 0.0000001f;
    glm::vec3 edge1, edge2, h, s, q, v0, v1, v2;

    for (auto& mesh : this->_model->getMeshes()) {
        std::vector<EGE::Vertex> vertices = mesh.getVertices();
        for (int i = 0; i < vertices.size(); i += 3) {
            v0 = vertices[i]._position;
            v1 = vertices[i + 1]._position;
            v2 = vertices[i + 2]._position;

            edge1 = v1 - v0;
            edge2 = v2 - v0;

            h = glm::cross(rayPosition, edge2);
            float a = glm::dot(edge1, h);

            if (a > -EPSILON && a < EPSILON)
                continue;

            float f = 1.0 / a;
            s = rayOrigin - v0;
            u = f * glm::dot(s, h);

            if (u < 0.0 || u > 1.0)
                continue;

            q = glm::cross(s, edge1);
            v = f * glm::dot(rayPosition, q);

            if (v < 0.0 || u + v > 1.0)
                continue;

            t = f * glm::dot(edge2, q);

            if (t > EPSILON)
                return true;
        }
    }
    return false;
}
