#include <iostream>
#include "avltree.h" 
#include <typeinfo> 


using namespace std; 


int main()
{
     
    avltree <int, double> t; 
    t.insert(2, 2.0); 
    cout << "!!!!!!!!!!!!!" << endl;
    t.insert(1, 1.0); 
    cout << "!!!!!!!!!!!!!" << endl;
     t.insert(3, 3.0); 
     cout << "!!!!!!!!!!!!!" << endl;
     t.insert(4, 4.0); 
     cout << "!!!!!!!!!!!!!" << endl;
    t.printAvlTree(); 
    cout << "ok" << endl; 
    return 0;
}
