#include <iostream>
#include <raylib.h>
#include <Code_Utilities_Light_v2.h>

#include "Globals.h"
#include "GameSnow.h"
#include "Player.h"
#include "Snowflake.h"
#include "SnowflakeRebound.h"
#include "SnowflakeNoContact.h"
#include "SnowflakeSine.h"

using namespace std;
using namespace SF;

GameSnow::GameSnow()
    : _pause(false)
    , _p(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2)
    , _snowPool(nullptr), _snowPoolNoContact(nullptr), _snowPoolRebound(nullptr), _snowPoolSine(nullptr)
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_TITLE);
    SetTargetFPS(FPS); // Set our game to run at 30 frames-per-second
    init(_presets[0]);

    BdB::srandInt((uint)time(0));
}

GameSnow::~GameSnow()
{
    CloseWindow();
}

void GameSnow::init(uint n)
{
    cout << "Init with " << n << " particles" << endl;
   

    //_snowflakes.clear();

    _snowPool = make_unique<SnowflakePool<Snowflake>>(n);
    _snowPoolNoContact = make_unique<SnowflakePool<SnowflakeNoContact>>(n);
    _snowPoolRebound = make_unique<SnowflakePool<SnowflakeRebound>>(n);
    _snowPoolSine = make_unique<SnowflakePool<SnowflakeSine>>(n);

    for (uint i{}; i<n; ++i)
    {
        double x = BdB::randInt(SCREEN_WIDTH);
        double y = BdB::randInt(10, SCREEN_HEIGHT);

        addSnowflake(x, y);
    }
}

void GameSnow::addSnowflake()
{
    // Default : top of the screen
    addSnowflake(BdB::randInt(SCREEN_WIDTH), -10);
}

void GameSnow::addSnowflake(double x, double y)
{   
    int rnd = BdB::randInt(RAND_MAX);
    
        if (rnd < RAND_MAX / 10)       
            _snowPoolNoContact->spawn(x, y);          
         
        else if (rnd < RAND_MAX / 5 * 2)       
            _snowPoolRebound->spawn(x, y);                      
        
        else if (rnd < RAND_MAX / 2)       
            _snowPoolSine->spawn(x, y);                      
        
        else       
            _snowPool->spawn(x, y);                                
                 
}
template<typename T>
uint GameSnow::countActiveSnowFlake(T& pool)
{
    uint counter = {};
    for (uint i = {}; i < pool->getMaxSize(); ++i)
    {
        if (pool->get(i).isActive())
        {
            ++counter;
        }
    }
    return uint(counter);
}

int GameSnow::getClickX()
{
    return std::clamp(GetMouseX(), 0, SCREEN_WIDTH);

}

int GameSnow::getClickY()
{
    return std::clamp(GetMouseY(), 0, SCREEN_HEIGHT);
}

void GameSnow::handleInput()
{
    // Mouse
    if (IsMouseButtonDown(MOUSE_LEFT_BUTTON))
       _p.setPosition(GetMouseX(), GetMouseY());

    // Direction pressed
    _p.setDirection(
        IsKeyDown(KeyboardKey::KEY_LEFT),
        IsKeyDown(KeyboardKey::KEY_RIGHT),
        IsKeyDown(KeyboardKey::KEY_DOWN),
        (IsKeyDown(KeyboardKey::KEY_UP) || IsKeyDown(KeyboardKey::KEY_SPACE))
    );

    // Key pressed
    int key = GetKeyPressed();
    switch (key)
    {
            // Pause
        case KeyboardKey::KEY_P:            
            _pause = !_pause;// Pause
            break;
        case KeyboardKey::KEY_ESCAPE:
            _keepPlaying = false;
            break;

        // Number of particles
        case KeyboardKey::KEY_KP_1:
        case KeyboardKey::KEY_KP_2:
        case KeyboardKey::KEY_KP_3:
        case KeyboardKey::KEY_KP_4:
        case KeyboardKey::KEY_KP_5:
        case KeyboardKey::KEY_KP_6:
        case KeyboardKey::KEY_KP_7:
        case KeyboardKey::KEY_KP_8:
        case KeyboardKey::KEY_KP_9:
            init(_presets[key - KeyboardKey::KEY_KP_1]);
            break;
    }
}

bool GameSnow::shouldDelete(const GameObject* ptr)
{
    return ptr->shouldDelete();
}

// Function to add the 4 snowflake pools by template
template<typename T>
void updateCollisions(T& pool , Player p)
{
    for (int i = 0; i < pool->getMaxSize(); ++i)
    {
        pool->get(i).update();
    }

    // Collisions
    for (int i = 0; i < pool->getMaxSize(); ++i)
    {
        pool->get(i).testCollision(p);
    }
}

template <typename T>
void updateDestroy(T& pool)
{
    
    for (int i = {}; i < pool->getMaxSize(); ++i)
    {
        if (pool->get(i).shouldDelete())
        {
            pool->destroy(i);          
        }
    }
    
}

void GameSnow::update()
{
    if (_pause) 
        return;

    //double delta_t = dt / 1000.0;

    // Physics
    _p.update();

    updateCollisions(_snowPool, _p);
    updateCollisions(_snowPoolNoContact, _p);
    updateCollisions(_snowPoolRebound, _p);
    updateCollisions(_snowPoolSine, _p);


    // Remove unused objects
    /*long size_before = _snowflakes.size();

    _snowflakes.erase(remove_if(_snowflakes.begin(),
                               _snowflakes.end(),
                               [](auto& ptr) {
                                   return ptr->shouldDelete();
                               }),
                     _snowflakes.end());

    long nb_new_snowflakes = size_before - _snowflakes.size();*/
    
    uint size_before = 0;
    size_before += countActiveSnowFlake(_snowPool);
    size_before += countActiveSnowFlake(_snowPoolNoContact);
    size_before += countActiveSnowFlake(_snowPoolRebound);
    size_before += countActiveSnowFlake(_snowPoolSine);

    updateDestroy(_snowPool);
    updateDestroy(_snowPoolNoContact);
    updateDestroy(_snowPoolRebound);
    updateDestroy(_snowPoolSine);
  

    long nb_new_snowflakes = size_before - (countActiveSnowFlake(_snowPool) + countActiveSnowFlake(_snowPoolNoContact) +
                                             countActiveSnowFlake(_snowPoolRebound) + countActiveSnowFlake(_snowPoolSine));
   
    for (int i{}; i < nb_new_snowflakes; ++i)
    {
        addSnowflake();
    }
}

template <typename T>
void renderPool(T& pool)
{
    for (int i = {}; i < pool->getMaxSize(); ++i)
    {
        if (pool->get(i).isActive())
        {
            pool->get(i).render();
        }
    }
}
void GameSnow::render() const
{
    BeginDrawing();
    {
        ClearBackground(BLANK);
        _p.render();
        
            renderPool(_snowPool);
        
        
            renderPool(_snowPoolNoContact);
        
        
            renderPool(_snowPoolRebound);
        
        
            renderPool(_snowPoolSine);
        
        DrawFPS(20, 20);
    }
    EndDrawing();
}