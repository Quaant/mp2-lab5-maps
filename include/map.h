#include <iostream>
#include <vector>

template <typename Tkey, typename Tval>
class TMap
{
    struct Node
    {
        Tkey key;
        Tval val;
        Node(const Tkey &k, const Tval &v) : key(k), val(v);
    };
    std::vector<Node *> list;
    size_t size;     // фактическое количество занятых
    size_t capacity; // размер массива
public:
    virtual bool search(Tkey key);
    virtual Node search(Tkey key);
    virtual void Insert(Tkey key);
    virtual Node Pop(Tkey key); // тут после удаления надо вернуть предыдущую ноду
    virtual void Remove(Tkey key);
    virtual size_t size();
    virtual size_t musor(); // вернуть количество пустых яйчеек capacity - size
    virtual size_t capacity();
    virtual void resize(); // если массив заполнился, то перевыделяем память, в стд векторе в 2 раза увеличивается, мы будем делать мб в 1.5 раза
};