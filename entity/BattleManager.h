
#pragma once
#include <vector>
#include <memory>
#include <algorithm>
#include <iostream>
#include "entity.h"
#include "player.h"
#include "enemy.h"

class BattleManager {
    private:
        std::shared_ptr<player> mainPlayer;
        std::vector<std::shared_ptr<entity>> enemies;

    public:
        void setPlayer(std::shared_ptr<player> p) {
            mainPlayer = std::move(p);
        }

        void addEnemy(std::shared_ptr<entity> newEnemy) {
            enemies.push_back(std::move(newEnemy));
        }

        void clearDeadEnemies() {            
            std::erase_if(enemies, [](const std::shared_ptr<entity>& e) {
                if (!e->isAlive()) {
                    std::cout << e->getName() << " has been defeated!\n";
                    return true; 
                }
                return false;
            });
        }

        bool isBattleOver() const {
            return !mainPlayer->isAlive() || enemies.empty();
        }
        
        std::vector<std::shared_ptr<entity>>& getEnemies() {
            return enemies;
        }
};