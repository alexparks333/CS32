//
//  Map.cpp
//  Homework_1
//
//  Created by Anirudh Balasubramaniam on 1/17/18.
//  Copyright © 2018 Anirudh Balasubramaniam. All rights reserved.
//


#include <stdio.h>
#include "Map.h"
#include <iostream>

Map::Map(): m_size(0) //set size to 0, as Map is empty
{
    //Set head and tail pointer to null, as the Map is empty
    head = nullptr;
    tail = nullptr;
}

Map::~Map()
{
    if(!empty()) //If Map is not empty, delete its MapNodes
    {
        MapNode * current = head;
        MapNode * nextNode = head->next;
        
        //Traverse through all but the first MapNode in the Map, and delete them
        while(nextNode != nullptr)
        {
            current = nextNode;
            nextNode = nextNode->next;
            delete current;
        }
        
        delete head; //Delete the first MapNode (aka head)
    }
}

Map::Map(const Map & other)
{
    MapNode * p = other.head;
    head = nullptr;
    tail = nullptr;
    m_size = 0;
    
    //Traverse through the MapNodes in other and insert them one by one to create a copy of other
    while(p != nullptr)
    {
        insert(p->key, p->value);
        p = p->next;
    }
}

Map & Map::operator=(const Map & other)
{
    if(this == &other) //Check for aliasing
        return * this;
    
    //If the Map isn't empty, delete its MapNodes
    if(!empty())
    {
        MapNode * current = head;
        MapNode * nextNode = head->next;
        
        while(nextNode != nullptr)
        {
            current = nextNode;
            nextNode = nextNode->next;
            delete current;
        }
        
        delete head;
        m_size = 0;
    }
    
    head = nullptr;
    tail = nullptr;
    
    //Traverse through the MapNodes in other and insert them one by one into this Map
    MapNode * p = other.head;
    
    for(int i = 0; i < other.m_size; i++)
    {
        insert(p->key, p->value);
        p = p->next;
    }
    
    return *this;
}

bool Map::empty() const
{
    return (m_size == 0); //Return true if m_size is 0
}

int Map::size() const
{
    return m_size;  //Return the number of MapNodes in Map
}

bool Map::insert(const KeyType& key, const ValueType& value)
{
    //If the key doesn't exist in the Map, create a new MapNode with given values
    //and put it at the end of the LinkedList
    if(!contains(key))
    {
        MapNode * p = new MapNode;
        p->key = key;
        p->value = value;
        p->next = nullptr;
        p->prev = tail;
        tail = p;
        if(empty()) //If Map is empty, also set head to the new MapNode
            head = p;
        else
            p->prev->next = p; //Else set the current tail's next to the new MapNode
        m_size++;
        return true;
    }
    
    return false;
}

bool Map::update(const KeyType& key, const ValueType& value)
{
    //If the key exists in the Map, find the MapNode corresponding to it, by traversing
    //through all the MapNodes in the Map, and change its value
    if(contains(key))
    {
        MapNode * p = head;
        
        while(p != nullptr)
        {
            if(p->key == key)
            {
                p->value = value;
                return true;
            }
            p = p->next;
        }
    }
    
    return false;
}

bool Map::insertOrUpdate(const KeyType& key, const ValueType& value)
{
    //First, try to update the Map with the given parameters. If that returns true, the function will return true.
    //Otherwise, call the insert method with the given parameters. If that returns true, function will return true,
    //otherwise, the function will return false.
    if(!update(key, value) && !insert(key, value))
        return false;
    return true;
}

bool Map::erase(const KeyType& key)
{
    if(contains(key))   //Check to see if the key exists in the Map
    {
        MapNode * p = head;
        
        //Traverse through the Map to find the MapNode with the given key and then
        //set the next and prev and/or head and/or tail values to show the removal of this MapNode
        //and then delete the MapNode
        while(p != nullptr)
        {
            if(p->key == key)
            {
                if(head == p)
                    head = p->next;
                else
                   p->prev->next = p->next;
                if(tail == p)
                    tail = p->prev;
                else
                    p->next->prev = p->prev;
                delete p;
                m_size--;
                return true;
            }
            p = p->next;
        }
    }
        
    return false;
}

bool Map::contains(const KeyType& key) const
{
    MapNode * p = head;

    //Traverse through all the MapNodes in Map to see if there exists one with the given key
    while(p != nullptr)
    {
        if(p->key == key)
            return true;
        p = p->next;
    }
    
    return false;
}

bool Map::get(const KeyType& key, ValueType& value) const
{
    if(contains(key)) //Check if the key exists in the Map
    {
        MapNode * p = head;
        
        //Traverse through the MapNodes in Map till MapNode with given key is found.
        //Then set value to that MapNode's value.
        while(p != nullptr)
        {
            if(p->key == key)
            {
                value = p->value;
                return true;
            }
            p = p->next;
        }
    }
    
    return false;
}

bool Map::get(int i, KeyType& key, ValueType& value) const
{
    if(i >= 0 && i < m_size) //Check if i fits the bounds of the LinkedList
    {
        MapNode * p = head;
        
        //Traverse through the Map till the ith MapNode if found
        for(int j = 0; j < i; j++)
            p = p->next;
        
        //Set key and value to that MapNode's key and value
        key = p->key;
        value = p->value;
        return true;
    }
    
    return false;
}

void Map::swap(Map& other)
{
    //Temporary variables for this Map's members
    int tempSize = size();
    MapNode * tempHead = head;
    MapNode * tempTail = tail;
    
    //Set this Map's members to other's members
    m_size = other.m_size;
    head = other.head;
    tail = other.tail;
    
    //Set other's members to this' members by using the temporary variables
    other.m_size = tempSize;
    other.head = tempHead;
    other.tail = tempTail;
}

void Map::dump() const
{
    //Traverse through all the MapNodes in the Map and print its key and value
    MapNode * p = head;
    while(p != nullptr)
    {
        std::cerr<<p->key<<" "<<p->value<<"\n";
        p = p->next;
    }
}

bool combine(const Map& m1, const Map& m2, Map& result)
{
    Map temp; //Temporary Map to avoid aliasing errors
    KeyType key1, key2;
    ValueType value1, value2;
    bool sameValue = true;
    
    for(int j = 0; j < m2.size(); j++)  //Insert all the MapNodes in m2 into temp
    {
        m2.get(j, key2, value2);
        temp.insert(key2, value2);
    }
    
    for(int i = 0; i < m1.size(); i++) //Traverse through the MapNodes in the first Map
    {
        m1.get(i, key1, value1);
        
        temp.insert(key1, value1);  //Insert the current MapNode into temp (Insert already checks if a MapNode exists with the given key to ensure no duplicates)
        if(m2.contains(key1))
        {
            m2.get(key1, value2);
            if(value1 != value2)
            {
                temp.erase(key1);
                sameValue = false;
                //If a key exists in both maps, but with different values, delete the corresponding MapNode with that key
                //from temp and set the return value "sameValue" to false.
            }
        }
    }
        
    result.swap(temp); //Swap the temp Map with the result Map, as temp Map has all the needed MapNodes, whereas
                       //result could have MapNodes and other values that are irrelevant
    return sameValue;
}
void subtract(const Map& m1, const Map& m2, Map& result)
{
    Map temp; //Temporary Map to avoid aliasing errors
    KeyType key1;
    ValueType value1;
    
    for(int i = 0; i < m1.size(); i++) //Traverse through the MapNodes in the first Map
    {
        m1.get(i, key1, value1);
        if(!m2.contains(key1)) //Only insert the current MapNode if its key does not exist in both maps
            temp.insert(key1, value1);
    }
    
    result.swap(temp); //Swap the temp Map with the result Map, as temp Map has all the needed MapNodes, whereas
                       //result could have MapNodes and other values that are irrelevant
}
