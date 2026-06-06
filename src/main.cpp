#include <iostream>
#include <vector>
#include "heap.h"
using namespace std;

int main() {
    vector <int> a = {1, 2, 3, 4, 5};
    dheap <int> h(a, 3); 
    

    h.print();

    h.push(-1);
    h.print();
    
    h.remove(2);
    
    h.print(); 
    
    return 0;
}
