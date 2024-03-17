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
