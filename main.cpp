#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <cassert>
#include <iterator>
#include <algorithm>
//#include <stdlib.h>

using namespace std;

const string fileName = "dictionary.txt";

class notSameLength
{
    size_t length;
public:
    notSameLength (size_t length) : length(length) {}

    bool operator()(string str) {
        return length != str.length();
    }
};

int LengthSelect (size_t length, vector<string> &dic) {
    dic.erase(remove_if(dic.begin(),dic.end(),notSameLength(length)), dic.end());
    return dic.size();
}

void LoadDic(vector<string> &dic) {
    ifstream input("dictionary.txt");
    assert(input.is_open());
    istream_iterator<string> eos;
    copy(istream_iterator<string>(input), eos, inserter(dic, dic.begin()));
//    copy(dic.begin(),dic.end(),ostream_iterator<string>(cout,"\n"));
}

class game {
private:
    size_t wordLength;
    size_t remainChance;
    vector<char> guessedLetters;
    int wordRemain;

    string currentWord;

public:
    vector<string> dictionary;


    game() {
        LoadDic(dictionary);
        inputWordLength();
        remainChance = wordLength;
        setWordRemain(LengthSelect(wordLength,dictionary));

        string temp;
        temp.append(wordLength,'-');
        setCurrentWord(temp);
    }
    typename vector<char>::iterator start() {
        return guessedLetters.begin();
    }
    typename vector<char>::iterator final() {
        return guessedLetters.end();
    }

    void pushGuessed(char a) {
        guessedLetters.push_back(a);
    }

    void setCurrentWord(string word) { currentWord = word; }
    string getCurrentWord() { return currentWord; }

    void setWordLength(int length) { wordLength = length; }
    int getWordLength() { return wordLength; }

    int getRemainChance () { return remainChance; }
    void setRemainChance (int chance) { remainChance = chance; }

    int getWordRemain () { return wordRemain; }
    void setWordRemain (int input) {wordRemain = input;}

    void inputWordLength ();
};

void game::inputWordLength() {
    cout << "Please input word length: ";
    cin >> wordLength;
    string dummy;
    getline(cin,dummy);
}


void PrintOut (game &hangman) {
    cout << "Word Length: " << hangman.getWordLength() << endl;
    cout << "Current Word: " << hangman.getCurrentWord() << endl;
    cout << "Mistakes Remaining: " << hangman.getRemainChance() << endl;
    cout << "Letters Guessed: ";
    copy(hangman.start(), hangman.final(), ostream_iterator<char>(cout, " "));
    cout << endl;
    cout << "Words Remaining: " << hangman.getWordRemain() << endl;
    cout << "===================================" << endl << endl;
}

string Getline() {
    string a;
    getline(cin,a);
    return a.c_str();
}

class containLetter
{
    char letter;
public:
    containLetter(char letter) : letter(letter) {}

    bool operator()(string input) {
        return input.find(letter);
    }

};


void analysis(game &hangman, char letter) {
    size_t sizeBefore = hangman.dictionary.size();
    for (auto itr = hangman.dictionary.begin(); itr != hangman.dictionary.end(); ) {
        size_t found = itr->find(letter);
        if (found != string::npos)
            hangman.dictionary.erase(itr);
        else
            itr++;
    }
    size_t sizeAfter = hangman.dictionary.size();

    if (sizeBefore == sizeAfter) {

    }

}


void SelectWords(game &hangman) {
    cout << "Guess a letter: ";
    string temp = Getline();
    char letter = temp[0];
//    cout << letter <<endl;
    hangman.pushGuessed(letter);
    hangman.setRemainChance(hangman.getRemainChance() - 1);

//    remove_if(hangman.dictionary.begin(), hangman.dictionary.end(), containLetter(letter));

    analysis(hangman, letter);

}

int main() {

    game hangman;

    while(hangman.getRemainChance()) {
        SelectWords(hangman);

//        system("CLS");
        PrintOut(hangman);
    }
    return 0;
}
