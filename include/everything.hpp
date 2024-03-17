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





class FreeList {
private:
    const uint16_t END_OF_LIST = 0;
    uint16_t head;
    std::vector<uint16_t> list;

public:
    inline FreeList() : head(END_OF_LIST) { }

    inline void reset() {
        head = END_OF_LIST;
        list.clear();
        // i removed this because prefabs always are loaded first, and 0 is always null prefab!
        // don't use the first one so zero can represent null
        //list.push_back(END_OF_LIST);
    }

    inline uint16_t allocate() {
        uint16_t value = head;
        if (value == END_OF_LIST ) {
            value = list.size();
            list.push_back(END_OF_LIST);
        } else {
            uint16_t index = value;
            head = list[index];
            list[index] = END_OF_LIST;
        }
        return value;
    }
};



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



struct Components {
    FreeList manager;
    std::vector<uint16_t> generation;
    std::vector<uint16_t> flags;
    std::vector<uint8_t> type;
    std::vector<Body> body;
    std::vector<Player> player;
    std::vector<Enemy> enemy;
    std::vector<Animator> animator;
};


struct Reference {

    Reference(Components& c, uint16_t i) : 
        index(i), 
        generation(c.generation[index]),
        flags(c.flags[index]),
        type(c.type[index]),
        body(c.body[index]),
        player(c.player[index]),
        enemy(c.enemy[index]),
        animator(c.animator[index])
    { }

    uint16_t& index;
    uint16_t& generation;
    uint16_t& flags;
    uint8_t& type;
    Body& body;
    Player& player;
    Enemy& enemy;
    Animator& animator;
};



inline void load_prefab(Reference& r, ObjType::Enum t) {
    auto& p = Jsons::get("prefabs")[t];

    // compute flags
    for (const auto &c : p.object()) {
        r.flags |= Atoms::get<CpFl::Enum>(c.first);
    }

    // type
    r.type = Atoms::get<ObjType::Enum>("ObjType::" + p["Type"].value());

    // body
    r.body.position.y = p["Body"]["position"]["y"].value();
    r.body.position.y = p["Body"]["position"]["y"].value();
    r.body.velocity.x = p["Body"]["velocity"]["x"].value();
    r.body.velocity.y = p["Body"]["velocity"]["y"].value();
    r.body.size.x = p["Body"]["size"]["x"].value();
    r.body.size.y = p["Body"]["size"]["y"].value();

    // player
    r.player.slot = p["Player"]["slot"].value();
    r.player.delayFire = p["Player"]["delayFire"].value();
    r.player.damage = p["Player"]["damage"].value();

    // enemy
    r.enemy.counter = p["Enemy"]["counter"].value();
    r.enemy.delayFire = p["Enemy"]["delayFire"].value();
    r.enemy.direction = p["Enemy"]["direction"].value();

    // animator
    r.animator.frame = Atoms::get<ObjType::Enum>("AniFrame::" + p["Animator"]["frame"].value());
    r.animator.count = p["Animator"]["count"].value();
}





#endif // EVERYTHING_HPP
