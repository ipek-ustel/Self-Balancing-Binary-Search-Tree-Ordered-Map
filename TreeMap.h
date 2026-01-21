#ifndef TREEMAP_H
#define TREEMAP_H

#include <iostream>
#include <vector>

#include "KeyValuePair.h"
#include "BinarySearchTree.h"

template<class K, class V>
class TreeMap {
public:
    TreeMap();

    void clear();
    const V &get(const K &key) const;
    const V &operator[](const K &key) const;

    void put(const K &key, const V &value);

    bool containsKey(const K &key);
    bool deletekey(const K &key);
    bool pop(const K &key);
    bool update(const K &key, const V &value);

    const KeyValuePair<K, V> &ceilingEntry(const K &key);
    const KeyValuePair<K, V> &floorEntry(const K &key);
    const KeyValuePair<K, V> &firstEntry();
    const KeyValuePair<K, V> &lastEntry();

    void pollFirstEntry();
    void pollLastEntry();
    
    void print() const;
    int size();

private:
    BinarySearchTree<KeyValuePair<K, V> > stree;
};

template<class K, class V>
TreeMap<K, V>::TreeMap() {}

template<class K, class V>
void TreeMap<K, V>::clear() {
    //TODO
    
    stree.removeAllNodes();
    
}

template<class K, class V>
const V &TreeMap<K, V>::get(const K &key) const {
    //TODO
    
    KeyValuePair<K, V> pair(key);
    const KeyValuePair<K, V>& pair_found = stree.get(pair);     //const reference dikkat et
    return pair_found.getValue();
    
}

template<class K, class V>
bool TreeMap<K, V>::pop(const K &key) {
    //TODO
    
    return stree.deletekey(key);
    
}

template<class K, class V>
bool TreeMap<K, V>::update(const K &key, const V &value) {
    //TODO
    
    if (containsKey(key)) {
        put(key, value);
        return true;
    }
    
    return false;
    
    /*try {
        KeyValuePair<K, V> search_pair(key);
        KeyValuePair<K, V> pair_found = stree.get(search_pair);
        pair_found.setValue(value);
        return true;
    } 
    catch (const NoSuchItemException &) {
        return false;
    }*/
    
}

template<class K, class V>
const KeyValuePair<K, V> &TreeMap<K, V>::ceilingEntry(const K &key) {
    //TODO
    
    KeyValuePair<K, V> pair(key);
    return stree.getCeiling(pair);
    
}

template<class K, class V>
const KeyValuePair<K, V> &TreeMap<K, V>::floorEntry(const K &key) {
    //TODO
    
    KeyValuePair<K, V> pair(key);
    return stree.getFloor(pair);
    
}

template<class K, class V>
const KeyValuePair<K, V> &TreeMap<K, V>::firstEntry() {
    //TODO
    
    return stree.getMin();
    
}

template<class K, class V>
const KeyValuePair<K, V> &TreeMap<K, V>::lastEntry() {
    //TODO
    
    return stree.getMax();
    
}

template<class K, class V>
void TreeMap<K, V>::pollFirstEntry() {
    //TODO
    
    return remove(stree.firstEntry());
    
}

template<class K, class V>
void TreeMap<K, V>::pollLastEntry() {
    //TODO
    
    return remove(stree.lastEntry());

}

template<class K, class V>
void TreeMap<K, V>::print() const {
    std::cout << "# TreeMap (BinarySearchTree):" << std::endl;
    stree.printPretty();
    std::cout << "# End TreeMap" << std::endl;
}

template<class K, class V>
int TreeMap<K, V>::size() {
    //TODO
    
    return stree.getSize();
    
}

template<class K, class V>
void TreeMap<K, V>::put(const K &key, const V &value) {
    //TODO
    
    KeyValuePair<K, V> pair(key, value);
    stree.insert(pair);
    
}

template<class K, class V>
const V &TreeMap<K, V>::operator[](const K &key) const {
    //TODO
    
    return get(key);
    
}

template<class K, class V>
bool TreeMap<K, V>::deletekey(const K &key) {
    //TODO
    
    KeyValuePair<K, V> pair(key);
    return stree.remove(pair);
    
}

template<class K, class V>
bool TreeMap<K, V>::containsKey(const K &key) {
    //TODO
    
    try {
        KeyValuePair<K, V> searchPair(key);
        stree.get(searchPair);
        return true;
    } 
    catch (const NoSuchItemException &) {
        return false;
    }
    
}






#endif
