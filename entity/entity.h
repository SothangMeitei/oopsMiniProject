#pragma once
#include<iostream>
#include<string>
#include"../vec2.h"
#include<vector>
#include<memory>

class item;

class entity{
    protected:
        std::string m_name;
        long long entityID;
        int m_health;
        int m_level;
        int m_damageMul;
        bool m_is_Alive;
        vec2 m_position{};
        vec2 m_velocity{};
        vec2 m_acceleration{};
        vec2 m_direction{};

        std::vector<std::shared_ptr<item>> m_items;
        std::shared_ptr<item> m_item1;
        std::shared_ptr<item> m_item2;

    public:

        entity() = default;
        entity(const std::string& name): m_name(name) {}

        void printStatus(){
            std::cout << "=== Entity Status ===" << std::endl;
            std::cout << "Name: " << m_name << std::endl;
            std::cout << "Health: " << m_health << std::endl;
            std::cout << "Level: " << m_level << std::endl;
            std::cout << "Is Alive: " << (m_is_Alive ? "Yes" : "No") << std::endl;
            std::cout << "Position: " <<m_position<<std::endl;
        }
        void addItem(std::shared_ptr<item> newItem){
            m_items.push_back(std::move(newItem)); // std::move avoids a copy overhead
        }
        void mutate_item1(int indexOfNewItem){
            m_item1 = m_items.at(indexOfNewItem);
        }
        void mutate_item2(int indexOfNewItem){
            m_item2 = m_items.at(indexOfNewItem);
        }

        vec2 get_position(){
            return m_position;
        }
        vec2 get_velocity(){
            return m_velocity;
        }

        void set_postion(const vec2& newPosition){
            m_position = newPosition;
        }

        void set_velocity(const vec2& newVelocity){
            m_velocity = newVelocity;
        }

        void set_acceleration(const vec2& newAcceleration){
            m_acceleration = newAcceleration;
        }

        void set_health(int newHealth){
            m_health = newHealth;
        }

        int getDamageMul(){return m_damageMul;}
        void setDamageMul(int newValue){
            this->m_damageMul = newValue;
        }

        long long getEntityID(){
            return entityID;
        }

        int getHealth() {return m_health;}
        bool isAlive(){return m_is_Alive;}
        void set_isAlive(bool input){m_is_Alive = input;}

        const std::string& getName() const {return m_name;}
};