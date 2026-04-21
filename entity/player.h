#pragma once
#include "entity.h"
#include "../item/item.h"
#include <string>
#include <iostream>

class player : public entity {
    private:
        bool m_main_player;
        
    public:
        player(std::string name, int startingHealth) {
            this->m_name = name;
            this->m_health = startingHealth;
            this->m_is_Alive = true;
            this->m_level = 1;
            this->m_damageMul = 1;
            this->m_main_player = true; 
        }

        bool getMainPlayerStatus() const { return m_main_player; }

        void useItemFromInventory(int inventoryIndex, entity* target) {
            if (inventoryIndex >= 0 && inventoryIndex < m_items.size()) {
                m_items[inventoryIndex]->use(this, target); 
            } else {
                std::cout << "Invalid item slot!\n";
            }
        }
                
        void printInventory() const {
            std::cout << "--- Inventory ---\n";
            if (m_items.empty()) {
                std::cout << "(Empty)\n";
                return;
            }
            for (size_t i = 0; i < m_items.size(); ++i) {
                std::cout << i << ". Item Slot " << i << "\n"; 
            }
        }
};