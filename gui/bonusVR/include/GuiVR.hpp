/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** GuiVR
*/

#ifndef GUIVR_HPP_
    #define GUIVR_HPP_

    #include "ModelVR.hpp"
    #include "WindowVR.hpp"
    #include "EntityVR.hpp"
    #include <memory>

    #include "ItemVR.hpp"
    #include "MapVR.hpp"

class GuiVR {
    public:
        GuiVR(android_app *app);
        ~GuiVR();

        void update();

        bool isRunning();

        void createMap(int width, int height);

    protected:
        std::shared_ptr<EGE::WindowVR> _window;
        std::vector<std::shared_ptr<EntityVR>> _entities;
        std::shared_ptr<MapVR> _map;
        std::shared_ptr<EGE::Shader> _shader;
    private:
};

#endif /* !GUIVR_HPP_ */
