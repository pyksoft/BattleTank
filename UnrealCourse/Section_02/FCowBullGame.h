//
// Created by Kevin Amiranoff on 09/10/2016.
//

#ifndef COWBULLGAME_FCOWBULLGAME_H
#define COWBULLGAME_FCOWBULLGAME_H

#include <stdio.h>
#include <string>

using FString = std::string; //Unreal string.
using int32 = int; // Unreal integer

struct FBullCowCount {
    int32 Bulls;
    int32 Cows;
};

enum class EGuessStatus {
    Invalid_Status,
    OK,
    Not_Isogram,
    Wrong_Number_Of_Letters,
    Not_Lowercase,
};

class FBullCowGame {

public:

    FBullCowGame(); // constructor

    void Reset(); // @TODO make a more rich return value

    int32 GetHiddenWordLength() const;

    int32 GetMaxTries() const;

    int32 GetCurrentTry() const;

    bool IsGameWon() const;

    bool SetGameStatus(bool);

    EGuessStatus CheckGuessValidity(FString) const;

    FBullCowCount SubmitValidGuess(FString);

private:
    int32 MyCurrentTry;
    int32 MyMaxTries;
    FString MyHiddenWord;
    bool bIsGameWon;
};


#endif //COWBULLGAME_FCOWBULLGAME_H
