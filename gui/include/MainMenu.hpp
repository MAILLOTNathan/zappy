/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** MainMenu
*/

#ifndef MAINMENU_HPP_
#define MAINMENU_HPP_

#include "Camera.hpp"
#include "Error.hpp"
#include "Window.hpp"

#include "TcpClient.hpp"

#include "Gui.hpp"

namespace Onyx {
    /**
     * @class MainMenu
     * @brief The MainMenu class represents the main menu of the application.
     *
     * The MainMenu class is responsible for managing the main menu of the application.
     * It provides functions for updating and looping the menu, checking if the application is running,
     * creating the main panel, and getting the TCP client.
     * It also contains member variables for storing the running state, TCP client, window, camera,
     * delta time, and user interface.
     */
    class MainMenu {
        public:
            /**
             * @brief Default constructor for MainMenu.
             */
            MainMenu(const std::string& ip, int port);

            /**
             * @brief Destructor for MainMenu.
             */
            ~MainMenu();

            /**
             * @brief Updates the main menu.
             */
            void update();

            /**
             * @brief Loops the main menu.
             */
            void loop();

            /**
             * @brief Checks if the application is running.
             * @return true if the application is running, false otherwise.
             */
            bool isRunning() const;

            /**
             * @brief Creates the main panel of the menu.
             */
            void createMainPanel();

            /**
             * @brief Gets the TCP client.
             * @return A pointer to the TCP client.
             */
            net::TcpClient *getClient() const;

            /**
             * @brief Get the window object.
             *
             * @return std::shared_ptr<EGE::Window> The window object.
             */
            std::shared_ptr<EGE::Window> getWindow();

        protected:
            bool _running;                                  /**< A boolean that indicates whether the application is running. */
            net::TcpClient *_client;                        /**< The TCP client used for communication. */
            std::shared_ptr<EGE::Window> _window;           /**< The window used for rendering the graphical user interface. */
            std::shared_ptr<EGE::Camera> _camera;           /**< The camera used for rendering the entities. */
            float _deltaTime;                               /**< The time between frames. */
            std::shared_ptr<UserInterface> _interface;      /**< The Interface which displays information about the world. */
            std::string _ip;                                /**< The IP address of the server. */
            int _port;                                      /**< The port number of the server. */
    };
}

#endif /* !MAINMENU_HPP_ */
