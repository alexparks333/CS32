////
////  CarMap.cpp
////  Homework_1
////
////  Created by Anirudh Balasubramaniam on 1/17/18.
////  Copyright © 2018 Anirudh Balasubramaniam. All rights reserved.
////
//
//#include <stdio.h>
//#include <iostream>
//#include "CarMap.h"
//
//CarMap::CarMap()
//{
//}
//// Create an empty car map.
//
//
//bool CarMap::addCar(std::string license)
//{
//    return m_map.insert(license, 0);
//}
//// If a car with the given license plate is not currently in the map,
//// and there is room in the map, add an entry for that car recording
//// that it has 0 gallons of gas in it, and return true.  Otherwise,
//// make no change to the map and return false.
//
//double CarMap::gas(std::string license) const
//{
//    ValueType gallonsOfGas = 0;
//    if(m_map.get(license, gallonsOfGas))
//        return gallonsOfGas;
//    return -1;
//}
//// If a car with the given license plate is in the map, return the
//// number of gallons of gas in its tank; otherwise, return -1.
//
//bool CarMap::addGas(std::string license, double gallons)
//{
//    if(gallons < 0)
//        return false;
//    
//    ValueType currentGas = 0;
//    m_map.get(license, currentGas);
//    return m_map.update(license, currentGas+gallons);
//}
//// If no car with the given license plate is in the map or if
//// gallons is negative, make no change to the map and return
//// false.  Otherwise, increase the number of gallons of gas in the
//// indicated car by the gallons parameter and return true.
//
//bool CarMap::useGas(std::string license, double gallons)
//{
//    if(gallons < 0)
//        return false;
//    
//    ValueType currentGas = 0;
//    m_map.get(license, currentGas);
//    
//    if(gallons > currentGas)
//        return false;
//    
//     return m_map.update(license, currentGas-gallons);
//}
//// If no car with the given license plate is in the map or if
//// gallons is negative or if gallons > gas(), make no change to the
//// map and return false.  Otherwise, decrease the number of gallons
//// of gas in the indicated car by the gallons parameter and return
//// true.
//
//int CarMap::fleetSize() const
//{
//    return m_map.size();
//}  // Return the number of cars in the CarMap.
//
//void CarMap::print() const
//{
//    ValueType value = 0;
//    KeyType key = "";
//    
//    for(int i = 0; i < fleetSize(); i++)
//    {
//        m_map.get(i, key, value);
//        std::cout<<key<<" "<<value<<"\n";
//    }
//}
//// Write to cout one line for every car in the map.  Each line
//// consists of the car's license plate, followed by one space,
//// followed by the number of gallons in that car's tank.  Write
//// no other text.
//
//
