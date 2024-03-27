#ifndef JSON_JSON_HPP
#define JSON_JSON_HPP

#include <cassert>
#include <cstdint>
#include <string>
#include <vector>
#include <map>


//#include<generated/atoms.hpp>

// object, array, number, string, Boolean (true or false), or null.



// forward declare key value object
class JsonKeyValue;

class JsonValue {
public:
    using string_type = std::string;
    using map_type = std::map<std::string, JsonValue>;
    using vector_type = std::vector<JsonValue>;

    enum Enum : uint8_t {
        Null = 0,
        Object,
        Array,
        String,
        Boolean,
        Float32,
        Float64,
        Int64,
        Uint64,
        Int32,
        Uint32,
        Int16,
        Uint16,
        Int8,
        Uint8
    };

private:
    template<typename T>
    struct value_type {
        static const uint8_t id; 
    };

    struct Leaf {
        uint8_t type;
        string_type string;
        uint64_t other;
    
        inline Leaf() : other(0) { }
        inline Leaf(const char* s) : other(0), string(s) { }
        inline Leaf(const std::string& s) : other(0), string(s) { }
        
        // initialize primitive types that are stored in "value"
        template<typename T>
        inline Leaf(T t) : other(*reinterpret_cast<const uint64_t*>(&t)) { }

        // template to make implicit converions of "value" more pretty
        template<typename T>
        inline T get_value() const {
            if (type != value_type<T>::id) {
                uint64_t zero = 0;
                return *reinterpret_cast<const T*>(&zero);
            }
            return *reinterpret_cast<const T*>(&other);
        }

        // implicit conversions
        inline operator std::nullptr_t() const { return nullptr; }   
        
        inline operator std::string() const { return string; }
        inline operator const char*() const { return string.c_str(); }

        inline operator bool() const { return get_value<bool>(); }
        inline operator float() const { return get_value<float>(); }
        inline operator double() const { return get_value<double>(); }
        inline operator int64_t() const { return get_value<int64_t>(); }
        inline operator uint64_t() const { return get_value<uint64_t>(); }
        inline operator int32_t() const { return get_value<int32_t>(); }
        inline operator uint32_t() const { return get_value<uint32_t>(); }
        inline operator int16_t() const { return get_value<int16_t>(); }
        inline operator uint16_t() const { return get_value<uint16_t>(); }
        inline operator int8_t() const { return get_value<int8_t>(); }
        inline operator uint8_t() const { return get_value<uint8_t>(); }
        
    };

    Leaf data;
    vector_type vector;
    map_type map;

public:
    inline static const JsonValue& globalNull() {
        static const JsonValue v = JsonValue(nullptr);
        return v;
    }

    // used to initialize arrays and objects
    inline JsonValue(std::initializer_list<JsonValue> v);
    inline JsonValue(std::initializer_list<JsonKeyValue> v);

    // initialize primitive types
    inline JsonValue() { }
    inline JsonValue(std::nullptr_t v) { }
    inline JsonValue(const char* v) : data(v) { }
    inline JsonValue(const std::string& v) : data(v) { }
    inline JsonValue(bool v) : data(v) { }
    inline JsonValue(float v) : data(v) { }
    inline JsonValue(double v) : data(v) { }
    inline JsonValue(int64_t v) : data(v) { }
    inline JsonValue(uint64_t v) : data(v) { }
    inline JsonValue(int32_t v) : data(v) { }
    inline JsonValue(uint32_t v) : data(v) { }
    inline JsonValue(int16_t v) : data(v) { }
    inline JsonValue(uint16_t v) : data(v) { }
    inline JsonValue(int8_t v) : data(v) { }
    inline JsonValue(uint8_t v) : data(v) { }
    

    // functions
    inline bool isNull() const {
        return data.type == Null;
    }

    inline size_t count() const {
        switch (data.type) {
        case Object:    return map.size();
        case Array:     return vector.size();
        case String:    return data.string.size();
        default:        return 0;
        };
    }

    inline const map_type& object() const {
        return map;
    }

    inline const vector_type& array() const {
        return vector;
    }

    inline const Leaf& value() const {
        return data;
    }

    inline const JsonValue& operator[](size_t index) const {
        if (index < 0 || index >= vector.size()) {
            return globalNull();
        }
        return vector[index];
    }
    
    inline const JsonValue& operator[](const char* key) const {
        auto iter = map.find(key);
        if (iter == map.end()) {
            return globalNull();
        }
        return iter->second;
    }

};

// used to initalize objects
class JsonKeyValue {
public:
    std::string key;
    JsonValue value;
    inline JsonKeyValue(const std::string& s, const JsonValue& v) : key(s), value(v) { }
};

inline JsonValue::JsonValue(std::initializer_list<JsonValue> v) {
    data.type = Object;
    vector.insert(vector.end(), v.begin(), v.end());
}

inline JsonValue::JsonValue(std::initializer_list<JsonKeyValue> v) {
    data.type = Array;
    auto iter = v.begin();
    while (iter != v.end()) {
        map.insert(std::make_pair(iter->key, iter->value));
        ++iter;
    }
}

// this is so I only have to link types to ids once
template<> struct JsonValue::value_type<bool> { static const uint8_t id = JsonValue::Boolean; };
template<> struct JsonValue::value_type<float> { static const uint8_t id = JsonValue::Float32; };
template<> struct JsonValue::value_type<double> { static const uint8_t id = JsonValue::Float64; };
template<> struct JsonValue::value_type<int64_t> { static const uint8_t id = JsonValue::Int64; };
template<> struct JsonValue::value_type<uint64_t> { static const uint8_t id = JsonValue::Uint64; };
template<> struct JsonValue::value_type<int32_t> { static const uint8_t id = JsonValue::Int32; };
template<> struct JsonValue::value_type<uint32_t> { static const uint8_t id = JsonValue::Uint32; };
template<> struct JsonValue::value_type<int16_t> { static const uint8_t id = JsonValue::Int16; };
template<> struct JsonValue::value_type<uint16_t> { static const uint8_t id = JsonValue::Uint16; };
template<> struct JsonValue::value_type<int8_t> { static const uint8_t id = JsonValue::Int8; };
template<> struct JsonValue::value_type<uint8_t> { static const uint8_t id = JsonValue::Uint8; };



#endif // JSON_JSON_HPP