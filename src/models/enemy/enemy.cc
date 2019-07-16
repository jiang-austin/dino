#include "enemy.h"
#include "./../tower/tower.h"

#include <algorithm>

using namespace std;

Enemy::Enemy(int hp) : isFrozen(0), hp(hp), targetable(true) {}

int Enemy::getHP() const {
    return hp;
}

void Enemy::decFrozen() {
    isFrozen = isFrozen > 0 ? isFrozen-1 : 0;
}

int Enemy::getFrozen() const {
    return isFrozen;
}

int Enemy::notify(Tower * tower){
    pair<char, int> type = tower->getType();
    if(type.first == 'D') {
        int ret = 0;
        int prevHP = hp;
        hp -= type.second;
        return max(0, min(prevHP, type.second));
    }
    else if (type.first == 'F') {
        if (!isFrozen) {
            isFrozen = type.second;
        }
    }
    return 0;
}

void Enemy::observeTowers(vector<Tower*> towers){
    for(size_t i = 0; i < towers.size(); ++i) {
        towers[i]->attach(this);
    }
}

void Enemy::removeTowers(){
    for(size_t i = 0; i < subjects.size(); ++i){
        subjects[i]->detach(this);
    }
    subjects.clear();
}

bool Enemy::isTargetable() {
    return targetable;
}

ostream& operator<<(std::ostream& out, Enemy& enemy) {
    out << "type: " << enemy.getType() << ", hp: " << enemy.getHP() << ", frozen: ";
    out << (enemy.getFrozen() > 0 ? "Yes" : "No") << ", targetable: "<< (enemy.isTargetable() ? "Yes" : "No") << endl;
    return out;
}

Enemy::~Enemy(){
    for(size_t i = 0; i < subjects.size(); ++i){
        subjects[i]->detach(this);
    }
}