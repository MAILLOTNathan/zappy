/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** EndWin
*/

#include "EndWin.hpp"

Onyx::EndWin::EndWin(const std::string &teamName)
{
    this->_window = std::make_shared<EGE::Window>("Onyx", EGE::Maths::Vector2<int>(1920, 1080), EGE::Window::Styles::Close & EGE::Window::Styles::Titlebar);
    this->_window->create();
    this->_camera = std::make_shared<EGE::Camera>(EGE::Maths::Vector3<float>(7.0f, 3.0f, 7.0f), EGE::Maths::Vector3<float>(0.0f, 1.0f, 0.0f), -135.0f, 0.0f);
    this->_deltaTime = 0.0f;
    this->_interface = std::make_shared<Onyx::UserInterface>();
    this->_window->bindWindowTrigger<GLFWwindow *>(EGE::Event::WindowTrigger::WindowClose, [this] (GLFWwindow *win) {
        std::exit(0);
    });
    this->_window->bindTrigger(EGE::Event::Trigger(EGE::Event::Keyboard, EGE::Event::Key::KeyEscape, EGE::Event::Mode::JustPressed, [this]() {
        std::exit(0);
    }));

    this->createMainPanel(teamName);
    this->_interface->init(this->_window.get());
    this->_interface->defaultMode();
}

Onyx::EndWin::~EndWin()
{
}

void Onyx::EndWin::createMainPanel(const std::string &teamName)
{
    EGE::Panel *panel = new EGE::Panel("End of Game");
    EGE::Text *text = new EGE::Text("The game is over, the winner team is: " + teamName);
    EGE::Button *button = new EGE::Button("Okay !", [this](){
        this->_window->close();
    });

    panel->add(text, "0 End of Game");
    panel->add(button, "1 Okay");
    this->_interface->_panels["End of Game"] = panel;
}

void Onyx::EndWin::update()
{
    static float lastFrame = 0.0f;
    static float timer = 0.0f;

    this->_deltaTime = glfwGetTime() - lastFrame;
    lastFrame = glfwGetTime();
    timer += this->_deltaTime;
    this->_window->pollEvents();
    this->_window->clear(EGE::Color(0.0f, 0.0f, 0.0f, 1.0f));
    this->_interface->clear();
    this->_interface->draw();
    this->_interface->display();
    this->_window->display();
    if (!this->_window->isOpen())
        this->_running = false;
}

bool Onyx::EndWin::isRunning() const
{
    return this->_running;
}

void Onyx::EndWin::loop()
{
    this->_running = true;
    while (this->_running) {
        this->update();
    }
}

std::shared_ptr<EGE::Window> Onyx::EndWin::getWindow()
{
    return this->_window;
}
