/*
** EPITECH PROJECT, 2024
** gui
** File description:
** Player
*/

#include "Player.hpp"

std::map<std::string, Onyx::Player::Color> Onyx::Player::_colorMap = {};

Onyx::Player::Player(const std::string &teamName, const EGE::Maths::Vector2<int>& position, const std::string& rotation) : _teamName(teamName)
{
    this->_level = 1;
    if (Player::_colorMap[teamName] == 0) {
        Player::_colorMap[teamName] = static_cast<Color>(Player::_colorMap.size());
    }
    if (Player::_colorMap[teamName] >= Onyx::Player::Color::LAST) {
        throw Onyx::PlayerError("The GUI does not support more than " + std::to_string(static_cast<int>(Onyx::Player::Color::LAST) - 1) + " teams.");
    }
    this->_color = Player::_colorMap[teamName];
    std::string mtl = Utils::getFileContent("./assets/models/player/lvl1/lvl1.mtl");
    this->_setColor(mtl);
    Utils::setFileContent("./assets/models/player/lvl1/lvl1.mtl", mtl, false);
    this->_position = EGE::Maths::Vector3<float>(position.x * CELL_SIZE, 2, position.y * CELL_SIZE);
    switch (rotation[0]) {
        case 'N':
            this->_rotation = EGE::Maths::Vector3<float>(0.0f, 0.0f, 0.0f);
            break;
        case 'E':
            this->_rotation = EGE::Maths::Vector3<float>(0.0f, 90.0f, 0.0f);
            break;
        case 'S':
            this->_rotation = EGE::Maths::Vector3<float>(0.0f, 180.0f, 0.0f);
            break;
        case 'W':
            this->_rotation = EGE::Maths::Vector3<float>(0.0f, 270.0f, 0.0f);
            break;
        default:
            throw Onyx::PlayerError("Invalid rotation: " + rotation);
            break;
    }
    this->_model = std::make_shared<EGE::Model>("./assets/models/player/lvl1/lvl1.obj", this->_position, this->_rotation, this->_scale);
}

Onyx::Player::~Player()
{
}

void Onyx::Player::update(std::shared_ptr<EGE::Shader> shader)
{
    this->_model->draw(*shader.get());
}

void Onyx::Player::evolve()
{
    this->_level++;
    std::string mtl = Utils::getFileContent("./assets/models/player/lvl" + std::to_string(this->_level) + "/lvl" + std::to_string(this->_level) + ".mtl");
    this->_setColor(mtl);
    Utils::setFileContent("./assets/models/player/lvl" + std::to_string(this->_level) + "/lvl" + std::to_string(this->_level) + ".mtl", mtl, false);
    this->_model = std::make_shared<EGE::Model>("./assets/models/player/lvl" + std::to_string(this->_level) + "/lvl" + std::to_string(this->_level) + ".obj", this->_position, this->_scale);
}

void Onyx::Player::setLevel(int level)
{
    this->_level = level;
}

int Onyx::Player::getLevel()
{
    return this->_level;
}

void Onyx::Player::setColor(const Color &color)
{
    this->_color = color;
}

Onyx::Player::Color Onyx::Player::getColor()
{
    return this->_color;
}

void Onyx::Player::setTeamName(const std::string &teamName)
{
    this->_teamName = teamName;
}

std::string Onyx::Player::getTeamName()
{
    return this->_teamName;
}

void Onyx::Player::_setColor(std::string &fileContent)
{
    std::string newFile = "../colors/";
    switch (this->_color) {
    case Onyx::Player::Color::RED:
        newFile += "red.png";
        break;
    case Onyx::Player::Color::GREEN:
        newFile += "green.png";
        break;
    case Onyx::Player::Color::BLUE:
        newFile += "blue.png";
        break;
    case Onyx::Player::Color::PINK:
        newFile += "pink.png";
        break;
    case Onyx::Player::Color::YELLOW:
        newFile += "yellow.png";
        break;
    case Onyx::Player::Color::ORANGE:
        newFile += "orange.png";
        break;
    case Onyx::Player::Color::PURPLE:
        newFile += "purple.png";
        break;
    case Onyx::Player::Color::CYAN:
        newFile += "cyan.png";
        break;
    default:
        break;
    }
    fileContent = std::regex_replace(fileContent, std::regex("map_Kd .+"), "map_Kd " + newFile);
}