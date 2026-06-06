
#include <benchmark/benchmark.h>
#include "../include/hash.h"
#include <string>
#include <random>
#include <vector>


static void BM_CockooInsert(benchmark::State& state) {
    for (auto _ : state) {
        CockooHashTable<int, int> table;
        for (int i = 0; i < state.range(0); ++i) {
            table.insert(i, i * 2);
        }
    }
}
BENCHMARK(BM_CockooInsert)->Range(8, 8 << 10);

static void BM_CockooFind(benchmark::State& state) {
    CockooHashTable<int, int> table;
    for (int i = 0; i < state.range(0); ++i) {
        table.insert(i, i * 2);
    }

    for (auto _ : state) {
        benchmark::DoNotOptimize(table.Find(state.range(0) / 2));
    }
}
BENCHMARK(BM_CockooFind)->Range(8, 8 << 10);

static void BM_CockooFindMiss(benchmark::State& state) {
    CockooHashTable<int, int> table;
    for (int i = 0; i < state.range(0); ++i) {
        table.insert(i, i * 2);
    }

    for (auto _ : state) {
        benchmark::DoNotOptimize(table.Find(-1));
    }
}
BENCHMARK(BM_CockooFindMiss)->Range(8, 8 << 10);


static void BM_CockooRemove(benchmark::State& state) {
    for (auto _ : state) {
        state.PauseTiming();
        CockooHashTable<int, int> table;
        const int n = static_cast<int>(state.range(0));
        for (int i = 0; i < n; ++i) {
            table.insert(i, i * 2);
        }
        state.ResumeTiming();
        table.remove(n / 2);
    }
}
BENCHMARK(BM_CockooRemove)->Range(8, 8 << 10);


static void BM_CockooRandomInsert(benchmark::State& state) {
    std::mt19937 gen(42);
    std::uniform_int_distribution<int> dist(0, state.range(0) * 10);

    std::vector<int> keys(state.range(0));
    for (int i = 0; i < state.range(0); ++i) {
        keys[i] = dist(gen);
    }

    for (auto _ : state) {
        CockooHashTable<int, int> table;
        for (int i = 0; i < state.range(0); ++i) {
            table.insert(keys[i], i);
        }
    }
}
BENCHMARK(BM_CockooRandomInsert)->Range(8, 8 << 10);

static void BM_CockooRandomFind(benchmark::State& state) {
    std::mt19937 gen(42);
    std::uniform_int_distribution<int> dist(0, state.range(0) * 10);

    CockooHashTable<int, int> table;
    std::vector<int> keys(state.range(0));
    for (int i = 0; i < state.range(0); ++i) {
        keys[i] = dist(gen);
        table.insert(keys[i], i);
    }

    size_t index = 0;
    for (auto _ : state) {
        benchmark::DoNotOptimize(table.Find(keys[index]));
        index = (index + 1) % keys.size();
    }
}
BENCHMARK(BM_CockooRandomFind)->Range(8, 8 << 10);


BENCHMARK_MAIN();
    





   float swish_fwd(float s, float alpha) {                    
       //  1) calculate alpha * x                         
       float alpha_x = alpha * s;                                                                        
       // 2) calculate sigmoid(alpha * x)                                
       float v = logistic_fwd(alpha_x);                                                            
   }                                                      
   float logistic_fwd(float x) {                              
       return 1.0f / (1.0f + expf(-x));                      
   }                                                                              
   // For shape 1×64×56×56 = 200 704 elements:             
   for (int i = 0; i < 200704; i++) {                         
       output[i] = swish_fwd(input[i], alpha);                
   }                                                          
   // Problems:                                               
   // ❌ 200 704 calls swish_fwd()                          
   // ❌ 200 704 calls logistic_fwd()                       
   // ❌ 200 704 calls expf()                             
   // ❌ Processing 1 element per iteration               
   // ❌ RVV vector registers are idle



 





   void jit_swish_emitter::emit_isa() {                       
       // 1) save original input vector x                 
       vmv.v.v(vaux, vsrc)        // vaux = x (all elements)                                                                
       // 2) load alpha scalar into float register       
       load_table_val("swish_alpha", falpha)                  
       // 3) multiply by alpha (vector instruction)      
       vfmul.vf (vsrc, vsrc, falpha)  // src = alpha * x                                                              
       // 4) compute sigmoid(alpha * x)                  
       // (delegated to nested jit_sigmoid_emitter)           
       sigmoid_emitter->emit_code()                           
       // inside sigmoid: exp → vfdiv.vv → result in vdst    

       // 5) final multiply by saved original x          
       vfmul.vv  vdst, vdst, vaux  // dst = x * sigmoid       
   }                                                                                                            
   // Advantages over reference:                               
   // ✅ 0 C++ function calls                                  
   // ✅ 16+ elements per instruction (RVV vectors)            
   // ✅ All operations in vector registers                    
   // ✅ Alpha constant loaded from data section               
   // ✅ Code generated once, reused for every inference       
   // Comparison on 200K element tensor:                       
   // Reference: ~600K function calls (swish + logistic + exp) 
   // JIT:       ~12K vector instructions (50x fewer)         
