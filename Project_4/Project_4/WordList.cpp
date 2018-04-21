#include "provided.h"
#include "MyHash.h"
#include <string>
#include <vector>
#include <functional>
#include <algorithm>
#include <fstream>
#include <iostream>
using namespace std;

class WordListImpl
{
public:
    bool loadWordList(string filename);
    bool contains(string word) const;
    vector<string> findCandidates(string cipherWord, string currTranslation) const;
private:
    MyHash<string, bool> allWords;
    MyHash<string, vector<string>> indexedWords;
    bool wordWorks(string word, string currTranslation) const;
    string getPattern(string word) const;
    void clear();
    void toLower(string &str) const;
};

void WordListImpl::clear()
{
    //clear the used MyHash tables
    allWords.reset();
    indexedWords.reset();
}

void WordListImpl::toLower(string &str) const
{
    transform(str.begin(), str.end(), str.begin(), ::tolower);
}

string WordListImpl::getPattern(string word) const
{
    MyHash<char, char> letters;
    char c = ' ', patternLetter = 'a';
    char * associated;
    string pattern = "";

    //find if letter is in letters MyHash. If not add current patternLetter to
    //pattern and increment patternLetter and associate the letter with its patternLetter
    //in letters. Oterhwise, add associated patternLetter to pattern.
    for(int i = 0; i < word.size(); i++)
    {
        c = word[i];
        associated = letters.find(c);
        if(associated != nullptr)
            pattern += *associated;
        else
        {
            letters.associate(c, patternLetter);
            pattern += patternLetter;
            patternLetter++;
        }
    }

    return pattern;
}

bool WordListImpl::loadWordList(string filename)
{
    clear();

    ifstream infile(filename);

    if(!infile)
        return false;

    string s, sPattern;
    vector<string> * words;
    while(getline(infile, s))
    {
        toLower(s);
        if(s.find_first_not_of("abcdefghijklmnopqrstuvwxyz'") == -1)
        {
            allWords.associate(s, true); //add word to allWords
            sPattern = getPattern(s);
            words = indexedWords.find(sPattern);
            if(words == nullptr)
            {
                //if can't find word pattern in indexedWords, add new associate with
                //pattern and a vector with the current word
                vector<string> tWords;
                tWords.push_back(s);
                indexedWords.associate(sPattern, tWords);
            }
            else
                words->push_back(s); //if word pattern is in indexedWords, add s to its associated vector
        }
    }

    return true;
}

bool WordListImpl::contains(string word) const
{
    toLower(word);
    return (allWords.find(word) != nullptr);
}

vector<string> WordListImpl::findCandidates(string cipherWord, string currTranslation) const
{
    vector<string> words, result;
    toLower(cipherWord);
    toLower(currTranslation);
    if(cipherWord.size() != currTranslation.size())
        return words;
    if(cipherWord.find_first_not_of("abcdefghijklmnopqrstuvwxyz'?") != -1 ||
       currTranslation.find_first_not_of("abcdefghijklmnopqrstuvwxyz'?") != -1)
        return words;

    if(indexedWords.find(getPattern(cipherWord)) == nullptr)
        return words;

    words = *indexedWords.find(getPattern(cipherWord));
    string word;

    //ensure currTranslation and cipherWord match each other
    for(int i = 0; i < currTranslation.size(); i++)
    {
        if(isalpha(currTranslation[i]) && !isalpha(cipherWord[i]))
            return *(new vector<string>);
        
        if(currTranslation[i] == '?' && !isalpha(cipherWord[i]))
            return *(new vector<string>);
        
        if(currTranslation[i] == '\'' && cipherWord[i] != '\'')
            return *(new vector<string>);
    }

    //add all the words that work as a candidate to result
    for(vector<string>::iterator iter = words.begin(); iter != words.end(); iter++)
    {
        word = *iter;
        if(wordWorks(word, currTranslation)) //check if word can be a candidate
            result.push_back(word);
    }

    return result;
}

bool WordListImpl::wordWorks(string word, string currTranslation) const
{
    for(int i = 0 ; i < word.size(); i++)
    {
        //letter in i position in currTranslation is not equal to letter in i position in word
        if(isalpha(currTranslation[i]) && currTranslation[i] != word[i])
            return false;

        //? in i position in currTranslation is not associated with a letter in i position in word
        else if(currTranslation[i] == '?' && !isalpha(word[i]))
            return false;

        //' in i position in currTranslation is not equal to ' in i position in word
        else if(currTranslation[i] == '\'' && word[i] != '\'')
            return false;
    }
    return true;
}

//***** hash functions for string, int, and char *****

unsigned int hash(const std::string& s)
{
    return std::hash<std::string>()(s);
}

unsigned int hash(const int& i)
{
    return std::hash<int>()(i);
}

unsigned int hash(const char& c)
{
    return std::hash<char>()(c);
}

//******************** WordList functions ************************************

// These functions simply delegate to WordListImpl's functions.
// You probably don't want to change any of this code.

WordList::WordList()
{
    m_impl = new WordListImpl;
}

WordList::~WordList()
{
    delete m_impl;
}

bool WordList::loadWordList(string filename)
{
    return m_impl->loadWordList(filename);
}

bool WordList::contains(string word) const
{
    return m_impl->contains(word);
}

vector<string> WordList::findCandidates(string cipherWord, string currTranslation) const
{
   return m_impl->findCandidates(cipherWord, currTranslation);
}


