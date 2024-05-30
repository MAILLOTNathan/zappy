/*
** EPITECH PROJECT, 2024
** gui
** File description:
** Item
*/

#pragma once

#define CELL_SIZE 3

#include "Entity.hpp"
#include "Error.hpp"

/**
 * @namespace Onyx
 * The Onyx namespace contains all the classes and functions for the Onyx game engine.
 */
namespace Onyx {

    /**
     * @class Item
     * @brief This class represents an item in the Onyx game engine.
     * @details It inherits from the Entity class in the Onyx namespace.
     */
    class Item : public Onyx::Entity {
        public:

            /**
             * @class ItemError
             * @brief This class represents an error related to the Item class.
             * @details It inherits from the Error class in the EGE namespace.
             */
            class ItemError : public EGE::Error {
                public:
                    /**
                     * @brief Constructor for the ItemError class.
                     * @param message The error message.
                     */
                    ItemError(std::string const &message) : EGE::Error(message) {}
            };

            /**
             * @enum TYPE
             * @brief This enum represents the type of an item.
             */
            enum TYPE {
                FOOD = 0,
                LINEMATE,
                DERAUMERE,
                SIBUR,
                MENDIANE,
                PHIRAS,
                THYSTAME,
                MAX
            };

            /**
             * @brief Constructor for the Item class.
             * @param position The position of the item.
             * @param type The type of the item.
             */
            Item(EGE::Maths::Vector2<int> position, Onyx::Item::TYPE type);

            /**
             * @brief Destructor for the Item class.
             */
            ~Item();

            /**
             * @brief Updates the item.
             * @param shader The shader to use for the update.
             */
            void update(std::shared_ptr<EGE::Shader> shader) override;

            /**
             * @brief Gets the type of the item.
             * @return The type of the item.
             */
            TYPE getType() const;

            /**
             * @brief Sets the type of the item.
             * @param type The new type of the item.
             */
            void setType(TYPE type);

            /**
             * @brief Gets the position of the item in the grid of the game.
             *
             * @return The position of the item.
            */
            EGE::Maths::Vector2<int> getPos() const;

            /**
             * @brief Sets the position of the item in the grid of the game.
             *
             * @param position The new position of the item.
            */
            void setPos(EGE::Maths::Vector2<int> position);
        private:
            /**
             * @brief The type of the item.
             */
            TYPE _type;

            /**
             * @brief The position of the item.
             */
            EGE::Maths::Vector2<int> _position;
    };
}