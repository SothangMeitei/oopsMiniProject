#pragma once
#include "item.h"
#include "../entity/entity.h"
#include <iostream>
#include <chrono>
#include <thread>
#include <string>

inline void potion_animation() {
    std::string frames[4] = {
        "      __    \n     |  |   \n    /    \\  \n   |      | \n    \\____/  \n",
        "      __    \n     |  |   \n    /  o \\  \n   |   o  | \n    \\____/  \n",
        "      __    \n     | o|   \n    / o  \\  \n   | o  o | \n    \\____/  \n",
        "    * __ * \n   * |  | * \n    /    \\  \n   |      | \n    \\____/  \n"
    };

    for (int i = 0; i < 12; i++) {
        std::cout << "\x1B[2J\x1B[H"; // Clear screen
        std::cout << "\n\n  -- GLUG GLUG GLUG --\n\n";
        
        std::cout << frames[i % 4];
        
        std::cout << std::flush;
        std::this_thread::sleep_for(std::chrono::milliseconds(150));
    }
}

class potion : public item {
    private:
        int m_healValue;

    public:
        potion(std::string name, int healValue) : item(name), m_healValue(healValue) {}

        void use(entity* user, entity* target) override {
            user->set_health(user->getHealth() + m_healValue);
            
            potion_animation();
            
            std::this_thread::sleep_for(std::chrono::milliseconds(300));
            
            std::cout << "\n" << user->getName() << " drinks " << m_name 
                      << " and recovers " << m_healValue << " HP!\n";
            std::this_thread::sleep_for(std::chrono::milliseconds(300));
        }
};