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
    std::string vertexSource = EGE::UtilsVR::readAssetFile("shaders/vertex.vert");
    std::string fragmentSource = EGE::UtilsVR::readAssetFile("shaders/fragment.frag");
    this->_shader = std::make_shared<EGE::Shader>();
    this->_shader->compile(vertexSource, fragmentSource);
}

GuiVR::~GuiVR()
{
}

void GuiVR::update()
{
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
