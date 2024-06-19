/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** PlayerVR
*/

#include "PlayerVR.hpp"

std::map<std::string, PlayerVR::Color> PlayerVR::_colorMap = {};
std::vector<std::shared_ptr<ItemVR>> PlayerVR::_items = {};
static int currentColor = 1;


PlayerVR::PlayerVR(int id, const std::string &teamName, const EGE::Maths::Vector2<int>& position, const std::string& rotation, float timeUnit, std::shared_ptr<EGE::WindowVR> window) : _teamName(teamName)
{
    this->_level = 1;
    memset(this->_quantity, 0, sizeof(this->_quantity));
    this->_items.push_back(std::make_shared<ItemVR>(EGE::Maths::Vector2<int>(0, 0), ItemVR::TYPE::FOOD, window));
    this->_items.push_back(std::make_shared<ItemVR>(EGE::Maths::Vector2<int>(0, 0), ItemVR::TYPE::LINEMATE, window));
    this->_items.push_back(std::make_shared<ItemVR>(EGE::Maths::Vector2<int>(0, 0), ItemVR::TYPE::DERAUMERE, window));
    this->_items.push_back(std::make_shared<ItemVR>(EGE::Maths::Vector2<int>(0, 0), ItemVR::TYPE::SIBUR, window));
    this->_items.push_back(std::make_shared<ItemVR>(EGE::Maths::Vector2<int>(0, 0), ItemVR::TYPE::MENDIANE, window));
    this->_items.push_back(std::make_shared<ItemVR>(EGE::Maths::Vector2<int>(0, 0), ItemVR::TYPE::PHIRAS, window));
    this->_items.push_back(std::make_shared<ItemVR>(EGE::Maths::Vector2<int>(0, 0), ItemVR::TYPE::THYSTAME, window));
    if (PlayerVR::_colorMap[teamName] == 0) {
        PlayerVR::_colorMap[teamName] = static_cast<Color>(currentColor++);
    }
    if (PlayerVR::_colorMap[teamName] >= PlayerVR::Color::LAST) {
        throw PlayerVRError("The GUI does not support more than " + std::to_string(static_cast<int>(PlayerVR::Color::LAST) - 1) + " teams.");
    }
    this->_id = id;
    this->_color = PlayerVR::_colorMap[teamName];
    std::string mtl = EGE::UtilsVR::readAssetFile("models/player/lvl" + std::to_string(this->_level) + "/lvl" + std::to_string(this->_level) + ".mtl");
    this->_setColor(mtl);
    gMemoryIOSystem->addFile("models/player/lvl" + std::to_string(this->_level) + "/lvl" + std::to_string(this->_level) + ".mtl", mtl);
    this->_position = EGE::Maths::Vector3<float>(position.x * CELL_SIZE, 1, position.y * CELL_SIZE);
    this->_pos = position;
    this->_deltaTime = 0.0f;
    if (rotation.size() != 1)
        throw PlayerVRError("Invalid rotation: " + rotation);
    this->_model = std::make_shared<EGE::ModelVR>("models/player/lvl" + std::to_string(this->_level) + "/lvl" + std::to_string(this->_level) + ".obj", this->_position, this->_rotation, this->_scale, false, true);
    window->addModel("Map", this->_model);
    this->_window = window;
    this->setRotation(rotation);
    this->isAnimated = false;
}

PlayerVR::~PlayerVR()
{
}

void PlayerVR::update(std::shared_ptr<EGE::Shader> shader)
{
}

void PlayerVR::evolve()
{
    this->_level++;
    std::string mtl = EGE::UtilsVR::readAssetFile("models/player/lvl" + std::to_string(this->_level) + "/lvl" + std::to_string(this->_level) + ".mtl");
    this->_setColor(mtl);
    gMemoryIOSystem->addFile("models/player/lvl" + std::to_string(this->_level) + "/lvl" + std::to_string(this->_level) + ".mtl", mtl);
    this->_window->removeModel("Map", this->_model);
    this->_model = std::make_shared<EGE::ModelVR>("models/player/lvl" + std::to_string(this->_level) + "/lvl" + std::to_string(this->_level) + ".obj", this->_position, this->_rotation, this->_scale, false, true);
    this->_window->addModel("Map", this->_model);
}

void PlayerVR::forward()
{
}

void PlayerVR::left()
{
}

void PlayerVR::right()
{
}

void PlayerVR::setDelta(float deltaTime)
{
    this->_deltaTime = deltaTime;
}

float PlayerVR::getDelta() const
{
    return this->_deltaTime;
}

void PlayerVR::setLevel(int level)
{
    this->_level = level;
}

int PlayerVR::getLevel() const
{
    return this->_level;
}

void PlayerVR::setColor(const Color &color)
{
    this->_color = color;
}

PlayerVR::Color PlayerVR::getColor() const
{
    return this->_color;
}

void PlayerVR::setTeamName(const std::string &teamName)
{
    this->_teamName = teamName;
}

std::string PlayerVR::getTeamName() const
{
    return this->_teamName;
}

void PlayerVR::setTimeUnit(int timeUnit)
{
    this->_timeUnit = timeUnit;
}

int PlayerVR::getTimeUnit() const
{
    return this->_timeUnit;
}

void PlayerVR::setPos(EGE::Maths::Vector2<int> pos)
{
    this->_pos = pos;
    this->setPosition(EGE::Maths::Vector3<float>(pos.x * CELL_SIZE, 0.8, pos.y * CELL_SIZE));
}

EGE::Maths::Vector2<int> PlayerVR::getPos() const
{
    return this->_pos;
}

void PlayerVR::setRotation(const std::string& rotation)
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
            throw PlayerVRError("Invalid rotation: " + rotation);
            break;
    }
    this->_rotationString = rotation;
    this->_model->setRotation(this->_rotation);
}

std::string PlayerVR::getRotation() const
{
    return this->_rotationString;
}

void PlayerVR::setRotationString(const std::string &rotation)
{
    this->_rotationString = rotation;
    this->setRotation(this->_rotationString);
}

std::string PlayerVR::getRotationString() const
{
    return this->_rotationString;
}

int PlayerVR::getId() const
{
    return this->_id;
}

int PlayerVR::getQuantity(ItemVR::TYPE type)
{
    return this->_quantity[type];
}

void PlayerVR::setInventory(int quantity, ItemVR::TYPE type)
{
    this->_quantity[type] = quantity;
}

std::string PlayerVR::getAnimationString(Animation animation)
{
    switch (animation) {
    case Animation::LEFT:
        return "left";
    case Animation::RIGHT:
        return "right";
    case Animation::BROADCAST:
        return "broadcast";
    case Animation::INCANTATION:
        return "incantation";
    case Animation::EXPULSE:
        return "expulse";
    case Animation::FORWARD_EAST:
        return "forward_east";
    case Animation::FORWARD_SOUTH:
        return "forward_south";
    case Animation::FORWARD_WEST:
        return "forward_west";
    default:
        return "";
    }
}


void PlayerVR::_setColor(std::string &fileContent)
{
    std::string newFile = "colors/";
    switch (this->_color) {
    case PlayerVR::Color::RED:
        newFile += "red.png";
        break;
    case PlayerVR::Color::GREEN:
        newFile += "green.png";
        break;
    case PlayerVR::Color::BLUE:
        newFile += "blue.png";
        break;
    case PlayerVR::Color::PINK:
        newFile += "pink.png";
        break;
    case PlayerVR::Color::YELLOW:
        newFile += "yellow.png";
        break;
    case PlayerVR::Color::ORANGE:
        newFile += "orange.png";
        break;
    case PlayerVR::Color::PURPLE:
        newFile += "purple.png";
        break;
    case PlayerVR::Color::CYAN:
        newFile += "cyan.png";
        break;
    default:
        break;
    }
    fileContent = std::regex_replace(fileContent, std::regex("diffuseColorMap: .*"), "diffuseColorMap: " + newFile);
}
