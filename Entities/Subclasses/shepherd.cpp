#include "shepherd.h"

Shepherd::Shepherd(int spawnX, int spawnY) {
    id = 1;

    MaxHealth = ShepherdHealth;
    Health = MaxHealth;

    x = spawnX;
    y = spawnY;
}

void Shepherd::SwingAttack(Entity** entities, Particle* particles) {
    animation = 2;
    ActivateParticle(particles, 1, x, y);

    // Pause any sheep and attack any wolves within a tile radius of the Shepherd
    for (int w = x-1; w <= x+1; w++) {
        for (int z = y-1; z <= y+1; z++) {
            Entity* obj = GetEntityAtLocation(entities, w, z);
            if (obj) {
                if (obj->GetID() == 1)  //If sheep, toggle pause
                    obj->Paused = !obj->Paused;
            }
        }
    }
}