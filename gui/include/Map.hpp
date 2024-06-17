/*
** EPITECH PROJECT, 2024
** gui
** File description:
** Map
*/

#pragma once

#define UNUSED __attribute__((unused))

#include "Floor.hpp"
#include "Maths/Vector2.hpp"
#include "Utils.hpp"

#include <regex>

namespace Onyx {
    /**
     * @brief Represents a map in the game.
     *
     * The Map class is a derived class of the Onyx::Entity class and represents a map in the game.
     * It contains a collection of floor objects and provides functionality to update the map using a shader.
     */
    class Map : public Onyx::Entity {
        public:
            /**
             * @brief Constructs a Map object with the specified size.
             *
             * @param size The size of the map.
             */
            Map();

            /**
             * @brief Constructs a Map object with the specified size.
             *
             * @param size The size of the map.
             */
            Map(const EGE::Maths::Vector2<int>& size);

            /**
             * @brief Destroys the Map object.
             */
            ~Map();

            /**
             * @brief Updates the map using the specified shader.
             *
             * @param shader The shader used to update the map.
             */
            void update(std::shared_ptr<EGE::Shader> shader);

            /**
             * @brief Adds an item to the map at the specified position.
             *
             * @param position The position where the item should be added.
             * @param type The type of the item to be added.
             * @param number The number of items to be added (default is 1).
             */
            void addItem(const EGE::Maths::Vector2<int>& position, Onyx::Item::TYPE type, int number = 1);

            /**
             * @brief Removes an item of a specific type from the map at the given position.
             *
             * @param position The position of the item to be removed.
             * @param type The type of the item to be removed.
             */
            void removeItem(const EGE::Maths::Vector2<int>& position, Onyx::Item::TYPE type);

            /**
             * @brief Gets the size of the map.
             *
             * @return The size of the map as a 2D vector.
             */
            EGE::Maths::Vector2<int> getSize() const;

            /**
             * @brief Retrieves the vector of shared pointers to Floor objects.
             *
             * This function returns a vector containing shared pointers to Floor objects.
             * Each shared pointer represents a floor tile on the map.
             *
             * @return A vector of shared pointers to Floor objects.
             */
            std::vector<std::shared_ptr<Floor>> getFloor() const;

            /**
             * @brief Gets the tile selected by the mouse on the map.
             *
             * This function takes the camera position, camera front direction, and mouse position as parameters
             * and returns the index of the tile selected on the map.
             *
             * @param cameraPosition The position of the camera in 3D space.
             * @param cameraFront The front direction of the camera.
             * @param mousePos The position of the mouse on the screen.
             * @return The index of the tile selected on the map.
             */
            int getTileSelected(EGE::Maths::Vector3<float> cameraPositon, EGE::Maths::Vector3<float> cameraFront, EGE::Maths::Vector2<int> mousePos);

        private:
            std::vector<std::shared_ptr<Floor>> _floor; /**< The collection of floor models in the map. */
            std::shared_ptr<EGE::Shader> _shader;       /**< The shader used to update the map. */
            EGE::Maths::Vector2<int> _size;             /**< The size of the map. */
    };
}