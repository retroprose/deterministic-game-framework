#ifndef EVERYTHING_HPP
#define EVERYTHING_HPP



#include <iostream>
#include <string>
#include <vector>
#include <map>

#include<generated/atoms.hpp>
#include<generated/jsons.hpp>

#include<enums.hpp>

#include <entity.hpp>



struct Entity;


struct Vector2 {
    int32_t x;
    int32_t y;
};

struct Animator {
    Handle<Entity> parent;
    uint16_t frame;
    uint16_t count;
};

struct Body {
    Handle<Entity> parent;
    Vector2 position;
    Vector2 velocity;
    Vector2 size;
};

struct Player {
    Handle<Entity> parent;
    int8_t slot;
    uint16_t delayFire;
    uint16_t damage;
};

struct Enemy {
    Handle<Entity> parent;
    int8_t direction;
    uint8_t counter;
    uint16_t delayFire;
};


struct Entity {
    uint8_t type;
    Handle<Body> body;
    Handle<Animator> animator;
    Handle<Player> player;
    Handle<Enemy> enemy;
};



template<typename T>
class MemoryPool {

    enum Flags : uint8_t {
        FlagNone = 0
        FlagActive = 1 << 0,
        FlagAllocated = 1 << 1
    };

    std::vector<uint8_t> flags;
    std::vector<uint16_t> generation;
    std::vector<T> data;

    


};




inline void load_prefabs() {

    

}




#endif // EVERYTHING_HPP
