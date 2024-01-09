#include <raylib.h>
#include <Code_Utilities_Light_v2.h>

#include "Globals.h"
#include "GameObject.h"
#include "Player.h"

using namespace SF;

GameObject::GameObject() 
    : _x{}, _y{}
    , _vx{}, _vy{}, _ax{}, _ay{}
    , _colorR{}, _colorG{}, _colorB{}, _colorA{}
    , _deleteMe{false}
    , _isActive{false}
{}

void GameObject::update()
{
	float dt = GetFrameTime();
    _vx += dt * _ax;
    _vy += dt * _ay;

    _x += dt * _vx;
    _y += dt * _vy;
}

void GameObject::render() const
{
    Color c
    { 
       (uchar) (_colorR * 255),
       (uchar) (_colorG * 255),
       (uchar) (_colorB * 255),
       (uchar) (_colorA * 255)
    };

    Rectangle r{};
    r.x         = (float) _x;
    r.y         = (float) _y;
    r.width     = (float) _w;
    r.height    = (float) _h;

    DrawRectangleRec(r, c);
}

void GameObject::testCollision(Player& p)
{
    if (isColliding(p))
        collide(p);
}

bool GameObject::isColliding(const Player& p) const
{
    // No need for vectors we already have the positons and size on the objects.
    


    return !(
        // Un à gauche de l'autre
        p._x + p._w < _x ||
        _x + _w < p._x ||
        // Un en haut de l'autre
        p._y + p._h < _y ||
        _y + _h < p._y);
}

bool GameObject::shouldDelete() const
{
    return _deleteMe;
}
bool GameObject::isActive() const
{
    return _isActive;
}
void GameObject::clear()
{
    _isActive = false;
    _deleteMe = false;
}
void GameObject::initialize(double x, double y)
{
    _x = x;
    _y = y;
    _isActive = true;
}
