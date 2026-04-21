#pragma once

#include"item.h"
#include"../entity/entity.h"

class potion: public item{
    private:
        int m_potionValue;
        short potionType;

        enum class typesOfPotions{
            healing,
            damageBuff,
            defenceBuff
        };
        
    public:
        void use() override {
            switch(m_typeID){
                case type::potion: {
                    m_entityUsingItem->set_health(m_entityUsingItem->getHealth() - m_potionValue);
                    break;
                }
                case type::weapon: {

                }
                case type::shield: break;
            }
        }
};