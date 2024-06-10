/*
** EPITECH PROJECT, 2024
** gui
** File description:
** Player
*/

#include "Player.hpp"

std::map<std::string, Onyx::Player::Color> Onyx::Player::_colorMap = {};
static int currentColor = 1;

Onyx::Player::Player(const int& id, const std::string &teamName, const EGE::Maths::Vector2<int>& position, const std::string& rotation) : _teamName(teamName) , _id(id)
{
    this->_level = 1;
    memset(this->_quantity, 0, sizeof(this->_quantity));
    if (Onyx::Player::_items.empty()) {
        Onyx::Player::_items.push_back(std::make_shared<Onyx::Item>(EGE::Maths::Vector2<int>(0, 0), Onyx::Item::TYPE::FOOD));
        Onyx::Player::_items.push_back(std::make_shared<Onyx::Item>(EGE::Maths::Vector2<int>(0, 0), Onyx::Item::TYPE::LINEMATE));
        Onyx::Player::_items.push_back(std::make_shared<Onyx::Item>(EGE::Maths::Vector2<int>(0, 0), Onyx::Item::TYPE::DERAUMERE));
        Onyx::Player::_items.push_back(std::make_shared<Onyx::Item>(EGE::Maths::Vector2<int>(0, 0), Onyx::Item::TYPE::SIBUR));
        Onyx::Player::_items.push_back(std::make_shared<Onyx::Item>(EGE::Maths::Vector2<int>(0, 0), Onyx::Item::TYPE::MENDIANE));
        Onyx::Player::_items.push_back(std::make_shared<Onyx::Item>(EGE::Maths::Vector2<int>(0, 0), Onyx::Item::TYPE::PHIRAS));
        Onyx::Player::_items.push_back(std::make_shared<Onyx::Item>(EGE::Maths::Vector2<int>(0, 0), Onyx::Item::TYPE::THYSTAME));
    }
    if (Player::_colorMap[teamName] == 0) {
        Player::_colorMap[teamName] = static_cast<Color>(currentColor++);
    }
    if (Player::_colorMap[teamName] >= Onyx::Player::Color::LAST) {
        throw Onyx::PlayerError("The GUI does not support more than " + std::to_string(static_cast<int>(Onyx::Player::Color::LAST) - 1) + " teams.");
    }
    this->_color = Player::_colorMap[teamName];
    std::string mtl = Utils::getFileContent("./assets/models/player/lvl" + std::to_string(this->_level) + "/lvl" + std::to_string(this->_level) + ".mtl");
    this->_setColor(mtl);
    Utils::setFileContent("./assets/models/player/lvl" + std::to_string(this->_level) + "/lvl" + std::to_string(this->_level) + ".mtl", mtl, false);
    this->_position = EGE::Maths::Vector3<float>(position.x * CELL_SIZE, 2, position.y * CELL_SIZE);
    if (rotation.size() != 1)
        throw Onyx::PlayerError("Invalid rotation: " + rotation);
    switch (rotation[0]) {
        case 'S':
            this->_rotation = EGE::Maths::Vector3<float>(0.0f, 0.0f, 0.0f);
            break;
        case 'E':
            this->_rotation = EGE::Maths::Vector3<float>(0.0f, 90.0f, 0.0f);
            break;
        case 'N':
            this->_rotation = EGE::Maths::Vector3<float>(0.0f, 180.0f, 0.0f);
            break;
        case 'W':
            this->_rotation = EGE::Maths::Vector3<float>(0.0f, 270.0f, 0.0f);
            break;
        default:
            throw Onyx::PlayerError("Invalid rotation: " + rotation);
            break;
    }
    this->_model = std::make_shared<EGE::Model>("./assets/models/player/lvl" + std::to_string(this->_level) + "/lvl" + std::to_string(this->_level) + ".obj", this->_position, this->_rotation, this->_scale, false, true);
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
    this->_model = std::make_shared<EGE::Model>("./assets/models/player/lvl" + std::to_string(this->_level) + "/lvl" + std::to_string(this->_level) + ".obj", this->_position, this->_rotation, this->_scale, false, true);
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

void Onyx::Player::setID(const int &id)
{
    this->_id = id;
}

int Onyx::Player::getID()
{
    return this->_id;
}

int Onyx::Player::getQuantity(Onyx::Item::TYPE type)
{
    return this->_quantity[type];
}

void Onyx::Player::setInventory(int quantity, Onyx::Item::TYPE type)
{
    this->_quantity[type] = quantity;
}

void Onyx::Player::getInventory()
{
    for (auto &item : this->_items) {
        this->_quantity[item->getType()] = item->getQuantity();
    }
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
        newFile += "epitech_blue.png";
        break;
    default:
        break;
    }
    fileContent = std::regex_replace(fileContent, std::regex("map_Kd .+"), "map_Kd " + newFile);
}