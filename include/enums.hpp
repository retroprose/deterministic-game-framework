#ifndef ENUMS_HPP
#define ENUMS_HPP

#include <cstdint>

struct NodeType {
    enum Enum : uint16_t {
        // null node, not sure what I am doing with this!
        Generic = 0,

        // game entities
        Entity = 1,

        // component types
        Body = 2,
        Animator = 3,
        Enemy = 4,
        Player = 5,

        Count = 6
    };
};

struct NoFl {
    enum Enum : uint16_t {
        None = 0,
        Allocated = 1 << 0,
        Active = 1 << 1
    };
};


struct ObjType {
    enum Enum : uint8_t {
        Null = 0,
        Player = 1,
        Enemy = 2,
        Bullet = 3,
        BadBullet = 4,
        Boom = 5,
        PlayerBoom = 6,
        ShotCleaner = 7,
        Count = 8
    };
};

struct CpFl {
    enum Enum : uint16_t {
        None = 0,
        Component = 1 << 0,
        Type = 1 << 1,
        Body = 1 << 2,
        Player = 1 << 3,
        Enemy = 1 << 4,
        Animator = 1 << 5,
        Active = 1 << 6
    };
};

struct AniFrame {
    enum Enum : uint16_t {
        _null = 0,
        _null_persist = 1,
        enemy_00_a = 2,
        enemy_01_a = 3,
        enemy_02_a = 4,
        enemy_03_a = 5,
        enemy_04_a = 6,
        enemy_05_a = 7,
        enemy_06_a = 8,
        enemy_07_a = 9,
        enemy_08_a = 10,
        enemy_09_a = 11,
        enemy_10_a = 12,
        enemy_00_b = 13,
        enemy_01_b = 14,
        enemy_02_b = 15,
        enemy_03_b = 16,
        enemy_04_b = 17,
        enemy_05_b = 18,
        enemy_06_b = 19,
        enemy_07_b = 20,
        enemy_08_b = 21,
        enemy_09_b = 22,
        enemy_10_b = 23,
        player_ship_0 = 24,
        player_ship_1 = 25,
        player_shot = 26,
        enemy_shot = 27,
        easy_0 = 28,
        easy_1 = 29,
        player_boom_0 = 30,
        player_boom_1 = 31,
        player_boom_2 = 32,
        player_boom_3 = 33,
        player_boom_4 = 34,
        player_boom_5 = 35,
        player_boom_6 = 36,
        enemy_boom_0 = 37,
        enemy_boom_1 = 38,
        enemy_boom_2 = 39,
        enemy_boom_3 = 40,
        enemy_boom_4 = 41,
        enemy_boom_5 = 42,
        enemy_boom_6 = 43,
        local_player_0 = 44,
        local_player_1 = 45,
        text_ready = 46,
        text_no = 47,
        text_great = 48,
        target = 49,
        image_count = 50,
        _end_list = 51,
    };
};


#endif // ENUMS_HPP
