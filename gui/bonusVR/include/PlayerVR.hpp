/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** PlayerVR
*/

#ifndef PLAYERVR_HPP_
    #define PLAYERVR_HPP_

    #include "EntityVR.hpp"
    #include "MapVR.hpp"
    #include "Maths/Vector2.hpp"
    #include "Maths/Vector3.hpp"
    #include "UtilsVR.hpp"
    #include "ModelVR.hpp"
    #include "Animation.hpp"
    #include "WindowVR.hpp"

    #include <regex>

class PlayerVRError : public EGE::Error {
    public:
        PlayerVRError(const std::string& message) : EGE::Error(message) {}
};

class PlayerVR : public EntityVR {
    public:
        enum Color {
            UNDEFINED = 0,
            RED,
            GREEN,
            BLUE,
            PINK,
            YELLOW,
            ORANGE,
            PURPLE,
            CYAN,
            LAST
        };
        enum Animation {
            NONE = -1,
            FORWARD_NORTH = 0,
            LEFT,
            RIGHT,
            BROADCAST,
            INCANTATION,
            EXPULSE,
            FORWARD_EAST,
            FORWARD_SOUTH,
            FORWARD_WEST,
            MAX
        };
        PlayerVR(int id, const std::string& teamName, const EGE::Maths::Vector2<int>& position, const std::string& rotation, int level, float timeUnit, std::shared_ptr<EGE::WindowVR> window, std::shared_ptr<EGE::Shader> shader);
        ~PlayerVR();

        void update(std::shared_ptr<EGE::Shader> shader) override;

        void evolve(std::shared_ptr<EGE::Shader> shader);
        void forward();
        void left();
        void right();

        void setLevel(int level, std::shared_ptr<EGE::Shader> shader);
        int getLevel() const;

        void setColor(const Color& color);
        Color getColor() const;

        void setTeamName(const std::string& teamName);
        std::string getTeamName() const;

        void setRotation(const std::string& rotation);
        std::string getRotation() const;

        void setRotationString(const std::string& rotation);
        std::string getRotationString() const;

        void setPos(EGE::Maths::Vector2<int> pos);
        EGE::Maths::Vector2<int> getPos() const;

        void setTimeUnit(int timeUnit);
        int getTimeUnit() const;

        int getId() const;

        void setDelta(float deltaTime);
        float getDelta() const;

        int getQuantity(ItemVR::TYPE type);

        void setInventory(int quantity, ItemVR::TYPE type);

        static std::string getAnimationString(Animation animation);

        bool isAnimated;

    protected:
        void _setColor(std::string &teamName);

        int _id;
        Color _color;
        int _level;
        std::string _teamName;
        int _quantity[ItemVR::MAX];
        static std::vector<std::shared_ptr<ItemVR>> _items;
        static std::map<std::string, Color> _colorMap;
        EGE::Maths::Vector2<int> _pos;
        EGE::Maths::Vector3<float> _rotation;
        std::string _rotationString;
        const EGE::Maths::Vector3<float> _scale = {0.1f, 0.1f, 0.1f};
        float _deltaTime;
        float _timeUnit;
        std::shared_ptr<EGE::WindowVR> _window;
    private:
};

#endif /* !PLAYERVR_HPP_ */
