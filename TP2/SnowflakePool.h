#pragma once
#pragma once
#include <iostream>
#include <raylib.h>
#include <Code_Utilities_Light_v2.h>
#include "Snowflake.h"

using namespace std;

namespace SF
{
    
    template<typename T>
    class SnowflakePool
    {
    public:

        SnowflakePool(uint n) : _pool(make_unique<T[]>(n)), _nbParticles(0), _maxSize(n)
        {
         //making sure that the pool is clear.
            for (uint i = 0; i < n; i++)
            {
                _pool[i].clear();
            }
        }
        void spawn(double x, double y) // À compléter
        {
          
            // le prochain snowflake inactif
            if (_nbParticles >= _maxSize)
                return;
           
            _pool[_nbParticles].initialize(x, y);
            _nbParticles += 1;
        }
        void destroy(size_t deleteIdx)
        {           
            // make sure to kill a particle that actually exist
            if (deleteIdx >= _nbParticles)
                return;

            //killing a particle           
            _pool[deleteIdx].clear();
            //remove a particle from _nbParticles
            _nbParticles -= 1;

            // Swap to insure the selection of active particles only
            T temp = _pool[deleteIdx];
            _pool[deleteIdx] = _pool[_nbParticles];
            _pool[_nbParticles] = temp;
        }
        T& get(size_t idx)
        {
            return _pool[idx];
        }
       
        size_t getNbSnowflakes() const
        {
            return _nbParticles;
        }

        size_t getMaxSize() const
        {
            return _maxSize;
        }

    private:
        std::unique_ptr<T[]> _pool;
        size_t _nbParticles;
        const size_t _maxSize;
    };
}
