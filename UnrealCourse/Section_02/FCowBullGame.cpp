//
// Created by Kevin Amiranoff on 09/10/2016.
//

//
//  FBullCowGame.cpp
//  BullCowGame
//
//  Created by Kevin Amiranoff on 09/10/2016.
//  Copyright © 2016 Kevin Amiranoff. All rights reserved.
//


#pragma once
#include <iostream>
#include "FCowBullGame.h"
#include <map>

#define TMap std::map //Unreal map

using FString = std::string; //Unreal string.
using int32 = int; // Unreal integer

FBullCowGame::FBullCowGame() {
    Reset();
}

void FBullCowGame::Reset() {

    const FString HIDDEN_WORD = "planet"; //Must be an isogram;

    MyHiddenWord = HIDDEN_WORD;
    MyCurrentTry = 1;
    bIsGameWon = false;

    return;
}

EGuessStatus FBullCowGame::CheckGuessValidity(FString guess) const {

    int32 GuessLength = guess.length();


    if (!IsIsogram(guess)) {
        return EGuessStatus::Not_Isogram;
    } else if (!IsLowercase(guess)) {
        return EGuessStatus::Not_Lowercase;
    } else if (GuessLength != GetHiddenWordLength()) {
        return EGuessStatus::Wrong_Number_Of_Letters;
    } else {
        return EGuessStatus::OK;
    }
}

bool FBullCowGame::IsGameWon() const {
    return bIsGameWon;
}

FBullCowCount FBullCowGame::SubmitValidGuess(FString guess) {

    MyCurrentTry++;

    FBullCowCount BullCowCount;
    BullCowCount.Bulls = 0;
    BullCowCount.Cows = 0;


    int32 HiddenWordLength = MyHiddenWord.length();
    int32 GuessLength = guess.length();

    // loop through all letters in the Hidden word.
    for (int32 HiddenWordChar = 0; HiddenWordChar < HiddenWordLength; HiddenWordChar++) {
        // compare letters against the hidden word
        for (int32 GuessChar = 0; GuessChar < GuessLength; GuessChar++) {
            // if they match then
            if (MyHiddenWord[HiddenWordChar] == guess[GuessChar]) {
                //if they are in the same place
                if (HiddenWordChar == GuessChar) {
                    BullCowCount.Bulls++;
                } else {
                    BullCowCount.Cows++;
                }

            }
        }
    }

    if (BullCowCount.Bulls == HiddenWordLength) {
        SetGameStatus(true);
    }

    return BullCowCount;
}

int32 FBullCowGame::GetMaxTries() const {
    // difficulty table
    TMap<int32, int32> WordLengthToMaxTries{{3, 5},
                                            {4, 7},
                                            {5, 10},
                                            {6, 15},
                                            {7, 20}};
    return WordLengthToMaxTries[MyHiddenWord.length()];

}

int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }

int32 FBullCowGame::GetHiddenWordLength() const {
    int32 HiddenWordLength = MyHiddenWord.length();
    return HiddenWordLength;
}

bool FBullCowGame::SetGameStatus(bool gameStatus) {
    bIsGameWon = gameStatus;
    return bIsGameWon;
}

bool FBullCowGame::IsIsogram(FString word) const {
    //if its empty or 1 letter length
    if (word.length() <= 1) { return true; }

    //loop through all letters
    TMap<char, bool> LetterSeen; // TSet also possible (and better suited)
    for (auto Letter : word) {
        Letter = tolower(Letter);
        //if the letter is in the map
        if (LetterSeen.count(Letter) == 1) {
            return false;     // not an isogram
        } else { //otherwise adds letter to the map
            LetterSeen[Letter] = Letter;
        }

    }


    return true;
}

bool FBullCowGame::IsLowercase(FString word) const {
    for (auto Letter : word) {
        if (isupper(Letter)) {
            return false;
        }
    }
    return true;
}
