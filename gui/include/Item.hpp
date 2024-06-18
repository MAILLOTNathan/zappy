/*
** EPITECH PROJECT, 2024
** gui
** File description:
** Item
*/

#pragma once

#define CELL_SIZE 9

#define foodPosition EGE::Maths::Vector3<float>(position.x * CELL_SIZE - CELL_SIZE / 4.0f, 3.0f, position.y * CELL_SIZE - CELL_SIZE / 4.0f) ///< The position of the food item in the game grid. @note use only if a EGE::Maths::Vector2<int> position is defined in the current scope.
#define linematePosition EGE::Maths::Vector3<float>(position.x * CELL_SIZE, 3.0f, position.y * CELL_SIZE - CELL_SIZE / 4.0f) ///< The position of the linemate item in the game grid. @note use only if a EGE::Maths::Vector2<int> position is defined in the current scope.
#define deraumerePosition EGE::Maths::Vector3<float>(position.x * CELL_SIZE + CELL_SIZE / 4.0f, 3.0f, position.y * CELL_SIZE - CELL_SIZE / 4.0f) ///< The position of the deraumere item in the game grid. @note use only if a EGE::Maths::Vector2<int> position is defined in the current scope.
#define siburPosition EGE::Maths::Vector3<float>(position.x * CELL_SIZE - CELL_SIZE / 4.0f, 3.0f, position.y * CELL_SIZE) ///< The position of the sibur item in the game grid. @note use only if a EGE::Maths::Vector2<int> position is defined in the current scope.
#define mendianePosition EGE::Maths::Vector3<float>(position.x * CELL_SIZE + CELL_SIZE / 4.0f, 3.0f, position.y * CELL_SIZE) ///< The position of the mendiane item in the game grid. @note use only if a EGE::Maths::Vector2<int> position is defined in the current scope.
#define phirasPosition EGE::Maths::Vector3<float>(position.x * CELL_SIZE - CELL_SIZE / 4.0f, 3.0f, position.y * CELL_SIZE + CELL_SIZE / 4.0f) ///< The position of the phiras item in the game grid. @note use only if a EGE::Maths::Vector2<int> position is defined in the current scope.
#define thystamePosition EGE::Maths::Vector3<float>(position.x * CELL_SIZE + CELL_SIZE / 4.0f, 3.0f, position.y * CELL_SIZE + CELL_SIZE / 4.0f) ///< The position of the thystame item in the game grid. @note use only if a EGE::Maths::Vector2<int> position is defined in the current scope.

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
                FOOD = 0,   /// the steak item
                LINEMATE,   /// the purple item
                DERAUMERE,  /// the yellow item
                SIBUR,      /// the blue-green square
                MENDIANE,   /// the blue diamond
                PHIRAS,     /// the blue rectangle
                THYSTAME,   /// the pink (or red) square
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