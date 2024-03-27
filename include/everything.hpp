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


template<typename T, size_t S>
struct fixed_array {
    T data[S];
};







class TestWorld {
public:

    inline void RegisterGroups(const JsonValue& data) {
        auto groups = data.count();

        compIds.resize(groups);
        head.resize(groups);
        free.resize(groups);
        generation.resize(groups);

        for (auto&& groupId : data.object()) {
            auto gid = Atoms::get<uint8_t>("GroupType::" + groupId.first);
            head[gid] = EndOfList;
            for (auto&& componentId : groupId.second.array()) {
                auto cid = Atoms::get<uint16_t>("CpType::" + componentId.value());
                compIds[gid].push_back(cid);
            }
            std::sort(compIds[gid].begin(), compIds[gid].end());
        }

    }

    constexpr static size_t DataCount = 5;
    constexpr static uint16_t EndOfList = 0xffff;

    std::vector<std::vector<uint16_t>> compIds; 
    std::vector<uint16_t> head;
    std::vector<std::vector<uint16_t>> free;
    std::vector<std::vector<uint16_t>> generation;

    inline Handle create(uint8_t group) {
        Handle handle;
        if (head[group] == EndOfList) {
            handle.value.index = generation[group].size();
            free[group].push_back(EndOfList);
            generation[group].push_back(0);
            // this extends all of the components
            auto list = generic();
            for (auto&& id : compIds[group]) {
                list.data[id]->set(handle);
            }
        } else {
            handle.value.index = head[group];   
            head[group] = free[group][handle.value.index];
        }
        handle.value.type = group;
        handle.value.generation = generation[group][handle.value.index];
        return handle;
    }

    VectorMap<uint8_t> type;
    VectorMap<Animator> animator;
    VectorMap<Body> body;
    VectorMap<Player> player;
    VectorMap<Enemy> enemy;

    fixed_array<BaseContainer*, DataCount+1> generic() {
        return {{
            nullptr,
            &type,
            &animator,
            &body,
            &player,
            &enemy
        }};
    }

   

};








void experiment() {

    std::cout << "hello world." << std::endl;

    auto test = TestWorld();

    auto data = Jsons::get("groups");

    //test.RegisterGroups(data);

    //auto handle = test.create(GroupType::Type_Body_Animator_Player);

    //std::cout << handle.generation() << " " << handle.type() << " " << handle.index() << std::endl;

}






#endif // EVERYTHING_HPP