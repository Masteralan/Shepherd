#pragma once

#include <stdlib.h>

#include "Map/tile.h"
#include "config.h"

// Map - A class that holds a 2D array of tiles, as well as a list of entities that persist only within the map.
class Map {
    public:
        Map();

        struct Tile* tiles[MapWidth][MapHeight];

        int GetTileID(int x, int y);
        bool IsTileSolid(int x, int y);
        bool IsTileLiquid(int x, int y);

        void WallRectangle(int x, int y);
        void WallRectangle(int startX, int startY, int endX, int endY, int id);
        void FillRectangle(int startX, int startY, int endX, int endY, int id);
        void Free();
};