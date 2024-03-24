#ifndef ENTITY_HPP
#define ENTITY_HPP

//#include <typeinfo
#include <cstdint>
#include <vector>
#include <map>


class Handle {
public:
    inline Handle() { value.raw = 0; }
    inline Handle(uint8_t t, uint16_t i, uint16_t g) {
        value.type = t;
        value.index = i;
        value.generation = g;
    }

    inline uint16_t type() const { return value.type; }
    inline uint16_t index() const { return value.index; }
    inline uint16_t generation() const { return value.generation; }

    inline bool isNull() const { return value.raw == 0; }  

    union {
        struct {
            uint32_t index : 14;
            uint32_t generation : 10;
            uint32_t type : 8;
        };
        uint32_t raw;
    } value;

};


template<typename T>
using twod_vector = std::vector<std::vector<T>>;

template<typename... Ts>
class NodeData {
public:
    static const uint16_t END_OF_LIST = 0;
    
    // data types
    using tuple_type = std::tuple<Ts...>;
    constexpr static size_t tuple_size = std::tuple_size<tuple_type>::value;

    // type from integer
    template<uint16_t N>
    using node_type = typename std::tuple_element<N, tuple_type>::type;

    // tuple of vectors
    using node_vector_type = std::tuple<std::vector<Ts>...>;

    // tuple of vectors
    node_vector_type data;

    // head vector
    std::vector<uint16_t> head;

    // data used for all nodes
    twod_vector<uint16_t> free;
    twod_vector<uint16_t> generation;
    twod_vector<uint8_t> flags;
    
    // node links
    twod_vector<Handle> parent;
    twod_vector<Handle> firstChild;
    twod_vector<Handle> prevSib;
    twod_vector<Handle> nextSib;

    inline void resize_types(size_t size) {
        head.resize(size);
        
        free.resize(size);
        generation.resize(size);
        flags.resize(size);
        
        parent.resize(size);
        firstChild.resize(size);
        prevSib.resize(size);
        nextSib.resize(size);
    }

    inline NodeData() {
        resize_types(tuple_size + 1);
        // create null node!
        create<0>();
    }

    inline size_t type_count() const {
        return head.size();
    }

    inline size_t node_count(uint16_t type) const {
        return free[type].size();
    }

    inline void resize_nodes(uint16_t type, size_t size) {
        free[type].resize(size);
        generation[type].resize(size);
        flags[type].resize(size);

        parent[type].resize(size);
        firstChild[type].resize(size);
        prevSib[type].resize(size);
        nextSib[type].resize(size);
    }


    inline bool valid(Handle node) {
        return generation[node.type()][node.index()] == node.generation();
    }

    template<uint16_t N>
    inline Handle create() {
        uint16_t value = head[N];
        if (value == END_OF_LIST ) {
            value = node_count(N);
            resize_nodes(N, value + 1);
            // zero is for generic nodes that have no data!
            if constexpr(N > 0)
                std::get<N-1>(data).resize(value + 1);
            free[N][value] = END_OF_LIST;
            flags[N][value] = NoFl::Allocated;
        } else {
            head[N] = free[N][value];
            free[N][value] = END_OF_LIST;
        }
        return Handle(N, value, generation[N][value]);
    }

    // prints every element of a tuple
    template<size_t I = 0>
    inline void createHelper(uint16_t type, Handle& node) {
        if (I == type)
            node = create<I>();
        if constexpr(I < tuple_size)
            createHelper<I+1>(type, node);
    }
    
    inline Handle createDynamic(uint16_t type) {
        Handle node;
        createHelper<0>(type, node);
        return node;
    }

    inline void destroy(Handle node) {
        if (!node.isNull()) {
            ++generation[node.type()][node.index()];
            flags[node.type()][node.index()] = NoFl::None;
            free[node.type()][node.index()] = head[node.type()];
            head[node.type()] = node.index();
        }
    }

    // breaks if you try and get generic node data!
    template<uint16_t N>
    inline std::vector<node_type<N-1>>& get_data() {
        return std::get<N-1>(data);
    }

};


template<class U>
class Reference {
public:
    U& data;
    Handle handle;




};





#endif // ENTITY_HPP
