#include <raylib.h>
#include <Code_Utilities_Light_v2.h>
#include <cmath>

#include "Globals.h"
#include "Player.h"
#include "Snowflake.h"
#include "SnowflakeSine.h"

using namespace SF;

SnowflakeSine::SnowflakeSine()
    : Snowflake{}
{   
}
void SnowflakeSine::initialize(double x, double y)
{
    GameObject::initialize(x, y);

    _w = 3;
    _h = 6;

    _colorR = 0.8;
    _colorG = 0.8;
    _colorB = 1;
    _colorA = 0.3;

    _vy = 100 + BdB::randInt(RAND_MAX) / (double)RAND_MAX * 100;
    _timeSinceStart = BdB::randInt(RAND_MAX) / (double)RAND_MAX * 2 * PI;
}

void SnowflakeSine::update() 
{
    float dt = GetFrameTime();
    _timeSinceStart += dt;

    _vx = 50 * sin(3 * _timeSinceStart);

    Snowflake::update();
}
