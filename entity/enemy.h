#pragma once
#include <iostream>
#include"entity.h"
#include <string>
#include <thread>
#include <chrono>

class enemy : public entity {
private:
    int m_xpReward; 
public:
    enemy(std::string name, int startingHealth, int xpReward = 15) {
        this->m_name = name;
        this->m_health = startingHealth;
        this->m_is_Alive = true;
        this->m_level = 1;
        this->m_damage = 5;
        this->m_xpReward = xpReward;
    }

    int getXPReward() const {
        return m_xpReward;
    }

    const std::string& getName() const {
        return m_name;
    }
    void printStatus() const {
        std::cout << "[ENEMY] " << m_name 
                  << " | HP: " << m_health 
                  << " | Lvl: " << m_level << std::endl;
    }
};