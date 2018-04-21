#include "provided.h"
#include "MyHash.h"
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

class DecrypterImpl
{
public:
    DecrypterImpl();
    bool load(string filename);
    vector<string> crack(const string& ciphertext);
private:
    WordList wl;
    Translator translator;
    Tokenizer tokenizer;
    vector<string> translations;
    vector<string> words;
    string cipherText;
    void crackHelper();
    int chooseWord();
};

DecrypterImpl::DecrypterImpl(): tokenizer("0123456789 ,;:.!()[]{}-\"#$%^&")
{
}

bool DecrypterImpl::load(string filename)
{
    return wl.loadWordList(filename);
}

vector<string> DecrypterImpl::crack(const string& ciphertext)
{
    translations.clear();
    words = tokenizer.tokenize(ciphertext);

    cipherText = ciphertext;

    crackHelper();

    sort(translations.begin(), translations.end());

    return translations;
}

int DecrypterImpl::chooseWord()
{
    //choose word that has most ? in it
    int wPos = 0;
    string wTemp, temp;
    
    for(int i = 1; i < words.size(); i++)
    {
        wTemp = translator.getTranslation(words[wPos]);
        temp = translator.getTranslation(words[i]);
        if(count(wTemp.begin(), wTemp.end(), '?') < count(temp.begin(), temp.end(), '?'))
            wPos = i;
    }
    
    return wPos;
}

void DecrypterImpl::crackHelper()
{
    string w = words[chooseWord()];
    string wTranslated = translator.getTranslation(w);
    string translatedText;
    vector<string> tempWords;
    vector<string>candidates = wl.findCandidates(w, wTranslated);

    if(candidates.empty())
    {
        translator.popMapping();
        return;
    }

    for(int i = 0; i < candidates.size(); i++)
    {
        if(!translator.pushMapping(w, candidates[i]))
            continue;
        translatedText = translator.getTranslation(cipherText);
        tempWords = tokenizer.tokenize(translatedText);
        
        int wordsInList = 0, wordsNotInList = 0;

        for(int j = 0; j < tempWords.size(); j++)
        {
            if(tempWords[j].find('?') == -1 && !wl.contains(tempWords[j]))
                wordsNotInList++;
            else if(tempWords[j].find('?') == -1 && wl.contains(tempWords[j]))
                wordsInList++;
        }

        if(wordsNotInList > 0 || wordsInList == 0)
        {
            translator.popMapping();
            continue;
        }

        else if(wordsInList == tempWords.size())
        {
            translations.push_back(translatedText);
            translator.popMapping();
            continue;
        }

        else
            crackHelper();
    }

    translator.popMapping();
    return;
}



//******************** Decrypter functions ************************************

// These functions simply delegate to DecrypterImpl's functions.
// You probably don't want to change any of this code.

Decrypter::Decrypter()
{
    m_impl = new DecrypterImpl;
}

Decrypter::~Decrypter()
{
    delete m_impl;
}

bool Decrypter::load(string filename)
{
    return m_impl->load(filename);
}

vector<string> Decrypter::crack(const string& ciphertext)
{
    return m_impl->crack(ciphertext);
}


