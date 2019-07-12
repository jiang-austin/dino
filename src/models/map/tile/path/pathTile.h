#ifndef PATH_TILE_H_
#define PATH_TILE_H_

#include "../tile.h"
#include "../../../enemy/enemy.h"
#include <vector>
#include <iostream>

class PathTile : public Tile {
    std::vector<Enemy*> enemies;
    
    public:
        std::vector<PathTile*> next;
        std::vector<PathTile*> prev;

        PathTile(int, int);
        ~PathTile();
        bool endOfPath() const;
        void moveEnemies();
        void insertEnemy(Enemy *);
        char getType() const override;
        bool isOccupied() const override;
        std::vector<Enemy*> & getEnemies();
        friend std::ostream& operator<<(std::ostream&, PathTile&);
};

#endif
