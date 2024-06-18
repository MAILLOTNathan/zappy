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
             * @brief Constructs a Map object with (1, 1) size.
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
             * @brief Creates a map with the specified size.
             *
             * @param size The size of the map.
            */
            void createMap(const EGE::Maths::Vector2<int>& size);

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
             * @brief Gets the tile selected by the player.
             *
             * This function returns the index of the tile selected by the player.
             * The index is calculated based on the camera position, projection matrix, and view matrix.
             *
             * @param cameraPosition The position of the camera.
             * @param projection The projection matrix.
             * @param view The view matrix.
             * @return The index of the tile selected by the player.
            */
            int getTileSelected(const EGE::Maths::Vector3<float>& cameraPosition, const EGE::Maths::Matrix<4, 4, float>& projection, const EGE::Maths::Matrix<4, 4, float>& view);

            /**
             * @brief Adds an egg to the map at the specified position.
             *
             * @param pos The position where the egg should be added.
             */
            void addEgg(EGE::Maths::Vector3<int> pos);

            /**
             * @brief Returns the position vector of the eggs.
             *
             * @return The position vector of the eggs.
             */
            std::vector<EGE::Maths::Vector3<int>>& getEggPos();
        private:
            std::vector<std::shared_ptr<Floor>> _floor;     /**< The collection of floor models in the map. */
            std::shared_ptr<EGE::Shader> _shader;           /**< The shader used to update the map. */
            EGE::Maths::Vector2<int> _size;                 /**< The size of the map. */
            std::shared_ptr<EGE::Model> _egg;               /**< The egg model. */
            std::vector<EGE::Maths::Vector3<int>> _eggPos;  /**< The positions of the egg models on the map. */
    };
}