/*
** EPITECH PROJECT, 2024
** gui
** File description:
** Animator
*/

#pragma once

#include "Player.hpp"
#include "Movement.hpp"

namespace Onyx {
    struct Animation {
        int id;
        static int globalId;
        std::shared_ptr<Onyx::Player> player;
        EGE::Movement movement;
        std::function<void()> callback;
        float time;
        float elapsedTime;

        bool operator==(const Animation& other) const {
            return this->player.get() == other.player.get();
        }
    };
    class Animator {
        public:
            Animator(float timeUnit = 1.0f);
            ~Animator();

            void update(float deltaTime);

            void startAnimation(const std::shared_ptr<Onyx::Player>& player, const Onyx::Player::Animation& type, const std::function<void()>& callback);

            void setTimeUnit(float timeUnit);

        private:
            std::vector<Onyx::Animation> _animations;
            std::vector<Onyx::Animation> _queuedAnimations;
            float _timeUnit;
            EGE::Movement forwardNorth = EGE::Movement()
            .pushBackKeyFrame(EGE::Maths::Matrix<4, 4, float>({
                {0.0f, 0.0f, 0.0f, 0.0f},
                {0.0f, 0.0f, 0.0f, 0.0f},
                {0.0f, 0.0f, 0.0f, 0.0f},
                {0.0f, 0.0f, 0.0f, 0.0f}
            }))
            .pushBackKeyFrame(EGE::Maths::Matrix<4, 4, float>({
                {0.0f, 0.0f, 0.0f, 0.0f},
                {0.0f, 0.0f, 0.0f, 0.0f},
                {0.0f, 0.0f, 0.0f, -CELL_SIZE},
                {0.0f, 0.0f, 0.0f, 0.0f}
            }));

            EGE::Movement forwardSouth = EGE::Movement()
            .pushBackKeyFrame(EGE::Maths::Matrix<4, 4, float>({
                {0.0f, 0.0f, 0.0f, 0.0f},
                {0.0f, 0.0f, 0.0f, 0.0f},
                {0.0f, 0.0f, 0.0f, 0.0f},
                {0.0f, 0.0f, 0.0f, 0.0f}
            }))
            .pushBackKeyFrame(EGE::Maths::Matrix<4, 4, float>({
                {0.0f, 0.0f, 0.0f, 0.0f},
                {0.0f, 0.0f, 0.0f, 0.0f},
                {0.0f, 0.0f, 0.0f, CELL_SIZE},
                {0.0f, 0.0f, 0.0f, 0.0f}
            }));

            EGE::Movement forwardEast = EGE::Movement()
            .pushBackKeyFrame(EGE::Maths::Matrix<4, 4, float>({
                {0.0f, 0.0f, 0.0f, 0.0f},
                {0.0f, 0.0f, 0.0f, 0.0f},
                {0.0f, 0.0f, 0.0f, 0.0f},
                {0.0f, 0.0f, 0.0f, 0.0f}
            }))
            .pushBackKeyFrame(EGE::Maths::Matrix<4, 4, float>({
                {0.0f, 0.0f, 0.0f, CELL_SIZE},
                {0.0f, 0.0f, 0.0f, 0.0f},
                {0.0f, 0.0f, 0.0f, 0.0f},
                {0.0f, 0.0f, 0.0f, 0.0f}
            }));

            EGE::Movement forwardWest = EGE::Movement()
            .pushBackKeyFrame(EGE::Maths::Matrix<4, 4, float>({
                {0.0f, 0.0f, 0.0f, 0.0f},
                {0.0f, 0.0f, 0.0f, 0.0f},
                {0.0f, 0.0f, 0.0f, 0.0f},
                {0.0f, 0.0f, 0.0f, 0.0f}
            }))
            .pushBackKeyFrame(EGE::Maths::Matrix<4, 4, float>({
                {0.0f, 0.0f, 0.0f, -CELL_SIZE},
                {0.0f, 0.0f, 0.0f, 0.0f},
                {0.0f, 0.0f, 0.0f, 0.0f},
                {0.0f, 0.0f, 0.0f, 0.0f}
            }));

            EGE::Movement left = EGE::Movement()
            .pushBackKeyFrame(EGE::Maths::Matrix<4, 4, float>({
                {0.0f, 0.0f, 0.0f, 0.0f},
                {0.0f, 0.0f, 0.0f, 0.0f},
                {0.0f, 0.0f, 0.0f, 0.0f},
                {0.0f, 0.0f, 0.0f, 0.0f}
            }))
            .pushBackKeyFrame(EGE::Maths::Matrix<4, 4, float>({
                {0.0f, 0.0f, 0.0f, 0.0f},
                {90.0f, 0.0f, 0.0f, 0.0f},
                {0.0f, 0.0f, 0.0f, 0.0f},
                {0.0f, 0.0f, 0.0f, 0.0f}
            }));

            EGE::Movement right = EGE::Movement()
            .pushBackKeyFrame(EGE::Maths::Matrix<4, 4, float>({
                {0.0f, 0.0f, 0.0f, 0.0f},
                {0.0f, 0.0f, 0.0f, 0.0f},
                {0.0f, 0.0f, 0.0f, 0.0f},
                {0.0f, 0.0f, 0.0f, 0.0f}
            }))
            .pushBackKeyFrame(EGE::Maths::Matrix<4, 4, float>({
                {0.0f, 0.0f, 0.0f, 0.0f},
                {-90.0f, 0.0f, 0.0f, 0.0f},
                {0.0f, 0.0f, 0.0f, 0.0f},
                {0.0f, 0.0f, 0.0f, 0.0f}
            }));
    };
}


