#pragma once

#include "Snowflake.h"

namespace SF
{
    class SnowflakeSine : public Snowflake
    {
    public:
        SnowflakeSine();
        void initialize(double x, double y) override;

        void update() override;
    private:
        double _timeSinceStart;
    };
}
