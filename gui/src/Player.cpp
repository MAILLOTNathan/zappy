/*
** EPITECH PROJECT, 2024
** gui
** File description:
** Player
*/

#include "Player.hpp"

std::map<std::string, Onyx::Player::Color> Onyx::Player::_colorMap = {};
std::vector<std::shared_ptr<Onyx::Item>> Onyx::Player::_items = {};
static int currentColor = 1;

Onyx::Player::Player(int id, const std::string &teamName, const EGE::Maths::Vector2<int>& position, const std::string& rotation, float timeUnit) : _teamName(teamName)
{
    this->_level = 1;
    memset(this->_quantity, 0, sizeof(this->_quantity));
    this->_items.push_back(std::make_shared<Onyx::Item>(EGE::Maths::Vector2<int>(0, 0), Onyx::Item::TYPE::FOOD));
    this->_items.push_back(std::make_shared<Onyx::Item>(EGE::Maths::Vector2<int>(0, 0), Onyx::Item::TYPE::LINEMATE));
    this->_items.push_back(std::make_shared<Onyx::Item>(EGE::Maths::Vector2<int>(0, 0), Onyx::Item::TYPE::DERAUMERE));
    this->_items.push_back(std::make_shared<Onyx::Item>(EGE::Maths::Vector2<int>(0, 0), Onyx::Item::TYPE::SIBUR));
    this->_items.push_back(std::make_shared<Onyx::Item>(EGE::Maths::Vector2<int>(0, 0), Onyx::Item::TYPE::MENDIANE));
    this->_items.push_back(std::make_shared<Onyx::Item>(EGE::Maths::Vector2<int>(0, 0), Onyx::Item::TYPE::PHIRAS));
    this->_items.push_back(std::make_shared<Onyx::Item>(EGE::Maths::Vector2<int>(0, 0), Onyx::Item::TYPE::THYSTAME));
    if (Player::_colorMap[teamName] == 0) {
        Player::_colorMap[teamName] = static_cast<Color>(currentColor++);
    }
    if (Player::_colorMap[teamName] >= Onyx::Player::Color::LAST) {
        throw Onyx::PlayerError("The GUI does not support more than " + std::to_string(static_cast<int>(Onyx::Player::Color::LAST) - 1) + " teams.");
    }
    this->_id = id;
    this->_color = Player::_colorMap[teamName];
    std::string mtl = Utils::getFileContent("./assets/models/player/lvl" + std::to_string(this->_level) + "/lvl" + std::to_string(this->_level) + ".mtl");
    this->_setColor(mtl);
    Utils::setFileContent("./assets/models/player/lvl" + std::to_string(this->_level) + "/lvl" + std::to_string(this->_level) + ".mtl", mtl, false);
    this->_position = EGE::Maths::Vector3<float>(position.x * CELL_SIZE, 2, position.y * CELL_SIZE);
    this->_pos = position;
    this->_deltaTime = 0.0f;
    if (rotation.size() != 1)
        throw Onyx::PlayerError("Invalid rotation: " + rotation);
    this->_model = std::make_shared<EGE::Model>("./assets/models/player/lvl" + std::to_string(this->_level) + "/lvl" + std::to_string(this->_level) + ".obj", this->_position, this->_rotation, this->_scale, false, true);
    this->setRotation(rotation);
    this->isAnimated = false;
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

void Onyx::Player::forward()
{
}

void Onyx::Player::left()
{
    switch (this->_rotationString[0]) {
        case 'S':
            this->setRotation("E");
            break;
        case 'E':
            this->setRotation("N");
            break;
        case 'N':
            this->setRotation("W");
            break;
        case 'W':
            this->setRotation("S");
            break;
        default:
            throw Onyx::PlayerError("Invalid rotation: " + this->_rotationString);
            break;
    }
}

void Onyx::Player::right()
{
    switch (this->_rotationString[0]) {
        case 'S':
            this->setRotation("W");
            break;
        case 'E':
            this->setRotation("S");
            break;
        case 'N':
            this->setRotation("E");
            break;
        case 'W':
            this->setRotation("N");
            break;
        default:
            throw Onyx::PlayerError("Invalid rotation: " + this->_rotationString);
            break;
    }
}

void Onyx::Player::setDelta(float deltaTime)
{
    this->_deltaTime = deltaTime;
}

float Onyx::Player::getDelta()
{
    return this->_deltaTime;
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

void Onyx::Player::setTimeUnit(int timeUnit)
{
    this->_timeUnit = timeUnit;
}

int Onyx::Player::getTimeUnit()
{
    return this->_timeUnit;
}

int Onyx::Player::getQuantity(Onyx::Item::TYPE type)
{
    return this->_quantity[type];
}

void Onyx::Player::setInventory(int quantity, Onyx::Item::TYPE type)
{
    this->_quantity[type] = quantity;
}



// void Onyx::Player::getInventory()
// {
//     for (auto &item : this->_items) {
//         this->_quantity[item->getType()] = item->getQuantity();
//     }
// }

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

void Onyx::Player::setRotation(const std::string& rotation)
{
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
    this->_rotationString = rotation;
    this->_model->setRotation(this->_rotation);
}

EGE::Maths::Vector3<float> Onyx::Player::getRotation()
{
    return this->_rotation;
}

void Onyx::Player::setRotationString(const std::string& rotation)
{
    this->_rotationString = rotation;
}

std::string Onyx::Player::getRotationString()
{
    return this->_rotationString;
}

void Onyx::Player::setPos(EGE::Maths::Vector2<int> pos)
{
    this->_pos = pos;
    this->setPosition(EGE::Maths::Vector3<float>(pos.x * CELL_SIZE, 2, pos.y * CELL_SIZE));
}

EGE::Maths::Vector2<int> Onyx::Player::getPos()
{
    return this->_pos;
}

int Onyx::Player::getId()
{
    return this->_id;
}

std::string Onyx::Player::getAnimationString(Onyx::Player::Animation animation)
{
    switch (animation) {
        case Onyx::Player::Animation::FORWARD_NORTH:
            return "FORWARD_NORTH";
        case Onyx::Player::Animation::FORWARD_SOUTH:
            return "FORWARD_SOUTH";
        case Onyx::Player::Animation::FORWARD_EAST:
            return "FORWARD_EAST";
        case Onyx::Player::Animation::FORWARD_WEST:
            return "FORWARD_WEST";
        case Onyx::Player::Animation::LEFT:
            return "LEFT";
        case Onyx::Player::Animation::RIGHT:
            return "RIGHT";
        default:
            return "UNKNOWN";
    }
}