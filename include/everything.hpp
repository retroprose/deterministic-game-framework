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


template<typename T>
struct PoolTypeId;

template<typename T>
class Pool {
public:

    enum Flags : uint8_t {
        FlagNone = 0,
        FlagActive = 1 << 0,
        FlagAllocated = 1 << 1
    };

    struct Handle {

        uint32_t value;

    };

    struct Type {
        uint8_t flags;
        union {
            uint32_t free;
            T value;
        } data;
    };

    // free head
    uint32_t head;
    
    // use T as free list
    std::vector<uint16_t> generation;
    std::vector<Type> data;

    

};






struct Entity;


struct Vector2 {
    int32_t x;
    int32_t y;
};


struct Animator {
    Pool<Entity>::Handle parent;
    uint16_t frame;
    uint16_t count;
};
template<> struct PoolTypeId<Animator> { static const size_t Id = Type::Animator; };


struct Body {
    Pool<Entity>::Handle parent;
    Vector2 position;
    Vector2 velocity;
    Vector2 size;
};
template<> struct PoolTypeId<Body> { static const size_t Id = Type::Body; };


struct Player {
    Pool<Entity>::Handle parent;
    int8_t slot;
    uint16_t delayFire;
    uint16_t damage;
};
template<> struct PoolTypeId<Player> { static const size_t Id = Type::Player; };


struct Enemy {
    Pool<Entity>::Handle parent;
    int8_t direction;
    uint8_t counter;
    uint16_t delayFire;
};
template<> struct PoolTypeId<Enemy> { static const size_t Id = Type::Enemy; };


struct Entity {
    uint8_t type;
    Pool<Body>::Handle body;
    Pool<Animator>::Handle animator;
    Pool<Player>::Handle player;
    Pool<Enemy>::Handle enemy;
};
template<> struct PoolTypeId<Entity> { static const size_t Id = Type::Entity; };






inline void experiment() {

    

}




#endif // EVERYTHING_HPP
