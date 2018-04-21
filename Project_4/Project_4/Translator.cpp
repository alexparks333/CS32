#include "provided.h"
#include <string>
#include <unordered_map>
#include <iostream>
#include <algorithm>
using namespace std;

class TranslatorImpl
{
public:
    TranslatorImpl();
    ~TranslatorImpl();
    bool pushMapping(string ciphertext, string plaintext);
    bool popMapping();
    string getTranslation(const string& ciphertext) const;
private:
    struct Node
    {
        char charMapping[26]; //mapping of letters to their encrypter ones
        bool alreadyMapped[26]; //mapping of where a letter has been mapped to another letter
    };
    vector<Node> maps;
    void toLower(string &str) const;
};

TranslatorImpl::TranslatorImpl()
{
    Node node;
    for(int i = 0; i < 26; i++)
    {
        node.charMapping[i] = '?';
        node.alreadyMapped[i] = false;
    }
    
    maps.push_back(node);
}

TranslatorImpl::~TranslatorImpl()
{
    
}

void TranslatorImpl::toLower(string &str) const
{
    transform(str.begin(), str.end(), str.begin(), ::tolower);
}

bool TranslatorImpl::pushMapping(string ciphertext, string plaintext)
{
    toLower(ciphertext);
    toLower(plaintext);
    if(ciphertext.size() != plaintext.size() || ciphertext.find_first_not_of("abcdefghijklmnopqrstuvwxyz") != -1 || plaintext.find_first_not_of("abcdefghijklmnopqrstuvwxyz") != -1)
        return false;
    
    Node currentMap = maps[maps.size() - 1]; //current map is last map in the vector
    Node newMap;
    
    for(int i = 0; i < 26; i++ )
    {
        //add values from current map to new map
        newMap.charMapping[i] = currentMap.charMapping[i];
        newMap.alreadyMapped[i] = currentMap.alreadyMapped[i];
    }
    
    for(int i = 0; i < ciphertext.size(); i++)
    {
        //if one letter to points to 2 different plaintext letters
        if (newMap.charMapping[ciphertext[i]-97] != plaintext[i] && isalpha(newMap.charMapping[ciphertext[i]-97]))
            return false;
        
        //if two ciphertext letters point to the same letter
        else if (newMap.alreadyMapped[plaintext[i]-97] && newMap.charMapping[ciphertext[i]-97] != plaintext[i])
            return false;

        //add to the new map
        else if (newMap.charMapping[ciphertext[i]-97] == '?')
        {
            newMap.charMapping[ciphertext[i]-97] = plaintext[i];
            newMap.alreadyMapped[plaintext[i]-97] = true;
        }
    }
    
    //add newMap to the end of maps vector, making it the current map
    maps.push_back(newMap);
    
    return true;
}

bool TranslatorImpl::popMapping()
{
    if(maps.size() <= 1) //to prevent mapping from being popped more times than it has been pushed
        return false;
    
    maps.pop_back();
        
    return true;
}

string TranslatorImpl::getTranslation(const string& ciphertext) const
{
    string translatedWord = "";
    
    Node currentMap = maps[maps.size() - 1];
    
    for(int i = 0; i < ciphertext.size(); i++)
    {
        if(!isalpha(ciphertext[i])) //if not a letter, add it to the word
            translatedWord += ciphertext[i];
        
        else if(isupper(ciphertext[i])) //if upper char, return upper char based on current mapping
            translatedWord += toupper(currentMap.charMapping[ciphertext[i]-65]);
        
        else if(islower(ciphertext[i])) //if lower char, return lower char based on current mapping
            translatedWord += currentMap.charMapping[ciphertext[i]-97];
    }
    
    return translatedWord;
}

//******************** Translator functions ************************************

// These functions simply delegate to TranslatorImpl's functions.
// You probably don't want to change any of this code.

Translator::Translator()
{
    m_impl = new TranslatorImpl;
}

Translator::~Translator()
{
    delete m_impl;
}

bool Translator::pushMapping(string ciphertext, string plaintext)
{
    return m_impl->pushMapping(ciphertext, plaintext);
}

bool Translator::popMapping()
{
    return m_impl->popMapping();
}

string Translator::getTranslation(const string& ciphertext) const
{
    return m_impl->getTranslation(ciphertext);
}
