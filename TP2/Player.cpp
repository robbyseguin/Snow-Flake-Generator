#include <raylib.h>
#include <cassert>
#include <cmath>

#include "Globals.h"
#include "Player.h"

using namespace SF;

Player::Player(double x, double y) 
    : GameObject{}
    , _inputs{false}
    , _isJumping{false}
{
    _w = 70;
    _h = 50;

    _colorR = 0;
    _colorG = 0.63;
    _colorB = 0.8;
    _colorA = 1;

    _ay = +1000;
}

void Player::update()
{
    float dt = GetFrameTime();

    // Process input
    _ax = _inputs.left * -1000 + _inputs.right * 1000;

    if (!_isJumping && _inputs.jump) 
    {
        _vy = -600;
        _isJumping = true;
    }

    if (_inputs.down) 
    {
        if (_h == 50)
            _y += 25;
        _h = 25;
        _ay = +1500;
    } 
    else 
    {
        if (_h == 25)
            _y -= 25;
        _h = 50;
        _ay = +1000;
    }

    GameObject::update();

    // Damping
    if (!_inputs.left && !_inputs.right) 
    {
        double sign_vx = copysign(1, _vx);

        _vx -= dt * sign_vx * 300;

        // Sign change : set to zero
        if(copysign(1, _vx) != sign_vx)
            _vx = 0;
    }

    if (_vx > 350)
        _vx = 350;
    if (_vx < -350)
        _vx = -350;

    if (_x < 0) 
    {
        _x = 0;
        _vx *= -0.5;
    }

    if (_x + _w > SCREEN_WIDTH) 
    {
        _x = SCREEN_WIDTH - _w;
        _vx *= -0.5;
    }

    if (_y + _h > SCREEN_HEIGHT) 
    {
        _y = SCREEN_HEIGHT - _h;
        _vy = 0;
        _isJumping = false;
    }
}

void Player::setPosition(double x, double y)
{
    _x = x;
    _y = y;
}

void Player::setDirection(double l, double r, double d, double j)
{
    _inputs.left  = l;
    _inputs.right = r;
    _inputs.down  = d;
    _inputs.jump  = j;
}

void Player::render() const
{
    GameObject::render();

    Rectangle r;
    r.x         = (float) _x;
    r.y         = (float) _y;
    r.width     = (float) _w;
    r.height    = (float) _h;

    Color c1
    {
        (uchar)(_colorR * 255),
        (uchar)(_colorG * 255),
        (uchar)(_colorB * 255),
        (uchar)(_colorA * 255)
    };

    // Head
    DrawRectangleRec(r, c1);

    Color c2{0, 0, 0, 255};

    int offset = 0;

    if (_vx > 0)
        offset = 3;
    else if (_vx < 0)
        offset = -3;

    // Eyes
    r.width  = 6;
    r.height = 6;

    // Left eye
    r.x = (float) (_x + _w/4.0 - 3) + offset;
    r.y = (float) (_y + _h/3.0 - 3);
    DrawRectangleRec(r, c2);

    // Right eye
    r.x = (float) (_x + 3*_w/4.0 - 3) + offset;
    DrawRectangleRec(r, c2);

    // Mouth
    int mouthY = (int)(_y + 3*_h/4.0);
    DrawLine((int)(_x + _w/4.0), mouthY, (int)(_x + 3*_w/4.0), mouthY, c2);
}

void Player::collide(Player&)
{
    assert(0);
}
