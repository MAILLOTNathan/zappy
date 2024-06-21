/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** EndWin
*/

#ifndef ENDWIN_HPP_
#define ENDWIN_HPP_

#include "Camera.hpp"
#include "Error.hpp"
#include "Window.hpp"

#include "Gui.hpp"

namespace Onyx {
    class EndWin {
        public:
            EndWin(const std::string &teamName);
            ~EndWin();

            void update();

            void loop();

            bool isRunning() const;

            void createMainPanel(const std::string &teamName);

            std::shared_ptr<EGE::Window> getWindow();

        protected:
            bool _running;                                  /**< A boolean that indicates whether the application is running. */
            std::shared_ptr<EGE::Window> _window;           /**< The window used for rendering the graphical user interface. */
            std::shared_ptr<EGE::Camera> _camera;           /**< The camera used for rendering the entities. */
            float _deltaTime;                               /**< The time between frames. */
            std::shared_ptr<Onyx::UserInterface> _interface;      /**< The Interface which displays information about the world. */
    };
}

#endif /* !ENDWIN_HPP_ */
