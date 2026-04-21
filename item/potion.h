#pragma once

#include"item.h"
#include"../entity/entity.h"

class potion: public item{
    private:
        int m_ItemValue;

        enum class typesOfPotions{
            healing,
            damageBuff
        };

        typesOfPotions potionType;

    public:
        potion(std::string name , ): item(){}
        void use() override {
            switch(potionType){
                case typesOfPotions::healing: {
                    m_entityUsingItem->set_health(m_entityUsingItem->getHealth() - m_ItemValue);
                    this->m_ItemValue = 0;
                    break;
                }
                case typesOfPotions::damageBuff: {
                    m_entityUsingItem->setDamageMul(m_entityUsingItem->getDamageMul() * m_ItemValue);
                    this->m_ItemValue = 0;
                    break;
                }
            }
        }
};