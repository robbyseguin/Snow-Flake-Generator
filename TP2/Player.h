#pragma once

#include <string>

#include "GameObject.h"

namespace SF
{
    class Player : public GameObject
    {
    public:
        Player(double x, double y);

        void update() override;
        void render() const override;

        void collide(Player& o) override;

        void setPosition(double x, double y);
        void setDirection(double l, double r, double d, double j);

    private:
        struct Inputs
        {
            bool left;
            bool right;
            bool down;
            bool jump;
        } _inputs;

        bool _isJumping;
    };
}
