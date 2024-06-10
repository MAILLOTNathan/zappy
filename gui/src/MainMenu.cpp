/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** MainMenu
*/

#include "MainMenu.hpp"

Onyx::MainMenu::MainMenu()
{
    this->_window = std::make_shared<EGE::Window>("Onyx", EGE::Maths::Vector2<int>(1920, 1080), EGE::Window::Styles::Close & EGE::Window::Styles::Titlebar);
    this->_window->create();
    this->_camera = std::make_shared<EGE::Camera>(EGE::Maths::Vector3<float>(7.0f, 3.0f, 7.0f), EGE::Maths::Vector3<float>(0.0f, 1.0f, 0.0f), -135.0f, 0.0f);
    this->_deltaTime = 0.0f;
    this->_interface = std::make_shared<UserInterface>();
    this->_window->bindWindowTrigger<GLFWwindow *>(EGE::Event::WindowTrigger::WindowClose, [this] (GLFWwindow *win) {
        this->_window->close();
    });

    this->createMainPanel();
    this->_interface->init(this->_window.get());
}

Onyx::MainMenu::~MainMenu()
{
}

void Onyx::MainMenu::createMainPanel()
{
    EGE::Panel *panel = new EGE::Panel("Amber");
    EGE::ListBox *listBox = new EGE::ListBox("Server");

    EGE::String *address = new EGE::String("Address");
    EGE::Number *port = new EGE::Number("Port");

    address->setContent("127.0.0.1");
    port->setValue(4242);

    listBox->add(address, "0 Address");
    listBox->add(port, "1 Port");

    panel->add(listBox, "0 Server");

    EGE::Button *button = new EGE::Button("Launch simulation", [this, address, port](){
        this->_client = new net::TcpClient(address->getContent(), port->getValue());
        this->_window->close();
    });

    panel->add(button, "1 Launch");
    this->_interface->_panels["Main"] = panel;
}

void Onyx::MainMenu::update()
{
    static float lastFrame = 0.0f;
    static float timer = 0.0f;

    this->_deltaTime = glfwGetTime() - lastFrame;
    lastFrame = glfwGetTime();
    timer += this->_deltaTime;
    this->_window->pollEvents();
    this->_window->clear(EGE::Color(0.0f, 1.0f, 0.0f, 1.0f));
    this->_interface->clear();
    this->_interface->draw();
    this->_interface->display();
    this->_window->display();
    if (!this->_window->isOpen())
        this->_running = false;
}

bool Onyx::MainMenu::isRunning() const
{
    return this->_running;
}

net::TcpClient *Onyx::MainMenu::getClient() const
{
    return this->_client;
}

void Onyx::MainMenu::loop()
{
    this->_running = true;
    while (this->_running) {
        this->update();
    }
}
