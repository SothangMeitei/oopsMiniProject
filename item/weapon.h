#pragma once
#include "item.h"
#include "../entity/entity.h"
#include <iostream>
#include <chrono>
#include <thread>
#include <string>

// In-place stick figure lashing out animation
inline void attack_animation() {
    // Array of 5 frames showing a wind-up, strike, and recovery
    std::string frames[5] = {
        // Frame 1: Idle
        "\n\n        O \n       /|\\ \n       / \\ \n\n",
        
        // Frame 2: Winding up (leaning back)
        "\n\n      \\ O \n        |\\ \n       / \\ \n\n",
        
        // Frame 3: Lashing out!
        "\n\n        O    _/> \n      --|---/ \n       / \\ \n\n",
        
        // Frame 4: Impact frame with text flash
        "\n\n        O    _/>        *** SMACK! *** \n      --|---/ \n       / \\ \n\n",
        
        // Frame 5: Recovery
        "\n\n        O \n       /|\\ \n       / \\ \n\n"
    };

    // Play the animation exactly once
    for (int i = 0; i < 5; i++) {
        std::cout << "\x1B[2J\x1B[H"; // Clear screen
        std::cout << "\n\n  -- PLAYER ATTACK --\n";
        
        std::cout << frames[i]; 
        
        std::cout << std::flush;
        
        // Pause slightly longer on the impact frame (index 3) for dramatic effect
        if (i == 3) {
            std::this_thread::sleep_for(std::chrono::milliseconds(350));
        } else {
            std::this_thread::sleep_for(std::chrono::milliseconds(120));
        }
    }
}

class weapon : public item {
    private:
        int m_baseDamage;
    public:
        weapon(std::string name, int damage) : item(name), m_baseDamage(damage) {}

        void use(entity* user, entity* target) override {
            int totalDamage = m_baseDamage + user->getDamage(); 
            
            target->set_health(target->getHealth() - totalDamage);
            
            attack_animation();
            
            std::this_thread::sleep_for(std::chrono::milliseconds(200));
            
            std::cout << "\n" << user->getName() << " attacks " << target->getName() 
                      << " for " << totalDamage << " damage!\n";

            std::this_thread::sleep_for(std::chrono::milliseconds(200));
            if(target->getHealth() <= 0){
                target->set_isAlive(false);
            }
        }
};