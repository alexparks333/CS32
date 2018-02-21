////
////  testMap.cpp
////  Homework_1
////
////  Created by Anirudh Balasubramaniam on 1/17/18.
////  Copyright © 2018 Anirudh Balasubramaniam. All rights reserved.
////
//
//#include "Map.h"
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
//    Map b;
//    b.insert("Anirudh", 4.0);
//
//    b.dump();
//
//    b.swap(m);
//
//    cout<<"\n";
//
//    m.dump();
//
//    cout<<"\n";
//
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
