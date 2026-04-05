#include <iostream>
#include "avltree.h" 
#include <typeinfo> 


using namespace std; 


int main()
{
     
    avltree <int, double> t; 
    t.insert(30, 3.0); 
    cout << "!!!!!!!!!!!!!" << endl;
    t.insert(10, 1.0); 
    cout << "!!!!!!!!!!!!!" << endl;
     t.insert(20, 2.0);  
     cout << "!!!!!!!!!!!!!" << endl;
     cout << "!!!!!!!!!!!!!!!!!!" << endl; 
    t.printAvlTree(); 
    cout << "ok" << endl; 
    return 0;
}
