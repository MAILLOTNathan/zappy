/*
** EPITECH PROJECT, 2024
** gui
** File description:
** Floot
*/

#pragma once

#include "Entity.hpp"
#include "Shader.hpp"

namespace Onyx {
    class Floor : public Onyx::Entity {
        public:
            Floor(const EGE::Maths::Vector3<float>& position);
            ~Floor();

            void update(EGE::Shader& shader) override;
        private:
    };
}