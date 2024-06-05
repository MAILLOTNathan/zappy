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

    EGE::Menu *menu = new EGE::Menu("Settings");

    menu->add(new EGE::Item("World", [this] () {
        if (this->_interface->_panels["World settings"])
            return this->_interface->_panels["World settings"]->setVisible(true);
        EGE::Panel *panel = new EGE::Panel("World settings");
        EGE::Slider *frequency = new EGE::Slider("Frequency", 0, 10000);
        EGE::Button *apply = new EGE::Button("Apply", [this] () {
            this->_interface->_panels["World settings"]->setVisible(false);
        });

        panel->add(frequency, "0 Frequency");
        panel->add(apply, "1 Apply");
        this->_interface->_panels["World settings"] = panel;
    }), "0 World");
    menu->add(new EGE::Item("Camera", [this] () {
        if (this->_interface->_panels["Camera settings"])
            return this->_interface->_panels["Camera settings"]->setVisible(true);
        EGE::Panel *panel = new EGE::Panel("Camera settings");
        EGE::Slider *sensivity = new EGE::Slider("Sensivity", 1, 100);
        EGE::CheckBox *cinematicMode = new EGE::CheckBox("Cinematic mode");
        EGE::Button *apply = new EGE::Button("Apply", [this] () {
            this->_interface->_panels["Camera settings"]->setVisible(false);
        });

        panel->add(sensivity, "0 Sensivity");
        panel->add(cinematicMode, "1 Cinematic mode");
        panel->add(apply, "2 Apply");
        this->_interface->_panels["Camera settings"] = panel;
    }), "1 Camera");
    menu->add(new EGE::Item("Disconnect", [this] () {
        std::cout << "DISCONNECT" << std::endl;
    }), "2 Disconnect");
    menu->add(new EGE::Item("Quit", [this] () {
        std::cout << "quit" << std::endl;
    }), "3 Quit");

    this->_interface->_menuBar->add(menu, "Settings");

    this->_tileSelected = 0;
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

// void Onyx::Gui::createPlayerPanel()
// {
//     EGE::Panel *panel = new EGE::Panel("Trantorian");
//     EGE::ListBox *dimensions = new EGE::ListBox("Dimensions");

//     EGE::Maths::Vector2<int> size = this->_map->getSize();
//     dimensions->add(new EGE::Text("Width: " + std::to_string(size.x)), "width");
//     dimensions->add(new EGE::Text("Height: " + std::to_string(size.y)), "height");

//     panel->add(dimensions, "dimensions");

//     EGE::ListBox *content = new EGE::ListBox("Content");
//     std::map<std::string, int> items = {};

//     items["Food"] = 0;
//     items["Linemate"] = 0;
//     items["Deraumere"] = 0;
//     items["Sibur"] = 0;
//     items["Mendiane"] = 0;
//     items["Phiras"] = 0;
//     items["Thystame"] = 0;

//     for (auto &floor : this->_map->getFloor()) {
//         items["Food"] += floor->getQuantity(Onyx::Item::TYPE::FOOD);
//         items["Linemate"] += floor->getQuantity(Onyx::Item::TYPE::LINEMATE);
//         items["Deraumere"] += floor->getQuantity(Onyx::Item::TYPE::DERAUMERE);
//         items["Sibur"] += floor->getQuantity(Onyx::Item::TYPE::SIBUR);
//         items["Mendiane"] += floor->getQuantity(Onyx::Item::TYPE::MENDIANE);
//         items["Phiras"] += floor->getQuantity(Onyx::Item::TYPE::PHIRAS);
//         items["Thystame"] += floor->getQuantity(Onyx::Item::TYPE::THYSTAME);
//     }
//     content->add(new EGE::Text("Food: " + std::to_string(items["Food"])), "food");
//     content->add(new EGE::Text("Linemate: " + std::to_string(items["Linemate"])), "linemate");
//     content->add(new EGE::Text("Deraumere: " + std::to_string(items["Deraumere"])), "deraumere");
//     content->add(new EGE::Text("Sibur: " + std::to_string(items["Sibur"])), "sibur");
//     content->add(new EGE::Text("Mendiane: " + std::to_string(items["Mendiane"])), "mendiane");
//     content->add(new EGE::Text("Phiras: " + std::to_string(items["Phiras"])), "phiras");
//     content->add(new EGE::Text("Thystame: " + std::to_string(items["Thystame"])), "thystame");

//     panel->add(content, "content");
//     this->_interface->_panels["Trantorian"] = panel;
// }

void Onyx::Gui::createTilePanel()
{
    EGE::Panel *panel = new EGE::Panel("Tile");
    EGE::ListBox *content = new EGE::ListBox("Content");

    Onyx::Floor *floor = this->_map->getFloor().at(this->_tileSelected).get();
    content->add(new EGE::Text("Food: " + std::to_string(floor->getQuantity(Onyx::Item::FOOD))), "food");
    content->add(new EGE::Text("Linemate: " + std::to_string(floor->getQuantity(Onyx::Item::LINEMATE))), "linemate");
    content->add(new EGE::Text("Deraumere: " + std::to_string(floor->getQuantity(Onyx::Item::DERAUMERE))), "deraumere");
    content->add(new EGE::Text("Sibur: " + std::to_string(floor->getQuantity(Onyx::Item::SIBUR))), "sibur");
    content->add(new EGE::Text("Mendiane: " + std::to_string(floor->getQuantity(Onyx::Item::MENDIANE))), "mendiane");
    content->add(new EGE::Text("Phiras: " + std::to_string(floor->getQuantity(Onyx::Item::PHIRAS))), "phiras");
    content->add(new EGE::Text("Thystame: " + std::to_string(floor->getQuantity(Onyx::Item::THYSTAME))), "thystame");

    panel->add(content, "Content");

    this->_interface->_panels["Content"] = panel;
}

void Onyx::Gui::updateTilePanel()
{
    EGE::ListBox *content = dynamic_cast<EGE::ListBox *>(this->_interface->_panels["Content"]->get("Content"));
    Onyx::Floor *floor = this->_map->getFloor().at(this->_tileSelected).get();

    content->get("food")->setName("Food: " + std::to_string(floor->getQuantity(Onyx::Item::FOOD)));
    content->get("linemate")->setName("Linemate: " + std::to_string(floor->getQuantity(Onyx::Item::LINEMATE)));
    content->get("deraumere")->setName("Deraumere: " + std::to_string(floor->getQuantity(Onyx::Item::DERAUMERE)));
    content->get("sibur")->setName("Sibur: " + std::to_string(floor->getQuantity(Onyx::Item::SIBUR)));
    content->get("mendiane")->setName("Mendiane: " + std::to_string(floor->getQuantity(Onyx::Item::MENDIANE)));
    content->get("phiras")->setName("Phiras: " + std::to_string(floor->getQuantity(Onyx::Item::PHIRAS)));
    content->get("thystame")->setName("Thystame: " + std::to_string(floor->getQuantity(Onyx::Item::THYSTAME)));
}
