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
    #include "PlayerVR.hpp"

    #include "ItemVR.hpp"
    #include "MapVR.hpp"
    #include "TcpClient.hpp"

class GuiVR {
    public:
        GuiVR(android_app *app);
        ~GuiVR();

        void update();

        bool isRunning();

        void createMap(int width, int height);

        void addPlayer(int id, EGE::Maths::Vector2<int> position, const std::string &teamName, const std::string &rotation, int level, float timeUnit);

        std::shared_ptr<MapVR> _map;
    protected:
        float _timeUnit;
        std::shared_ptr<EGE::WindowVR> _window;
        std::shared_ptr<net::TcpClient> _client;
        std::vector<std::shared_ptr<EntityVR>> _entities;
        std::vector<std::shared_ptr<PlayerVR>> _players;
        std::shared_ptr<EGE::Shader> _shader;
    private:
};

#endif /* !GUIVR_HPP_ */
