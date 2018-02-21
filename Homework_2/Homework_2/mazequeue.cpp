//
//  mazestack.cpp
//  Homework_2
//
//  Created by Anirudh Balasubramaniam on 2/3/18.
//  Copyright © 2018 Anirudh Balasubramaniam. All rights reserved.
//

#include <queue>
#include <string>
#include <iostream>
using namespace std;

class Coord
{
public:
    Coord(int rr, int cc) : m_r(rr), m_c(cc) {}
    int r() const { return m_r; }
    int c() const { return m_c; }
private:
    int m_r;
    int m_c;
};

bool pathExists(string maze[], int nRows, int nCols, int sr, int sc, int er, int ec)
{
    queue<Coord> coordQueue;
    Coord coord(sr, sc);
    coordQueue.push(coord);
    maze[sr][sc] = 'o';
    
    while(!coordQueue.empty())
    {
        coord = coordQueue.front();
        cout<<coord.r()<<", "<<coord.c()<<endl;
        coordQueue.pop();
        if(coord.r() == er && coord.c() == ec)
            return true;
        if(maze[coord.r()][coord.c()+1] == '.')
        {
            Coord current(coord.r(),coord.c()+1);
            coordQueue.push(current);
            maze[coord.r()][coord.c()+1] = 'o';
        }
        if(maze[coord.r()+1][coord.c()] == '.')
        {
            Coord current(coord.r()+1,coord.c());
            coordQueue.push(current);
            maze[coord.r()+1][coord.c()] = 'o';
        }
        if(maze[coord.r()][coord.c()-1] == '.')
        {
            Coord current(coord.r(),coord.c()-1);
            coordQueue.push(current);
            maze[coord.r()][coord.c()-1] = 'o';
        }
        if(maze[coord.r()-1][coord.c()] == '.')
        {
            Coord current(coord.r()-1,coord.c());
            coordQueue.push(current);
            maze[coord.r()-1][coord.c()] = 'o';
        }
    }
    return false;
}

//int main()
//{
//    string maze[10] = {
//        "XXXXXXXXXX",
//        "X...X..X.X",
//        "X..XX....X",
//        "X.X.XXXX.X",
//        "XXX......X",
//        "X...X.XX.X",
//        "X.X.X..X.X",
//        "X.XXXX.X.X",
//        "X..X...X.X",
//        "XXXXXXXXXX"
//    };
//
//    if (pathExists(maze, 10,10, 4,3, 1,8))
//        cout << "Solvable!" << endl;
//    else
//        cout << "Out of luck!" << endl;
//}



