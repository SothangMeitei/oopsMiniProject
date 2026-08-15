
----------- Project title : Text Based, Simple, Turn Based Game ----------------------

This is a mini project for the demostration of the core concepts of Object Oriented Programming

In this project we hope to demostrate the core concepts of 
    1) Inheritance 2) Polymorphism 3) Abstraction 4) Encapsulation among other things

    1)Inheritance is demonstrated 
        in the part where 
            the enemy and the player class inherit from the class entity so
            enemy is an entity and player is an entity
        
            item is inherited by the classes potion and the class weapon
            so that potion is an item and weapon is an item
    
    2) polymorphism is demostrated when the purely abstract class of the item class is inherited and then
        its internal member funcitons are overriden by the derived classes of potions and weapon to define their class specific 
        implementations of the function use , which depending on the context of the item of what item it is the will differ the

        so that when the method use is called on the item if the item is a potion then the potion implementation is called
        else if the the item is a weapon then the weapon implementation of the use method is called
    
    3) Encapsulation
        here in the program all the calsses have getters and setters and the internal member variables are hidden form the user
        thus demostarting the idea of Encapsulation
    
    4) Abstraction
        Abstraction is demonstrated by reducing complex underlying combat mathematics into simple interfaces.
        For example, when a weapon is used, the main loop does not calculate the damage multipliers or health reductions.
        It simply calls item->use(this, target),and the complexity of the stat calculation is abstracted away
        behind that single method call.
        The complexity of the item class use function is hidden form the user just by seeing from the class of the item
        so this item class is an Abstract class , with the pure virtual function use() 

    5) Aggregation
        BattleManager class demonstrates Aggregation.
        A BattleManager is not an entity, but it has a collection of entities (std::vector<std::shared_ptr<entity>> enemies)