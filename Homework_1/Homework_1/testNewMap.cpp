////
////  testNewMap.cpp
////  Homework_1
////
////  Created by Anirudh Balasubramaniam on 1/17/18.
////  Copyright © 2018 Anirudh Balasubramaniam. All rights reserved.
////
//
//#include "newMap.h"
//#include <iostream>
//#include <cassert>
//using namespace std;
//
//void test()
//{
//    Map m;  // maps ints to strings
//    assert(m.empty());
//    
//    ValueType value;
//    
//    assert(m.insert("Ani", 3.9));
//    assert(m.insert("Vivek", 3.8));
//    assert(m.insert("bob", 3.0));
//    
//    assert(m.size() == 3);
//    
//    assert(m.insert("Ani", 2.0) == false);
//    assert(m.update("bob", 4.0) == true);
//    assert(m.update("Ruc", 3.0) == false);
//    assert(m.insertOrUpdate("Vivek", 4.0) == true);
//    assert(m.get("Vivek", value) == true);
//    assert(value == 4.0);
//    assert(m.get("Rod", value) == false);
//    assert(value == 4.0);
//    
//    Map e;
//    e.insert("Anirudh", 4.0);
//    
//    e.dump();
//    
//    e.swap(m);
//    
//    cout<<"\n";
//    
//    m.dump();
//    
//    cout<<"\n";
//    
//    //Map g(-2);
//    
//    Map a(1000);   // a can hold at most 1000 key/value pairs
//    Map b(5);      // b can hold at most 5 key/value pairs
//    Map c;         // c can hold at most DEFAULT_MAX_ITEMS key/value pairs
//    KeyType k[6] = { "hi", "yo", "hello", "hai", "wassup", "bro" };
//    ValueType v  = 2.0;
//    
//    // No failures inserting pairs with 5 distinct keys into b
//    for (int n = 0; n < 5; n++)
//        assert(b.insert(k[n], v));
//    
//    // Failure if we try to insert a pair with a sixth distinct key into b
//    assert(!b.insert(k[5], v));
//    
//    // When two Maps' contents are swapped, their capacities are swapped
//    // as well:
//    a.swap(b);
//    assert(!a.insert(k[5], v)  &&  b.insert(k[5], v));
//}
//
//int main()
//{
//    test();
//    cout << "Passed all tests" << endl;
//}
//
//
//
//
