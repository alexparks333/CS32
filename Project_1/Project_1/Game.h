//
//  Game.h
//  Project_1
//
//  Created by Anirudh Balasubramaniam on 1/13/18.
//  Copyright © 2018 Anirudh Balasubramaniam. All rights reserved.
//

#ifndef Game_h
#define Game_h

class City;

class Game
{
public:
    // Constructor/destructor
    Game(int rows, int cols, int nFlatulans);
    ~Game();
    
    // Mutators
    void play();
    
private:
    City* m_city;
    int decodeDirection(char dir);
};

#endif /* Game_h */
