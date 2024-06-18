/*
** EPITECH PROJECT, 2024
** gui
** File description:
** Gui
*/

#include "Gui.hpp"

float speed = 4.0f;

Onyx::Gui::Gui(net::TcpClient client)
{
    this->_window = std::make_shared<EGE::Window>("Onyx", EGE::Maths::Vector2<int>(1920, 1080), EGE::Window::Styles::Close & EGE::Window::Styles::Titlebar);
    this->_window->create();
    this->_shader = std::make_shared<EGE::Shader>("./assets/shaders/vertex.vert", "./assets/shaders/fragment.frag");
    this->_bindEvents();
    this->_camera = std::make_shared<EGE::Camera>(EGE::Maths::Vector3<float>(7.0f, 3.0f, 7.0f), EGE::Maths::Vector3<float>(0.0f, 1.0f, 0.0f), -135.0f, 0.0f);
    this->_camera->setSpeed(10.0f);
    this->_deltaTime = 0.0f;
    this->_timeUnit = 1.0f;
    this->_interface = std::make_shared<UserInterface>();

    this->_interface->initPlaylist("./assets/musics/");

    this->_cameraMode = true;
    this->createMenuBar();
    this->createTutorial();

    this->_interface->init(this->_window.get());
    this->_interface->defaultMode();
    this->_tileSelected = 0;
    this->_client = &client;
    this->_teams = {};
    this->_animator = Onyx::Animator();
    this->_map = std::make_shared<Onyx::Map>();
    this->_entities.push_back(this->_map);
}

Onyx::Gui::~Gui()
{
}

void Onyx::Gui::createMap(int width, int height)
{
    this->_map->createMap(EGE::Maths::Vector2<int>(width, height));
}

void Onyx::Gui::addPlayer(int id, EGE::Maths::Vector2<int> position, std::string teamName, const std::string& rotation, int level, float timeUnit)
{
    this->_players.push_back(std::make_shared<Onyx::Player>(id, teamName, position, rotation, level, timeUnit));
}

void Onyx::Gui::update()
{
    static float lastFrame = 0.0f;
    static float timer = 0.0f;
    double currentTime = glfwGetTime();
    this->_deltaTime = currentTime - lastFrame;
    lastFrame = currentTime;
    timer += this->_deltaTime;
    if (timer >= 1.0f) {
        std::cout << "FPS: " << 1 / this->_deltaTime << "\n";
        timer = 0.0f;
    }
    this->_window->pollEvents();
    this->_shader->use();
    this->_camera->update(*this->_shader.get(), static_cast<float>(this->_window->getSize().x) / static_cast<float>(this->_window->getSize().y));
    this->_window->clear(EGE::Color(0.0f, 0.0f, 0.0f, 1.0f));
    this->_interface->clear();
    if (this->_interface->_panels["Amber World"])
        this->_interface->draw();
    for (const auto& entity : this->_entities) {
        entity->update(this->_shader);
    }
    if (this->_timeUnit < 100.0f)
        this->_animator.update(this->_deltaTime);
    for (auto& player : this->_players) {
        player->update(this->_shader);
        this->updatePlayerPanel(player);
    }
    this->_interface->display();
    this->_window->display();
    if (!this->_window->isOpen())
        this->_running = false;
    this->_client->sendRequest("mct\n");
}

bool Onyx::Gui::isRunning() const
{
    return this->_window->isOpen();
}

void Onyx::Gui::loop()
{
    this->_client->addCommand("msz", net::type_command_t::MSZ, [this](std::vector<std::string>& args) {
        if (args.size() != 3)
            throw EGE::Error("[MSZ] Wrong number of param.");
        int x, y;
        try {
            x = std::stoi(args[1]);
        } catch (const std::exception& e) {
            std::cout << "[MSZ] Invalid x size : |" << args[1] << "|" <<  std::endl;
        }
        try {
            y = std::stoi(args[2]);
        } catch (const std::exception& e) {
            std::cout << "[MSZ] Invalid y size : |" << args[1] << "|" <<  std::endl;
        }
        this->createMap(std::stoi(args[1]), std::stoi(args[2]));
        this->createWorldPanel();
        this->createTilePanel();
        this->createPlayerPanel();
        this->createConsolePanel();
        this->updateConsolePanel(args);
    });

    this->_client->addCommand("bct", net::type_command_t::MCT, [this](std::vector<std::string>& args) {
        if (args.size() != 10)
            throw EGE::Error("[BCT] Wrong number of param.");
        int x, y;
        try {
            x = std::stoi(args[1]);
        } catch (const std::exception& e) {
            std::cout << "[BCT] Invalid x position : |" << args[1] << "|" <<  std::endl;
        }
        try {
            y = std::stoi(args[2]);
        } catch (const std::exception& e) {
            std::cout << "[BCT] Invalid y position : |" << args[1] << "|" <<  std::endl;
        }
        EGE::Maths::Vector2<int> position(x, y);
        this->_map->addItem(position, Onyx::Item::TYPE::FOOD, std::stoi(args[3]));
        this->_map->addItem(position, Onyx::Item::TYPE::LINEMATE, std::stoi(args[4]));
        this->_map->addItem(position, Onyx::Item::TYPE::DERAUMERE, std::stoi(args[5]));
        this->_map->addItem(position, Onyx::Item::TYPE::SIBUR, std::stoi(args[6]));
        this->_map->addItem(position, Onyx::Item::TYPE::MENDIANE, std::stoi(args[7]));
        this->_map->addItem(position, Onyx::Item::TYPE::PHIRAS, std::stoi(args[8]));
        this->_map->addItem(position, Onyx::Item::TYPE::THYSTAME, std::stoi(args[9]));
        this->updateWorldPanel();
        this->updateTilePanel();
        this->updateConsolePanel(args);
    });

    this->_client->addCommand("tna", net::type_command_t::TNA, [this](std::vector<std::string>& args) {
        if (args.size() != 2)
            throw EGE::Error("[TNA] Wrong number of param.");
        args.erase(args.begin());
        for (auto &teams: args) {
            this->_teams.push_back(teams);
        }
        this->updateWorldPanel();
    });

    this->_client->addCommand("pnw", net::type_command_t::PNW, [this](std::vector<std::string>& args) {
        if (args.size() != 7)
            throw EGE::Error("[PNW] Wrong number of param.");
        // 1: player id (need to remove the #)
        // 2: x pos
        // 3: y pos
        // 4: orientation (1: N, 2: E, 3: S, 4: W)
        // 5: level
        // 6: team name
        int id, x, y, level;
        try {
            id = std::stoi(args[1].erase(0, 1));
        } catch (std::exception &e) {
            throw EGE::Error("[PNW] Invalid id received : |" + args[1] + "|.");
        }
        try {
            x = std::stoi(args[2]);
        } catch (std::exception &e) {
            throw EGE::Error("[PNW] Invalid x position received : |" + args[2] + "|.");
        }
        try {
            y = std::stoi(args[3]);
        } catch (std::exception &e) {
            throw EGE::Error("[PNW] Invalid y position received : |" + args[3] + "|.");
        }
        try {
            level = std::stoi(args[5]);
        } catch (std::exception &e) {
            throw EGE::Error("[PNW] Invalid level received : |" + args[5] + "|.");
        }

        this->addPlayer(id, EGE::Maths::Vector2<int>(x, y), args[6], args[4], level, this->_timeUnit);
        for (auto &player : this->_players) {
            this->_client->sendRequest("pin #" + std::to_string(player->getId()) + "\n");
        }
        this->updateWorldPanel();
    });

    this->_client->addCommand("ppo", net::type_command_t::PPO, [this](std::vector<std::string>& args) {
        if (args.size() != 5)
            throw EGE::Error("[PPO] Wrong number of param.");
        int id, x, y;
        std::string rotation = args[4];
        EGE::Maths::Vector2<int> pos;
        try {
            id = std::stoi(args[1].substr(1));
        } catch (std::exception &e) {
            throw EGE::Error("[PPO] Invalid id : |" + args[1] + "|.");
        }
        try {
            x = std::stoi(args[2]);
        } catch (std::exception &e) {
            throw EGE::Error("[PPO] Invalid x position : |" + args[2] + "|.");
        }
        try {
            y = std::stoi(args[3]);
        } catch (std::exception &e) {
            throw EGE::Error("[PPO] Invalid y position : |" + args[3] + "|.");
        }
        if (rotation != "N" && rotation != "E" && rotation != "S" && rotation != "W")
            throw EGE::Error("[PPO] Invalid rotation : |" + rotation + "|.");
        for (auto& player : this->_players) {
            if (player->getId() == id) {
                if (this->_timeUnit < 100.0f) {
                    pos = player->getPos();
                    player->setPos(pos);
                    Onyx::Player::Animation animation = Onyx::Player::Animation::NONE;
                    if (pos.x != x || pos.y != y) {
                        std::string rstring = player->getRotationString();
                        if (rstring == "N") {
                            animation = Onyx::Player::Animation::FORWARD_NORTH;
                        } else if (rstring == "E") {
                            animation = Onyx::Player::Animation::FORWARD_EAST;
                        } else if (rstring == "S") {
                            animation = Onyx::Player::Animation::FORWARD_SOUTH;
                        } else if (rstring == "W") {
                            animation = Onyx::Player::Animation::FORWARD_WEST;
                        }
                    } else if (rotation != player->getRotationString()) {
                        std::string rstring = player->getRotationString();
                        if (rstring == "N") {
                            if (rotation == "E") {
                                animation = Onyx::Player::Animation::RIGHT;
                            } else if (rotation == "W") {
                                animation = Onyx::Player::Animation::LEFT;
                            }
                        } else if (rstring == "E") {
                            if (rotation == "S") {
                                animation = Onyx::Player::Animation::RIGHT;
                            } else if (rotation == "N") {
                                animation = Onyx::Player::Animation::LEFT;
                            }
                        } else if (rstring == "S") {
                            if (rotation == "W") {
                                animation = Onyx::Player::Animation::RIGHT;
                            } else if (rotation == "E") {
                                animation = Onyx::Player::Animation::LEFT;
                            }
                        } else if (rstring == "W") {
                            if (rotation == "N") {
                                animation = Onyx::Player::Animation::RIGHT;
                            } else if (rotation == "S") {
                                animation = Onyx::Player::Animation::LEFT;
                            }
                        }
                    }
                    if (animation == Onyx::Player::Animation::NONE) {
                        player->setPos(EGE::Maths::Vector2<int>(x, y));
                        player->setRotationString(rotation);
                    }
                    this->_animator.startAnimation(player, animation, [&player, x, y, rotation]() {
                        player->setPos(EGE::Maths::Vector2<int>(x, y));
                        player->setRotationString(rotation);
                    });
                } else {
                    player->setPos(EGE::Maths::Vector2<int>(x, y));
                    player->setRotationString(rotation);
                }
            }
        }
    });

    this->_client->addCommand("plv", net::type_command_t::PLV, [this](std::vector<std::string>& args) {
        if (args.size() != 3)
            throw EGE::Error("[PLV] Wrong number of param.");
        int id = 0;
        int level = 0;
        try {
            id = std::stoi(args[1].substr(1));
        } catch (std::exception &e) {
            throw EGE::Error("[PLV] Invalid id received : |" + args[1] + "|.");
        }
        try {
            level = std::stoi(args[2]);
        } catch (std::exception &e) {
            throw EGE::Error("[PLV] Invalid level received : |" + args[2] + "|.");
        }
        for (auto &player : this->_players) {
            if (player->getId() == id) {
                std::cout << "set player " << id << " to level " << level << std::endl;
                player->setLevel(level);
                this->updatePlayerPanel(player);
            }
        }
    });

    this->_client->addCommand("pin", net::type_command_t::PIN, [this](std::vector<std::string>& args) {
        if (args.size() != 11)
            throw EGE::Error("[PIN] Wrong number of param.");
        int id = 0;
        try {
            id = std::stoi(args[1].substr(1));
        } catch (std::exception &e) {
            throw EGE::Error("[PIN] Invalid id received : |" + args[1] + "|.");
        }
        for (auto &player : this->_players) {
            if (player->getId() == id) {
                player->setInventory(std::stoi(args[4]), Onyx::Item::TYPE::FOOD);
                player->setInventory(std::stoi(args[5]), Onyx::Item::TYPE::LINEMATE);
                player->setInventory(std::stoi(args[6]), Onyx::Item::TYPE::DERAUMERE);
                player->setInventory(std::stoi(args[7]), Onyx::Item::TYPE::SIBUR);
                player->setInventory(std::stoi(args[8]), Onyx::Item::TYPE::MENDIANE);
                player->setInventory(std::stoi(args[9]), Onyx::Item::TYPE::PHIRAS);
                player->setInventory(std::stoi(args[10]), Onyx::Item::TYPE::THYSTAME);
            }
        }
        for (auto &player : this->_players) {
            if (player->getId() == id) {
                this->updatePlayerPanel(player);
            }
        }
    });

    this->_client->addCommand("pex", net::type_command_t::PEX, [this](std::vector<std::string>& args) {
        if (args.size() != 2)
            throw EGE::Error("[PEX] Wrong number of param.");
        int id = 0;
        try {
            id = std::stoi(args[1].substr(1));
        } catch (std::exception &e) {
            throw EGE::Error("[PEX] Invalid id received : |" + args[1] + "|.");
        }
    });

    this->_client->addCommand("pbc", net::type_command_t::PBC, [this](std::vector<std::string>& args) {
        if (args.size() != 2 && args.size() != 3)
            throw EGE::Error("[PBC] Wrong number of param.");
        int id = 0;
        try {
            id = std::stoi(args[1].substr(1));
        } catch (std::exception &e) {
            throw EGE::Error("[PBC] Invalid id received : |" + args[1] + "|.");
        }
    });

    this->_client->addCommand("pic", net::type_command_t::PIC, [this](std::vector<std::string>& args) {
        if (args.size() < 5)
            throw EGE::Error("[PIC] Wrong number of param.");
        int id = 0;
        try {
            id = std::stoi(args[1].substr(1));
        } catch (std::exception &e) {
            throw EGE::Error("[PIC] Invalid id received in : |" + args[1] + "|.");
        }
    });

    this->_client->addCommand("pie", net::type_command_t::PIE, [this](std::vector<std::string>& args) {
        if (args.size() != 4)
            throw EGE::Error("[PIE] Wrong number of param.");
        int id = 0;
        try {
            id = std::stoi(args[1].substr(1));
        } catch (std::exception &e) {
            throw EGE::Error("[PIE] Invalid id received : |" + args[1] + "|.");
        }
    });

    this->_client->addCommand("pfk", net::type_command_t::PFK, [this](std::vector<std::string>& args) {
        if (args.size() != 2)
            throw EGE::Error("[PFK] Wrong number of param.");
        int id = 0;
        try {
            id = std::stoi(args[1].substr(1));
        } catch (std::exception &e) {
            throw EGE::Error("[PFK] Invalid id received : |" + args[1] + "|.");
        }
        // do not manage this command
    });

    this->_client->addCommand("pdr", net::type_command_t::PDR, [this](std::vector<std::string>& args) {
        if (args.size() != 3)
            throw EGE::Error("[PDR] Wrong number of param.");
        int id = 0;
        try {
            id = std::stoi(args[1].substr(1));
        } catch (std::exception &e) {
            throw EGE::Error("[PDR] Invalid id received : |" + args[1] + "|.");
        }
    });

    this->_client->addCommand("pgt", net::type_command_t::PGT, [this](std::vector<std::string>& args) {
        if (args.size() != 3)
            throw EGE::Error("[PGT] Wrong number of param.");
        int id, i;
        try {
            id = std::stoi(args[1].substr(1));
        } catch (std::exception &e) {
            throw EGE::Error("[PGT] Invalid id received : |" + args[1] + "|.");
        }
        try {
            i = std::stoi(args[2]);
        } catch (std::exception &e) {
            throw EGE::Error("[PGT] Invalid item received : |" + args[2] + "|.");
        }
        EGE::Maths::Vector2<int> pos;
        for (auto &player : this->_players) {
            if (player->getId() == id) {
                pos = player->getPos();
                this->_map->removeItem(pos, static_cast<Onyx::Item::TYPE>(i));
                player->setInventory(1, Onyx::Item::TYPE::FOOD);
                this->updatePlayerPanel(player);
            }
        }
    });

    this->_client->addCommand("pdi", net::type_command_t::PDI, [this](std::vector<std::string>& args) {
        if (args.size() != 2)
            throw EGE::Error("[PDI] Wrong number of param.");
        int id = 0;
        try {
            id = std::stoi(args[1].substr(1));
        } catch (std::exception &e) {
            throw EGE::Error("[PDI] Invalid id received : |" + args[1] + "|.");
        }
        for (auto &player : this->_players) {
            if (player->getId() == id) {
                this->_players.erase(std::remove(this->_players.begin(), this->_players.end(), player), this->_players.end());
                break;
            }
        }
    });

    this->_client->addCommand("enw", net::type_command_t::ENW, [this](std::vector<std::string>& args) {
        if (args.size() != 5)
            throw EGE::Error("[ENW] Wrong number of param.");
        int eggId = 0;
        int id = 0;
        int x = 0;
        int y = 0;
        try {
            eggId = std::stoi(args[1].substr(1));
        } catch (std::exception &e) {
            throw EGE::Error("[ENW] Invalid egg id received : |" + args[1] + "|.");
        }
        try {
            id = std::stoi(args[2].substr(1));
        } catch (std::exception &e) {
            throw EGE::Error("[ENW] Invalid id received : |" + args[2] + "|.");
        }
        try {
            x = std::atoi(args[3].c_str());
        } catch (std::exception &e) {
            throw EGE::Error("[ENW] Invalid x position received : |" + args[3] + "|.");
        }
        try {
            y = std::atoi(args[4].c_str());
        } catch (std::exception &e) {
            throw EGE::Error("[ENW] Invalid y position received : |" + args[4] + "|.");
        }

        this->_map->addEgg(EGE::Maths::Vector3<int>(x, y, eggId));
    });

    this->_client->addCommand("ebo", net::type_command_t::EBO, [this](std::vector<std::string>& args) {
        if (args.size() != 2)
            throw EGE::Error("[EBO] Wrong number of param.");
        int eggId = 0;
        try {
            eggId = std::stoi(args[1].substr(1));
        } catch (std::exception &e) {
            throw EGE::Error("[EBO] Invalid egg id received : |" + args[1] + "|.");
        }
        std::vector<EGE::Maths::Vector3<int>>& eggPos = this->_map->getEggPos();
        std::erase_if(eggPos, [eggId](const EGE::Maths::Vector3<int>& pos) {
            return pos.z == eggId;
        });
    });

    this->_client->addCommand("edi" , net::type_command_t::EDI, [this](std::vector<std::string>& args) {
        if (args.size() != 2)
            throw EGE::Error("[EDI] Wrong number of param.");
        int eggId = 0;
        try {
            eggId = std::stoi(args[1].substr(1));
        } catch (std::exception &e) {
            throw EGE::Error("[EDI] Invalid egg id received : |" + args[1] + "|.");
        }
        std::vector<EGE::Maths::Vector3<int>>& eggPos = this->_map->getEggPos();
        std::erase_if(eggPos, [eggId](const EGE::Maths::Vector3<int>& pos) {
            return pos.z == eggId;
        });
    });

     this->_client->addCommand("sgt", net::type_command_t::SGT, [this](std::vector<std::string>& args) {
        if (args.size() != 2)
            throw EGE::Error("[SGT] Wrong number of param.");
        float timeUnit;
        try {
            timeUnit = std::stof(args[1]);
        } catch (std::exception &e) {
            throw EGE::Error("[SGT] Invalid time unit received : |" + args[1] + "|.");
        }
        this->_timeUnit = timeUnit;
        this->_animator.setTimeUnit(timeUnit);
        this->updateWorldSettings(timeUnit);
    });

    this->_client->addCommand("sst", net::type_command_t::SST, [this](std::vector<std::string>& args) {
        if (args.size() != 2)
            throw EGE::Error("[SST] Wrong number of param.");
    });

    this->_client->addCommand("seg", net::type_command_t::SEG, [this](std::vector<std::string>& args) {
        if (args.size() != 2)
            throw EGE::Error("[SEG] Wrong number of param.");
        std::string winner;
        try {
            winner = args[1];
        } catch (std::exception &e) {
            throw EGE::Error("[SEG] Invalid winner received : |" + args[1] + "|.");
        }
    });

    this->_client->addCommand("smg", net::type_command_t::SMG, [this](std::vector<std::string>& args) {
        if (args.size() != 2)
            throw EGE::Error("[SMG] Wrong number of param.");
        std::string message;
        try {
            message = args[1];
        } catch (std::exception &e) {
            throw EGE::Error("[SMG] Invalid message received : |" + args[1] + "|.");
        }
    });

    this->_client->addCommand("suc", net::type_command_t::SUC, [this](std::vector<std::string>& args) {
        // if (args.size() != 1)
        //     throw EGE::Error("[SUC] Wrong number of param.");
    });

    this->_client->addCommand("sbp", net::type_command_t::SBP, [this](std::vector<std::string>& args) {
        // if (args.size() != 1)
        //     throw EGE::Error("[SBP] Wrong number of param.");
    });

    this->_client->addCommand("idm", net::type_command_t::IDM, [this](std::vector<std::string>& args) {
        if (args.size() != 3)
            throw EGE::Error("[IDM] Wrong number of param.");
        int id = std::stoi(args[1]);
        switch (args[2][0]) {
            case 'F':
            case 'L':
            case 'R':
                this->_client->sendRequest("ppo #" + args[1] + "\n");
            case 'I':
                this->_client->sendRequest("plv #" + args[1] + "\n");
                break;
            default:
                throw EGE::Error("[IDM] Invalid change received : |" + args[2] + "|.");
                break;
        }
    });

    this->_client->connection();
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    this->_client->sendRequest("sgt\n");
    this->_client->sendRequest("msz\n");
    this->_client->sendRequest("mct\n");
    this->_client->sendRequest("tna\n");
    this->_client->sendRequest("idm\n");

    while (this->isRunning()) {
        this->_client->waitEvent();
        this->update();
    }
    this->_client->disconnect();
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
        if (!this->_cameraMode)
            return;
        glfwSetCursorPos(win, this->_window->getSize().x / 2, this->_window->getSize().y / 2);
        float xoffset = xpos - this->_window->getSize().x / 2;
        float yoffset = this->_window->getSize().y / 2 - ypos;
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
    this->_window->bindTrigger(EGE::Event::Trigger(EGE::Event::Keyboard, EGE::Event::Key::KeyC, EGE::Event::Mode::JustPressed, [this]() {
        glfwSetCursorPos(this->_window->getWindow(), this->_window->getSize().x / 2, this->_window->getSize().y / 2);
        this->_cameraMode = !this->_cameraMode;
        if (!this->_cameraMode)
            this->_interface->show();
    }));
    this->_window->bindTrigger(EGE::Event::Trigger(EGE::Event::Keyboard, EGE::Event::Key::KeyI, EGE::Event::Mode::JustPressed, [this]() {
        this->_interface->toggle();
        if (!this->_interface->isVisible())
            this->_cameraMode = true;
    }));
    this->_window->bindTrigger(EGE::Event::Trigger(EGE::Event::Keyboard, EGE::Event::Key::KeyLShift, EGE::Event::Mode::JustPressed, [this]() {
        this->_camera->setSpeed(this->_camera->getSpeed() * 2);
    }));
    this->_window->bindTrigger(EGE::Event::Trigger(EGE::Event::Keyboard, EGE::Event::Key::KeyLShift, EGE::Event::Mode::JustReleased, [this]() {
        this->_camera->setSpeed(this->_camera->getSpeed() / 2);
    }));
    this->_window->bindTrigger(EGE::Event::Trigger(EGE::Event::Keyboard, EGE::Event::Key::KeyEscape, EGE::Event::Mode::JustPressed, [this]() {
        exit(0);
    }));
    // this->_window->bindTrigger(EGE::Event::Trigger(EGE::Event::Keyboard, EGE::Event::Key::KeyF1, EGE::Event::Mode::JustPressed, [this]() {
    //     this->_interface->toggle();
    // }));
    this->_window->bindTrigger(EGE::Event::Trigger(EGE::Event::JoystickAxis, EGE::Event::JoystickAxis::JoystickLX, EGE::Event::Mode::Pressed, [this](float value) {
        if (value > 0.1f)
            this->_camera->move(EGE::Camera::Movement::RIGHT, value * this->_deltaTime * speed);
        else if (value < -0.1f)
            this->_camera->move(EGE::Camera::Movement::LEFT, -value * this->_deltaTime * speed);
    }, 0));
    this->_window->bindTrigger(EGE::Event::Trigger(EGE::Event::JoystickAxis, EGE::Event::JoystickAxis::JoystickLY, EGE::Event::Mode::Pressed, [this](float value) {
        if (value > 0.1f)
            this->_camera->move(EGE::Camera::Movement::FORWARD, -value * this->_deltaTime * speed);
        else if (value < -0.1f)
            this->_camera->move(EGE::Camera::Movement::BACKWARD, value * this->_deltaTime * speed);
    }, 0));
    this->_window->bindTrigger(EGE::Event::Trigger(EGE::Event::JoystickAxis, EGE::Event::JoystickAxis::JoystickRX, EGE::Event::Mode::Pressed, [this](float value) {
        if (value > 0.1f)
            this->_camera->rotate(value * 1.5f, 0, true);
        else if (value < -0.1f)
            this->_camera->rotate(value * 1.5f, 0, true);
    }, 0));
    this->_window->bindTrigger(EGE::Event::Trigger(EGE::Event::JoystickAxis, EGE::Event::JoystickAxis::JoystickRY, EGE::Event::Mode::Pressed, [this](float value) {
        if (value > 0.1f)
            this->_camera->rotate(0, -value * 1.5f, true);
        else if (value < -0.1f)
            this->_camera->rotate(0, -value * 1.5f, true);
    }, 0));
    this->_window->bindTrigger(EGE::Event::Trigger(EGE::Event::JoystickAxis, EGE::Event::JoystickAxis::JoystickLT, EGE::Event::Mode::Pressed, [this](float value) {
        value += 1.0f;
        if (value > 0.1f)
            this->_camera->move(EGE::Camera::Movement::DOWN, value * this->_deltaTime);
    }, 0));
    this->_window->bindTrigger(EGE::Event::Trigger(EGE::Event::JoystickAxis, EGE::Event::JoystickAxis::JoystickRT, EGE::Event::Mode::Pressed, [this](float value) {
        value += 1.0f;
        if (value > 0.1f)
            this->_camera->move(EGE::Camera::Movement::UP, value * this->_deltaTime);
    }, 0));
    this->_window->bindTrigger(EGE::Event::Trigger(EGE::Event::JoystickButton, EGE::Event::JoystickButton::JoystickLThumb, EGE::Event::Mode::JustPressed, [this]() {
        speed = 8.0f;
    }, 0));
    this->_window->bindTrigger(EGE::Event::Trigger(EGE::Event::JoystickButton, EGE::Event::JoystickButton::JoystickLThumb, EGE::Event::Mode::JustReleased, [this]() {
        speed = 4.0f;
    }, 0));
    this->_window->bindTrigger(EGE::Event::Trigger(EGE::Event::Mouse, EGE::Event::Mouse::MouseLeft, EGE::Event::Mode::JustPressed, [this]() {
        this->_tileSelected = this->_map->getTileSelected(this->_camera->getPosition(), this->_camera->_projection, this->_camera->_view);
        std::cout << "Tile selected: " << this->_tileSelected << std::endl;
        if (this->_tileSelected >= 0)
            this->updateTilePanel();
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

    EGE::ListBox *teams = new EGE::ListBox("Teams");

    EGE::Maths::Vector2<int> size = this->_map->getSize();
    dimensions->add(new EGE::Text("Width: " + std::to_string(size.x)), "width");
    dimensions->add(new EGE::Text("Height: " + std::to_string(size.y)), "height");

    panel->add(dimensions, "dimensions");
    panel->add(teams, "teams");

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
    if (!this->_interface->_panels["Amber World"])
        return;
    EGE::ListBox *dimensions = dynamic_cast<EGE::ListBox *>(this->_interface->_panels["Amber World"]->get("dimensions"));
    EGE::ListBox *content = dynamic_cast<EGE::ListBox *>(this->_interface->_panels["Amber World"]->get("content"));
    EGE::ListBox *teams = dynamic_cast<EGE::ListBox *>(this->_interface->_panels["Amber World"]->get("teams"));
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

    for (auto &team : this->_teams) {
        EGE::ListBox *tmpTeam = new EGE::ListBox(team);
        for (auto &player : this->_players) {
            if (player->getTeamName() == team) {
                tmpTeam->add(new EGE::Button("Player #" + std::to_string(player->getId()), [this, player]() {
                    this->_camera->setPosition(EGE::Maths::Vector3<float>(player->getPos().x * CELL_SIZE, 3.0f, player->getPos().y * CELL_SIZE));
                    this->_client->sendRequest("pin #" + std::to_string(player->getId()) + "\n");
                }), "Player #" + std::to_string(player->getId()));
            }
        }
        teams->add(tmpTeam, team);
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

void Onyx::Gui::createPlayerPanel()
{
    EGE::Panel *panel = new EGE::Panel("Trantorian");
    EGE::Text *team = new EGE::Text("Team: None");
    EGE::Text *id = new EGE::Text("ID: 0");
    EGE::Text *level = new EGE::Text("Level: 0");
    EGE::ListBox *inventory = new EGE::ListBox("Inventory");

    inventory->add(new EGE::Text("Food: 0"), "food");
    inventory->add(new EGE::Text("Linemate: 0"), "linemate");
    inventory->add(new EGE::Text("Deraumere: 0"), "deraumere");
    inventory->add(new EGE::Text("Sibur: 0"), "sibur");
    inventory->add(new EGE::Text("Mendiane: 0"), "mendiane");
    inventory->add(new EGE::Text("Phiras: 0"), "phiras");
    inventory->add(new EGE::Text("Thystame: 0"), "thystame");

    panel->add(team, "Team");
    panel->add(id, "ID");
    panel->add(level, "Level");
    panel->add(inventory, "Inventory");

    this->_interface->_panels["Trantorian"] = panel;
}

void Onyx::Gui::updatePlayerPanel(std::shared_ptr<Onyx::Player> &player)
{
    if (this->_interface->_panels["Trantorian"] == nullptr)
        this->createPlayerPanel();
    EGE::Text *team = dynamic_cast<EGE::Text *>(this->_interface->_panels["Trantorian"]->get("Team"));
    EGE::Text *level = dynamic_cast<EGE::Text *>(this->_interface->_panels["Trantorian"]->get("Level"));
    EGE::Text *id = dynamic_cast<EGE::Text *>(this->_interface->_panels["Trantorian"]->get("ID"));
    EGE::ListBox *inventory = dynamic_cast<EGE::ListBox *>(this->_interface->_panels["Trantorian"]->get("Inventory"));

    team->setName("Team: " + player->getTeamName());
    level->setName("Level: " + std::to_string(player->getLevel()));
    id->setName("ID: " + std::to_string(player->getId()));
    inventory->get("food")->setName("Food: " + std::to_string(player->getQuantity(Onyx::Item::TYPE::FOOD)));
    inventory->get("linemate")->setName("Linemate: " + std::to_string(player->getQuantity(Onyx::Item::TYPE::LINEMATE)));
    inventory->get("deraumere")->setName("Deraumere: " + std::to_string(player->getQuantity(Onyx::Item::TYPE::DERAUMERE)));
    inventory->get("sibur")->setName("Sibur: " + std::to_string(player->getQuantity(Onyx::Item::TYPE::SIBUR)));
    inventory->get("mendiane")->setName("Mendiane: " + std::to_string(player->getQuantity(Onyx::Item::TYPE::MENDIANE)));
    inventory->get("phiras")->setName("Phiras: " + std::to_string(player->getQuantity(Onyx::Item::TYPE::PHIRAS)));
    inventory->get("thystame")->setName("Thystame: " + std::to_string(player->getQuantity(Onyx::Item::TYPE::THYSTAME)));
}

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
    if (this->_tileSelected < 0)
        return;
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

void Onyx::Gui::createConsolePanel()
{
    EGE::Panel *panel = new EGE::Panel("Console");

    this->_interface->_panels["Console"] = panel;
}

void Onyx::Gui::updateConsolePanel(std::vector<std::string>& args)
{
    std::string message = "";

    for (auto &arg : args)
        message += " " + arg;
    this->_interface->_panels["Console"]->add(new EGE::Text(message), message);
}

void Onyx::Gui::updateWorldSettings(float value)
{
    EGE::Slider *frequency = dynamic_cast<EGE::Slider *>(this->_interface->_panels["World settings"]->get("0 Frequency"));
    frequency->setValue(value);
}

void Onyx::Gui::updateSensitivities(float value)
{
    EGE::Slider *sensivity = dynamic_cast<EGE::Slider *>(this->_interface->_panels["Camera settings"]->get("0 Sensivity"));
    sensivity->setValue(value);
    this->_camera->setSensitivity(value);
}

void Onyx::Gui::createMenuBar()
{
    EGE::Menu *settings = new EGE::Menu("Settings");

    EGE::Panel *world = new EGE::Panel("World settings");
    EGE::CheckBox *darkMode = new EGE::CheckBox("Dark mode");
    EGE::Slider *frequency = new EGE::Slider("Frequency", 0.1, 2000);
    EGE::Button *worldApply = new EGE::Button("Apply", [this] () {
        EGE::Slider *frequ = dynamic_cast<EGE::Slider *>(this->_interface->_panels["World settings"]->get("0 Frequency"));
        EGE::CheckBox *dark = dynamic_cast<EGE::CheckBox *>(this->_interface->_panels["World settings"]->get("1 Dark mode"));

        if (dark->isChecked())
            this->_interface->darkMode();
        else
            this->_interface->defaultMode();
        this->_interface->_panels["World settings"]->setVisible(false);
        this->_client->sendRequest("sst " + std::to_string(frequ->getValue()) + "\n");
    });

    world->add(frequency, "0 Frequency");
    world->add(darkMode, "1 Dark mode");
    world->add(worldApply, "2 Apply");
    world->setVisible(false);
    this->_interface->_panels["World settings"] = world;

    settings->add(new EGE::Item("World", [this] () {
        if (this->_interface->_panels["World settings"])
            return this->_interface->_panels["World settings"]->setVisible(true);
    }), "0 World");

    EGE::Panel *cam = new EGE::Panel("Camera settings");
    EGE::Slider *sensivity = new EGE::Slider("Sensivity", 1, 100);
    sensivity->setValue(this->_camera->getSensitivity());
    EGE::Slider *speed = new EGE::Slider("Speed", 1, 100);
    speed->setValue(this->_camera->getSpeed());
    EGE::CheckBox *cinematicMode = new EGE::CheckBox("Cinematic mode");
    EGE::Button *camApply = new EGE::Button("Apply", [this] () {
        EGE::Slider *tmp = dynamic_cast<EGE::Slider *>(this->_interface->_panels["Camera settings"]->get("0 Sensivity"));
        this->_interface->_panels["Camera settings"]->setVisible(false);
        this->updateSensitivities(tmp->getValue());
        tmp = dynamic_cast<EGE::Slider *>(this->_interface->_panels["Camera settings"]->get("1 Speed"));
        this->_camera->setSpeed(tmp->getValue());
    });

    cam->add(sensivity, "0 Sensivity");
    cam->add(speed, "1 Speed");
    cam->add(cinematicMode, "2 Cinematic mode");
    cam->add(camApply, "3 Apply");
    cam->setVisible(false);
    this->_interface->_panels["Camera settings"] = cam;

    settings->add(new EGE::Item("Camera", [this] () {
        if (this->_interface->_panels["Camera settings"])
            return this->_interface->_panels["Camera settings"]->setVisible(true);
    }), "1 Camera");


    settings->add(new EGE::Item("Disconnect", [this] () {
        this->_client->disconnect();
        this->getWindow()->close();
    }), "2 Disconnect");
    settings->add(new EGE::Item("Quit", [this] () {
        exit(0);
    }), "3 Quit");

    this->_interface->_menuBar->add(settings, "0 Settings");

    EGE::Menu *music = new EGE::Menu("Music");

    music->add(new EGE::Item("Previous", [this] () {
        this->_interface->getPlaylist()->previous();
    }), "0 Previous");
    music->add(new EGE::Item("Play / Pause", [this] () {
        this->_interface->getPlaylist()->playPause();
    }), "1 Play");
    music->add(new EGE::Item("Next", [this] () {
        this->_interface->getPlaylist()->next();
    }), "2 Next");

    this->_interface->_menuBar->add(music, "1 Music");

    EGE::Menu *help = new EGE::Menu("Help");

    help->add(new EGE::Item("Launch Tutorial", [this] () {
        this->_interface->_panels["Tutorial"]->setVisible(true);
    }), "0 Tutorial");

    EGE::Panel *helpPanel = new EGE::Panel("Shortcuts");
    EGE::Button *done = new EGE::Button("Done", [this] () {
        this->_interface->_panels["Shortcuts"]->setVisible(false);
    });

    helpPanel->add(new EGE::Text(Utils::getFileContent("./assets/tutorial/shortcuts.txt")), "0 Shortcuts");
    helpPanel->add(done, "1 Done");
    helpPanel->setVisible(false);

    this->_interface->_panels["Shortcuts"] = helpPanel;

    help->add(new EGE::Item("Shortcuts", [this] () {
        if (this->_interface->_panels["Shortcuts"])
            return this->_interface->_panels["Shortcuts"]->setVisible(true);
    }), "1 Shortcuts");

    this->_interface->_menuBar->add(help, "2 Help");
}

void Onyx::Gui::createTutorial()
{
    EGE::Panel *main = new EGE::Panel("Tutorial");
    EGE::Text *mainDescription = new EGE::Text(Utils::getFileContent("./assets/tutorial/main.txt"));
    EGE::Button *mainDone = new EGE::Button("Lets do it !", [this] () {
        this->_interface->_panels["Tutorial"]->setVisible(false);
        this->_interface->_panels["Camera tutorial"]->setVisible(true);
    });

    main->add(mainDescription, "0 Main");
    main->add(mainDone, "1 Done");
    main->setVisible(false);
    this->_interface->_panels["Tutorial"] = main;

    EGE::Panel *camera = new EGE::Panel("Camera tutorial");
    EGE::Text *cameraDescription = new EGE::Text(Utils::getFileContent("./assets/tutorial/camera.txt"));
    EGE::Button *cameraDone = new EGE::Button("Done !", [this] () {
        this->_interface->_panels["Camera tutorial"]->setVisible(false);
        this->_interface->_panels["Settings tutorial"]->setVisible(true);
    });

    camera->add(cameraDescription, "0 Camera");
    camera->add(cameraDone, "1 Done");
    camera->setVisible(false);
    this->_interface->_panels["Camera tutorial"] = camera;

    EGE::Panel *settings = new EGE::Panel("Settings tutorial");
    EGE::Text *settingsDescription = new EGE::Text(Utils::getFileContent("./assets/tutorial/settings.txt"));
    EGE::Button *settingsDone = new EGE::Button("Done !", [this] () {
        this->_interface->_panels["Settings tutorial"]->setVisible(false);
        this->_interface->_panels["Music tutorial"]->setVisible(true);
    });

    settings->add(settingsDescription, "0 Settings");
    settings->add(settingsDone, "1 Done");
    settings->setVisible(false);
    this->_interface->_panels["Settings tutorial"] = settings;

    EGE::Panel *music = new EGE::Panel("Music tutorial");
    EGE::Text *musicDescription = new EGE::Text(Utils::getFileContent("./assets/tutorial/music.txt"));
    EGE::Button *musicDone = new EGE::Button("Done !", [this] () {
        this->_interface->_panels["Music tutorial"]->setVisible(false);
        this->_interface->_panels["Help tutorial"]->setVisible(true);
    });

    music->add(musicDescription, "0 Music");
    music->add(musicDone, "1 Done");
    music->setVisible(false);
    this->_interface->_panels["Music tutorial"] = music;

    EGE::Panel *help = new EGE::Panel("Help tutorial");
    EGE::Text *helpDescription = new EGE::Text(Utils::getFileContent("./assets/tutorial/help.txt"));
    EGE::Button *helpDone = new EGE::Button("Done !", [this] () {
        this->_interface->_panels["Help tutorial"]->setVisible(false);
        this->_interface->_panels["World tutorial"]->setVisible(true);
    });

    help->add(helpDescription, "0 Help");
    help->add(helpDone, "1 Done");
    help->setVisible(false);
    this->_interface->_panels["Help tutorial"] = help;

    EGE::Panel *world = new EGE::Panel("World tutorial");
    EGE::Text *worldDescription = new EGE::Text(Utils::getFileContent("./assets/tutorial/world.txt"));
    EGE::Button *worldDone = new EGE::Button("Done !", [this] () {
        this->_interface->_panels["World tutorial"]->setVisible(false);
        this->_interface->_panels["Trantorian tutorial"]->setVisible(true);
    });

    world->add(worldDescription, "0 World");
    world->add(worldDone, "1 Done");
    world->setVisible(false);
    this->_interface->_panels["World tutorial"] = world;

    EGE::Panel *trantorian = new EGE::Panel("Trantorian tutorial");
    EGE::Text *trantorianDescription = new EGE::Text(Utils::getFileContent("./assets/tutorial/trantorian.txt"));
    EGE::Button *trantorianDone = new EGE::Button("Done !", [this] () {
        this->_interface->_panels["Trantorian tutorial"]->setVisible(false);
        this->_interface->_panels["Tile tutorial"]->setVisible(true);
    });

    trantorian->add(trantorianDescription, "0 Trantorian");
    trantorian->add(trantorianDone, "1 Done");
    trantorian->setVisible(false);
    this->_interface->_panels["Trantorian tutorial"] = trantorian;

    EGE::Panel *tile = new EGE::Panel("Tile tutorial");
    EGE::Text *tileDescription = new EGE::Text(Utils::getFileContent("./assets/tutorial/tile.txt"));
    EGE::Button *tileDone = new EGE::Button("Done !", [this] () {
        this->_interface->_panels["Tile tutorial"]->setVisible(false);
        this->_interface->_panels["Console tutorial"]->setVisible(true);
    });

    tile->add(tileDescription, "0 Tile");
    tile->add(tileDone, "1 Done");
    tile->setVisible(false);
    this->_interface->_panels["Tile tutorial"] = tile;

    EGE::Panel *console = new EGE::Panel("Console tutorial");
    EGE::Text *consoleDescription = new EGE::Text(Utils::getFileContent("./assets/tutorial/console.txt"));
    EGE::Button *consoleDone = new EGE::Button("Done !", [this] () {
        this->_interface->_panels["Console tutorial"]->setVisible(false);
    });

    console->add(consoleDescription, "0 Console");
    console->add(consoleDone, "1 Done");
    console->setVisible(false);
    this->_interface->_panels["Console tutorial"] = console;
}
