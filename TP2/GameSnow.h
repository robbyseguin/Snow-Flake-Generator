#pragma once

#include <vector>
#include <array>
#include <memory>

#include "Globals.h"
#include "Player.h"
#include "Snowflake.h"
#include "Game.h"
#include "SnowflakePool.h"
#include "SnowflakeNoContact.h"
#include "SnowflakeRebound.h"
#include "SnowflakeSine.h"

using namespace std;
using namespace Core;

namespace SF
{
	class GameSnow final: public Game
	{
        using PresetList = std::array<ulong, 9>;
        using SnowFlakePtr = std::unique_ptr<Snowflake>;
        using SnowFlakeList = std::vector<SnowFlakePtr>;
	public:
	    GameSnow();
		~GameSnow();

	    void handleInput() override;
        void update() override;
        void render() const override;

	    void init(uint);
	    void addSnowflake();
	    void addSnowflake(double, double);
		inline static const uint MAX_OBJS = 1000000;
	private:
		template<typename T>
		uint countActiveSnowFlake(T& pool);
        int getClickX();
        int getClickY();

	    bool _pause;
	    inline static PresetList _presets = {80000, 100000, 150000, 160000, 170000, 180000, 190000, 200000, 250000};

	    Player _p;
		
		unique_ptr<SnowflakePool<Snowflake>>_snowPool;
		unique_ptr<SnowflakePool<SnowflakeNoContact>>_snowPoolNoContact;
		unique_ptr<SnowflakePool<SnowflakeRebound>>_snowPoolRebound;
		unique_ptr<SnowflakePool<SnowflakeSine>>_snowPoolSine;

		static bool shouldDelete(const GameObject* ptr);
	};
}
