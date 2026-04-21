#pragma once
#include"entity.h"

class player: public entity{
    private:
        bool m_main_player;
    public:
        bool getMainPlayerStatus(){return m_main_player;};

        void useItem1(){

        }
        void useItem2(){
            
        }
};