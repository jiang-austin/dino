#ifndef ENEMY_H_
#define ENEMY_H_

#include "./../observer/observer.h"
#include "./../tower/tower.h"
#include "./../subject/subject.h"

#include <vector>
#include <iostream>

class Enemy : public Observer {        
    private:
        std::vector<Tower*> subjects;
        int isFrozen;

        virtual char getType_() const = 0;
        virtual void nextState_() = 0;
        virtual int notify_(Tower*); 

    protected:
        int hp;
        bool targetable;

    public:
        Enemy(int);

        int getHP() const;
        
        void decFrozen();
        int getFrozen() const;

        char getType();
        void nextState();
        int notify(Tower*) override; 

        void observeTowers(std::vector<Tower*>);

        void removeTowers();
        bool isTargetable() const;

        virtual ~Enemy();
        friend std::ostream& operator<<(std::ostream&, Enemy&);
};

#endif
