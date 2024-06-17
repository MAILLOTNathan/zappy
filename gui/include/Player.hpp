/*
** EPITECH PROJECT, 2024
** gui
** File description:
** Player
*/

#pragma once

#include "Animator.hpp"
#include "Entity.hpp"
#include "Error.hpp"
#include "Map.hpp"
#include "Movement.hpp"
#include "Utils.hpp"

#include <regex>

namespace Onyx {
    /**
     * @class PlayerError
     * @brief Exception class for player-related errors.
     *
     * This class is derived from the EGE::Error class and is used to handle errors
     * related to players in the game.
     */
    class PlayerError : public EGE::Error {
        public:
            /**
             * @brief Constructs a PlayerError object with the given error message.
             * @param message The error message associated with the exception.
             */
            PlayerError(const std::string& message) : EGE::Error(message) {}
    };

    /**
     * @class Player
     * @brief Represents a player in the game.
     *
     * This class is derived from the Onyx::Entity class and provides functionality
     * to manipulate and retrieve information about a player in the game.
     */
    class Player : public Onyx::Entity {
        public:
            /**
             * @enum Color
             * @brief Represents the color of a player.
             */
            enum Color {
                UNDEFINED = 0, /**< Undefined color */
                RED, /**< Red color */
                GREEN, /**< Green color */
                BLUE, /**< Blue color */
                PINK, /**< Pink color */
                YELLOW, /**< Yellow color */
                ORANGE, /**< Orange color */
                PURPLE, /**< Purple color */
                CYAN, /**< Cyan color */
                LAST /**< Last color */
            };

            /**
             * @enum Animation
             * @brief Represents the animation of a player.
             */
            enum Animation {
                NONE = -1, /**< No animation */
                FORWARD_NORTH = 0, /**< Forward north animation */
                LEFT, /**< Left animation */
                RIGHT, /**< Right animation */
                BROADCAST, /**< Broadcast animation */
                INCANTATION, /**< Incantation animation */
                EXPULSE, /**< Expulse animation */
                FORWARD_EAST, /**< Forward east animation */
                FORWARD_SOUTH, /**< Forward south animation */
                FORWARD_WEST, /**< Forward west animation */
                MAX /**< Maximum animation */
            };

            /**
             * @brief Constructs a Player object with the specified parameters.
             * @param id The ID of the player.
             * @param teamName The name of the team the player belongs to.
             * @param position The position of the player.
             * @param rotation The rotation of the player.
             * @param timeUnit The time unit of the player.
             */
            Player(int id, const std::string& teamName, const EGE::Maths::Vector2<int>& position, const std::string& rotation, float timeUnit);

            /**
             * @brief Destructor for the Player object.
             */
            ~Player();

            /**
             * @brief Updates the player's state.
             * @param shader The shader used for rendering.
             */
            void update(std::shared_ptr<EGE::Shader> shader) override;

            /**
             * @brief Evolves the player.
             */
            void evolve();

            /**
             * @brief Moves the player forward.
             */
            void forward();

            /**
             * @brief Rotates the player to the left.
             */
            void left();

            /**
             * @brief Rotates the player to the right.
             */
            void right();

            /**
             * @brief Sets the level of the player.
             * @param level The level to set.
             */
            void setLevel(int level);

            /**
             * @brief Gets the level of the player.
             * @return The level of the player.
             */
            int getLevel();

            /**
             * @brief Sets the color of the player.
             * @param color The color to set.
             */
            void setColor(const Color& color);

            /**
             * @brief Gets the color of the player.
             * @return The color of the player.
             */
            Color getColor();

            /**
             * @brief Sets the team name of the player.
             * @param teamName The team name to set.
             */
            void setTeamName(const std::string& teamName);

            /**
             * @brief Gets the team name of the player.
             * @return The team name of the player.
             */
            std::string getTeamName();

            /**
             * @brief Sets the rotation of the player.
             * @param rotation The rotation to set.
             */
            void setRotation(const std::string& rotation);

            /**
             * @brief Gets the rotation of the player.
             * @return The rotation of the player.
             */
            EGE::Maths::Vector3<float> getRotation();

            /**
             * @brief Sets the rotation string of the player.
             * @param rotation The rotation string to set.
             */
            void setRotationString(const std::string& rotation);

            /**
             * @brief Gets the rotation string of the player.
             * @return The rotation string of the player.
             */
            std::string getRotationString();

            /**
             * @brief Sets the position of the player.
             * @param pos The position to set.
             */
            void setPos(EGE::Maths::Vector2<int> pos);

            /**
             * @brief Gets the position of the player.
             * @return The position of the player.
             */
            EGE::Maths::Vector2<int> getPos();

            /**
             * @brief Sets the time unit of the player.
             * @param timeUnit The time unit to set.
             */
            void setTimeUnit(int timeUnit);

            /**
             * @brief Gets the time unit of the player.
             * @return The time unit of the player.
             */
            int getTimeUnit();

            /**
             * @brief Gets the ID of the player.
             * @return The ID of the player.
             */
            int getId();

            /**
             * @brief Sets the delta time of the player.
             * @param deltaTime The delta time to set.
             */
            void setDelta(float deltaTime);

            /**
             * @brief Gets the delta time of the player.
             * @return The delta time of the player.
             */
            float getDelta();

            /**
             * @brief Gets the quantity of a specific item in the player's inventory.
             * @param type The type of the item.
             * @return The quantity of the item.
             */
            int getQuantity(Onyx::Item::TYPE type);

            /**
             * @brief Sets the quantity of a specific item in the player's inventory.
             * @param quantity The quantity to set.
             * @param type The type of the item.
             */
            void setInventory(int quantity, Onyx::Item::TYPE type);

            /**
             * @brief Gets the string representation of an animation.
             * @param animation The animation.
             * @return The string representation of the animation.
             */
            static std::string getAnimationString(Onyx::Player::Animation animation);

            bool isAnimated; /**< Flag indicating if the player is animated. */

        private:
            /**
             * @brief Sets the color of the player based on the team name.
             * @param teamName The team name.
             */
            void _setColor(std::string &teamName);

            int _id; /**< The ID of the player. */
            Color _color; /**< The color of the player. */
            int _level; /**< The level of the player. */
            std::string _teamName; /**< The team name of the player. */
            int _quantity[Onyx::Item::TYPE::MAX]; /**< The quantity of items in the player's inventory. */
            static std::vector<std::shared_ptr<Onyx::Item>> _items; /**< The items in the game. */
            static std::map<std::string, Color> _colorMap; /**< The color map. */
            EGE::Maths::Vector2<int> _pos; /**< The position of the player. */
            EGE::Maths::Vector3<float> _rotation; /**< The rotation of the player. */
            std::string _rotationString; /**< The rotation string of the player. */
            const EGE::Maths::Vector3<float> _scale = {0.2f, 0.2f, 0.2f}; /**< The scale of the player. */
            float _timeUnit; /**< The time unit of the player. */
            float _deltaTime; /**< The delta time of the player. */
    };
}