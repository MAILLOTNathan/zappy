/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** EntityVR
*/

#ifndef ENTITYVR_HPP_
#define ENTITYVR_HPP_

    #include "Maths/Vector3.hpp"
    #include "ModelVR.hpp"
    #include "Shader.hpp"


class EntityVR {
    public:
        ~EntityVR() = default;

        virtual void update(std::shared_ptr<EGE::Shader> shader);

        virtual void setPosition(const EGE::Maths::Vector3<float>& position);

        virtual EGE::Maths::Vector3<float> getPosition();

    protected:
        std::shared_ptr<EGE::ModelVR> _model;
        EGE::Maths::Vector3<float> _position;
    private:
};

#endif /* !ENTITYVR_HPP_ */
