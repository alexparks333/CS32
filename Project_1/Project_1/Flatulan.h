//
//  Flatulan.h
//  Project_1
//
//  Created by Anirudh Balasubramaniam on 1/13/18.
//  Copyright © 2018 Anirudh Balasubramaniam. All rights reserved.
//

#ifndef Flatulan_h
#define Flatulan_h
#include "globals.h"

class Flatulan
{
public:
    // Constructor
    Flatulan(City* cp, int r, int c);
    
    // Accessors
    int  row() const;
    int  col() const;
    
    // Mutators
    void move();
    bool possiblyGetConverted();
    
    
private:
    City* m_city;
    int   m_row;
    int   m_col;
};
#endif /* Flatulan_h */
