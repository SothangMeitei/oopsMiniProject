#pragma once
#include"entity.h"
#include"../item/item.h"

class player: public entity{
    private:
        bool m_main_player;
        
    public:
        bool getMainPlayerStatus(){return m_main_player;};

        void useItem1(){
            if(m_item1){
                m_item1->use();
            }
        }
        void useItem2(){
            if(m_item2){
                m_item2->use();
            }
        }
};