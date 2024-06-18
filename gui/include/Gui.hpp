/**
 * @file Gui.hpp
 * @brief Contains the declaration of the Gui class.
 */

#pragma once

#include "Camera.hpp"
#include "Entity.hpp"
#include "Error.hpp"
#include "Item.hpp"
#include "Map.hpp"
#include "OnyxAnimator.hpp"
#include "Player.hpp"
#include "Window.hpp"

#include "TcpClient.hpp"

#include "UserInterface.hpp"

namespace Onyx {
    /**
     * @class Gui
     * @brief The Gui class represents the graphical user interface for the application.
     *
     * This class is responsible for managing the graphical elements and rendering them on the screen.
     */
    class Gui {
        public:
            /**
             * @brief Constructs a Gui object.
             * @param client The TCP client used for communication with the server.
             */
            Gui(net::TcpClient client);

            /**
             * @brief Destroys the Gui object.
             */
            ~Gui();

            /**
             * @brief Updates the graphical user interface.
             *
             * This method is called to update the graphical user interface.
            */
            void update();

            /**
             * @brief Creates a map.
             *
             * This method is called to create a map with the specified width and height.
             * @param width The width of the map.
             * @param height The height of the map.
            */
            void createMap(int width, int height);

            /**
             * @brief Adds a player to the graphical user interface.
             * @param id The ID of the player.
             * @param position The position of the player.
             * @param teamName The name of the team the player belongs to.
             * @param rotation The rotation of the player.
             * @param timeUnit The time unit of the world.
             */
            void addPlayer(int id, EGE::Maths::Vector2<int> position, std::string teamName, const std::string& rotation, int level, float timeUnit);

            /**
             * @brief Gets the map.
             * @return A shared pointer to the map object.
             */
            std::shared_ptr<Onyx::Map> getMap();

            /**
             * @brief Gets the window.
             * @return A shared pointer to the window object.
             */
            std::shared_ptr<EGE::Window> getWindow() const;

            /**
             * @brief Starts the main loop of the graphical user interface.
             */
            void loop();

            /**
             * @brief Checks if the graphical user interface is running.
             * @return True if the graphical user interface is running, false otherwise.
             */
            bool isRunning() const;

            /**
             * @brief Creates the world panel.
             */
            void createWorldPanel();

            /**
             * @brief Creates the tile panel.
             */
            void createTilePanel();

            /**
             * @brief Creates the console panel.
             */
            void createConsolePanel();

            /**
             * @brief Creates the menu bar.
             */
            void createMenuBar();

            /**
             * @brief Creates the tutorial.
             */
            void createTutorial();

            /**
             * @brief Creates the player panel.
             */
            void createPlayerPanel();

            /**
             * @brief Updates the player panel.
             * @param player A shared pointer to the player object.
             */
            void updatePlayerPanel(std::shared_ptr<Onyx::Player> &player);

            /**
             * @brief Updates the world panel.
             */
            void updateWorldPanel();

            /**
             * @brief Updates the tile panel.
             */
            void updateTilePanel();

            /**
             * @brief Updates the console panel.
             * @param args The arguments to be displayed in the console panel.
             */
            void updateConsolePanel(std::vector<std::string>& args);

            /**
             * @brief Updates the world settings.
             * @param value The value of the world settings.
             */
            void updateWorldSettings(float value);

            /**
             * @brief Updates the sensitivities.
             * @param value The value of the sensitivities.
             */
            void updateSensitivities(float value);

        private:
            /**
             * @brief Binds the events to the window.
             *
             * This method is called by the constructor to bind the events to the window.
             */
            void _bindEvents();

            /**
             * @brief Updates the camera.
             *
             * This method is called to update the camera's position and orientation.
             */
            void _updateCamera();

            std::shared_ptr<EGE::Window> _window;                   /**< The window used for rendering the graphical user interface. */
            std::vector<std::shared_ptr<Entity>> _entities;         /**< The entities in the graphical user interface. */
            std::shared_ptr<EGE::Shader> _shader;                   /**< The shader used for rendering the entities. */
            std::shared_ptr<EGE::Camera> _camera;                   /**< The camera used for rendering the entities. */
            float _deltaTime;                                       /**< The time between frames. */
            std::shared_ptr<Onyx::Map> _map;                        /**< The map in the graphical user interface. */
            int _tileSelected;                                      /**< The selected tile. */
            std::shared_ptr<UserInterface> _interface;              /**< The Interface which displays informations about the world. */
            bool _running;                                          /**< A boolean that indicates whether the application is running. */
            net::TcpClient *_client;                                /**< The TCP client used for communication with the server. */
            std::vector<std::shared_ptr<Onyx::Player>> _players;    /**< The players in the graphical user interface. */
            std::vector<std::string> _teams;                        /**< The names of all the teams. */
            bool _cameraMode;                                       /**< A boolean that indicates whether the camera mode is enabled. */
            float _timeUnit;                                        /**< The time unit. */
            Onyx::Animator _animator;                               /**< The animator used for animating the players. */
    };
}