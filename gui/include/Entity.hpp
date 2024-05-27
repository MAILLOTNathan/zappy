/*
** EPITECH PROJECT, 2024
** gui
** File description:
** Entity
*/

#pragma once

#include "Maths/Vector3.hpp"
#include "Model.hpp"
#include "Shader.hpp"

#include <memory>

namespace Onyx {
    class Entity {
        public:
            ~Entity() = default;

            virtual void update(EGE::Shader& shader);
        protected:
            std::shared_ptr<EGE::Model> _model;
            EGE::Maths::Vector3<float> _position;
    };
}