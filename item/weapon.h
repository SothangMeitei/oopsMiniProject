#pragma once
#include "item.h"
#include "../entity/entity.h"
#include <iostream>

class weapon : public item {
    private:
        int m_baseDamage;

    public:
        weapon(std::string name, int damage) : item(name), m_baseDamage(damage) {}

        void use(entity* user, entity* target) override {
            int totalDamage = m_baseDamage * user->getDamageMul(); 
            
            target->set_health(target->getHealth() - totalDamage);
            
            std::cout << user->getName() << " attacks " << target->getName() 
                       << " for " << totalDamage << " damage!\n";
        }
};