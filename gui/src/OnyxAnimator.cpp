/*
** EPITECH PROJECT, 2024
** gui
** File description:
** Animator
*/

#include "OnyxAnimator.hpp"

int Onyx::Animation::globalId = 0;

Onyx::Animator::Animator(float timeUnit)
{
    if (timeUnit == 0.0f)
        throw EGE::Movement::MovementError("Time unit cannot be equal to 0");
    if (timeUnit < 0.0f)
        throw EGE::Movement::MovementError("Time unit cannot be negative");
    this->_timeUnit = timeUnit;
}

Onyx::Animator::~Animator()
{
}

void Onyx::Animator::update(float deltaTime)
{
    int size = this->_animations.size();
    for (int i = 0; i < size; i++) {
        this->_animations[i].elapsedTime += deltaTime;
        this->_animations[i].movement.move(deltaTime);
        if (this->_animations[i].elapsedTime >= (this->_animations[i].time / 1000.0f)) {
            if (this->_animations[i].callback)
                this->_animations[i].callback();
            this->_animations[i].player->isAnimated = false;
            this->_animations.erase(std::remove(this->_animations.begin(), this->_animations.end(), this->_animations[i]), this->_animations.end());
            size--;
            i--;
        }
    }
    size = this->_queuedAnimations.size();
    for (int i = 0; i < size; i++) {
        if (this->_queuedAnimations[i].player->isAnimated) {
            continue;
        }
        this->_queuedAnimations[i].player->isAnimated = true;
        this->_animations.push_back(this->_queuedAnimations[i]);
        this->_queuedAnimations.erase(std::remove(this->_queuedAnimations.begin(), this->_queuedAnimations.end(), this->_queuedAnimations[i]), this->_queuedAnimations.end());
        size--;
        i--;
    }
}

// ! Animations give segfaults if the gui receives too many animations to do on the same player
// ! e.g. if the server sends 2 "Left"  animations in a row, the player will segfault because the first animation is not finished so the player's data is not updated
// ! this causes the player to try to rotate first from North to East, then from East to South, but the player is still facing North but North to South is not a valid rotation

void Onyx::Animator::startAnimation(const std::shared_ptr<Onyx::Player>& player, const Onyx::Player::Animation& type, const std::function<void()>& callback)
{
    Onyx::Animation animation;
    animation.player = player;
    animation.id = Onyx::Animation::globalId++;
    switch (type) {
        case Onyx::Player::Animation::FORWARD_NORTH:
            animation.movement = EGE::Movement(this->forwardNorth);
            animation.time = 7000 / this->_timeUnit;
            break;
        case Onyx::Player::Animation::FORWARD_SOUTH:
            animation.movement = EGE::Movement(this->forwardSouth);
            animation.time = 7000 / this->_timeUnit;
            break;
        case Onyx::Player::Animation::FORWARD_EAST:
            animation.movement = EGE::Movement(this->forwardEast);
            animation.time = 7000 / this->_timeUnit;
            break;
        case Onyx::Player::Animation::FORWARD_WEST:
            animation.movement = EGE::Movement(this->forwardWest);
            animation.time = 7000 / this->_timeUnit;
            break;
        case Onyx::Player::Animation::LEFT:
            animation.movement = EGE::Movement(this->left);
            animation.time = 7000 / this->_timeUnit;
            break;
        case Onyx::Player::Animation::RIGHT:
            animation.movement = EGE::Movement(this->right);
            animation.time = 7000 / this->_timeUnit;
            break;
        default:
            break;
    }
    animation.movement.addModel("player", player->getModel());
    animation.movement.setDuration(animation.time);
    animation.callback = callback;
    animation.elapsedTime = 0.0;
    this->_queuedAnimations.push_back(animation);
}

void Onyx::Animator::setTimeUnit(float timeUnit)
{
    if (timeUnit == 0.0f)
        throw EGE::Movement::MovementError("Time unit cannot be equal to 0");
    if (timeUnit < 0.0f)
        throw EGE::Movement::MovementError("Time unit cannot be negative");
    this->_timeUnit = timeUnit;
}