
#include "std_pre.cpp"

class LRUCache
{
public:
    int capacity;
    OrderedMap om;
    LRUCache(int capacity)
    {
        this->capacity = capacity;
    }

    int get(int key)
    {
        // 已经存在: 获取返回v, 调整位置
        // 不存在: 返回-1
        int v = -1;
        if (om.count(key))
        {
            v = om[key];
            om.move_to_end(key, true);
        }
        return v;
    }

    void put(int key, int value)
    {
        // 已经存在: 更改v, 调整位置
        // 不存在: 插入最后; 逐出(容量)
        bool exists = om.count(key);
        om[key] = value;
        if (exists)
        {
            om.move_to_end(key, true);
        }
        else if (om.size() > capacity)
        {
            om.pop_front();
        }
    }
};

int main()
{
    LRUCache lRUCache(2);
    lRUCache.put(1, 1);              // 缓存是 {1=1}
    lRUCache.put(2, 2);              // 缓存是 {1=1, 2=2}
    cout << lRUCache.get(1) << '\n'; // 返回 1
    lRUCache.put(3, 3);              // 该操作会使得关键字 2 作废，缓存是 {1=1, 3=3}
    cout << lRUCache.get(2) << '\n'; // 返回 -1 (未找到)
    lRUCache.put(4, 4);              // 该操作会使得关键字 1 作废，缓存是 {4=4, 3=3}
    cout << lRUCache.get(1) << '\n'; // 返回 -1 (未找到)
    cout << lRUCache.get(3) << '\n'; // 返回 3
    cout << lRUCache.get(4) << '\n'; // 返回 4
    cout << lRUCache.om << '\n';
}
