/*
** EPITECH PROJECT, 2024
** gui
** File description:
** Floot
*/

#pragma once

#include "Entity.hpp"
#include "Shader.hpp"

namespace Onyx {
    /**
     * @brief The Floor class represents a floor entity in the game.
     *
     * This class inherits from the Onyx::Entity class and provides functionality
     * to update and render the floor entity.
     */
    class Floor : public Onyx::Entity {
        public:
            /**
             * @brief Constructs a Floor object with the given position.
             *
             * @param position The position of the floor entity.
             */
            Floor(const EGE::Maths::Vector3<float>& position);

            /**
             * @brief Destroys the Floor object.
             */
            ~Floor();

            /**
             * @brief Updates the floor entity.
             *
             * This function is called to update the floor entity's state.
             *
             * @param shader A shared pointer to the shader used for rendering.
             */
            void update(std::shared_ptr<EGE::Shader> shader) override;
    };
}