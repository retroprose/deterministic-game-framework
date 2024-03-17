#ifndef GENERATED_JSONS_HPP
#define GENERATED_JSONS_HPP


#include<json/json.hpp>


struct Jsons {

    using k = JsonKeyValue;

    inline static const JsonValue& get(const char* s) {        
        static JsonValue r = {
            k("prefabs", {
                {
                    k("Type", "Null")
                },
                {
                    k("Type", "Player"),
                    k("Body", {
                        k("size", {
                            k("x", 16),
                            k("y", 10)
                        })
                    }),
                    k("Player", {
                        k("slot", -1)
                    }),
                    k("Animator", {
                        k("frame", "player_ship_0")
                    })
                },
                {
                    k("Type", "Enemy"),
                    k("Body", {
                        k("size", {
                            k("x", 16),
                            k("y", 10)
                        })
                    }),
                    k("Enemy", {
                        k("direction", 1)
                    }),
                    k("Animator", {
                        k("frame", "enemy_00_a")
                    })
                },
                {
                    k("Type", "Bullet"),
                    k("Body", {
                        k("velocity", {
                            k("x", 0),
                            k("y", 16)
                        }),
                        k("size", {
                            k("x", 12),
                            k("y", 20)
                        })
                    }),
                    k("Animator", {
                        k("frame", "player_shot")
                    })
                },
                {
                    k("Type", "BadBullet"),
                    k("Body", {
                        k("velocity", {
                            k("x", 0),
                            k("y", -8)
                        }),
                        k("size", {
                            k("x", 7),
                            k("y", 7)
                        })
                    }),
                    k("Animator", {
                        k("frame", "enemy_shot")
                    })
                },
                {
                    k("Type", "Boom"),
                    k("Body", {
                        k("size", {
                            k("x", 14),
                            k("y", 14)
                        })
                    }),
                    k("Animator", {
                        k("frame", "enemy_boom_0")
                    })
                },
                {
                    k("Type", "PlayerBoom"),
                    k("Body", {
                        k("size", {
                            k("x", 22),
                            k("y", 21)
                        })
                    }),
                    k("Animator", {
                        k("frame", "player_boom_0")
                    })
                },
                {
                    k("Type", "ShotCleaner"),
                    k("Body", {
                        k("size", {
                            k("x", 960),
                            k("y", 540)
                        })
                    })
                }
            })
        };
        return r[s];
    }
};

#endif // GENERATED_JSONS_HPP