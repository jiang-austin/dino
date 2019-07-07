#ifndef TOWER_H_
#define TOWER_H_

#include "./../subject/subject.h"

class Tower : public Subject {
    protected:
        int range;
        
    public:
        Tower();
        ~Tower();

        virtual std::pair<char, int> getType() const = 0;
        virtual int getCost() const = 0;
        virtual int getUpgradeCost() const = 0;
        
        virtual void upgrade() = 0;

        int getRange() const;
        void attack();
};

#endif
