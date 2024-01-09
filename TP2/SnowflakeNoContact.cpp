#include <iostream>

#include "Globals.h"
#include "Player.h"
#include "Snowflake.h"
#include "SnowflakeNoContact.h"

using namespace std;
using namespace SF;

SnowflakeNoContact::SnowflakeNoContact() : Snowflake{}
{
    _colorA = 0.2;
}

void SnowflakeNoContact::collide(Player&) {}
