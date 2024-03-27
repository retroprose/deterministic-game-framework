#ifndef CONTAINER_HPP
#define CONTAINER_HPP

#include <cassert>
#include <cstdint>
#include <vector>
#include <map>
#include <algorithm>

/*
    This file contains containers implemented with the standard library.
    These could be reimplemented from scratch if you want to avoid the
    standard library all together.
*/

/*
    This class simply encapsulates a pointer.  It will assert if
    the pointer is dereferenced and that pointer is nullptr
*/
template<typename T>
class Ref {
public:
    Ref(T* ptr = nullptr) : ptr_(ptr) { }

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




template<typename T>
class VectorMap {
public:
	
    
    using hash_type = VMHash;
    
    using table_type = std::map<uint8_t, std::vector<T>>;
    
    using vector_iterator = typename std::vector<T>::iterator;


    using pair_type = std::pair<uint8_t, std::vector<T>>;
    table_type table;

    using value_type = T;

    size_t size() const {
        return 0;
    }

    bool hasHash(hash_type hash) const {
        bool has = true;
        typename table_type::const_iterator it = table.find(hash.signature);
        if (it == table.end() || hash.index >= it->second.size())
            has = false;
        return has;
    }

    T& operator[](hash_type hash) {
        typename table_type::iterator it = table.find(hash.signature);
        assert(it != table.end() && hash.index < it->second.size());
        return it->second[hash.index];
    }

    Ref<T> find(hash_type hash) {
        Ref<T> ref;
        typename table_type::iterator it = table.find(hash.signature);
        if (it != table.end() && hash.index < it->second.size()) {
            ref = Ref<T>( &(it->second[hash.index]) );
        }
        return ref;
    }

    typename table_type::iterator begin() {
        return table.begin();
    }

    typename table_type::iterator end() {
        return table.end();
    }

    vector_iterator begin(uint16_t signature) {
        return table[signature].begin();
    }

    vector_iterator end(uint16_t signature) {
        return table[signature].begin();
    }

    /*
        This function will move a component from one hash to another as
        signatures of entities change.
    */
    void move(hash_type oldHash, hash_type newHash) {
        typename table_type::iterator newSig = table.find(newHash.signature);
        if (newSig == table.end()) {
            if (newHash.signature == 0) return;
            auto ret = table.insert(pair_type(newHash.signature, std::vector<T>()));
            newSig = ret.first; // BUG?!
        }

        if (newSig->second.size() <= newHash.index) {
            newSig->second.resize(newHash.index + 1);
        }

        typename table_type::iterator oldSig = table.find(oldHash.signature);

        if (oldSig != table.end()) {
            std::swap(oldSig->second[oldHash.index], newSig->second[newHash.index]);
        }
    }

};



/*
    This container is simply a wrapper around a vector,
    all objects are stored sequentially in memory.
*/
/*
template<typename T>
class Dense {
private:
    using table_type = std::vector<T>;
    table_type table;

public:
    using value_type = T;

	void clear() {
		table.clear();
	}

    size_t size() const {
        return table.size();
    }

    const T& operator[](uint16_t index) const {
        assert(index >= 0 && index < table.size());
        return table[index];
    }

    T& operator[](uint16_t index) {
        assert(index >= 0 && index < table.size());
        return table[index];
    }

    Ref<T> find(uint16_t index) {
        Ref<T> ref;
        if (index >= 0 && index < table.size())
            ref = Ref<T>( &(table[index]) );
        return ref;
    }

	typename table_type::iterator begin() {
		return table.begin();
	}

	typename table_type::iterator end() {
		return table.end();
	}

    void insert(uint16_t index) {
        if ((uint32_t)(index + 1) > table.size()) {
            table.resize((uint32_t)(index + 1));
        }
    }

    void erase(uint16_t index) {

    }

};
*/







#endif // CONTAINER_HPP
