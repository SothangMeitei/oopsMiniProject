#pragma once
#include"entity.h"

#pragma once
#include "entity.h"
#include <string>
#include <iostream>

class enemy : public entity {
private:
    int m_xpReward; 
public:
    enemy(std::string name, int startingHealth, int xpReward = 15) {
        this->m_name = name;
        this->m_health = startingHealth;
        this->m_is_Alive = true;
        this->m_level = 1;
        this->m_damageMul = 1;
        this->m_xpReward = xpReward;
    }

    int calculateAttackDamage() const {
        int baseDamage = 5;
        return baseDamage * m_damageMul; 
    }

    int getXPReward() const {
        return m_xpReward;
    }

    std::string getName() const {
        return m_name;
    }
    void printStatus() const {
        std::cout << "[ENEMY] " << m_name 
                  << " | HP: " << m_health 
                  << " | Lvl: " << m_level << std::endl;
    }
};