#include "fireball.h"

Fireball::Fireball(int spawnX, int spawnY, int dirX, int dirY, int type) {
    id = 3;
    x = spawnX;
    y = spawnY;
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

void Fireball::Burst(Entity** entities, Particle* particles) {
    Particle* explosionEffect = ActivateParticle(particles, 5, x, y);
    for (int iX = -1; iX < 2; iX++) {
        for (int iY = -1; iY < 2; iY++) {
            Entity* hit = GetEntityAtLocation(entities, x + iX, y + iY);
            if (hit && !hit->HasFire) {
                hit->HasFire = HasFire;
                hit->HasFrost = HasFrost;
                if (hit->GetID() == 6) {
                    Torch* torch = dynamic_cast<Torch*>(hit);
                    if (torch)
                        torch->UpdateAnimationData();
                }
            }
        }
    }

    RemoveEntity(entities, this);
}