#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <typeinfo>


#include <iostream>

/*
    This class simply encapsulates a pointer.  It will assert if
    the pointer is dereferenced and that pointer is nullptr
*/
template<typename T>
class Reference {
public:
    Reference(T* ptr = nullptr) : ptr_(ptr) { }

    T& get() {
        assert( !isNull() );
        return *ptr_;
    }

    const T& get() const {
        assert( !isNull() );
        return *ptr_;
    }

    T& operator *() {
        assert( !isNull() );
        return *ptr_;
    }

    T* operator -> () {
        assert( !isNull() );
        return ptr_;
    }

    const T& operator *() const {
        assert( !isNull() );
        return *ptr_;
    }

    const T* operator -> () const {
        assert( !isNull() );
        return ptr_;
    }

    void set(const T& t) {
        *ptr_ = t;
    }

    bool isNull() const {
        return ptr_ == nullptr;
    }

	void* getVoid() {
		return ptr_;
	}

private:
    T* ptr_; // pointer

};



class Handle {
public:
    Handle() { value.raw = 0x00000000; }
	Handle(uint32_t in) { value.raw = in; }

    bool operator< (const Handle& rhs) const { return value.raw <  value.raw; }
    bool operator==(const Handle& rhs) const { return value.raw == value.raw; }
    bool operator!=(const Handle& rhs) const { return value.raw != value.raw; }

	bool isNull() const {
		return value.raw == 0x00000000;
	}

    uint8_t type() const { 
        return value.type;
    }

    uint16_t index() const {
        return value.index;
    }

    uint16_t generation() const {
        return value.generation;
    }

    uint32_t raw() const {
        return value.raw;
    }

//private:
    union {
        struct {
            uint32_t index : 14;
            uint32_t type : 8;
            uint32_t generation : 10;
        };
        uint32_t raw;
    } value;

};



class BaseContainer {
public:


    virtual bool coreHas(Handle h) const = 0;
    virtual void coreClone(Handle from, Handle to) = 0;
    virtual void coreSet(Handle h) = 0;

    
    inline bool has(Handle h) const {
        return coreHas(h);
    }

    inline void clone(Handle from, Handle to) {
        coreClone(from, to);
    }

    inline void set(Handle h) {
        coreSet(h);
    }

};



template<typename T>
class Map : public BaseContainer {
public:

    virtual bool coreHas(Handle h) const { return has(h); }
    virtual void coreClone(Handle from, Handle to) { clone(from, to); }
    virtual void coreSet(Handle h) { set(h); }


    using value_type = T;

    using table_type = std::map<uint32_t, T>;

    table_type table;

    inline T& operator[](Handle h) {
        auto it = table.find(h.type());
        assert(it != table.end());
        return *(it->second);
    }

    inline void set(Handle h) {
        table[h] = T();
    }

    inline void set(Handle h, const T& v) {
        table[h] = v;
    }

    inline bool has(Handle h) const {
        bool has = true;
        auto it = table.find(h.type());
        if (it == table.end())
            has = false;
        return has;
    }

    inline void clone(Handle from, Handle to) {
        (*this)[to] = (*this)[from];
    }

};



template<typename T>
class VectorMap : public BaseContainer {
public:

    virtual bool coreHas(Handle h) const { return has(h); }
    virtual void coreClone(Handle from, Handle to) { clone(from, to); }
    virtual void coreSet(Handle h) { set(h); }

    using value_type = T;

    using table_type = std::map<uint8_t, std::vector<T>>;

    table_type table;

    inline T& operator[](Handle h) {
        auto it = table.find(h.type());
        assert(it != table.end() && h.index() < it->second.size());
        return it->second[h.index()];
    }

    inline void set(Handle h, const T& v) {
        auto pair = table.insert(make_pair(h.type(), std::vector<T>()));
        if (h.index() >= pair.first->second.size()) {
            pair.first->second.resize(h.index() + 1);
        }        
        pair.first->second[h.index()] = v;
    }

    inline void set(Handle h) {
        auto pair = table.insert(make_pair(h.type(), std::vector<T>()));
        if (h.index() >= pair.first->second.size()) {
            pair.first->second.resize(h.index() + 1);
        }        
        pair.first->second[h.index()] = T();
    }

    inline bool has(Handle h) const {
        bool has = true;
        auto it = table.find(h.type());
        if (it == table.end() || h.index() >= it->second.size())
            has = false;
        return has;
    }

    inline void clone(Handle from, Handle to) {
        (*this)[to] = (*this)[from];
    }

};


template<typename T>
class VectorVector : public BaseContainer {
public:

    virtual bool coreHas(Handle h) const { return has(h); }
    virtual void coreClone(Handle from, Handle to) { clone(from, to); }
    virtual void coreSet(Handle h) { set(h); }

    using value_type = T;

    using table_type = std::vector<std::vector<T>>;

    table_type table;

    inline T& operator[](Handle h) {
        assert(h.type() < table.size() && h.index() < table[h.type()].size());
        return table[h.type()][h.index()];
    }

    inline void set(Handle h, const T& v) {
        if (h.type() >= table.size()) {
            table.resize(h.type());
        }  
        if (h.index() >= table[h.type()].size()) {
            table[h.type()].resize(h.index());
        }        
        table[h.type()][h.index()] = v;
    }

    inline void set(Handle h) {
        if (h.type() >= table.size()) {
            table.resize(h.type());
        }  
        if (h.index() >= table[h.type()].size()) {
            table[h.type()].resize(h.index());
        }        
        table[h.type()][h.index()] = T();
    }

    inline bool has(Handle h) const {
        return !(h.type() >= table.size() || h.index() >= table[h.type()].size());
    }

    inline void clone(Handle from, Handle to) {
        (*this)[to] = (*this)[from];
    }

};




#endif // ENTITY_HPP
