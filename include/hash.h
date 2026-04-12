#include <iostream>
#include <functional> 
#include <random>

using namespace std; 


template <typename k, typename v>
class CockooHashTable{ 
    private: 
    static constexpr size_t S1 = 0x9e3779b97f4a7c15; 
    size_t seed1, seed2; 
    static constexpr double rehash_const = 0.5; 

    size_t max_iteration = 128; 

    struct bucket {
        k key; 
        v value;  
        bucket(k& a, v& b){
            key = a; 
            value = b; 
        }
        bucket(bucket&& other) noexcept 
            : key(move(other.key))
            , value(move(other.value));
        }
        
        
        bucket& operator=(bucket&& other) noexcept {
            if (this != &other) {
                key = move(other.key);
                value = move(other.value);
               
            }
            return *this;
        }
    }
    vector<bucket> table;
    size_t half_capacity = 16; 
    size_t num_elem = 0; 
   
    double load_factor(){ 
        return static_cast<double>(num_elem / table.size());
    }

    bool need_rehash(){ 
        if (load_factor() > rehash_const){ 
            return true;
        }
        return false; 
    }

    size_t half_size() {
        return table.size() / 2;
    }

    int h1(const &k key, size_t hs){ 
        size_t h = hash<k>{}(key); // вот тут {} потому что hash это не функция а тип 
        h ^= seed2; 
        h ^= h >> 17;
        h *= S1; 
        return h % hs; 
    }

    int h2(const &k key, size_t hs){
        size_t h = hash<k>{}(key); 
        h ^= seed2;
        h ^= h >> 17; 
        h *= S1; 
        return hs + (h % hs);  // half_size .. table.size()-1

    }

    void rehash(){
        size_t new_hc = half_capacity * 2; 
        vector <bucket> new_table(new_hc * 2); 

        random_device rd;

        size_t new_seed1 = rd(); 
        size_t new_seed2 = rd(); 

        size_t new_count 
        for (auto i : table){ 

        }

    };
    

    public:

    void insert(double val){}; 
    void remove(double val){}; 
    double Find(double val){}; 

}