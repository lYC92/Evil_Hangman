#include <iostream>
#include <fstream>
#include <string>
#include <cassert>
#include <iterator>
#include <algorithm>
#include <map>

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
}

class game {
private:
    size_t wordLength;
    size_t remainChance;
    vector<char> guessedLetters;    // e.g. "c"
    int wordRemain;         // e.g. 100
    string currentWord;     // e.g. "---a---e--"

public:
    vector<string> dictionary;
//    map<string, vector<int>> relation;

    game() {
        LoadDic(dictionary);
        inputWordLength();
        remainChance = wordLength * 10;
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

    void inputWordLength () {
        cout << "Please input word length: ";
        cin >> wordLength;
        string dummy;
        getline(cin,dummy);
    }
};


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


void analysis(game &hangman, char letter) {
// this will update hangman.currentWord
    map<string, pair<vector<size_t>,size_t>> relation ;

    map<vector<size_t>,size_t> summary;

    for(auto itr = hangman.dictionary.begin(); itr != hangman.dictionary.end(); itr++) {
        string word = *itr;
        vector<size_t> position;

        size_t pos = word.find(letter,0);
        while (pos != string::npos) {
            position.push_back(pos);
            pos = word.find(letter,pos+1);
        }
        relation[word] = make_pair(position,position.size());

        summary[position] = summary[position] + 1;

    }

    auto itrInitial = relation.begin();
    vector<size_t> maxIndx = itrInitial->second.first;
    for (auto itr = summary.begin(); itr != summary.end(); itr++) {
        if (itr->second > summary[maxIndx])
            maxIndx = itr->first;
    }
    cout << "max chances is for " << letter << " is ";
    copy(maxIndx.begin(),maxIndx.end(),ostream_iterator<size_t>(cout," "));
    cout << endl;

    hangman.dictionary.clear();
    for (auto itr = relation.begin(); itr != relation.end(); ++itr) {
        if (itr->second.first == maxIndx)
            hangman.dictionary.push_back(itr->first);
    }

    for (auto itr = maxIndx.begin(); itr != maxIndx.end(); ++itr) {
        string temp = hangman.getCurrentWord();
        temp[*itr] = letter;
        hangman.setCurrentWord(temp);
    }

    copy(hangman.dictionary.begin(),hangman.dictionary.end(),ostream_iterator<string>(cout, "\n"));

}


void SelectWords(game &hangman) {
    char letter;
    do {
        cout << "Guess a letter (not guessed one): ";
        string temp = Getline();
        letter = temp[0];
    }while( find(hangman.start(), hangman.final(), letter) != hangman.final());

//    update guessed letter and remain chances
    hangman.pushGuessed(letter);
    hangman.setRemainChance(hangman.getRemainChance() - 1);

    analysis(hangman, letter);
    hangman.setWordRemain(hangman.dictionary.size());
}

int main() {

    game hangman;

    while(hangman.getRemainChance()) {
        SelectWords(hangman);
        PrintOut(hangman);
        if (hangman.getWordRemain() == 1) {
            cout << "You win!" << endl;
            break;
        }
        if (hangman.getRemainChance() == 0)
            cout << "You lose." << endl;
    }

    return 0;
}
