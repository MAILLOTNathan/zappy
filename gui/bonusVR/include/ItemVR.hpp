/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** ItemVR
*/

#ifndef ITEMVR_HPP_
#define ITEMVR_HPP_

#include "EntityVR.hpp"
#include "WindowVR.hpp"
#include "Maths/Vector2.hpp"

#define CELL_SIZE 2
#define foodPosition EGE::Maths::Vector3<float>(position.x * CELL_SIZE - CELL_SIZE / 4.0f, 1, position.y * CELL_SIZE - CELL_SIZE / 4.0f) ///< The position of the food item in the game grid. @note use only if a EGE::Maths::Vector2<int> position is defined in the current scope.


class ItemVR : public EntityVR {
    public:
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

        ItemVR(const EGE::Maths::Vector2<int>& position, ItemVR::TYPE type, std::shared_ptr<EGE::WindowVR> window);
        ~ItemVR();

        void update(std::shared_ptr<EGE::Shader> shader);

        void setType(TYPE type);

        TYPE getType() const;

        void setPos(EGE::Maths::Vector2<int> position);

        EGE::Maths::Vector2<int> getPos() const;

    protected:
        TYPE _type;
        EGE::Maths::Vector2<int> _position;
    private:
};

#endif /* !ITEMVR_HPP_ */
