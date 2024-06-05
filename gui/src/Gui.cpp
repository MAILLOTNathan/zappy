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
    this->_camera = std::make_shared<EGE::Camera>(EGE::Maths::Vector3<float>(7.0f, 3.0f, 7.0f), EGE::Maths::Vector3<float>(0.0f, 1.0f, 0.0f), -135.0f, 0.0f);
    this->_camera->setSpeed(10.0f);
    this->_deltaTime = 0.0f;
    this->_interface = std::make_shared<UserInterface>();

    this->_interface->init(this->_window.get());

    this->_interface->_menuBar->add(new EGE::Menu("File"), "file");
    this->_interface->_menuBar->add(new EGE::Menu("Edit"), "edit");
    this->_interface->_menuBar->add(new EGE::Menu("View"), "view");
    this->_interface->_menuBar->add(new EGE::Menu("Help"), "help");
}

Onyx::Gui::~Gui()
{
    this->_window->close();
}

void Onyx::Gui::createMap(int width, int height)
{
    this->_map = std::make_shared<Onyx::Map>(EGE::Maths::Vector2(width, height));
    this->_entities.push_back(this->_map);
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
    this->_interface->clear();
    this->_interface->draw();
    for (const auto& entity : this->_entities) {
        entity->update(this->_shader);
    }
    this->_interface->display();
    this->_window->display();
    if (!this->_window->isOpen())
        running = false;
}

std::shared_ptr<Onyx::Map> Onyx::Gui::getMap()
{
    return this->_map;
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

std::shared_ptr<EGE::Window> Onyx::Gui::getWindow() const
{
    return this->_window;
}

void Onyx::Gui::createWorldPanel()
{
    EGE::Panel *panel = new EGE::Panel("Amber World");
    EGE::ListBox *dimensions = new EGE::ListBox("Dimensions");

    EGE::Maths::Vector2<int> size = this->_map->getSize();
    dimensions->add(new EGE::Text("Width: " + std::to_string(size.x)), "width");
    dimensions->add(new EGE::Text("Height: " + std::to_string(size.y)), "height");

    panel->add(dimensions, "dimensions");

    EGE::ListBox *content = new EGE::ListBox("Content");
    std::map<std::string, int> items = {};

    items["Food"] = 0;
    items["Linemate"] = 0;
    items["Deraumere"] = 0;
    items["Sibur"] = 0;
    items["Mendiane"] = 0;
    items["Phiras"] = 0;
    items["Thystame"] = 0;

    for (auto &floor : this->_map->getFloor()) {
        items["Food"] += floor->getQuantity(Onyx::Item::TYPE::FOOD);
        items["Linemate"] += floor->getQuantity(Onyx::Item::TYPE::LINEMATE);
        items["Deraumere"] += floor->getQuantity(Onyx::Item::TYPE::DERAUMERE);
        items["Sibur"] += floor->getQuantity(Onyx::Item::TYPE::SIBUR);
        items["Mendiane"] += floor->getQuantity(Onyx::Item::TYPE::MENDIANE);
        items["Phiras"] += floor->getQuantity(Onyx::Item::TYPE::PHIRAS);
        items["Thystame"] += floor->getQuantity(Onyx::Item::TYPE::THYSTAME);
    }
    content->add(new EGE::Text("Food: " + std::to_string(items["Food"])), "food");
    content->add(new EGE::Text("Linemate: " + std::to_string(items["Linemate"])), "linemate");
    content->add(new EGE::Text("Deraumere: " + std::to_string(items["Deraumere"])), "deraumere");
    content->add(new EGE::Text("Sibur: " + std::to_string(items["Sibur"])), "sibur");
    content->add(new EGE::Text("Mendiane: " + std::to_string(items["Mendiane"])), "mendiane");
    content->add(new EGE::Text("Phiras: " + std::to_string(items["Phiras"])), "phiras");
    content->add(new EGE::Text("Thystame: " + std::to_string(items["Thystame"])), "thystame");

    panel->add(content, "content");

    EGE::ListBox *Teams = new EGE::ListBox("Teams");
    //send request to serveur for the teams names
    Teams->add(new EGE::Text("Team 1"));
    Teams->add(new EGE::Text("Team 2"));

    panel->add(Teams, "teams");

    this->_interface->_panels["Amber World"] = panel;
}

void Onyx::Gui::updateWorldPanel()
{
    EGE::ListBox *dimensions = dynamic_cast<EGE::ListBox *>(this->_interface->_panels["Amber World"]->get("dimensions"));
    EGE::ListBox *content = dynamic_cast<EGE::ListBox *>(this->_interface->_panels["Amber World"]->get("content"));
    EGE::Maths::Vector2<int> size = this->_map->getSize();
    std::map<std::string, int> items = {};

    items["Food"] = 0;
    items["Linemate"] = 0;
    items["Deraumere"] = 0;
    items["Sibur"] = 0;
    items["Mendiane"] = 0;
    items["Phiras"] = 0;
    items["Thystame"] = 0;

    for (auto &floor : this->_map->getFloor()) {
        items["Food"] += floor->getQuantity(Onyx::Item::TYPE::FOOD);
        items["Linemate"] += floor->getQuantity(Onyx::Item::TYPE::LINEMATE);
        items["Deraumere"] += floor->getQuantity(Onyx::Item::TYPE::DERAUMERE);
        items["Sibur"] += floor->getQuantity(Onyx::Item::TYPE::SIBUR);
        items["Mendiane"] += floor->getQuantity(Onyx::Item::TYPE::MENDIANE);
        items["Phiras"] += floor->getQuantity(Onyx::Item::TYPE::PHIRAS);
        items["Thystame"] += floor->getQuantity(Onyx::Item::TYPE::THYSTAME);
    }

    dimensions->get("width")->setName("Width: " + std::to_string(size.x));
    dimensions->get("height")->setName("Height: " + std::to_string(size.y));
    content->get("food")->setName("Food: " + std::to_string(items["Food"]));
    content->get("linemate")->setName("Linemate: " + std::to_string(items["Linemate"]));
    content->get("deraumere")->setName("Deraumere: " + std::to_string(items["Deraumere"]));
    content->get("sibur")->setName("Sibur: " + std::to_string(items["Sibur"]));
    content->get("mendiane")->setName("Mendiane: " + std::to_string(items["Mendiane"]));
    content->get("phiras")->setName("Phiras: " + std::to_string(items["Phiras"]));
    content->get("thystame")->setName("Thystame: " + std::to_string(items["Thystame"]));
}

EGE::Panel *Onyx::Gui::createPLayerPanel()
{
    EGE::Panel *panel = new EGE::Panel("Trantorian");
    EGE::ListBox *player = new EGE::ListBox("Player");
    EGE::ListBox *inventory = new EGE::ListBox("Inventory");


    player->add(new EGE::Text("ID: 1"));
    player->add(new EGE::Text("Level: 1"));
    player->add(new EGE::Text("Position"));
    player->add(new EGE::Text("X: 0"));
    player->add(new EGE::Text("Y: 0"));
    player->add(new EGE::Text("Direction: Nord"));


    std::map<std::string, int> items = {};

    items["Food"] = 0;
    items["Linemate"] = 0;
    items["Deraumere"] = 0;
    items["Sibur"] = 0;
    items["Mendiane"] = 0;
    items["Phiras"] = 0;
    items["Thystame"] = 0;
}

// EGE::Panel *Onyx::Gui::createPlayerPanel()
// {
    // EGE::Panel *panel = new EGE::Panel("Trantorian");

    // client.addCommand("plv", net::type_command_t::PLV, [&panel](std::vector<std::string>& args) {
    //     if (args.size() != 3)
    //         throw EGE::Error("Wrong number of param.");
    //     panel->add(new EGE::Text("ID: " + args[1]));
    //     panel->add(new EGE::Text("Level: " + args[2]));
    // });
    // client.addCommand("ppo", net::type_command_t::PPO, [&panel](std::vector<std::string>& args) {
    //     if (args.size() != 4)
    //         throw EGE::Error("Wrong number of param.");
    //     EGE::ListBox *listBox = new EGE::ListBox("Position");
    //     listBox->add(new EGE::Text("X: " + args[2]));
    //     listBox->add(new EGE::Text("Y: " + args[3]));
    //     if (args[4] == "1")
    //         listBox->add(new EGE::Text("Direction: Nord"));
    //     else if (args[4] == "2")
    //         listBox->add(new EGE::Text("Direction: East"));
    //     else if (args[4] == "3")
    //         listBox->add(new EGE::Text("Direction: South"));
    //     else
    //         listBox->add(new EGE::Text("Direction: West"));
    //     panel->add(listBox);
    // });
    // client.addCommand("pin", net::type_command_t::PIN, [&panel](std::vector<std::string>& args) {
    //     if (args.size() != 11)
    //         throw EGE::Error("Wrong number of param.");
    //     EGE::ListBox *listBox = new EGE::ListBox("Inventory");
    //     listBox->add(new EGE::Text("Food: " + args[4]));
    //     listBox->add(new EGE::Text("Linemate: " + args[5]));
    //     listBox->add(new EGE::Text("Deraumere: " + args[6]));
    //     listBox->add(new EGE::Text("Sibur: " + args[7]));
    //     listBox->add(new EGE::Text("Mendiane: " + args[8]));
    //     listBox->add(new EGE::Text("Phiras: " + args[9]));
    //     listBox->add(new EGE::Text("Thystame: " + args[10]));
    //     panel->add(listBox);
    // });
    // return panel;
// }
