#pragma once
#include "item.h"
#include "../entity/entity.h"
#include <iostream>

class potion : public item {
    private:
        int m_healValue;

    public:
        potion(std::string name, int healValue) : item(name), m_healValue(healValue) {}

        // Potions heal the user. They ignore the target parameter entirely.
        void use(entity* user, entity* target) override {
            user->set_health(user->getHealth() + m_healValue);
            std::cout << user->getName() << " drinks healing potion" 
                      << " and recovers " << m_healValue << " HP!\n";
        }
};