#ifndef EVERYTHING_HPP
#define EVERYTHING_HPP



#include <iostream>
#include <string>
#include <vector>
#include <map>

#include<generated/atoms.hpp>
#include<generated/jsons.hpp>

#include<enums.hpp>

/*
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
*/


class Handle {
public:


    union {
        struct {
            uint32_t type : 8;
            uint32_t data : 24;
        } untracked;
        struct {
            uint32_t type : 8;
            uint32_t index : 14;
            uint32_t generation : 10;
        } tracked;
        uint32_t raw;
    } value;

};



struct Type {
    uint8_t active : 1;
    uint8_t type : 7;
};

struct Vector2 {
    int32_t x;
    int32_t y;
};


 
/*using body_tuple = std::tuple<
    Vector2,
    Vector2,
    Vector2
>;

using animator_tuple = std::tuple<
    uint16_t,
    uint16_t
>;

using player_tuple = std::tuple<
    int8_t,
    uint16_t,
    uint16_t
>;

using enemy_tuple = std::tuple<
    int8_t,
    uint8_t,
    uint16_t
>;

using data_tuple = std::tuple<
    body_tuple,
    animator_tuple,
    player_tuple,
    enemy_tuple
>;*/


// Data
using data_tuple = std::tuple<
    // Body
    std::tuple<
        Vector2,
        Vector2,
        Vector2
    >,
    // Animator
    std::tuple<
        uint16_t,
        uint16_t
    >,
    // Player
    std::tuple<
        int8_t,
        uint16_t,
        uint16_t
    >,
    // Enemy
    std::tuple<
        int8_t,
        uint8_t,
        uint16_t
    >
>;


template<typename T>
struct VectorTuple;

template<typename... Ts>
struct VectorTuple<std::tuple<Ts...>> {
    using type = std::tuple<std::vector<Ts>...>;
};


template<typename T>
class TestDataClass {
public:

    // the group tuples
    template<size_t N>
    using group_tuple = typename std::tuple_element<N, T>::type;

    // the vector tuples
    template<typename T>
    struct VectorTuple;

    template<typename... Ts>
    struct VectorTuple<std::tuple<Ts...>> {
        using type = std::tuple<std::vector<Ts>...>;
    };

    template<size_t N>
    using vector_tuple = typename VectorTuple<group_tuple<N>>::type;

    


};


using data_type = TestDataClass<data_tuple>;



class BodyRef {
public:
    inline BodyRef() { }

    //Vector2& position;
    //Vector2& velocity;
    //Vector2& size;
};


inline void experiment() {

    data_type::vector_tuple<0> thing;





}



#endif // EVERYTHING_HPP
