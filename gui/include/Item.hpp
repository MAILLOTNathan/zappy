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

            EGE::Maths::Vector2<int> getPos() const;

            void setPos(EGE::Maths::Vector2<int> position);
        private:
            TYPE _type;
            EGE::Maths::Vector2<int> _position;
    };
}