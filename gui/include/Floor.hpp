/*
** EPITECH PROJECT, 2024
** gui
** File description:
** Floot
*/

#pragma once

#include "Entity.hpp"
#include "Item.hpp"
#include "Shader.hpp"

#include <GL/glu.h>

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
            Floor(const EGE::Maths::Vector2<int>& position);

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

            /**
             * @brief Adds an item to the floor entity.
             *
             * @param type The type of the item to add.
             */
            void addItem(Onyx::Item::TYPE type, int number);

            /**
             * @brief Removes an item from the floor entity.
             *
             * @param type The type of the item to remove.
             */
            void removeItem(Onyx::Item::TYPE type);

            /**
             * @brief Gets the items on the floor entity.
             *
             * @return A vector of shared pointers to the items on the floor entity.
             */
            int getQuantity(Onyx::Item::TYPE type) const;

            float getDistance(const EGE::Maths::Vector3<float>& cameraPositon, const EGE::Maths::Vector3<float>& cameraFront) const;

            EGE::Maths::Vector2<int> getPos() const;

        private:
            int _quantity[Onyx::Item::TYPE::MAX]; /**< The quantity of each item on the floor entity. */
            static std::vector<std::shared_ptr<Onyx::Item>> _items; /**< The collection of items in the map. */
            EGE::Maths::Vector2<int> _pos; /**< The position of the floor entity. */
    };
}