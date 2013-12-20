

// Entity base class.

#pragma once
#include <vector>
#include "vec.h"



namespace entitySys
{
    // Types of entities
    enum entType {
        entTypePlayer,
        entTypeEnemy,
        entTypeGoal
    };





    // Base entity class - this is an abstract class.
    class entity
    {
      // Class global
      public:
        static  unsigned int uidCtr; // UID counter, increments on create
        
        static  std::vector<entity*> entVec;
        static  entity* const sysAdd   (       entity* const entPtr );
        static  void          sysRemove( const entity* const entPtr );

        static  void generateStepEvents();      // 
        static  void generateCollisionEvents(); // 
        static  void generateDrawEvents();      // 


      // Instance local
      public: 
        unsigned int uid;    // Unique ID
        entType type;        // Type of entity
                             
        bool  collideEnable; // Whether entity is considered for collisions
        float radius;        // Collision radius
        vec3  pos;           // Position, and centre for collision circle
        float scale;         // Scale of graphical representation


      public:
        void clampPosToWorldBoundaries(); // Self explanatory :)

        // Pure virtual functions
        virtual void evCollide( entity* const other ) = 0; // Collision event
        virtual void evStep() = 0;                         // Game logic update event
        virtual void evDraw() const = 0;                   // Draw event

                 entity();
        virtual ~entity();
    };

};





