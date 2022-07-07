

#include "pre.cpp"

int main()
{
    Trie trie;
    trie.insert("apple");
    cout << trie.search("apple");
    cout << trie.search("app");
    cout << trie.starts_with("app");
    trie.insert("app");
    cout << trie.search("app");
}