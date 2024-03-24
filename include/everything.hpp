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



struct Vector2 {
    int32_t x;
    int32_t y;
};

struct Animator {
    uint16_t frame;
    uint16_t count;
};

struct Body {
    Vector2 position;
    Vector2 velocity;
    Vector2 size;
};

struct Player {
    int8_t slot;
    uint16_t delayFire;
    uint16_t damage;
};

struct Enemy {
    int8_t direction;
    uint8_t counter;
    uint16_t delayFire;
};

struct Entity {
    Handle body;
    Handle animator;
    Handle enemy;
    Handle player;
};



// your list of node types
using MyNodeData = NodeData<
    // entity types
    Entity,

    // component types
    Body,
    Animator,
    Enemy,
    Player
>;




inline void load_prefabs() {

    

}




#endif // EVERYTHING_HPP
