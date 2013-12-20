

// Player class, inherits from entity

#pragma once
#include "entity.h"



namespace entitySys
{
    class entPlayer: public entity
    {
      public:
        static const float speedMove;
        static const float speedRotate; // Degrees per step, +CCW looking down -Z


      public:
        virtual void evCollide( entity* const other );
        virtual void evStep();
        virtual void evDraw() const;

                 entPlayer();
        virtual ~entPlayer();
    };
};





