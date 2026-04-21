#include <iostream>
#include <memory>
#include "entity/entity.h"
#include "entity/player.h"
#include "entity/enemy.h"
#include "entity/BattleManager.h"
#include "item/weapon.h"
#include "item/potion.h"
#include <limits>
void clearScreen() {
    std::cout << "\x1B[2J\x1B[H";
}

// Pauses the game loop so the player can read what just happened
void waitForNextTurn() {
    std::cout << "\n[Press ENTER to continue...]";
    
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    
    std::cin.get(); 
}

int main() {
    BattleManager manager;

    //Create the Player
    auto myPlayer = std::make_shared<player>("Sothang The Main Hero", 100);
    
    auto steelSword = std::make_shared<weapon>("Steel Sword", 20); // 20 damage
    auto healthPotion = std::make_shared<potion>("Health Potion", 50); // 50 heal

    
    myPlayer->addItem(steelSword);
    myPlayer->addItem(healthPotion);

    manager.setPlayer(myPlayer);

    //Create and place enemies into the "Arena"
    auto goblin1 = std::make_shared<enemy>("Goblin A", 30 , 15);
    auto goblin2 = std::make_shared<enemy>("Goblin B", 30 , 15);
    
    manager.addEnemy(goblin1);
    manager.addEnemy(goblin2);

    clearScreen();
    std::cout << "=== BATTLE START ===\n";
    std::cout << "You have been ambushed by goblins!\n";
    waitForNextTurn();
    clearScreen();

    while (!manager.isBattleOver()) {
        
        // PLAYER'S TURN 
        std::cout << "\nYour Health: " << myPlayer->getHealth() << "\n";
        std::cout << "Enemies present:\n";
        
        auto& activeEnemies = manager.getEnemies();
        for (size_t i = 0; i < activeEnemies.size(); ++i) {
            std::cout << i << ". " << activeEnemies[i]->getName() 
                    << " (HP: " << activeEnemies[i]->getHealth() << ")\n";
        }

        // Inside your main battle loop...

        std::cout << "\nChoose an action:\nUse Item : press any integer to use item form inventory\n Skip current move: press -1 to skip current move\n";
        int actionChoice;
        std::cin >> actionChoice;

        if (actionChoice != -1) {
            myPlayer->printInventory();
            std::cout << "Which item? (Enter slot number): ";
            int itemIndex;
            std::cin >> itemIndex;

            std::cout << "Which enemy do you want to target? (Enter number): ";

            int targetIndex;
            std::cin >> targetIndex;

            // Fetch the target from the Manager
            auto& activeEnemies = manager.getEnemies();
            
            if (targetIndex >= 0 && targetIndex < activeEnemies.size()) {
                myPlayer->useItemFromInventory(itemIndex, activeEnemies[targetIndex].get());
            }
        } 

        manager.clearDeadEnemies();

        if (manager.isBattleOver()) break; 

        //move of the enemy
        std::cout << "\n--- Enemy Turn ---\n";
        for (auto& e : manager.getEnemies()) {
            //every surviving enemy attacks the player
            std::cout << e->getName() << " attacks you for 5 damage!\n";
            myPlayer->set_health(myPlayer->getHealth() - 5);
            if(myPlayer->getHealth() <= 0){
                myPlayer->set_isAlive(false);
            }
        }

        waitForNextTurn(); 
        clearScreen();
    }

    clearScreen();
    std::cout << "=== BATTLE FINISHED ===\n\n";
    if (myPlayer->isAlive()) {
        std::cout << "\nVICTORY! You defeated all enemies.\n";
    } else {
        std::cout << "\nGAME OVER. You were defeated.\n";
    }

    return 0;
}