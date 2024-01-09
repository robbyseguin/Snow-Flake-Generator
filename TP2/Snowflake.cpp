
#include <Code_Utilities_Light_v2.h>

#include "Globals.h"
#include "Player.h"
#include "Snowflake.h"

using namespace SF;

Snowflake::Snowflake()
    : GameObject{}
{   
}

void Snowflake::initialize(double x, double y)
{
    GameObject::initialize(x, y);

    _w = 3;
    _h = 6;

    _colorR = 0.8;
    _colorG = 0.8;
    _colorB = 1;
    _colorA = 0.3;

    _vy = 100 + BdB::randInt(RAND_MAX) / (double)RAND_MAX * 100;
}

void Snowflake::update()
{
    GameObject::update();

    if (_y > SCREEN_HEIGHT + _h) 
    {
        _deleteMe = true;
    }
}

void Snowflake::collide(Player&)
{
    _deleteMe = true;
}
