#pragma once

#include<iostream>
#include<string>

class entity;
//pure abstract class
class item{
    protected:
        std::string m_name;
        entity* m_entityUsingItem;

    public:
        item(const std::string& name): m_name{name}  {}

        virtual ~item() = default;
        
        virtual void use(entity* user, entity* target) = 0;

        const std::string& getName() const {return m_name;}
};