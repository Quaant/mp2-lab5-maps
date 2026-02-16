#include <iostream>
#include <vector>

template <typename Tkey, typename Tval>
class TMap
{
    struct pair
    {
        Tkey key;
        Tval val;
        pair(const Tkey &k, const Tval &v) : key(k), val(v);
    };

public:
    virtual bool search(const Tkey &key);
    virtual Tval search_elem(const Tkey &key);
    virtual void Insert(const Tkey &k, const Tval &v);

    virtual pair Pop(const Tkey &key);
    virtual pair Pop(size_t pos); // дописать в ordermap
    virtual void Remove(const Tkey &key);
    virtual void Remove(size_t pos); // дописать в ordermap
    virtual void resize();           // если массив заполнился, то перевыделяем память, в стд векторе в 2 раза увеличивается, мы будем делать мб в 1.5 раза
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