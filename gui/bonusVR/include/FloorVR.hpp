/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** FloorVR
*/

#ifndef FLOORVR_HPP_
#define FLOORVR_HPP_

#include "EntityVR.hpp"
#include "ItemVR.hpp"
#include "Shader.hpp"
#include "WindowVR.hpp"

class FloorVR : public EntityVR {
    public:
        FloorVR(const EGE::Maths::Vector2<int>& position, std::shared_ptr<EGE::WindowVR> window);

        ~FloorVR();

        void update(std::shared_ptr<EGE::Shader> shader);

        void addItem(ItemVR::TYPE type, int number = 1);

        void removeItem(ItemVR::TYPE type);

        int getQuantity(ItemVR::TYPE type) const;

        EGE::Maths::Vector2<int> getPosition() const;

    protected:
        int _quantity[ItemVR::TYPE::MAX];
        static std::vector<std::shared_ptr<ItemVR>> _items;
        EGE::Maths::Vector2<int> _pos;
    private:
};

#endif /* !FLOORVR_HPP_ */
