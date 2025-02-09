#ifndef STATE_H_
#define STATE_H_

#include "./../enemy/enemy.h"
#include "./../map/map.h"
#include "./../shop/shop.h"
#include "./../tower/tower.h"
#include "./../spawner/spawner.h"
#include "./../view/view.h"

#include <stack>
#include <vector>


struct StateImpl {
    long long money;
    int hp, round;

    Shop* shop;
    Map* map;
    Spawner* spawner;

    std::vector<Tower *> towers;
    std::vector<Enemy *> enemies;
    std::stack<Enemy *> pendingEnemies;

    public:
        StateImpl(int, bool, bool);
        ~StateImpl();
};

class State {
    friend class View;

    private:
        StateImpl* p;

        static const int MAX_ROUND = 50;
        static const int MAX_LIVES = 100;
        static const int MIN_LIVES = 0;
        static const int MAX_HP = 1000;

        bool surviveDmg(int);
        void incrementMoney(int);

        void addTower(Tower *);
        void addEnemy(Enemy *);
        void removeEnemy(Enemy *);
        void removeTower(Tower *);


        int constructEnemies();

        int totalHP(std::vector<Enemy *>);

        bool moveEnemies(int, int);

        bool preFrame(int, int);

        void processFrame();
        void postFrame();

        void getMoneyTowerIncome();
        void getRoundIncome();
        void updateState(int, int, double);

    public:
        bool sellTower(int, int);

        State(bool, bool);
        ~State();

        void displayMap();
        bool buyTower(char, int, int);
        bool upgradeTower(int, int);

        void startRound();

        int getHp();
        void setHp(int hp);
        long long getMoney();
        int getRound();
        void setRound(int round);
        Map* getMap();
        Tower* getTower(int, int);
        Tower* getTowerFromShop(char);
        Spawner* getSpawner();
        PathTile* getPathTile(int, int);
        std::vector<Enemy *> getEnemies();
};

#endif