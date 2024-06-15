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
    this->_client = std::make_shared<net::TcpClient>("192.168.56.247", 4242);
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

    this->_client->sendRequest("msz\n");
}

GuiVR::~GuiVR()
{
}

void GuiVR::update()
{
    __android_log_print(ANDROID_LOG_INFO, "MYTAG", "Updating");
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
