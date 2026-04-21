#pragma once

#include<iostream>
#include<string>

class entity;
//pure abstract class
class item{
    protected:
        enum class type{
            weapon,
            potion,
            shield
        };

        std::string m_type;
        type m_typeID;
        entity* m_entityUsingItem;

    public:
        item(std::string type): m_type{type}  {
            if (type == "weapon") m_typeID = item::type::weapon;
            else if (type == "potion") m_typeID = item::type::potion;
            else if (type == "shield") m_typeID = item::type::shield;

            else{
                std::cerr<<"Creation of the input entity failed name is not matching\n";
            }
        }

        virtual ~item() = 0;
        
        virtual void use(entity* user, entity* target) = 0;
        virtual void mutate() = 0;
};