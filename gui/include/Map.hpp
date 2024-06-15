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

            void createMap(const EGE::Maths::Vector2<int>& size);

            void addItem(const EGE::Maths::Vector2<int>& position, Onyx::Item::TYPE type, int number = 1);

            void removeItem(const EGE::Maths::Vector2<int>& position, Onyx::Item::TYPE type);

            EGE::Maths::Vector2<int> getSize() const;

            std::vector<std::shared_ptr<Floor>> getFloor() const;

            int getTileSelected(const EGE::Maths::Vector3<float>& cameraPosition, const EGE::Maths::Matrix<4, 4, float>& projection, const EGE::Maths::Matrix<4, 4, float>& view);

            void addEgg(EGE::Maths::Vector3<int> pos);

            std::vector<EGE::Maths::Vector3<int>>& getEggPos();

        private:
            std::vector<std::shared_ptr<Floor>> _floor; /**< The collection of floor models in the map. */
            std::shared_ptr<EGE::Shader> _shader;       /**< The shader used to update the map. */
            EGE::Maths::Vector2<int> _size;             /**< The size of the map. */
            std::shared_ptr<EGE::Model> _egg;           /**< The egg model. */
            std::vector<EGE::Maths::Vector3<int>> _eggPos; /**< The positions of the egg models on the map. */
    };
}