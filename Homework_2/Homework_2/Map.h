//
//  Map.h
//  Project_2
//
//  Created by Anirudh Balasubramaniam on 1/26/18.
//  Copyright © 2018 Anirudh Balasubramaniam. All rights reserved.
//

#ifndef Map_h
#define Map_h

#include <string>

using KeyType = char;
using ValueType = int;

class Map
{
public:
    Map();
    ~Map();
    Map(const Map & other);
    Map & operator=(const Map & other);
    bool empty() const;
    int size() const;
    bool insert(const KeyType& key, const ValueType& value);
    bool update(const KeyType& key, const ValueType& value);
    bool insertOrUpdate(const KeyType& key, const ValueType& value);
    bool erase(const KeyType& key);
    bool contains(const KeyType& key) const;
    bool get(const KeyType& key, ValueType& value) const;
    bool get(int i, KeyType& key, ValueType& value) const;
    void swap(Map& other);
    void dump() const;

private:
    int m_size;
    /*struct MapValues
    {
        KeyType key;
        ValueType value;
    };*/
    
    struct MapNode
    {
        KeyType key;
        ValueType value;
        MapNode * next;
        MapNode * prev;
    };
    
    MapNode * head, * tail;
};

bool combine(const Map& m1, const Map& m2, Map& result); 
void subtract(const Map& m1, const Map& m2, Map& result);

#endif /* Map_h */
