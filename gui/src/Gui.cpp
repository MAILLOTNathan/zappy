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
    this->_shader = std::make_shared<EGE::Shader>("./assets/shaders/vertex.vert", "./assets/shaders/fragment.frag");
    this->_bindEvents();
    this->_map = std::make_shared<Onyx::Map>(EGE::Maths::Vector2<int>(10, 10));
    this->_entities.push_back(this->_map);
    this->_camera = std::make_shared<EGE::Camera>(EGE::Maths::Vector3<float>(7.0f, 3.0f, 7.0f), EGE::Maths::Vector3<float>(0.0f, 1.0f, 0.0f), -135.0f, 0.0f);
    this->_camera->setSpeed(10.0f);
    this->_deltaTime = 0.0f;
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            this->_map->addItem(EGE::Maths::Vector2<int>(i, j), Onyx::Item::TYPE::FOOD);
        }
    }
}

Onyx::Gui::~Gui()
{
    this->_window->close();
}

void Onyx::Gui::update(bool& running)
{
    static float lastFrame = 0.0f;
    static float timer = 0.0f;
    this->_deltaTime = glfwGetTime() - lastFrame;
    lastFrame = glfwGetTime();
    timer += this->_deltaTime;
    if (timer >= 1.0f) {
        std::cout << "FPS: " << 1 / this->_deltaTime << "\n";
        timer = 0.0f;
    }
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
    this->_window->bindWindowTrigger<GLFWwindow *, double, double>(EGE::Event::WindowTrigger::WindowCursorMoved, [this] (GLFWwindow *win, double xpos, double ypos) {
        static double lastX = 0.0;
        static double lastY = 0.0;
        static bool firstMouse = true;
        if (firstMouse) {
            lastX = xpos;
            lastY = ypos;
            firstMouse = false;
        }
        double xoffset = xpos - lastX;
        double yoffset = lastY - ypos;
        lastX = xpos;
        lastY = ypos;
        this->_camera->rotate(xoffset, yoffset, true);
    });
    this->_window->bindTrigger(EGE::Event::Trigger(EGE::Event::Keyboard, EGE::Event::Key::KeyW, EGE::Event::Mode::Pressed, [this]() {
        this->_camera->move(EGE::Camera::Movement::FORWARD, this->_deltaTime);
    }));
    this->_window->bindTrigger(EGE::Event::Trigger(EGE::Event::Keyboard, EGE::Event::Key::KeyS, EGE::Event::Mode::Pressed, [this]() {
        this->_camera->move(EGE::Camera::Movement::BACKWARD, this->_deltaTime);
    }));
    this->_window->bindTrigger(EGE::Event::Trigger(EGE::Event::Keyboard, EGE::Event::Key::KeyA, EGE::Event::Mode::Pressed, [this]() {
        this->_camera->move(EGE::Camera::Movement::LEFT, this->_deltaTime);
    }));
    this->_window->bindTrigger(EGE::Event::Trigger(EGE::Event::Keyboard, EGE::Event::Key::KeyD, EGE::Event::Mode::Pressed, [this]() {
        this->_camera->move(EGE::Camera::Movement::RIGHT, this->_deltaTime);
    }));
    this->_window->bindTrigger(EGE::Event::Trigger(EGE::Event::Keyboard, EGE::Event::Key::KeyQ, EGE::Event::Mode::Pressed, [this]() {
        this->_camera->move(EGE::Camera::Movement::DOWN, this->_deltaTime);
    }));
    this->_window->bindTrigger(EGE::Event::Trigger(EGE::Event::Keyboard, EGE::Event::Key::KeyE, EGE::Event::Mode::Pressed, [this]() {
        this->_camera->move(EGE::Camera::Movement::UP, this->_deltaTime);
    }));
    this->_window->bindTrigger(EGE::Event::Trigger(EGE::Event::Keyboard, EGE::Event::Key::KeyLShift, EGE::Event::Mode::JustPressed, [this]() {
        this->_camera->setSpeed(this->_camera->getSpeed() * 2);
    }));
    this->_window->bindTrigger(EGE::Event::Trigger(EGE::Event::Keyboard, EGE::Event::Key::KeyLShift, EGE::Event::Mode::JustReleased, [this]() {
        this->_camera->setSpeed(this->_camera->getSpeed() / 2);
    }));
    this->_window->bindTrigger(EGE::Event::Trigger(EGE::Event::Keyboard, EGE::Event::Key::KeyEscape, EGE::Event::Mode::JustPressed, [this]() {
        this->_window->close();
    }));
}