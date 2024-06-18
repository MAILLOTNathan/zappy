/*
** EPITECH PROJECT, 2024
** gui
** File description:
** Entity
*/

#pragma once

#include "Maths/Vector3.hpp"
#include "Model.hpp"
#include "Shader.hpp"

#include <memory>

namespace Onyx {
    /**
     * @class Entity
     * @brief Represents an entity in the game.
     *
     * This class provides a base for all entities in the game. It contains common
     * attributes and methods that are shared among different types of entities.
     */
    class Entity {
        public:
            /**
             * @brief Default destructor.
             */
            ~Entity() = default;

            /**
             * @brief Updates the entity.
             *
             * This method is called to update the entity's state.
             *
             * @param shader The shader used for rendering the entity.
             */
            virtual void update(std::shared_ptr<EGE::Shader> shader);

            /**
             * @brief Set the new position of the floor
             *
             * @param position The new position as a Vector3 of float
            */
            virtual void setPosition(const EGE::Maths::Vector3<float>& position);

            /**
             * @brief Returns the position of the floor
             *
             * @return The floor position as a Vector3 of float
            */
            virtual EGE::Maths::Vector3<float> getPosition();

            /**
             * @brief Returns the model associated with the entity.
             *
             * @return A shared pointer to the EGE::Model object representing the entity's model.
             */
            virtual std::shared_ptr<EGE::Model> getModel();

            /**
             * @brief Checks if the entity intersects with a ray.
             *
             * @param rayOrigin The origin of the ray.
             * @param rayPosition The position of the ray.
             * @param t The distance from the ray origin to the intersection point.
             * @param u The barycentric coordinate u of the intersection point.
             * @param v The barycentric coordinate v of the intersection point.
             * @return True if the entity intersects with the ray, false otherwise.
             */
            bool intersects(const glm::vec3& rayOrigin, const glm::vec3& rayPosition, float& t, float& u, float& v);
        protected:
            std::shared_ptr<EGE::Model> _model; /**< The model used for rendering the entity. */
            EGE::Maths::Vector3<float> _position; /**< The position of the entity in 3D space. */
    };
}