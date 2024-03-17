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





class EntityManager {
private:
    uint16_t _max;
    uint16_t _active;
    uint16_t head;
    std::vector<uint16_t> list;
    std::vector<uint16_t> _generation;

public:
    static const uint16_t END_OF_LIST = 0;

    inline EntityManager() : _max(0xffff), _active(0), head(END_OF_LIST) { }

    inline uint16_t active() const {
        return _active;
    }

    inline uint16_t full() const {
        return _active >= _max;
    }

    inline uint16_t size() const {
        return list.size();
    }

    inline uint16_t generation(uint16_t value) const {
        return _generation[value];
    }

    inline void reset() {
        _active = 0;
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
            _generation.push_back(0);
            ++_active;
        } else {
            head = list[value];
            list[value] = END_OF_LIST;
            ++_active;
        }
        return value;
    }

    inline void free(uint16_t value) {
        if (value != END_OF_LIST) {
            if (list[value] == END_OF_LIST) {
                ++_generation[value];
                list[value] = head;
                head = value;
                --_active;
            }
        }
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

    // the free list manager
    EntityManager manager;

    // user components
    std::vector<uint16_t> flags;
    std::vector<uint8_t> type;
    std::vector<Body> body;
    std::vector<Player> player;
    std::vector<Enemy> enemy;
    std::vector<Animator> animator;

    inline size_t size() const {
        return flags.size();
    }

    inline void resize(size_t s) {
        if (size() < s) {
            flags.resize(s);
            type.resize(s);
            body.resize(s);
            player.resize(s);
            enemy.resize(s);
            animator.resize(s);
        }
    }

    inline Entity clone(Entity entity) {
        return clone(entity.index());
    }

    inline Entity clone(uint16_t index) {
        Entity entity;
        if (!manager.full()) {
            uint16_t value = manager.allocate();
            resize(value);
            
            flags[value] = flags[index];
            type[value] = type[index];
            body[value] = body[index];
            player[value] = player[index];
            enemy[value] = enemy[index];
            animator[value] = animator[index];

            entity = Entity(value, manager.generation(value));
        }
        return entity;
    }

    inline Entity entity_from_index(uint16_t index) const {
        return Entity(index, manager.generation(index));
    }

    inline bool valid(Entity entity) const {
        return !entity.isNull() && entity.generation() == manager.generation(entity.index());
    }

    inline void destroy(Entity entity) {
        if (valid(entity)) {
            flags[entity.index()] = CpFl::None;
            manager.free(entity.index());
        }
    }

    inline Entity create() {
        Entity entity;
        uint16_t value = manager.allocate();
        if (!manager.full()) {
            resize(value);
            flags[value] = CpFl::None;
            entity = Entity(value, manager.generation(value));
        }
        return entity;
    }

};


struct Reference {

    Reference(Components& c, uint16_t i) : 
        entity(c.entity_from_index(i)),
        flags(c.flags[i]),
        type(c.type[i]),
        body(c.body[i]),
        player(c.player[i]),
        enemy(c.enemy[i]),
        animator(c.animator[i])
    { }

    Entity entity;
    
    uint16_t& flags;
    uint8_t& type;
    Body& body;
    Player& player;
    Enemy& enemy;
    Animator& animator;

};



inline void load_prefabs(Components& c) {

    auto& json = Jsons::get("prefabs");

    uint8_t index = 0;

    for (const auto &p : json.array()) {

        auto entity = c.create();

        auto r = Reference(c, entity.index());

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

        ++index;
    }
   
}





#endif // EVERYTHING_HPP
