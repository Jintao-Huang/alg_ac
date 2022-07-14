
#ifndef _ORDERED_SM
#define _ORDERED_SM

#include "../load_modules.cpp"
#include "../io.cpp"

class OrderedSet
{
};

class OrderedMap
// 使用hashmap指向list节点的方法.
{
private:
    using list_pair = list<pair<int, int>>; // 存储k, v
    list_pair l;
    unordered_map<int, list_pair::iterator> um; // 存储k, ListNode

public:
    int &operator[](int i)
    {
        // 访问即赋值.
        if (um.count(i) == 0)
        {
            // 插入
            l.emplace_back(i, 0);
            list_pair::iterator i_it = l.end();
            i_it--;
            um[i] = i_it;
        }
        return get<1>(*um[i]);
    }

    void erase(int k)
    {
        auto it = um[k];
        um.erase(k);
        l.erase(it);
    }
    int back()
    {
        return get<1>(l.back());
    }
    int front()
    {
        return get<1>(l.front());
    }
    void pop_back()
    {
        auto t = l.back();
        l.pop_back();
        int k = get<0>(t);
        um.erase(k);
    }
    void pop_front()
    {
        auto t = l.front();
        l.pop_front();
        int k = get<0>(t);
        um.erase(k);
    }
    void move_to_end(int k, bool to_end = true)
    {
        int v = (*this)[k];
        this->erase(k); // erase的时候会把listnode
        (*this)[k] = v; // 重新生成listnode
    }

    int count(int k)
    {
        return um.count(k);
    }
    int size()
    {
        return um.size();
    }
    //
    vector<pair<int, int>> &to_vector(vector<pair<int, int>> &dst)
    {
        for (auto it = l.begin(); it != l.end(); ++it)
        {
            dst.emplace_back(*it);
        }
        return dst;
    }
    friend ostream &operator<<(ostream &out, OrderedMap &om)
    {
        vector<pair<int, int>> vp;

        out << om.to_vector(vp);
        return out;
    }
};

// int main(){
//     OrderedMap om;
//     om[0] = 1;
//     om[0] = 2;
//     om[2] = 3;
//     om[0] = 2;
//     cout << om << '\n';
// }
#endif
