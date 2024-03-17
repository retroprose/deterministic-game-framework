#ifndef ENTITY_HPP
#define ENTITY_HPP

#include<typeinfo>
#include<sstream>
#include<fstream>

#include <container.hpp>


/*
    Class that represents an entity, is simply a 32 bit unsigned integer.
*/
class Entity {
public:
    Entity() { data.raw.value = 0x00000000; }
	Entity(uint32_t in) { data.raw.value = in; }

    bool operator< (const Entity& rhs) const { return data.raw.value <  rhs.data.raw.value; }
    bool operator==(const Entity& rhs) const { return data.raw.value == rhs.data.raw.value; }
    bool operator!=(const Entity& rhs) const { return data.raw.value != rhs.data.raw.value; }

	bool isNull() const {
		return data.raw.value == 0x00000000;
	}

    bool untracked() const {
        return data.tracked.untracked;
    }

    uint16_t index() const {
        assert(data.tracked.untracked == 0);
        return data.tracked.index;
    }

    uint16_t generation() const {
        assert(data.tracked.untracked == 0);
        return data.tracked.generation;
    }

    uint16_t type() const {
        assert(data.tracked.untracked == 1);
        return data.untracked.type;
    }

    uint16_t user() const {
        assert(data.tracked.untracked == 1);
        return data.untracked.user;
    }

    uint32_t raw() const {
        return data.raw.value;
    }

	uint8_t* typePtr() {
		uint8_t* ptr = reinterpret_cast<uint8_t*>(&data.raw.value);
		return ptr + 3;
	}

private:
    template<typename... Ts>
    friend class State;

    /*
        Normal entities created with the State manager
    */
    struct Tracked {
        uint32_t index : 16;        // index of entity
        uint32_t generation : 15;   // generation of entity
        uint32_t untracked : 1;     // should always be zero
    };

    /*
        This can be used to make always active entities that don't
        use up any memory.

        For example, if the untracked bit is set, you can use the type
        to store a "TILE_TYPE", and use the user data bits to store
        an x and y value.  This would represent a tile on the map that
        would always be active.  it would be possible to add components to
        tiles if I changed the HashMaps to store entire entity
        values rather than just the index.

        Still experimental.
    */
    struct Untracked {
        uint32_t user : 24;         // user data, can be used any way you want
        uint32_t type : 7;          // type of entity
        uint32_t untracked : 1;     // should always be 1
    };

    struct Raw {
        uint32_t value;
    };

    Entity(Tracked in) { data.tracked = in; }
    Entity(Untracked in) { data.untracked = in; }

    union {
        Tracked tracked;
        Untracked untracked;
        Raw raw;
    } data;

};






#endif // ENTITY_HPP
