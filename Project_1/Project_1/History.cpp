//
//  History.cpp
//  Project_1
//
//  Created by Anirudh Balasubramaniam on 1/13/18.
//  Copyright © 2018 Anirudh Balasubramaniam. All rights reserved.
//

#include "History.h"
#include <iostream>
using namespace std;

History::History(int nRows, int nCols): m_rows(nRows), m_cols(nCols)
{
    for(int i = 1; i <= m_rows; i++)
    {
        for(int j = 1; j <= m_cols; j++)
        {
            m_historyGrid[i][j] = 0;
        }
    }
}

bool History::record(int r, int c)
{
    if(r > m_rows || c > m_cols || r <= 0 || c <= 0)
        return false;
    m_historyGrid[r][c]++;
    return true;
}

void History::display() const
{
    clearScreen();
    for(int i = 1; i <= m_rows; i++)
    {
        for(int j = 1; j <= m_cols; j++)
        {
            if(m_historyGrid[i][j] == 0)
                cout<<".";
            else if(m_historyGrid[i][j] >= 26)
                cout<<"Z";
            else
                cout<<(char)(m_historyGrid[i][j]+64);
        }
        cout<<"\n";
    }
    
    cout<<endl;
}

