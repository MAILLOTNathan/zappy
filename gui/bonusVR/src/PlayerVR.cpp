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


PlayerVR::PlayerVR(int id, const std::string &teamName, const EGE::Maths::Vector2<int>& position, const std::string& rotation, int level, float timeUnit, std::shared_ptr<EGE::WindowVR> window, std::shared_ptr<EGE::Shader> shader) : _teamName(teamName)
{
    __android_log_print(ANDROID_LOG_INFO, "MYTAG", "in player constructor\n");
    this->_level = level;
    __android_log_print(ANDROID_LOG_FATAL, "DEBUG", "PlayerVR.cpp:19\n");
    memset(this->_quantity, 0, sizeof(this->_quantity));
    __android_log_print(ANDROID_LOG_FATAL, "DEBUG", "PlayerVR.cpp:21\n");
    this->_items.push_back(std::make_shared<ItemVR>(EGE::Maths::Vector2<int>(0, 0), ItemVR::TYPE::FOOD, window));
    __android_log_print(ANDROID_LOG_FATAL, "DEBUG", "PlayerVR.cpp:23\n");
    this->_items.push_back(std::make_shared<ItemVR>(EGE::Maths::Vector2<int>(0, 0), ItemVR::TYPE::LINEMATE, window));
    __android_log_print(ANDROID_LOG_FATAL, "DEBUG", "PlayerVR.cpp:25\n");
    this->_items.push_back(std::make_shared<ItemVR>(EGE::Maths::Vector2<int>(0, 0), ItemVR::TYPE::DERAUMERE, window));
    __android_log_print(ANDROID_LOG_FATAL, "DEBUG", "PlayerVR.cpp:27\n");
    this->_items.push_back(std::make_shared<ItemVR>(EGE::Maths::Vector2<int>(0, 0), ItemVR::TYPE::SIBUR, window));
    __android_log_print(ANDROID_LOG_FATAL, "DEBUG", "PlayerVR.cpp:29\n");
    this->_items.push_back(std::make_shared<ItemVR>(EGE::Maths::Vector2<int>(0, 0), ItemVR::TYPE::MENDIANE, window));
    __android_log_print(ANDROID_LOG_FATAL, "DEBUG", "PlayerVR.cpp:31\n");
    this->_items.push_back(std::make_shared<ItemVR>(EGE::Maths::Vector2<int>(0, 0), ItemVR::TYPE::PHIRAS, window));
    __android_log_print(ANDROID_LOG_FATAL, "DEBUG", "PlayerVR.cpp:33\n");
    this->_items.push_back(std::make_shared<ItemVR>(EGE::Maths::Vector2<int>(0, 0), ItemVR::TYPE::THYSTAME, window));
    __android_log_print(ANDROID_LOG_FATAL, "DEBUG", "PlayerVR.cpp:35\n");
    if (PlayerVR::_colorMap[teamName] == 0) {
        __android_log_print(ANDROID_LOG_FATAL, "DEBUG", "PlayerVR.cpp:37\n");
        PlayerVR::_colorMap[teamName] = static_cast<Color>(currentColor++);
        __android_log_print(ANDROID_LOG_FATAL, "DEBUG", "PlayerVR.cpp:39\n");
    }
    __android_log_print(ANDROID_LOG_FATAL, "DEBUG", "PlayerVR.cpp:41\n");
    if (PlayerVR::_colorMap[teamName] >= PlayerVR::Color::LAST) {
        __android_log_print(ANDROID_LOG_FATAL, "DEBUG", "PlayerVR.cpp:43\n");
        throw PlayerVRError("The GUI does not support more than " + std::to_string(static_cast<int>(PlayerVR::Color::LAST) - 1) + " teams.");
    }
    __android_log_print(ANDROID_LOG_FATAL, "DEBUG", "PlayerVR.cpp:46\n");
    this->_id = id;
    __android_log_print(ANDROID_LOG_FATAL, "DEBUG", "PlayerVR.cpp:48\n");
    this->_color = PlayerVR::_colorMap[teamName];
    __android_log_print(ANDROID_LOG_FATAL, "DEBUG", "PlayerVR.cpp:50\n");
    std::string mtl = EGE::UtilsVR::readAssetFile("models/player/lvl" + std::to_string(this->_level) + "/lvl" + std::to_string(this->_level) + ".mtl");
    __android_log_print(ANDROID_LOG_FATAL, "DEBUG", "PlayerVR.cpp:52\n");
    this->_setColor(mtl);
    __android_log_print(ANDROID_LOG_FATAL, "DEBUG", "PlayerVR.cpp:54\n");
    gMemoryIOSystem->addFile("models/player/lvl" + std::to_string(this->_level) + "/lvl" + std::to_string(this->_level) + ".mtl", mtl);
    __android_log_print(ANDROID_LOG_FATAL, "DEBUG", "PlayerVR.cpp:56\n");
    this->_position = EGE::Maths::Vector3<float>(position.x * CELL_SIZE, CELL_SIZE / 2.5f, position.y * CELL_SIZE);
    __android_log_print(ANDROID_LOG_FATAL, "DEBUG", "PlayerVR.cpp:58\n");
    this->_pos = position;
    __android_log_print(ANDROID_LOG_FATAL, "DEBUG", "PlayerVR.cpp:60\n");
    this->_deltaTime = 0.0f;
    __android_log_print(ANDROID_LOG_FATAL, "DEBUG", "PlayerVR.cpp:62\n");
    if (rotation.size() != 1) {
        __android_log_print(ANDROID_LOG_FATAL, "DEBUG", "PlayerVR.cpp:64\n");
        throw PlayerVRError("Invalid rotation: " + rotation);
    }
    this->_model = std::make_shared<EGE::ModelVR>("models/player/lvl" + std::to_string(this->_level) + "/lvl" + std::to_string(this->_level) + ".obj", this->_position, this->_rotation, this->_scale, false, true);
    __android_log_print(ANDROID_LOG_FATAL, "DEBUG", "PlayerVR.cpp:68\n");
    window->addDrawable("player_" + std::to_string(id), shader, [this] (const std::shared_ptr<EGE::Shader> shader, float view_proj[16]) {
        __android_log_print(ANDROID_LOG_INFO, "MYTAG", "draw a player\n");
        shader->use();
        shader->setMat("view_proj", EGE::Maths::Matrix<4, 4, float>(view_proj));
        this->_model->draw(*shader.get());
    });
    __android_log_print(ANDROID_LOG_FATAL, "DEBUG", "PlayerVR.cpp:75\n");
    this->_window = window;
    __android_log_print(ANDROID_LOG_FATAL, "DEBUG", "PlayerVR.cpp:77\n");
    this->setRotation(rotation);
    __android_log_print(ANDROID_LOG_FATAL, "DEBUG", "PlayerVR.cpp:79\n");
    this->isAnimated = false;
}

PlayerVR::~PlayerVR()
{
}

void PlayerVR::update(std::shared_ptr<EGE::Shader> shader)
{
}


void PlayerVR::evolve(std::shared_ptr<EGE::Shader> shader)
{
    this->_level++;
    std::string mtl = EGE::UtilsVR::readAssetFile("models/player/lvl" + std::to_string(this->_level) + "/lvl" + std::to_string(this->_level) + ".mtl");
    this->_setColor(mtl);
    gMemoryIOSystem->addFile("models/player/lvl" + std::to_string(this->_level) + "/lvl" + std::to_string(this->_level) + ".mtl", mtl);
    this->_window->removeDrawable("player_" + std::to_string(this->_id));
    this->_model = std::make_shared<EGE::ModelVR>("models/player/lvl" + std::to_string(this->_level) + "/lvl" + std::to_string(this->_level) + ".obj", this->_position, this->_rotation, this->_scale, false, true);
    this->_window->addDrawable("player_" + std::to_string(this->_id), shader, [this] (const std::shared_ptr<EGE::Shader> shader, float view_proj[16]) {
        this->_model->draw(*shader.get());
    });
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

void PlayerVR::setLevel(int level, std::shared_ptr<EGE::Shader> shader)
{
    this->_level = level;
    this->_window->removeDrawable("player_" + std::to_string(this->_id));
    std::string mtl = EGE::UtilsVR::readAssetFile("models/player/lvl" + std::to_string(this->_level) + "/lvl" + std::to_string(this->_level) + ".mtl");
    this->_setColor(mtl);
    gMemoryIOSystem->addFile("models/player/lvl" + std::to_string(this->_level) + "/lvl" + std::to_string(this->_level) + ".mtl", mtl);
    this->_model = std::make_shared<EGE::ModelVR>("models/player/lvl" + std::to_string(this->_level) + "/lvl" + std::to_string(this->_level) + ".obj", this->_position, this->_rotation, this->_scale, false, true);
    this->_window->addDrawable("player_" + std::to_string(this->_id), shader, [this] (const std::shared_ptr<EGE::Shader> shader, float view_proj[16]) {
        this->_model->draw(*shader.get());
    });
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
    fileContent = std::regex_replace(fileContent, std::regex("map_Kd .+"), "map_Kd " + newFile);
}
