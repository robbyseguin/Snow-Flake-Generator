#pragma once

#include "Snowflake.h"

namespace SF
{
    class SnowflakeNoContact final : public Snowflake
    {
    public:
        SnowflakeNoContact();
       
        void collide(Player& o) override;
    };
}
