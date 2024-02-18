#include <memory>
#include <span>
#include <unordered_map>

template <typename V>
class Value {
public:
    V value;
    long time;

    Value(V v, long t)
    {
        value = v;
        time = t;
    }
};

template <typename K, typename V>
class HashMap {
private:
    std::unordered_map<K, Value<V>> _map;
    long _time;
    std::shared_ptr<Value<V>> _setAll;

public:
    HashMap()
        : _time(0)
        , _setAll(std::make_shared<Value<V>>(V(), -1))
    {
    }

    void put(const K& key, const V& value)
    {
        _map[key] = std::make_shared<Value<V>>(value, _time++);
    }

    void setAll(const V& value)
    {
        _setAll = std::make_shared<Value<V>>(value, _time++);
    }

    V get(const K& key)
    {
        if (_map.find(key) == _map.end()) {
            return V();
        }
        if (_map[key]->time > _setAll->time) {
            return _map[key]->value;
        } else {
            return _setAll.value;
        }
    }
};