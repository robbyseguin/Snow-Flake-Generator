#include <iostream>
#include <Code_Utilities_Light_v2.h>

#include "Globals.h"
#include "Player.h"
#include "Snowflake.h"
#include "SnowflakeRebound.h"

using namespace std;
using namespace SF;

SnowflakeRebound::SnowflakeRebound()
    : Snowflake{}
    , _alreadyHit{false}
{  
}
void SnowflakeRebound::initialize(double x, double y)
{
    GameObject::initialize(x, y);

    _w = 3;
    _h = 6;

    _colorR = 0.8;
    _colorG = 0.8;
    _colorB = 1;
    _colorA = 0.3;

    _vy = 100 + BdB::randInt(RAND_MAX) / (double)RAND_MAX * 100;

    _h = 2;
    _w = 2;
    _colorA = 1;
    _vx = BdB::randInt(RAND_MAX) < RAND_MAX / 2 ? -30 : 30;
}

void SnowflakeRebound::update()
{
    Snowflake::update();

    if (_x < _w || _x > SCREEN_WIDTH + _w) 
    {
        _deleteMe = true;
        return;
    }

    if (_y + _h > SCREEN_HEIGHT && !_alreadyHit) 
        rebound();
    else if (_y > SCREEN_HEIGHT + _h && _alreadyHit) 
        _deleteMe = true;
}

void SnowflakeRebound::collide(Player&)
{
    if (!_alreadyHit)
        rebound();
    else
        _deleteMe = true;
}

void SnowflakeRebound::rebound()
{
    _vy *= -1;
    _ay = 300;
    _alreadyHit = true;
}
