
#pragma once
#include<iostream>

class vec2{
    private:
        int x{};
        int y{};
    public:
        vec2() = default;
        vec2(int x , int y):x{x} , y{y}{}

        vec2 operator+(const vec2& rhs){
            return vec2(this->x + rhs.x , this->y + rhs.y);
        }

        vec2 operator-(const vec2& rhs){
            return vec2(this->x - rhs.x , this->y - rhs.y);
        }

        vec2 dot(const vec2& rhs){
            return vec2(this->x * rhs.x , this->y * rhs.y);
        }

        vec2 getVector(){
            return vec2(this->x , this->y);
        }

        void operator=(const vec2& rhs){
            this->x = rhs.x;
            this->y = rhs.y;
        }

        friend std::ostream& operator<<(std::ostream& stream, const vec2& vec){
            return stream<<" "<<vec.x<<" , "<<vec.y<<" ";
        }
};