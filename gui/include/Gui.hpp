/*
** EPITECH PROJECT, 2024
** gui
** File description:
** Gui
*/

#pragma once

#include "Camera.hpp"
#include "Entity.hpp"
#include "Error.hpp"
#include "Item.hpp"
#include "Map.hpp"
#include "Window.hpp"

#include "TcpClient.hpp"

#include "UserInterface.hpp"

namespace Onyx {
    /**
     * @class Gui
     * @brief The Gui class represents the graphical user interface for the application.
     *`
     * This class is responsible for managing the graphical elements and rendering them on the screen.
     */
    class Gui {
        public:
            /**
             * @brief Constructs a Gui object.
             */
            Gui();

            /**
             * @brief Destroys the Gui object.
             */
            ~Gui();

            /**
             * @brief Updates the graphical user interface.
             *
             * This method is called to update the graphical user interface.
             * @param running A reference to a boolean that indicates whether the application is running.
            */
            void update(bool& running);

            /**
             * @brief Creates a map.
             *
             * This method is called to create a map with the specified width and height.
             * @param width The width of the map.
             * @param height The height of the map.
            */
            void createMap(int width, int height);

            std::shared_ptr<Onyx::Map> getMap();

            std::shared_ptr<EGE::Window> getWindow() const;

            void createWorldPanel();

            void updateWorldPanel();
            // EGE::Panel *createPlayerPanel();

        private:
            /**
             * @brief Binds the events to the window.
             * @note This method is called by the constructor to bind the events to the window.
            */
            void _bindEvents();

            /**
             * @brief Updates the camera.
             * @note This method is called to update the camera's position and orientation.
            */
            void _updateCamera();

            std::shared_ptr<EGE::Window> _window;           /**< The window used for rendering the graphical user interface. */
            std::vector<std::shared_ptr<Entity>> _entities; /**< The entities in the graphical user interface. */
            std::shared_ptr<EGE::Shader> _shader;           /**< The shader used for rendering the entities. */
            std::shared_ptr<EGE::Camera> _camera;           /**< The camera used for rendering the entities. */
            float _deltaTime;                               /**< The time between frames. */
            std::shared_ptr<Onyx::Map> _map;                /**< The map in the graphical user interface. */
            std::shared_ptr<UserInterface> _interface;
    };
}