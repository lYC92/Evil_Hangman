#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <cassert>
#include <iterator>
#include <algorithm>
#include <stdlib.h>

using namespace std;

const string fileName = "dictionary.txt";


void LoadDic(set<string> &dic) {
    ifstream input("dictionary.txt");
    assert(input.is_open());
    istream_iterator<string> eos;
    copy(istream_iterator<string>(input), eos, inserter(dic, dic.begin()));
//    copy(dic.begin(),dic.end(),ostream_iterator<string>(cout,"\n"));
}

class game {
private:
    int wordLength;
    int remainChance;
    set<char> guessedLetters;
    int wordRemain;

public:
    game() {
        inputWordLength();
        remainChance = wordLength;
    }
    typename set<char>::iterator start() {
        return guessedLetters.begin();
    }
    typename set<char>::iterator final() {
        return guessedLetters.end();
    }

    void pushGuessed(char a) {
        guessedLetters.insert(a);
    }

    void setWordLength(int length) { wordLength = length; }
    int getWordLength() { return wordLength; }

    int getRemainChance () { return remainChance; }
    void setRemainChance (int chance) { remainChance = chance; }

    int getWordRemain () { return wordRemain; }


    void inputWordLength () {
        cout << "Please input word length: ";
        cin >> wordLength;

        string dummy;
        getline(cin,dummy);
    }

};

void PrintOut (game &hangman) {
    cout << "Word Length: " << hangman.getWordLength() << endl;
    cout << "Current Word: " ;
    int length = hangman.getWordLength();
    for (int i = 0; i < length; i++) {
        cout << "-";
    }
    cout << endl;
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

void LengthSelect (game &hangman, set<string> &dic) {
    int length = hangman.getWordLength();
    for (auto itr = dic.begin(); itr != dic.end(); itr++) {
        if (itr->length() != length) {
            dic.erase(itr);
        }
    }
}


void SelectWords(game &hangman, set<string> &dic) {
    cout << "Guess a letter: ";
    string temp = Getline();
    char letter = temp[0];
    cout << letter <<endl;
    hangman.pushGuessed(letter);
    hangman.setRemainChance(hangman.getRemainChance() - 1);



}

int main() {
    set<string> dictionary;
    LoadDic(dictionary);

    game hangman;
    LengthSelect(hangman,dictionary);

    while(hangman.getRemainChance()) {
        SelectWords(hangman, dictionary);

        system("CLS");
        PrintOut(hangman);
    }
    return 0;
}
