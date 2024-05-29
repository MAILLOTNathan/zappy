/*
** EPITECH PROJECT, 2024
** gui
** File description:
** Gui
*/

#include "Gui.hpp"
#include "GL/gl.h"

Onyx::Gui::Gui()
{
    this->_window = std::make_shared<EGE::Window>("Onyx", EGE::Maths::Vector2<int>(1920, 1080), EGE::Window::Styles::Close & EGE::Window::Styles::Titlebar);
    this->_window->create();
    glEnable(GL_DEPTH_TEST);
    // check what is cull face and do the GL_DEPTH_TEST in the game engine ENCAPSULATION
    this->_shader = std::make_shared<EGE::Shader>("./assets/shaders/vertex.vert", "./assets/shaders/fragment.frag");
    this->_bindEvents();
    this->_entities.push_back(std::make_shared<Onyx::Map>(EGE::Maths::Vector2<int>(10, 10)));
    this->_camera = std::make_shared<EGE::Camera>(EGE::Maths::Vector3<float>(10.0f, 3.0f, 10.0f), EGE::Maths::Vector3<float>(0.0f, 1.0f, 0.0f), -135.0f, 0.0f);
}

Onyx::Gui::~Gui()
{
    this->_window->close();
}

void Onyx::Gui::update(bool& running)
{
    this->_window->pollEvents();
    this->_shader->use();
    this->_camera->update(*this->_shader.get(), static_cast<float>(this->_window->getSize().x) / static_cast<float>(this->_window->getSize().y));
    this->_window->clear(EGE::Color(0.0f, 1.0f, 0.0f, 1.0f));
    for (const auto& entity : this->_entities) {
        entity->update(this->_shader);
    }
    this->_window->display();
    if (!this->_window->isOpen())
        running = false;
}

void Onyx::Gui::_bindEvents()
{
    this->_window->bindWindowTrigger<GLFWwindow *>(EGE::Event::WindowTrigger::WindowClose, [this] (GLFWwindow *win) {
        this->_window->close();
    });
    // this->_window->bindWindowTrigger<GLFWwindow *, double, double>(EGE::Event::WindowTrigger::WindowCursorMoved, [this] (GLFWwindow *win, double xpos, double ypos) {
    //     this->_camera->rotate(xpos, ypos, true);
    // });
}