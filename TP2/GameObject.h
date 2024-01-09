#pragma once

namespace SF
{
    class Player;

    class GameObject
    {
    public:
        GameObject();

        virtual void update();
        virtual void render() const;
        void testCollision(Player&);

        bool shouldDelete() const;
        bool isActive() const;
        void clear();
        virtual void initialize(double x, double y);

    protected:
        bool isColliding(const Player&) const;
        virtual void collide(Player&) = 0;
        double _x;
        double _y;
        double _w, _h;
        double _vx;
        double _vy;
        double _ax;
        double _ay;

        double _colorR, _colorG, _colorB, _colorA;
        bool _deleteMe{ false };
        bool _isActive{ false };
    };
}
