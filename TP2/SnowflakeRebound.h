#pragma once

#include "Snowflake.h"

namespace SF
{
    class SnowflakeRebound final : public Snowflake
    {
    public:
        SnowflakeRebound();
        void initialize(double x, double y) override;
        

        void update() override;
        void collide(Player&) override;

    private:
        bool _alreadyHit;
        void rebound();
    };
}
