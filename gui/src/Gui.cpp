/*
** EPITECH PROJECT, 2024
** gui
** File description:
** Gui
*/

#include "Gui.hpp"

Onyx::Gui::Gui()
{
    this->_window = std::make_shared<EGE::Window>("Onyx", EGE::Maths::Vector2<int>(1920, 1080), EGE::Window::Styles::Close & EGE::Window::Styles::Titlebar);
    this->_window->create();
    this->_bindEvents();
}

Onyx::Gui::~Gui()
{
}

void Onyx::Gui::update(bool& running)
{
    this->_window->pollEvents();
    this->_window->clear();
    this->_window->display();
    if (!this->_window->isOpen())
        running = false;
}

void Onyx::Gui::_bindEvents()
{
    this->_window->bindWindowTrigger<GLFWwindow *>(EGE::Event::WindowTrigger::WindowClose, [this] (GLFWwindow *win) {
        this->_window->close();
    });
}