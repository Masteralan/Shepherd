#include "fireball.h"

Fireball::Fireball(int spawnX, int spawnY, int dirX, int dirY, int type) {
    id = EntityID::EE_Fireball;
    x = spawnX;
    y = spawnY;
    lastX = spawnX;
    lastY = spawnY;
    speedX = dirX*FireballSpeed;
    speedY = dirY*FireballSpeed;
    
    if (type > 1) {
        HasFrost = true;
        animation = 1;
    } else {
        HasFire = true;
        animation = 0;
    }
}

// Causes the fireball to burst, setting nearby entities on fire as well as deleting the fireball itself
void Fireball::Burst(Entity** entities, Particle* particles) {
    Particle* explosionEffect = ActivateParticle(particles, 5, x, y);

    for (int iX = -1; iX < 2; iX++) {
        for (int iY = -1; iY < 2; iY++) {

            Entity* hit = GetEntityAtLocation(entities, x + iX, y + iY);
            if (hit && !hit->HasFire) {

                // If it hits a torch, attempt to ignite it
                if (hit->GetID() == EntityID::EE_Torch) {
                    Torch* torch = dynamic_cast<Torch*>(hit);
                    if (torch && torch->Extinguishable) {
                        torch->HasFire = HasFire;
                        torch->HasFrost = HasFrost;
                    }
                // If it hits a crate, incinerate it
                } else if (hit->GetID() == EntityID::EE_Crate) {    // Hitting crates with fireballs will incinerate them
                    Crate* crate = dynamic_cast<Crate*>(hit);
                    if (crate && crate->canIncinerate) crate->Incinerate(particles, this);

                } else if (hit->GetID() == EntityID::EE_Lever) {    // Hitting levers with fireballs will flip them
                    Lever* lever = dynamic_cast<Lever*>(hit);
                    if (lever) lever->Flip();

                } else if (hit->GetID() == EntityID::EE_Shepherd || hit->GetID() == EntityID::EE_Sheep) {
                    hit->Paused = true; // Stun shepherd and sheep
                    if (hit->GetID() == EntityID::EE_Shepherd) hit->animation = 3; // Force Shepherd to kneel for visual cue
                    else if (hit->GetID() == EntityID::EE_Sheep) hit->animation = 1;
                    if (enemy) { // If the fireball was slung by an enemy, damage them
                        hit->TakeDamage(1, this);
                    }

                } else { // Otherwise set entity on fire and take damage
                    hit->HasFire = HasFire;
                    hit->HasFrost = HasFrost;
                    hit->TakeDamage(1, this); // if (!enemy)
                }
            }
        }
    }

    return RemoveEntity(entities, this);
}