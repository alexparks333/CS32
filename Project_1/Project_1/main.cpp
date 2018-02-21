//
//  main.cpp
//  Project_1
//
//  Created by Anirudh Balasubramaniam on 1/13/18.
//  Copyright © 2018 Anirudh Balasubramaniam. All rights reserved.
//

#include "Game.h"
#include "City.h"
#include "History.h"
#include "Player.h"
#include "Flatulan.h"
#include "globals.h"
int main()
{
    // Create a game
    // Use this instead to create a mini-game:   Game g(3, 4, 2);
    Game g(7, 8, 25);
    
    // Play the game
    g.play();
}

