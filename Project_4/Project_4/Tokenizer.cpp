#include "provided.h"
#include <string>
#include <vector>
#include <unordered_set>
using namespace std;

class TokenizerImpl
{
public:
    TokenizerImpl(string separators);
    vector<string> tokenize(const string& s) const;
private:
    unordered_set<char> separatorSet;
};

TokenizerImpl::TokenizerImpl(string separators)
{
    //add all the separators to an unordered_set
    for(int i = 0; i < separators.size(); i++)
        separatorSet.insert(separators[i]);
}

vector<string> TokenizerImpl::tokenize(const string& s) const
{
    vector<string> words;
    string word = "";
    bool addChar = true;
    
    unordered_set<char>::const_iterator it;
    
    for(int i = 0; i < s.size(); i++)
    {
        //find current char in the set
        it = separatorSet.find(s[i]);
        if(it != separatorSet.end())
            addChar = false;
        
        if(addChar)
            word += s[i]; //if its not a token, add it to current word
        
        if(!word.empty() && (!addChar || i == s.size() - 1))
        {
            words.push_back(word); //if it is a token, add current word to the vector
            word = "";
        }
        
        addChar = true;
    }
    
    return words;
}

//******************** Tokenizer functions ************************************

// These functions simply delegate to TokenizerImpl's functions.
// You probably don't want to change any of this code.

Tokenizer::Tokenizer(string separators)
{
    m_impl = new TokenizerImpl(separators);
}

Tokenizer::~Tokenizer()
{
    delete m_impl;
}

vector<string> Tokenizer::tokenize(const string& s) const
{
    return m_impl->tokenize(s);
}
