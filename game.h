#ifndef GAME_H
#define GAME_H


class game {
private:
    int wordLength;
    int remainChance;
    vector<char> guessedLetters;
    int wordRemain;

public:
    game() {
        inputWordLength();
        remainChance = wordLength;
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


#endif // GAME_H
