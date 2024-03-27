#ifndef EVERYTHING_HPP
#define EVERYTHING_HPP



#include <iostream>
#include <string>
#include <vector>
#include <map>

#include <generated/atoms.hpp>
#include <generated/jsons.hpp>

#include <enums.hpp>

#include <entity.hpp>



/*


using data_type = std::tuple<
    Ts...,                  // user defined components
    EmptyHashMap,           // active component -7
    Vector<VMHash>,         // hashes -6
    Vector<GenerationInfo>, // generation id -5
    VectorMap<uint8_t>,     // dynamic comps -4
    VectorMap<uint16_t>,    // entity -3
    HashMap<FreeInfo>,      // free hashes -2
    Single<FreeComp>        // free entities -1
>;
constexpr static size_t pack_size = std::tuple_size<data_type>::value; // size of tuple



EmptyHashMap,             // don't need
Vector<VMHash>,           // entity value now is the vector map hash
Vector<GenerationInfo>,   // will be needed
VectorMap<uint8_t>,       // dynamic comps will be optional now
VectorMap<uint16_t>,      // linked persistent entity now optional
HashMap<FreeInfo>,        // will be needed
Single<FreeComp>          // NOT SURE (will actually be merged with above ^)


*/








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


 


class TestWorld {
public:

    constexpr static size_t DataCount = 5;
    constexpr static uint16_t EndOfList = 0xffff;
    
    struct comp_array {
        BaseContainer* data[DataCount + 1];
    };

    inline void RegisterGroups(const JsonValue& data) {
        auto groups = data.count() + 1;

        compIds.resize(groups);
        head.resize(groups);
        free.resize(groups);
        generation.resize(groups);

        head[0] = EndOfList;

        for (auto&& groupId : data.object()) {
            auto gid = Atoms::get<uint8_t>("GroupType::" + groupId.first);
            head[gid] = EndOfList;
            for (auto&& componentId : groupId.second.array()) {
                auto cid = Atoms::get<uint16_t>("CpType::" + componentId.str());
                compIds[gid].push_back(cid);               
            }
            std::sort(compIds[gid].begin(), compIds[gid].end());
        }

    }

    inline bool valid(Handle handle) {
        return handle.generation() == generation[handle.type()][handle.index()];
    }

    inline Handle create(uint8_t group) {
        Handle handle;
        if (head[group] == EndOfList) {
            handle.value.type = group;
            handle.value.index = generation[group].size();
            handle.value.generation = 0;
            free[group].push_back(EndOfList);
            generation[group].push_back(0);
            // this extends all of the components
            auto list = generic();
            for (auto&& id : compIds[group]) {
                list.data[id]->set(handle);
            }
        } else {
            handle.value.type = group;
            handle.value.index = head[group];   
            handle.value.generation = generation[group][handle.value.index];
            head[group] = free[group][handle.value.index];
            free[group][handle.value.index] = EndOfList;
        }
        return handle;
    }

    inline void destroy(Handle handle) {
        if (valid(handle)) {
            ++generation[handle.type()][handle.index()];
            free[handle.type()][handle.index()] = head[handle.type()];
            head[handle.type()] = handle.index();
        }
    }


    std::vector<std::vector<uint16_t>> compIds; 
    std::vector<uint16_t> head;
    std::vector<std::vector<uint16_t>> free;
    std::vector<std::vector<uint16_t>> generation;

    VectorMap<uint8_t> type;
    VectorMap<Animator> animator;
    VectorMap<Body> body;
    VectorMap<Player> player;
    VectorMap<Enemy> enemy;

    comp_array generic() {
        return {{
            nullptr,
            &type,
            &body,
            &animator,
            &player,
            &enemy
        }};
    }

   

};


class Body_Ref {
public:
    inline Body_Ref(TestWorld& w, Handle h) : 
        body(w.body[h])
    { }

    Body& body;

};

class Body_Iter {
public:

    inline Body_Iter(TestWorld& w) : it(w.body.table.begin()), index(0), world(w) {
        if (!valid()) { incerment(); }
    }

    VectorMap<Body>::table_type::iterator it;
    uint16_t index;

    TestWorld& world;

    inline bool valid() const {
        bool ret = true;
        if (index >= it->second.size()) 
            ret = false;
        if (it->first == 0)
            ret = false;
        return ret;
    }

    inline bool isEnd() const {
        return it == world.body.table.end();
    }

    inline void incerment() {
        do {      
            ++index;
            if (index >= it->second.size()) {
                ++it;
                index = 0;
            }
        } while (!valid() && !isEnd());
    }

    inline Body_Ref get() {
        Handle handle;
        handle.value.index = index;
        handle.value.type = it->first;
        handle.value.generation = 0;
        return Body_Ref(world, handle);
    }

};









void experiment() {

    std::cout << "hello world." << std::endl;

   

}






#endif // EVERYTHING_HPP