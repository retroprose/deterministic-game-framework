#ifndef GENERATED_ATOMS_HPP
#define GENERATED_ATOMS_HPP

#include <string>
#include <map>

#include <enums.hpp>

struct Atoms {
    template<typename T>
    inline static T get(std::string s) {
        static std::map<std::string, uint32_t> m = {
            {"ObjType::Null", ObjType::Null},
            {"ObjType::Player", ObjType::Player},
            {"ObjType::Enemy", ObjType::Enemy},
            {"ObjType::Bullet", ObjType::Bullet},
            {"ObjType::BadBullet", ObjType::BadBullet},
            {"ObjType::Boom", ObjType::Boom},
            {"ObjType::PlayerBoom", ObjType::PlayerBoom},
            {"ObjType::ShotCleaner", ObjType::ShotCleaner},
            {"ObjType::Count", ObjType::Count},
            {"CpFl::None", CpFl::None},
            {"CpFl::Component", CpFl::Component},
            {"CpFl::Type", CpFl::Type},
            {"CpFl::Body", CpFl::Body},
            {"CpFl::Player", CpFl::Player},
            {"CpFl::Enemy", CpFl::Enemy},
            {"CpFl::Animator", CpFl::Animator},
            {"CpFl::Active", CpFl::Active},
            {"AniFrame::_null", AniFrame::_null},
            {"AniFrame::_null_persist", AniFrame::_null_persist},
            {"AniFrame::enemy_00_a", AniFrame::enemy_00_a},
            {"AniFrame::enemy_01_a", AniFrame::enemy_01_a},
            {"AniFrame::enemy_02_a", AniFrame::enemy_02_a},
            {"AniFrame::enemy_03_a", AniFrame::enemy_03_a},
            {"AniFrame::enemy_04_a", AniFrame::enemy_04_a},
            {"AniFrame::enemy_05_a", AniFrame::enemy_05_a},
            {"AniFrame::enemy_06_a", AniFrame::enemy_06_a},
            {"AniFrame::enemy_07_a", AniFrame::enemy_07_a},
            {"AniFrame::enemy_08_a", AniFrame::enemy_08_a},
            {"AniFrame::enemy_09_a", AniFrame::enemy_09_a},
            {"AniFrame::enemy_10_a", AniFrame::enemy_10_a},
            {"AniFrame::enemy_00_b", AniFrame::enemy_00_b},
            {"AniFrame::enemy_01_b", AniFrame::enemy_01_b},
            {"AniFrame::enemy_02_b", AniFrame::enemy_02_b},
            {"AniFrame::enemy_03_b", AniFrame::enemy_03_b},
            {"AniFrame::enemy_04_b", AniFrame::enemy_04_b},
            {"AniFrame::enemy_05_b", AniFrame::enemy_05_b},
            {"AniFrame::enemy_06_b", AniFrame::enemy_06_b},
            {"AniFrame::enemy_07_b", AniFrame::enemy_07_b},
            {"AniFrame::enemy_08_b", AniFrame::enemy_08_b},
            {"AniFrame::enemy_09_b", AniFrame::enemy_09_b},
            {"AniFrame::enemy_10_b", AniFrame::enemy_10_b},
            {"AniFrame::player_ship_0", AniFrame::player_ship_0},
            {"AniFrame::player_ship_1", AniFrame::player_ship_1},
            {"AniFrame::player_shot", AniFrame::player_shot},
            {"AniFrame::enemy_shot", AniFrame::enemy_shot},
            {"AniFrame::easy_0", AniFrame::easy_0},
            {"AniFrame::easy_1", AniFrame::easy_1},
            {"AniFrame::player_boom_0", AniFrame::player_boom_0},
            {"AniFrame::player_boom_1", AniFrame::player_boom_1},
            {"AniFrame::player_boom_2", AniFrame::player_boom_2},
            {"AniFrame::player_boom_3", AniFrame::player_boom_3},
            {"AniFrame::player_boom_4", AniFrame::player_boom_4},
            {"AniFrame::player_boom_5", AniFrame::player_boom_5},
            {"AniFrame::player_boom_6", AniFrame::player_boom_6},
            {"AniFrame::enemy_boom_0", AniFrame::enemy_boom_0},
            {"AniFrame::enemy_boom_1", AniFrame::enemy_boom_1},
            {"AniFrame::enemy_boom_2", AniFrame::enemy_boom_2},
            {"AniFrame::enemy_boom_3", AniFrame::enemy_boom_3},
            {"AniFrame::enemy_boom_4", AniFrame::enemy_boom_4},
            {"AniFrame::enemy_boom_5", AniFrame::enemy_boom_5},
            {"AniFrame::enemy_boom_6", AniFrame::enemy_boom_6},
            {"AniFrame::local_player_0", AniFrame::local_player_0},
            {"AniFrame::local_player_1", AniFrame::local_player_1},
            {"AniFrame::text_ready", AniFrame::text_ready},
            {"AniFrame::text_no", AniFrame::text_no},
            {"AniFrame::text_great", AniFrame::text_great},
            {"AniFrame::target", AniFrame::target},
            {"AniFrame::image_count", AniFrame::image_count},
            {"AniFrame::_end_list", AniFrame::_end_list}
        };
        return static_cast<T>(m[s]);
    }
};

#endif // GENERATED_ATOMS_HPP