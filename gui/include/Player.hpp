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
#include "Utils.hpp"

#include <regex>

namespace Onyx {
    class PlayerError : public EGE::Error {
        public:
            PlayerError(const std::string& message) : EGE::Error(message) {}
    };

    class Player : public Onyx::Entity {
        public:
            enum Color {
                UNDEFINED = 0,
                RED,
                GREEN,
                BLUE,
                PINK,
                YELLOW,
                ORANGE,
                PURPLE,
                CYAN,
                LAST
            };
            Player(int id, const std::string& teamName, const EGE::Maths::Vector2<int>& position, const std::string& rotation);
            ~Player();

            void update(std::shared_ptr<EGE::Shader> shader) override;

            void evolve();
            void forward();
            void left();
            void right();

            void setLevel(int level);
            int getLevel();

            void setColor(const Color& color);
            Color getColor();

            void setTeamName(const std::string& teamName);
            std::string getTeamName();

            void setRotation(const std::string& rotation);
            EGE::Maths::Vector3<float> getRotation();
            std::string getRotationString();

            void setPos(EGE::Maths::Vector2<int> pos);
            EGE::Maths::Vector2<int> getPos();

            int getId();

            int getQuantity(Onyx::Item::TYPE type);

            void setInventory(int quantity, Onyx::Item::TYPE type);
        private:
            void _setColor(std::string &teamName);

            int _id;
            Color _color;
            int _level;
            std::string _teamName;
            int _quantity[Onyx::Item::TYPE::MAX];
            static std::vector<std::shared_ptr<Onyx::Item>> _items;
            static std::map<std::string, Color> _colorMap;
            EGE::Maths::Vector2<int> _pos;
            EGE::Maths::Vector3<float> _rotation;
            std::string _rotationString;
            const EGE::Maths::Vector3<float> _scale = {0.2f, 0.2f, 0.2f};
    };
}