#ifndef HASH_H
#define HASH_H

#include <cstddef>
#include <functional>
#include <random>
#include <stdexcept>
#include <utility>
#include <vector>

template <typename K, typename V>
class CockooHashTable {
private:
    static constexpr size_t kMul = 0x9e3779b97f4a7c15ULL;
    static constexpr double kMaxLoad = 0.48;
    static constexpr size_t kMaxKick = 128;

    struct Bucket {
        K key{};
        V value{};
        bool occupied = false;
    };

    std::vector<Bucket> table_;
    size_t half_ = 16;
    size_t num_elem_ = 0;
    size_t seed1_ = 0;
    size_t seed2_ = 0;

    size_t mix(size_t h) const {
        h ^= h >> 17;
        h *= kMul;
        return h;
    }

    size_t index1(const K& key) const {
        size_t h = std::hash<K>{}(key);
        h ^= seed1_;
        h = mix(h);
        return h % half_;
    }

    size_t index2(const K& key) const {
        size_t h = std::hash<K>{}(key);
        h ^= seed2_;
        h = mix(h);
        return half_ + (h % half_);
    }

    double load_factor() const {
        if (table_.empty()) {
            return 0.0;
        }
        return static_cast<double>(num_elem_) / static_cast<double>(table_.size());
    }

    bool need_rehash() const { return load_factor() > kMaxLoad; }

    bool insert_no_rehash(const K& key, const V& val) {
        K cur_k = key;
        V cur_v = val;
        size_t idx = index1(cur_k);

        for (size_t iter = 0; iter < kMaxKick; ++iter) {
            if (!table_[idx].occupied) {
                table_[idx].key = cur_k;
                table_[idx].value = cur_v;
                table_[idx].occupied = true;
                ++num_elem_;
                return true;
            }
            if (table_[idx].key == cur_k) {
                table_[idx].value = cur_v;
                return true;
            }
            std::swap(cur_k, table_[idx].key);
            std::swap(cur_v, table_[idx].value);
            const size_t i1 = index1(cur_k);
            const size_t i2 = index2(cur_k);
            idx = (idx == i1) ? i2 : i1;
        }
        return false;
    }

    void grow_and_reseed() {
        std::vector<std::pair<K, V>> items;
        items.reserve(num_elem_);
        for (const Bucket& b : table_) {
            if (b.occupied) {
                items.emplace_back(b.key, b.value);
            }
        }

        std::random_device rd;
        for (;;) {
            half_ *= 2;
            table_.assign(2 * half_, Bucket{});
            num_elem_ = 0;
            seed1_ = (static_cast<size_t>(rd()) << 32) ^ static_cast<size_t>(rd());
            seed2_ = (static_cast<size_t>(rd()) << 32) ^ static_cast<size_t>(rd());
            if (seed1_ == seed2_) {
                ++seed2_;
            }

            bool ok = true;
            for (const auto& kv : items) {
                if (!insert_no_rehash(kv.first, kv.second)) {
                    ok = false;
                    break;
                }
            }
            if (ok) {
                return;
            }
        }
    }

public:
    CockooHashTable() {
        std::random_device rd;
        seed1_ = (static_cast<size_t>(rd()) << 32) ^ static_cast<size_t>(rd());
        seed2_ = (static_cast<size_t>(rd()) << 32) ^ static_cast<size_t>(rd());
        if (seed1_ == seed2_) {
            ++seed2_;
        }
        table_.assign(2 * half_, Bucket{});
    }

    void insert(const K& key, const V& val) {
        if (V* p = Find(key)) {
            *p = val;
            return;
        }
        for (;;) {
            while (need_rehash()) {
                grow_and_reseed();
            }
            if (insert_no_rehash(key, val)) {
                return;
            }
            grow_and_reseed();
        }
    }

    void remove(const K& key) {
        const size_t i1 = index1(key);
        if (table_[i1].occupied && table_[i1].key == key) {
            table_[i1].occupied = false;
            --num_elem_;
            return;
        }
        const size_t i2 = index2(key);
        if (table_[i2].occupied && table_[i2].key == key) {
            table_[i2].occupied = false;
            --num_elem_;
            return;
        }
        throw std::runtime_error("remove: key not found");
    }

    V* Find(const K& key) {
        const size_t i1 = index1(key);
        if (table_[i1].occupied && table_[i1].key == key) {
            return &table_[i1].value;
        }
        const size_t i2 = index2(key);
        if (table_[i2].occupied && table_[i2].key == key) {
            return &table_[i2].value;
        }
        return nullptr;
    }
};

#endif
