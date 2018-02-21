//
//  newMap.cpp
//  Homework_1
//
//  Created by Anirudh Balasubramaniam on 1/17/18.
//  Copyright © 2018 Anirudh Balasubramaniam. All rights reserved.
//

#include <stdio.h>
#include "newMap.h"
#include <iostream>

Map::Map(): maxItems(DEFAULT_MAX_ITEMS), m_size(0)
{
    m_pairs = new MapValues[DEFAULT_MAX_ITEMS];
}

Map::Map(int maxSize): m_size(0), maxItems(maxSize)
{
    if(maxSize < 0)
    {
        std::cout<<"Error: Size is negative!"<<std::endl;
        exit(9);
    }
    m_pairs = new MapValues[maxItems];
}
// Create an empty map (i.e., one with no key/value pairs)

Map::~Map()
{
    delete [] m_pairs;
}

Map::Map(const Map &other)
{
    m_size = other.size();
    maxItems = other.maxItems;

    m_pairs = new MapValues[maxItems];

    for(int i = 0; i < m_size; i++)
        m_pairs[i] = other.m_pairs[i];

}

Map& Map::operator=(const Map &other)
{
    if(this == &other)
        return *this;

    delete [] m_pairs;

    m_size = other.size();
    maxItems = other.maxItems;

    m_pairs = new MapValues[maxItems];

    for(int i = 0; i < m_size; i++)
        m_pairs[i] = other.m_pairs[i];

    return *this;
}

bool Map::doesKeyExist(KeyType key)
{
    for(int i = 0; i < m_size; i++)
    {
        if(m_pairs[i].key == key)
        {
            m_keyIndex = i;
            return true;
        }
    }

    return false;
}

bool Map::insert(const KeyType& key, const ValueType& value)
{
    if(doesKeyExist(key) || m_size >= maxItems)
        return false;

    m_pairs[m_size].key = key;
    m_pairs[m_size].value = value;

    m_size++;

    return true;
}
// If key is not equal to any key currently in the map, and if the
// key/value pair can be added to the map, then do so and return true.
// Otherwise, make no change to the map and return false (indicating
// that either the key is already in the map, or the map has a fixed
// capacity and is full).

bool Map::update(const KeyType& key, const ValueType& value)
{
    if(doesKeyExist(key))
    {
        m_pairs[m_keyIndex].value = value;
        return true;
    }

    return false;
}
// If key is equal to a key currently in the map, then make that key no
// longer map to the value it currently maps to, but instead map to
// the value of the second parameter; return true in this case.
// Otherwise, make no change to the map and return false.

bool Map::insertOrUpdate(const KeyType& key, const ValueType& value)
{
    if(!update(key, value) && !insert(key, value))
        return false;
    return true;
}
// If key is equal to a key currently in the map, then make that key no
// longer map to the value it currently maps to, but instead map to
// the value of the second parameter; return true in this case.
// If key is not equal to any key currently in the map and if the
// key/value pair can be added to the map, then do so and return true.
// Otherwise, make no change to the map and return false (indicating
// that the key is not already in the map and the map has a fixed
// capacity and is full).

bool Map::erase(const KeyType& key)
{
    if(doesKeyExist(key))
    {
        for(int i = m_keyIndex; i < m_size-1; i++)
        {
            m_pairs[i].key = m_pairs[i+1].key;
            m_pairs[i].value = m_pairs[i+1].value;
        }
        m_size--;
        return true;
    }
    return false;
}
// If key is equal to a key currently in the map, remove the key/value
// pair with that key from the map and return true.  Otherwise, make
// no change to the map and return false.

bool Map::contains(const KeyType& key) const
{
    for(int i = 0; i < m_size; i++)
    {
        if(m_pairs[i].key == key)
            return true;
    }

    return false;
}
// Return true if key is equal to a key currently in the map, otherwise
// false.

bool Map::get(const KeyType& key, ValueType& value) const
{
    for(int i = 0; i < m_size; i++)
    {
        if(m_pairs[i].key == key)
        {
            value = m_pairs[i].value;
            return true;
        }
    }

    return false;
}
// If key is equal to a key currently in the map, set value to the
// value in the map that that key maps to, and return true.  Otherwise,
// make no change to the value parameter of this function and return
// false.

bool Map::get(int i, KeyType& key, ValueType& value) const
{
    if(i >= 0 && i < m_size)
    {
        key = m_pairs[i].key;
        value = m_pairs[i].value;
        return true;
    }

    return false;
}
// If 0 <= i < size(), copy into the key and value parameters the
// key and value of one of the key/value pairs in the map and return
// true.  Otherwise, leave the key and value parameters unchanged and
// return false.  (See below for details about this function.)

void Map::swap(Map& other)
{
    /*Map tempMap = *this;
    *this = other;
    other = tempMap;*/

    std::swap(*this, other);

    /*int biggerSize = 0;

    KeyType tempKey;
    ValueType tempValue;

    if(other.m_size > m_size)
    {
        biggerSize = other.m_size;
        other.m_size = m_size;
        m_size = biggerSize;
    }
    else
    {
        biggerSize = m_size;
        m_size = other.m_size;
        other.m_size = biggerSize;
    }

    for(int i = 0; i < biggerSize; i++)
    {
        tempKey = m_pairs[i].key;
        tempValue = m_pairs[i].value;

        m_pairs[i].key = other.m_pairs[i].key;
        m_pairs[i].value = other.m_pairs[i].value;

        other.m_pairs[i].key = tempKey;
        other.m_pairs[i].value = tempValue;
    }*/
}
// Exchange the contents of this map with the other one.

void Map::dump() const
{
    for (int i = 0; i < m_size; i++)
    {
        std::cerr<<m_pairs[i].key<<" "<<m_pairs[i].value<<"\n";
    }
}




