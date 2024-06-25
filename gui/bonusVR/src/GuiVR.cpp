/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** GuiVR
*/

#include "GuiVR.hpp"

GuiVR::GuiVR(android_app *app)
{
    __android_log_print(ANDROID_LOG_FATAL, "DEBUG", "GuiVR.cpp: GuiVR():12");
    this->_window = std::make_shared<EGE::WindowVR>(app);
    __android_log_print(ANDROID_LOG_FATAL, "DEBUG", "GuiVR.cpp: GuiVR():14");
    this->_window->create();
    __android_log_print(ANDROID_LOG_FATAL, "DEBUG", "GuiVR.cpp: GuiVR():16");
    this->_client = std::make_shared<net::TcpClient>("192.168.197.247", 4242);
    __android_log_print(ANDROID_LOG_FATAL, "DEBUG", "GuiVR.cpp: GuiVR():18");
    this->_client->connection();
    __android_log_print(ANDROID_LOG_FATAL, "DEBUG", "GuiVR.cpp: GuiVR():20");
    std::string vertexSource = EGE::UtilsVR::readAssetFile("shaders/vertex.vert");
    std::string fragmentSource = EGE::UtilsVR::readAssetFile("shaders/fragment.frag");
    this->_shader = std::make_shared<EGE::Shader>();
    this->_shader->compile(vertexSource, fragmentSource);
    __android_log_print(ANDROID_LOG_FATAL, "DEBUG", "GuiVR.cpp: GuiVR():23");

    this->_client->addCommand("msz", net::MSZ, [this](std::vector<std::string> args) {
        if (args.size() != 3) {
            __android_log_print(ANDROID_LOG_FATAL, "DEBUG", "[MSZ] Wrong number of param.");
            throw EGE::Error("[MSZ] Wrong number of param.");
        }
        this->createMap(std::stoi(args[1]), std::stoi(args[2]));
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
        this->_map->addItem(position, ItemVR::TYPE::FOOD, std::stoi(args[3]));
        this->_map->addItem(position, ItemVR::TYPE::LINEMATE, std::stoi(args[4]));
        this->_map->addItem(position, ItemVR::TYPE::DERAUMERE, std::stoi(args[5]));
        this->_map->addItem(position, ItemVR::TYPE::SIBUR, std::stoi(args[6]));
        this->_map->addItem(position, ItemVR::TYPE::MENDIANE, std::stoi(args[7]));
        this->_map->addItem(position, ItemVR::TYPE::PHIRAS, std::stoi(args[8]));
        this->_map->addItem(position, ItemVR::TYPE::THYSTAME, std::stoi(args[9]));
    });
    __android_log_print(ANDROID_LOG_FATAL, "DEBUG", "GuiVR.cpp: GuiVR():30");

    this->_client->addCommand("pnw", net::type_command_t::PNW, [this](std::vector<std::string>& args) {
        if (args.size() != 7) {
            __android_log_print(ANDROID_LOG_FATAL, "DEBUG", "[PNW] Wrong number of param.");
            throw EGE::Error("[PNW] Wrong number of param.");
        }
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
            __android_log_print(ANDROID_LOG_FATAL, "DEBUG", "[PNW] Invalid id received : |%s|.", args[1].c_str());
            throw EGE::Error("[PNW] Invalid id received : |" + args[1] + "|.");
        }
        try {
            x = std::stoi(args[2]);
        } catch (std::exception &e) {
            __android_log_print(ANDROID_LOG_FATAL, "DEBUG", "[PNW] Invalid x position received : |%s|.", args[2].c_str());
            throw EGE::Error("[PNW] Invalid x position received : |" + args[2] + "|.");
        }
        try {
            y = std::stoi(args[3]);
        } catch (std::exception &e) {
            __android_log_print(ANDROID_LOG_FATAL, "DEBUG", "[PNW] Invalid y position received : |%s|.", args[3].c_str());
            throw EGE::Error("[PNW] Invalid y position received : |" + args[3] + "|.");
        }
        try {
            level = std::stoi(args[5]);
        } catch (std::exception &e) {
            __android_log_print(ANDROID_LOG_FATAL, "DEBUG", "[PNW] Invalid level received : |%s|.", args[5].c_str());
            throw EGE::Error("[PNW] Invalid level received : |" + args[5] + "|.");
        }
        __android_log_print(ANDROID_LOG_FATAL, "DEBUG", "before add player");
        this->addPlayer(id, EGE::Maths::Vector2<int>(x, y), args[6], args[4], level, this->_timeUnit);
        __android_log_print(ANDROID_LOG_FATAL, "DEBUG", "after add player");
    });

    this->_client->addCommand("ppo", net::type_command_t::PPO, [this](std::vector<std::string>& args) {
        if (args.size() != 5) {
            __android_log_print(ANDROID_LOG_FATAL, "DEBUG", "[PPO] Wrong number of param.");
            throw EGE::Error("[PPO] Wrong number of param.");
        }
        for (const auto& arg : args)
            std::cout << arg << std::endl;
        int id, x, y;
        std::string rotation = args[4];
        EGE::Maths::Vector2<int> pos;
        try {
            id = std::stoi(args[1].substr(1));
        } catch (std::exception &e) {
            __android_log_print(ANDROID_LOG_FATAL, "DEBUG", "[PPO] Invalid id : |%s|.", args[1].c_str());
            throw EGE::Error("[PPO] Invalid id : |" + args[1] + "|.");
        }
        try {
            x = std::stoi(args[2]);
        } catch (std::exception &e) {
            __android_log_print(ANDROID_LOG_FATAL, "DEBUG", "[PPO] Invalid x position : |%s|.", args[2].c_str());
            throw EGE::Error("[PPO] Invalid x position : |" + args[2] + "|.");
        }
        try {
            y = std::stoi(args[3]);
        } catch (std::exception &e) {
            __android_log_print(ANDROID_LOG_FATAL, "DEBUG", "[PPO] Invalid y position : |%s|.", args[3].c_str());
            throw EGE::Error("[PPO] Invalid y position : |" + args[3] + "|.");
        }
        if (rotation != "N" && rotation != "E" && rotation != "S" && rotation != "W") {
            __android_log_print(ANDROID_LOG_FATAL, "DEBUG", "[PPO] Invalid rotation : |%s|.", rotation.c_str());
            throw EGE::Error("[PPO] Invalid rotation : |" + rotation + "|.");
        }
        for (auto& player : this->_players) {
            if (player->getId() == id) {
                pos = player->getPos();
                player->setPos(pos);
                PlayerVR::Animation animation = PlayerVR::Animation::NONE;
                if (pos.x != x || pos.y != y) {
                    std::string rstring = player->getRotationString();
                    if (rstring == "N") {
                        animation = PlayerVR::Animation::FORWARD_NORTH;
                    } else if (rstring == "E") {
                        animation = PlayerVR::Animation::FORWARD_EAST;
                    } else if (rstring == "S") {
                        animation = PlayerVR::Animation::FORWARD_SOUTH;
                    } else if (rstring == "W") {
                        animation = PlayerVR::Animation::FORWARD_WEST;
                    }
                } else {
                    std::string rstring = player->getRotationString();
                    if (rstring == "N") {
                        if (rotation == "E") {
                            animation = PlayerVR::Animation::RIGHT;
                        } else if (rotation == "W") {
                            animation = PlayerVR::Animation::LEFT;
                        }
                    } else if (rstring == "E") {
                        if (rotation == "S") {
                            animation = PlayerVR::Animation::RIGHT;
                        } else if (rotation == "N") {
                            animation = PlayerVR::Animation::LEFT;
                        }
                    } else if (rstring == "S") {
                        if (rotation == "W") {
                            animation = PlayerVR::Animation::RIGHT;
                        } else if (rotation == "E") {
                            animation = PlayerVR::Animation::LEFT;
                        }
                    } else if (rstring == "W") {
                        if (rotation == "N") {
                            animation = PlayerVR::Animation::RIGHT;
                        } else if (rotation == "S") {
                            animation = PlayerVR::Animation::LEFT;
                        }
                    }
                }
                player->setRotationString(rotation);
                player->setPos(EGE::Maths::Vector2<int>(x, y));
                __android_log_print(ANDROID_LOG_INFO, "MYTAG", "in idm command PNW");
                // this->_animator.startAnimation(player, animation, [&player, x, y, rotation]() {
                //     player->setPos(EGE::Maths::Vector2<int>(x, y));
                //     player->setRotationString(rotation);
                // });

            }
        }
    });

    this->_client->addCommand("plv", net::type_command_t::PLV, [this](std::vector<std::string>& args) {
        if (args.size() != 3) {
            __android_log_print(ANDROID_LOG_FATAL, "DEBUG", "[PLV] Wrong number of param.");
            throw EGE::Error("[PLV] Wrong number of param.");
        }
        int id = 0;
        int level = 0;
        try {
            id = std::stoi(args[1].substr(1));
        } catch (std::exception &e) {
            __android_log_print(ANDROID_LOG_FATAL, "DEBUG", "[PLV] Invalid id received : |%s|.", args[1].c_str());
            throw EGE::Error("[PLV] Invalid id received : |" + args[1] + "|.");
        }
        try {
            level = std::stoi(args[2]);
        } catch (std::exception &e) {
            __android_log_print(ANDROID_LOG_FATAL, "DEBUG", "[PLV] Invalid level received : |%s|.", args[2].c_str());
            throw EGE::Error("[PLV] Invalid level received : |" + args[2] + "|.");
        }
        for (auto &player : this->_players) {
            if (player->getId() == id) {
                std::cout << "set player " << id << " to level " << level << std::endl;
                player->setLevel(level, this->_shader);
            }
        }
    });

    this->_client->addCommand("pdi", net::type_command_t::PDI, [this](std::vector<std::string>& args) {
        if (args.size() != 2) {
            __android_log_print(ANDROID_LOG_FATAL, "DEBUG", "[PDI] Wrong number of param.");
            throw EGE::Error("[PDI] Wrong number of param.");
        }
        int id = 0;
        try {
            id = std::stoi(args[1].substr(1));
        } catch (std::exception &e) {
            __android_log_print(ANDROID_LOG_FATAL, "DEBUG", "[PDI] Invalid id received : |%s|.", args[1].c_str());
            throw EGE::Error("[PDI] Invalid id received : |" + args[1] + "|.");
        }
        for (auto &player : this->_players) {
            if (player->getId() == id) {
                this->_window->removeDrawable("player_" + std::to_string(id));
                this->_players.erase(std::remove(this->_players.begin(), this->_players.end(), player), this->_players.end());
                break;
            }
        }
        __android_log_print(ANDROID_LOG_INFO, "MYTAG", "in pdi command\n");
    });

    this->_client->addCommand("enw", net::type_command_t::ENW, [this](std::vector<std::string>& args) {
        if (args.size() != 5) {
            __android_log_print(ANDROID_LOG_FATAL, "DEBUG", "[ENW] Wrong number of param.");
            throw EGE::Error("[ENW] Wrong number of param.");
        }
        int eggId = 0;
        int id = 0;
        int x = 0;
        int y = 0;
        try {
            eggId = std::stoi(args[1].substr(1));
        } catch (std::exception &e) {
            __android_log_print(ANDROID_LOG_FATAL, "DEBUG", "[ENW] Invalid egg id received : |%s|.", args[1].c_str());
            throw EGE::Error("[ENW] Invalid egg id received : |" + args[1] + "|.");
        }
        try {
            id = std::stoi(args[2].substr(1));
        } catch (std::exception &e) {
            __android_log_print(ANDROID_LOG_FATAL, "DEBUG", "[ENW] Invalid id received : |%s|.", args[2].c_str());
            throw EGE::Error("[ENW] Invalid id received : |" + args[2] + "|.");
        }
        try {
            x = std::atoi(args[3].c_str());
        } catch (std::exception &e) {
            __android_log_print(ANDROID_LOG_FATAL, "DEBUG", "[ENW] Invalid x position received : |%s|.", args[3].c_str());
            throw EGE::Error("[ENW] Invalid x position received : |" + args[3] + "|.");
        }
        try {
            y = std::atoi(args[4].c_str());
        } catch (std::exception &e) {
            __android_log_print(ANDROID_LOG_FATAL, "DEBUG", "[ENW] Invalid y position received : |%s|.", args[4].c_str());
            throw EGE::Error("[ENW] Invalid y position received : |" + args[4] + "|.");
        }
        __android_log_print(ANDROID_LOG_DEBUG, "MYTAG", "%d %d %d\n", x, y, eggId);
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
        for (auto& pos : eggPos) {
            if (pos.z == eggId) {
                eggPos.erase(std::remove(eggPos.begin(), eggPos.end(), pos), eggPos.end());
                break;
            }
        }
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
        for (auto& pos : eggPos) {
            if (pos.z == eggId) {
                eggPos.erase(std::remove(eggPos.begin(), eggPos.end(), pos), eggPos.end());
                break;
            }
        }
    });


    this->_client->addCommand("sgt", net::type_command_t::SGT, [this](std::vector<std::string>& args) {
        if (args.size() != 2) {
            __android_log_print(ANDROID_LOG_FATAL, "DEBUG", "[SGT] Wrong number of param.");
            throw EGE::Error("Wrong number of param.");
        }
        float timeUnit;
        try {
            timeUnit = std::stof(args[1]);
        } catch (std::exception &e) {
            __android_log_print(ANDROID_LOG_FATAL, "DEBUG", "[SGT] Invalid time unit received : |%s|.", args[1].c_str());
            throw EGE::Error("Invalid time unit received in sgt command : |" + args[1] + "|.");
        }
        this->_timeUnit = timeUnit;
        // this->_animator.setTimeUnit(timeUnit);
        // this->updateWorldSettings(timeUnit);
    });

    this->_client->addCommand("idm", net::type_command_t::IDM, [this](std::vector<std::string>& args) {
        if (args.size() != 3) {
            __android_log_print(ANDROID_LOG_FATAL, "DEBUG", "[IDM] Wrong number of param.");
            throw EGE::Error("[IDM] Wrong number of param.");
        }
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
                __android_log_print(ANDROID_LOG_FATAL, "DEBUG", "[IDM] Invalid change received : |%s|.", args[2].c_str());
                throw EGE::Error("[IDM] Invalid change received : |" + args[2] + "|.");
                break;
        }
    });

    this->_client->sendRequest("msz\n");
    this->_client->sendRequest("sgt\n");
    this->_client->sendRequest("mct\n");
}

GuiVR::~GuiVR()
{
}

void GuiVR::update()
{
    __android_log_print(ANDROID_LOG_FATAL, "DEBUG", "GuiVR.cpp: update(): 265");
    this->_client->waitEvent();
    __android_log_print(ANDROID_LOG_FATAL, "DEBUG", "GuiVR.cpp: update(): 267");
    this->_window->appUpdatePumpEvents();
    __android_log_print(ANDROID_LOG_FATAL, "DEBUG", "GuiVR.cpp: update(): 269");
    if (!this->_window->isSessionReady()) {
        __android_log_print(ANDROID_LOG_FATAL, "DEBUG", "GuiVR.cpp: update(): 271");
        return;
    }
    __android_log_print(ANDROID_LOG_FATAL, "DEBUG", "GuiVR.cpp: update(): 274");
    this->_window->appUpdateBeginFrame();
    __android_log_print(ANDROID_LOG_FATAL, "DEBUG", "GuiVR.cpp: update(): 276");
    if (this->_window->isShouldRender()) {
        __android_log_print(ANDROID_LOG_FATAL, "DEBUG", "GuiVR.cpp: update(): 278");
        this->_window->display();
        __android_log_print(ANDROID_LOG_FATAL, "DEBUG", "GuiVR.cpp: update(): 280");
    }
    __android_log_print(ANDROID_LOG_FATAL, "DEBUG", "GuiVR.cpp: update(): 282");
    this->_window->appUpdateEndFrame();
    __android_log_print(ANDROID_LOG_FATAL, "DEBUG", "GuiVR.cpp: update(): 284");
}

bool GuiVR::isRunning()
{
    return this->_window->isRunning();
}

void GuiVR::createMap(int width, int height)
{
    this->_map = std::make_shared<MapVR>(EGE::Maths::Vector2<int>(width, height), this->_window, this->_shader);
}

void GuiVR::addPlayer(int id, EGE::Maths::Vector2<int> position, const std::string &teamName, const std::string& rotation, int level, float timeUnit)
{
    this->_players.push_back(std::make_shared<PlayerVR>(id, teamName, position, rotation, level, timeUnit, this->_window, this->_shader));
}

