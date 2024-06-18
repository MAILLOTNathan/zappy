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
    /**
     * @brief Represents an animation for the OnyxAnimator class.
     */
    struct Animation {
        int id; /**< The ID of the animation. */
        static int globalId; /**< The global ID of the animation. */
        std::shared_ptr<Onyx::Player> player; /**< The player associated with the animation. */
        EGE::Movement movement; /**< The movement of the animation. */
        std::function<void()> callback; /**< The callback function to be executed after the animation is completed. */
        float time; /**< The total duration of the animation. */
        float elapsedTime; /**< The elapsed time since the animation started. */

        /**
         * @brief Overloaded equality operator for comparing animations.
         * @param other The other animation to compare with.
         * @return True if the animations are equal, false otherwise.
         */
        bool operator==(const Animation& other) const {
            return this->player.get() == other.player.get();
        }
    };

    /**
     * @class Animator
     * @brief The Animator class is responsible for managing animations for a player.
     *
     * The Animator class provides methods to start and update animations for a player.
     * It supports different types of animations and allows setting the time unit for animation updates.
     */
    class Animator {
        public:
            /**
             * @brief Constructs an instance of the Animator class.
             *
             * @param timeUnit The time unit used for animation (default is 1.0f).
             */
            Animator(float timeUnit = 1.0f);
            ~Animator();

            /**
             * @brief Updates the animator.
             *
             * This function is called to update the animator's state based on the elapsed time since the last update.
             *
             * @param deltaTime The time elapsed since the last update, in seconds.
             */
            void update(float deltaTime);

            /**
             * Starts an animation for a player.
             *
             * @param player The player to animate.
             * @param type The type of animation to start.
             * @param callback The callback function to be called when the animation is finished.
             */
            void startAnimation(const std::shared_ptr<Onyx::Player>& player, const Onyx::Player::Animation& type, const std::function<void()>& callback);

            /**
             * @brief Sets the time unit for the animator.
             *
             * This function sets the time unit for the animator. The time unit determines the speed at which the animation plays.
             *
             * @param timeUnit The time unit to set.
             */
            void setTimeUnit(float timeUnit);

        private:
            std::vector<Onyx::Animation> _animations;           /**< Vector of animation frames. */
            std::vector<Onyx::Animation> _queuedAnimations;     /**< Vector of animations which is waiting to be played. */
            float _timeUnit;                                    /**< Time unit of a frame. */
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


