#include <iostream>
#include <memory>
#include "entity/entity.h"
#include "entity/player.h"
#include "entity/enemy.h"
#include "entity/BattleManager.h"

int main() {
    BattleManager manager;

    //Create the Player
    auto myPlayer = std::make_shared<player>("Sothang The Main Hero", 100);
    manager.setPlayer(myPlayer);

    //Create and place enemies into the "Arena"
    auto goblin1 = std::make_shared<enemy>("Goblin A", 30 , 15);
    auto goblin2 = std::make_shared<enemy>("Goblin B", 30 , 15);
    
    manager.addEnemy(goblin1);
    manager.addEnemy(goblin2);

    std::cout << "=== BATTLE START ===\n";

    while (!manager.isBattleOver()) {
        
        // PLAYER'S TURN 
        std::cout << "\nYour Health: " << myPlayer->getHealth() << "\n";
        std::cout << "Enemies present:\n";
        
        auto& activeEnemies = manager.getEnemies();
        for (size_t i = 0; i < activeEnemies.size(); ++i) {
            std::cout << i << ". " << activeEnemies[i]->getName() 
                    << " (HP: " << activeEnemies[i]->getHealth() << ")\n";
        }

        std::cout << "\nChoose an item form the inventory to be used input -1 to skip move\n";
        int inventoryChoice;
        std::cin >> inventoryChoice;

        if (inventoryChoice != -1) {
            std::cout << "Which enemy do you want to attack? (Enter number): ";
            int targetIndex;
            std::cin >> targetIndex;
            
            
        } 

        manager.clearDeadEnemies();

        if (manager.isBattleOver()) break; 

        //move of the enemy
        std::cout << "\n--- Enemy Turn ---\n";
        for (auto& e : manager.getEnemies()) {
            //every surviving enemy attacks the player
            std::cout << e->getName() << " attacks you for 5 damage!\n";
            myPlayer->set_health(myPlayer->getHealth() - 5);
        }
    }

    if (myPlayer->isAlive()) {
        std::cout << "\nVICTORY! You defeated all enemies.\n";
    } else {
        std::cout << "\nGAME OVER. You were defeated.\n";
    }

    return 0;
}