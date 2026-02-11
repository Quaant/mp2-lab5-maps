#include <iostream>
#include <vector>

template <typename Tkey, typename Tval>
class TMap
{
    struct Node
    {
        Tkey key;
        Tval val;
        Node *next;
        Node(const Tkey &k, const Tval &v, Node *n) : key(k), val(v), next(n);
    };
    std::vector<Node *> a;
    size_t size;     // фактическое количество занятых
    size_t capacity; // размер массива
public:
    virtual bool search(const Tkey &key);
    virtual Node search(const Tkey &key);
    virtual void Insert(const Tkey &k, const Tval &v);
    Node &operator[](size_t pos)
    {
        return a[pos];
    }
    virtual Node Pop(const Tkey &key);
    virtual void Remove(const Tkey &key);
    size_t size()
    {
        return size;
    };
    size_t musor() // вернуть количество пустых яйчеек capacity - size
    {
        return capacity - size;
    };
    size_t capacity()
    {
        return capacity;
    };
    virtual void resize(); // если массив заполнился, то перевыделяем память, в стд векторе в 2 раза увеличивается, мы будем делать мб в 1.5 раза
    ostream &operator<<(ostream &out, Tmap<Tkey, Tval> &l)
    {
        out << "[";
        for (int i = 0; i < l.size(); i++)
        {
            out << "{" << l.a[i]->key << ": " << l.a[i]->val << "}";
            if (i < size - 1)
            {
                out << ", ";
            }
        }
        out << "]";
        return out;
    };
};