#pragma once

#include "GameObject.h"
#include "Player.h"

namespace SF
{
    class Snowflake : public GameObject
    {
    public:
        Snowflake();      
        void initialize(double x, double y) override;

        virtual void update() override;
        virtual void collide(Player&) override;

        void clear()
        {
            _isActive = false;
            _deleteMe = false;
        }
    };
}
