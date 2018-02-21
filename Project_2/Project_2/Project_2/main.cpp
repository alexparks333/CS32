#include <iostream>
#include "Map.h"
#include <string>
#include <cassert>
using namespace std;

int main()
{
    Map a,b,c,d, res; //default constructor
    KeyType key, key2;
    ValueType value, value2;
    a.insert("1", 1.8);
    a.insert("2", 1.6);
    a.insert("3", 1.5);
    a.insert("4", 1.2);
    a.insert("vie", 42);

    b.insert("1", 1.8);
    b.insert("2", 99);
    b.insert("20", 22);

    assert(c.empty()); //test empty with empty Map
    assert(!a.empty()); //test empty with non-empty Map
    
    assert(a.size() == 5); //test size
    assert(!a.insert("1", 2.0)); //test insert with existing key
    assert(c.insert("55", 5.5)); //test insert with non-existing key
    c.get("55", value);
    assert(value == 5.5); //test if insert worked
    assert(!c.erase("2")); //test erase with non-existing key
    assert(c.erase("55")); //test erase with existing key
    assert(c.size() == 0); //test size after all MapNodes are erase
    
    
    assert(a.update("2", 22.0)); //test update with existing key
    assert(!a.update("53", 241.1)); //test update with non-existing key, nothing to update
    a.get("2", value);
    assert(value == 22.0); //test if value was updated
    assert(b.insertOrUpdate("19", 19.9)); //test insertOrUpdate, value should be inserted
    assert(b.insertOrUpdate("1", 1.1)); //test insertOrUpdate, value should be updated
    b.get("19", value);
    assert(value == 19.9); //check if value was inserted
    b.get("1", value);
    assert(value == 1.1); //check if value was updated
    
    assert(a.contains("4")); //test contains
    assert(!b.contains("2324309")); //test contains
    
    d.insert("a", 97);
    d.insert("b", 98);
    d.insert("c", 99);
    
    d.get("a", value);
    assert(value == 97); //test get with only key parameter
    
    //test get with int parameter
    for(int i = 0; i < 3; i++)
    {
        d.get(i, key, value);
        assert(value == (i+97));
        assert(int(key.at(0)) == (i+97));
    }
    
    d.swap(c); //swap d with empty Map
    a.swap(b); //swap two non-empty Maps
    assert(d.empty() && c.size() == 3); //test if sizes were swapped
    c.get("b", value);
    assert(value == 98); //test if key/value pairs were swapped
    assert(b.size() == 5 && a.size() == 4); //test if sizes were swapped
    b.get(4, key, value);
    assert(key == "vie" && value == 42); //test if key/value pairs were swapped
    
    d.insert("11", 11.8);
    d.insert("vie", 42);
    assert(combine(b, d, res)); //test combine
    assert(res.contains("vie") && res.contains("11") && res.contains("1") && res.contains("2")
           && res.contains("3") && res.contains("4")); //test if combine creates a correct Map with necessary MapNodes
    d.update("vie", 3.14);
    assert(!combine(b, d, res)); //test combine for 2 Maps with same key but different value
    assert(!res.contains("vie")); //test if the result Map does not contain that key
    
    d.insert("4", 1.2);
    subtract(b, d, res);
    assert(res.contains("1") && res.contains("2") && res.contains("3")); //test subtract creates Map with necessary keys
    subtract(d, b, res);
    assert(res.contains("11") && !res.contains("vie")); //test subtract but with order of Maps reversed
    
    c = a; //check if assignment operator works as it should
    assert(c.size() == a.size()); //test if sizes are same
    //test if all of the key and value pairs are equal
    for(int i = 0; i < a.size(); i++)
    {
        c.get(i, key, value);
        a.get(i, key2, value2);
        assert(key == key2 && value == value2);
    }
    
    Map f(a); //ceck if the copy constructor works as it should
    assert(f.size() == a.size()); //test if sizes are same
    //test if all of the key and value pairs are equal
    for(int i = 0; i < f.size(); i++)
    {
        f.get(i, key, value);
        a.get(i, key2, value2);
        assert(key == key2 && value == value2);
    }
    
    cerr<<"Passed all tests\n";

    return 0;
}

//11111111111

//#include "Map.h"
//#include <type_traits>
//
//#define CHECKTYPE(f, t) { auto p = static_cast<t>(f); (void)p; }
//
//static_assert(std::is_default_constructible<Map>::value,
//              "Map must be default-constructible.");
//static_assert(std::is_copy_constructible<Map>::value,
//              "Map must be copy-constructible.");
//
//void ThisFunctionWillNeverBeCalled()
//{
//    CHECKTYPE(&Map::operator=,      Map& (Map::*)(const Map&));
//    CHECKTYPE(&Map::empty,          bool (Map::*)() const);
//    CHECKTYPE(&Map::size,           int  (Map::*)() const);
//    CHECKTYPE(&Map::insert,         bool (Map::*)(const KeyType&, const ValueType&));
//    CHECKTYPE(&Map::update,         bool (Map::*)(const KeyType&, const ValueType&));
//    CHECKTYPE(&Map::insertOrUpdate, bool (Map::*)(const KeyType&, const ValueType&));
//    CHECKTYPE(&Map::erase,          bool (Map::*)(const KeyType&));
//    CHECKTYPE(&Map::contains,       bool (Map::*)(const KeyType&) const);
//    CHECKTYPE(&Map::get,            bool (Map::*)(const KeyType&, ValueType&) const);
//    CHECKTYPE(&Map::get,            bool (Map::*)(int, KeyType&, ValueType&) const);
//    CHECKTYPE(&Map::swap,           void (Map::*)(Map&));
//
//    CHECKTYPE(combine,  bool (*)(const Map&, const Map&, Map&));
//    CHECKTYPE(subtract, void (*)(const Map&, const Map&, Map&));
//}
//
//int main()
//{}

//2222222
//#include "Map.h"
//#include <iostream>
//#include <cassert>
//using namespace std;
//
//void test()
//{
//    Map m;
//    assert(m.insert("Fred", 123));
//    assert(m.insert("Ethel", 456));
//    assert(m.size() == 2);
//    ValueType v = 42;
//    assert(!m.get("Lucy", v)  &&  v == 42);
//    assert(m.get("Fred", v)  &&  v == 123);
//    v = 42;
//    KeyType x = "Lucy";
//    assert(m.get(0, x, v)  &&
//           ((x == "Fred"  &&  v == 123)  ||  (x == "Ethel"  &&  v == 456)));
//    KeyType x2 = "Ricky";
//    assert(m.get(1, x2, v)  &&
//           ((x2 == "Fred"  &&  v == 123)  ||  (x2 == "Ethel"  &&  v == 456))  &&
//           x != x2);
//}
//
//int main()
//{
//    test();
//    cout << "Passed all tests" << endl;
//}

//333333
//#include "Map.h"
//#include <iostream>
//#include <cassert>
//using namespace std;
//
//void test()
//{
//    Map m;
//    assert(m.insert(10, "diez"));
//    assert(m.insert(20, "veinte"));
//    assert(m.size() == 2);
//    ValueType v = "cuarenta y dos";
//    assert(!m.get(30, v)  &&  v == "cuarenta y dos");
//    assert(m.get(10, v)  &&  v == "diez");
//    v = "cuarenta y dos";
//    KeyType x = 30;
//    assert(m.get(0, x, v)  &&
//           ((x == 10  &&  v == "diez")  ||  (x == 20  &&  v == "veinte")));
//    KeyType x2 = 40;
//    assert(m.get(1, x2, v)  &&
//           ((x2 == 10  &&  v == "diez")  ||  (x2 == 20  &&  v == "veinte"))  &&
//           x != x2);
//}
//
//int main()
//{
//    test();
//    cout << "Passed all tests" << endl;
//}



