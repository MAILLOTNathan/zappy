/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** GuiVR
*/

#include "GuiVR.hpp"

GuiVR::GuiVR(android_app *app)
{
    this->_window = std::make_shared<EGE::WindowVR>(app);
    this->_window->create();
    this->_client = std::make_shared<net::TcpClient>("192.168.180.247", 4242);
    this->_client->connection();
    std::string vertexSource = EGE::UtilsVR::readAssetFile("shaders/vertex.vert");
    std::string fragmentSource = EGE::UtilsVR::readAssetFile("shaders/fragment.frag");
    this->_shader = std::make_shared<EGE::Shader>();
    this->_shader->compile(vertexSource, fragmentSource);
    this->_window->addNewSlot("Map", this->_shader);

    this->_client->addCommand("msz", net::MSZ, [this](std::vector<std::string> args) {
        if (args.size() != 3)
            throw EGE::Error("[MSZ] Wrong number of param.");
        this->createMap(std::stoi(args[1]), std::stoi(args[2]));
    });

    this->_client->addCommand("pnw", net::type_command_t::PNW, [this](std::vector<std::string>& args) {
        std::cout << "PNW passed" << std::endl;
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
        this->addPlayer(id, EGE::Maths::Vector2<int>(x, y), args[6], args[4], this->_timeUnit);
    });

    this->_client->addCommand("sgt", net::type_command_t::SGT, [this](std::vector<std::string>& args) {
        if (args.size() != 2)
            throw EGE::Error("Wrong number of param.");
        float timeUnit;
        try {
            timeUnit = std::stof(args[1]);
        } catch (std::exception &e) {
            throw EGE::Error("Invalid time unit received in sgt command : |" + args[1] + "|.");
        }
        this->_timeUnit = timeUnit;
        // this->_animator.setTimeUnit(timeUnit);
        // this->updateWorldSettings(timeUnit);
    });

    this->_client->addCommand("idm", net::type_command_t::IDM, [this](std::vector<std::string>& args) {
        std::cout << "IDM passed" << std::endl;
        if (args.size() != 3)
            throw EGE::Error("[IDM] Wrong number of param.");
        for (const auto& arg : args)
            std::cout << arg << std::endl;
        int id = std::stoi(args[1]);
        switch (args[2][0]) {
            case 'F':
            case 'L':
            case 'R':
                this->_client->sendRequest("ppo #" + args[1] + "\n");
                break;
            default:
                throw EGE::Error("[IDM] Invalid change received : |" + args[2] + "|.");
                break;
        }
    });

    this->_client->sendRequest("msz\n");
    this->_client->sendRequest("sgt\n");
}

GuiVR::~GuiVR()
{
}

void GuiVR::update()
{
    this->_client->waitEvent();
    this->_window->appUpdatePumpEvents();
    if (!this->_window->isSessionReady()) {
        return;
    }
    this->_window->appUpdateBeginFrame();
    if (this->_window->isShouldRender()) {
        this->_window->display();
    }
    this->_window->appUpdateEndFrame();
}

bool GuiVR::isRunning()
{
    return this->_window->isRunning();
}

void GuiVR::createMap(int width, int height)
{
    this->_map = std::make_shared<MapVR>(EGE::Maths::Vector2<int>(width, height), this->_window);
}

void GuiVR::addPlayer(int id, EGE::Maths::Vector2<int> position, const std::string &teamName, const std::string& rotation, float timeUnit)
{
    this->_players.push_back(std::make_shared<PlayerVR>(id, teamName, position, rotation, timeUnit, this->_window));
}

