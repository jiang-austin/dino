#ifndef MONEY_H_
#define MONEY_H_

#include "./../tower.h"

class MoneyTower : public Tower {
    private:
        int income, upCost;

    public:
        static const int cost = 30;

        MoneyTower();
        ~MoneyTower();

        int getIncome() const;

        int getCost() const override;
        int getUpgradeCost() const override;
        std::pair<char, int> getType() const override;
        
        void upgrade() override;
};

#endif
