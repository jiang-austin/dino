#ifndef MAP_H_
#define MAP_H_

#include "../tile/tile.h"
#include "../tile/path/pathTile.h"
#include "../enemy/enemy.h"
#include <vector>
#include <utility>
#include <iostream>

class Map {
    int width;
    int height;
    std::vector<std::vector<Tile*> > map;
    std::vector<PathTile*> path;
    std::vector<std::pair<int,int> > createPath(std::pair<int,int> from, std::pair<int,int> to);
    bool createPathHelper(
        std::vector<std::vector<bool> >&,
        std::pair<int,int>,
        std::pair<int,int>,
        std::vector<std::pair<int,int> >&);
        void initPath();
        void initMap();
    public:
        Map();
        ~Map();

        std::vector<Enemy*> nextFrame();
        std::vector<Enemy*> removeDeadEnemies();
        void insertEnemy(Enemy*);
        friend std::ostream& operator<<(std::ostream&, Map &);
};

#endif
