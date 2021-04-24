#include <bits/stdc++.h>
#include "trienode.hpp"
using namespace std;

template<typename T>
class trie{
    private:
        // Private Members
        TrieNode<T>* root;
        int capacity;

        // Private Methods
        TrieNode<T>* createNode(char key);
        TrieNode<T>* deleteNode(TrieNode<T>* root, string key, int depth = 0);
        void recursive_destroy(TrieNode<T>* root);

    public:
        // using iterator = trie_iterator<T>;

        // begin and end objects of template class trie_iterator
        // iterator begin();
        // iterator end();

        trie() {
            root = this->createNode('#');
            capacity = 0;
        }
        ~trie()
        {
            TrieNode<T>* parse = this->root;
            recursive_destroy(root);
            
            
        }
        T& operator[] (string key) {
            return ((this->insert(key))->value);
        }

        void deepcopyroot(TrieNode<T>* a, TrieNode<T>* b){
            for(auto x: a->next){
                b->next[x.first] = createNode(x.first);
                b->next[x.first]->addParent(b);
                b->eow = a->eow;
                b->value = a->value;
                deepcopyroot(x.second, b->next[x.first]);
            }
        }

        trie<T>& operator= (const trie<T> &x) {
            if(this != &x){
                this->capacity = x.capacity;
                deepcopyroot(x.root, this->root);
            }
            return *this;
        }

        TrieNode<T>* insert(string key, T value = T());
        bool contains(string key);
        void erase(string key);
        bool empty();
        int size();
};

template<typename T> void :: recursive_destroy(TrieNode<T>* root)
{
    if(root->next.size() == 0)
    {   
        delete(root);
        return;
    }
    map<char, TrieNode<T> *> :: iterator it = root->next.begin();
    for (it; it != root->next.end(); it++)
    {
        recursive_destroy(it.second);
        cout << it.second << " ";
    }
        
}

template<typename T> 
TrieNode<T>* trie<T>::createNode(char key) {
    TrieNode<T>* node = new TrieNode<T>();
    node->key = key;
    node->eow = 0;
    node->value = T();
    return node;
}

template<typename T>
TrieNode<T>* trie<T>::insert(string key, T value) {
    TrieNode<T>* parse = this->root;
    for(int i=0; i<key.size(); i++) {
        if(parse->next.find(key[i]) == parse->next.end()) {
          parse->next[key[i]] = this->createNode(key[i]);
          parse->next[key[i]]->addParent(parse);
        }
        parse = parse->next[key[i]];
    }
    if(!parse->eow) this->capacity++;
    parse->eow = 1;
    return parse;
}

template<typename T>
TrieNode<T>* trie<T>::deleteNode(TrieNode<T>* root, string key, int depth) {
    if (!root) return NULL;
    if (depth == key.size()) {
        if (root->eow) {this->capacity--; root->eow = 0;}
        if (root->next.empty()) {
            delete (root);
            root = NULL;
        }
        return root;
    }

    TrieNode<T>* temp = this->deleteNode(root->next[key[depth]], key, depth + 1);
    if(!temp) root->next.erase(key[depth]);
    else root->next[key[depth]] = temp;

    if (root->next.empty() && !root->eow) {
        delete (root);
        root = NULL;
    }
    return root;
}


template<typename T>
bool trie<T>::contains(string key) {
    TrieNode<T> *parse = this->root;
    for(int i=0; i<key.size(); i++) {
        if(parse->next.find(key[i]) == parse->next.end()) return 0;
        parse = parse->next[key[i]];
    }
    return parse->eow;
}

template<typename T>
void trie<T>::erase(string key) {
    deleteNode(this->root, key);
}

template<typename T>
bool trie<T>::empty() {
    return this->root->next.empty();
}

template<typename T>
int trie<T>::size() {
    return this->capacity;
}

// template<typename T> trie<T> :: begin()
// {

// }

// template<typename T> trie<T>::end()
// {

// }
