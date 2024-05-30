/*
** EPITECH PROJECT, 2024
** gui
** File description:
** Item
*/

#pragma once

#include "Entity.hpp"
#include "Error.hpp"
#include "Map.hpp"

namespace Onyx {
    class Item : public Onyx::Entity {
        public:
            class ItemError : public EGE::Error {
                public:
                    ItemError(std::string const &message) : EGE::Error(message) {}
            };
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

            Item(EGE::Maths::Vector2<int> position, Onyx::Item::TYPE type);
            ~Item();

            void update(std::shared_ptr<EGE::Shader> shader) override;

            TYPE getType() const;

            void setType(TYPE type);

            EGE::Maths::Vector2<int> getPosition() const;

            void setPosition(EGE::Maths::Vector2<int> position);
        private:
            TYPE _type;
            EGE::Maths::Vector2<int> _position;
    };
}