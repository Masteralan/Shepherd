#pragma once

#include "Core/config.h"

#include "Entities/entity.h"
#include "Entities/Subclasses/fireball.h"
#include "Entities/entity_management.h"

#include "Entities/particle.h"

// Shepherd - A character that cares for and commands a flock of sheep. Typically for player.
class Shepherd : public Entity {
    public:
        Shepherd(int spawnX, int spawnY);

    private:

    public:
        int lastX = 0;
        int lastY = 0;

        void SlingFireball(Entity** entities, Particle* particles);
        void SwingAttack(Entity** entities, Particle* particles);
};