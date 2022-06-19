#include "load-modules.cpp"

#ifndef _IO
#define _IO
ostream &operator<<(ostream &out, const vector<int> &v)
{
    out << '[';
    bool is_first = true;
    for (const int &x : v)
    {
        if (is_first)
        {
            is_first = false;
        }
        else
        {
            out << ", ";
        }
        //
        if (x == INT32_NULL)
        {
            out << "null";
        }
        else
        {
            out << x;
        }
    }
    out << ']';
    return out;
}

template<class T>
using pii = pair<T, int>;

template<class T>
ostream &operator<<(ostream &out, const vector<pii<T>> &vp)
{
    out << '{';
    bool is_first = true;
    for(const pair<T, int> &p : vp)
    {
        if (is_first)
        {
            is_first = false;
        }
        else
        {
            out << ", ";
        }
        out << p.first << ": "<< p.second;
    }
    out << '}';
    return out;
}

template <class T>
vector<pii<T>>& _unordered_map_to_vector(const unordered_map<T, int> &um, vector<pii<T>> &dst){
    for(typename unordered_map<T, int>::const_iterator it= um.begin(); it!=um.end(); it++){
        dst.emplace_back(*it);
    }
    return dst;
} 

template<class T>
ostream &operator<<(ostream &out, const unordered_map<T, int> &um){
    vector<pii<T>> vpii;
    out << _unordered_map_to_vector(um, vpii);
    return out;
}

// int main()
// {
//     unordered_map<string, int> um;
//     um["123"] = 1;
//     um["#45"] = 5;
//     cout << um << '\n';
//     //
//     unordered_map<int, int> um2;
//     um2[2] = 1;
//     um2[3] = 5;
//     cout << um2 << '\n';
// }





#endif