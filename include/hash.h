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
        bool occupied; 
        bucket() : occupied(false) {}
        bucket(k& a, v& b){
            key = a; 
            value = b; 
            occupied = true; 
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

    int h1(const &k key, size_t hs, size_t s1){ 
        size_t h = hash<k>{}(key); // вот тут {} потому что hash это не функция а тип 
        h ^= s1; 
        h ^= h >> 17;
        h *= S1; 
        return h % hs; 
    }

    int h2(const &k key, size_t hs, size_t s2){
        size_t h = hash<k>{}(key); 
        h ^= s2;
        h ^= h >> 17; 
        h *= S1; 
        return hs + (h % hs);  // half_size .. table.size()-1

    }
    bool insert_into_table(vector<bucket>& ntable, size_t half, size_t s1, size_t s2, const k& key, const &v, val){ 
        k current_key = key; 
        v current_val = val; 
        size_t index = h1(current_key, half, s1);
        
        for (size_t i = 0; i < max_iteration; i++){ 
            if (!ntable[index].occupied){
                tbl[index] = bucket(current_key, current_value);
                return true; 
            }
            else if( ntable[index].key == current_key){
                ntable[index].val = current_val; 
                return true; 
            } 

            swap(current_key, ntable[index].key); 
            swap(current_val, ntable[index].val); 

            if (index < half){
                index = h2(current_key, half, s2);
            }
            else{
                index = h1(current_key, half, s1); 
            }

            }
            return false;
        }
    
    void rehash(){
        //algoritm: 
        //make resize and reseed h1 and h2; try to push all elements(insert_into_table) from old table 
        //if we can't push all, again make resize while we cannot push all 
        // when we push, we swap all variables
        size_t new_hc = half_capacity * 2; 
        vector <bucket> new_table(new_hc * 2); 
         

        random_device rd;
        
        
        size_t new_seed1 = rd(); 
        size_t new_seed2 = rd(); 

        size_t new_count = 0; 
        bool flag = true; 
        for (auto i : table){ 
            if (i.occupied){ 
                if (!insert_into_table(new_table, new_hc, new_seed1, new_seed2, i.key, i.val)){
                    flag = false; 
                    break; 
                }
            new_count++; 
            }
        }
        while (!flag){ 
            new_hc *= 2; 
            new_table.clear(); 
            new_table.resize(new_hc * 2); 

            random_device rd2;

            new_seed1 = rd2(); 
            new_seed2 = rd2(); 

            new_count = 0; 
            all_inserted = true; 

            for (auto i : table){ 
            if (i.occupied){ 
                if (!insert_into_table(new_table, new_hc, new_seed1, new_seed2, i.key, i.val)){
                    flag = false; 
                    break; 
                }
            new_count++; 
            }
        }
        }
        table = move(new_table); 
        seed1 = new_seed1; 
        seed2 = new_seed2; 
        num_elements = new_count; 
    }

    

    public:

    CockooHastTable(){ 
        random_device rd; 
        seed1 = rd(); 
        seed2 = rd(); 
        table(half_capacity * 2); 
    }
    void insert(const k& key, const v& val){
        if (need_resash()){ 
            rehash(); 
        }
        size_t pos1 = h1(key);
        size_t pos2 = h2(key);

        if (table[pos1].occupied && table[pos1].key == key) {
            table[pos1].value = value;
            return;
        }
        if (table[pos2].occupied && table[pos2].key == key) {
            table[pos2].value = value;
            return;
        }
        
        if (!insert_into_table(table, half_size(), seed1, seed2, key, value)) {
            rehash();
            insert_into_table(table, half_size(), seed1, seed2, key, value);
        }
        
        ++num_elements;
    }


    void remove(const k& key){
        if (Find(key) == nullptr){ 
            throw("can't find element in massive")
        }
        size_t pos1 = h1(key);
        if (table[pos1].occupied && table[pos1].key == key) {
            table[pos1].occupied = false;
            --num_elements;
            return;
        }
        
        size_t pos2 = h2(key);
        if (table[pos2].occupied && table[pos2].key == key) {
            table[pos2].occupied = false;
            --num_elements;
            return;
        }
        
        return;
    };
    
    
    v* Find(const k& key){
        size_t pos1 = h1(key); 
        if (table[pos1].occupied && table[pos1].key == key) {
            return &table[pos1].value;
        }
        
        size_t pos2 = h2(key);
        if (table[pos2].occupied && table[pos2].key == key) {
            return &table[pos2].value;
        }
        
        return nullptr;
    }; 

}