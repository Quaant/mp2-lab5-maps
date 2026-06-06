#ifndef HEAP_H
#define HEAP_H

#include <algorithm>
#include <vector>

using namespace std;

template <typename T>
class dheap {
private:
    int d;
    vector<T> a;

    int parent(int i) const { return (i - 1) / d; }
    int first_child(int i) const { return d * i + 1; }

    void sift_up(int i) {
        while (i > 0) {
            const int p = parent(i);
            if (a[p] <= a[i]) {
                break;
            }
            swap(a[p], a[i]);
            i = p;
        }
    }

   
    void sift_down(int i) {
        const int n = a.size();
        while (true) {
            const int fc = first_child(i);
            if (fc >= n) {
                break;
            }
            int best = fc;
            const int last = min(fc + d, n);
            for (int j = fc + 1; j < last; ++j) {
                if (a[j] < a[best]) {
                    best = j;
                }
            }
            if (a[i] <= a[best]) {
                break;
            }
            swap(a[i], a[best]);
            i = best;
        }
    }

    void heapify(vector<T>& t, int dd) {
        if (dd < 2) {
            throw("arnost must be at least 2");
        }
        d = dd;
        a = move(t);
        for (int i = parent(a.size() - 1); i >= 0; --i) {
            sift_down(i);
        }
    }

public:
    dheap() : d(2) {}

    dheap(vector<T> t, int dd) { heapify(t, dd); }

    void push(const T& x) {
        a.push_back(x);
        sift_up(a.size() - 1);
    }


    T pop() {
        if (a.empty()) {
            throw("heap is empty");
        }
        T result = move(a[0]);
        a[0] = move(a.back());
        a.pop_back();
        if (!a.empty()) {
            sift_down(0);
        }
        return result;
    }

    const T& top() const {
        if (a.empty()) {
            throw("heap is empty");
        }
        return a[0];
    }

    void remove(int ind){ 
        a[ind] = move(a.back());  
        a.pop_back();              
        if (ind < a.size()) {
            sift_up(ind);          
            sift_down(ind);        
        }
    }

    bool empty() const { return a.empty(); }
    size_t size() const { return a.size(); }
    int arnost() const { return d; }
    void print(){ 
        for (int i = 0; i < a.size(); i++){ 
            cout << a[i] << ' '; 
        }
        cout << endl; 
    }
};

#endif
