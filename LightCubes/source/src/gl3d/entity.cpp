

#include "entity.h"
#include "def.h"
#include "draw.h"
#include "func.h"
#include "core.h"
#include "glCore.h"
#include "input.h"
#include "random.h"



namespace entitySys
{
    ///////////////////////////////////////
    // Entity: class global vars/functions
    /////////////////////////////////////

    // Entity unique ID counter
    unsigned int entity::uidCtr = 0;



    // Entities
    std::vector<entity*> entity::entVec;



    // Add to entVec for automatic processing of events.
    entity* const entity::sysAdd( entity* const entPtr ) {
        entVec.push_back( entPtr );
        return entPtr;
    }



    // Remove from entVec.
    void entity :: sysRemove( const entity* const entPtr ) {
        for (auto iter=entVec.begin(); iter!=entVec.end(); iter++) {
            if (*iter == entPtr) {
                entVec.erase( iter );
                return;
            }
        }
    }



    // Do game logic stuff for each entity.
    void entity::generateStepEvents()  {
        for (size_t i=0; i<entVec.size(); i++)
            entVec[i]->evStep();
    }



    // Test for collisions and respond to them.
    void entity::generateCollisionEvents() {
        // Loop through all possible unique pairings of entities.
        for (size_t iRef=0;      iRef<entVec.size(); iRef++)
        for (size_t iCom=iRef+1; iCom<entVec.size(); iCom++) {
            entity* const entRef = entVec[ iRef ];
            entity* const entCom = entVec[ iCom ];


            // Don't generate collisions for pairs where one ent has collisions disabled.
            if (entRef->collideEnable == false
            ||  entCom->collideEnable == false)
                continue;


            // Test for spherical overlap.
            const float radiusSum = entRef->radius  +  entCom->radius;
            const float dist      = distance( entRef->pos, entCom->pos );

            if (dist <= radiusSum) {
                // Synchronously generate the collision event pair.
                entRef->evCollide( entCom );
                entCom->evCollide( entRef );
            }
        }
    }



    // Draw each entity.
    void entity::generateDrawEvents()  {
        for (size_t i=0; i<entVec.size(); i++)
            entVec[i]->evDraw();
    }
    






    ///////////////////////////////////////
    // Entity: instance local functions
    /////////////////////////////////////



    // collide, step and draw are pure virtual functions and so don't have a body.
    // Derived entity types must implement these, entity can't be instanciated by itself.



    // Construct
    entity::entity() {
        // Initialise to defaults
        this->uid           = uidCtr++;
        this->collideEnable = true;
        this->radius        = 32.0f;
        this->pos           = 0.0f;
        this->scale         = 1.0f;
        
        // Add to event handling etc
        sysAdd( this );
    }



    // Destruct
    entity::~entity() {
        sysRemove( this );
    }

};





