/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** MapVR
*/

#ifndef MAPVR_HPP_
    #define MAPVR_HPP_

#include "Maths/Vector2.hpp"
#include "WindowVR.hpp"
#include "Shader.hpp"
#include "FloorVR.hpp"

class MapVR : public EntityVR {
    public:
        MapVR();

        MapVR(const EGE::Maths::Vector2<int>& size, std::shared_ptr<EGE::WindowVR> window);

        ~MapVR();

        void update(std::shared_ptr<EGE::Shader> shader);

        void addItem(const EGE::Maths::Vector2<int>& position, ItemVR::TYPE type, int number = 1);

        void removeItem(const EGE::Maths::Vector2<int>& position, ItemVR::TYPE type);

        EGE::Maths::Vector2<int> getSize() const;

        std::vector<std::shared_ptr<FloorVR>> getFloor() const;

        void addEgg(const EGE::Maths::Vector2<int>& position);

        std::vector<EGE::Maths::Vector2<int>>& getEggPos();

    protected:
        std::vector<std::shared_ptr<FloorVR>> _floor;
        EGE::Maths::Vector2<int> _size;
        std::shared_ptr<EGE::WindowVR> _window;
        std::shared_ptr<EGE::ModelVR> _modelEgg;
        std::vector<EGE::Maths::Vector2<int>> _eggPos;
    private:
};

#endif /* !MAPVR_HPP_ */
