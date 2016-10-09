//
//  Created by Kevin Amiranoff on 08/10/2016.
//  Copyright © 2016 Kevin Amiranoff. All rights reserved.
//

// Currently watching The Unreal Engine Developer Course
// at lecture 42



#include <iostream>
#include "FCowBullGame.h"

using FText = std::string; //Unreal immutable string type
using int32 = int; // Unreal integer

// Prototypes.
FBullCowGame BCGame; //instanciate a new game

void PlayGame();

void PrintGameIntro();

void LoopThroughGuesses(int32 limit);

FText GetValidGuessFromPlayer(int32 currentTry);

void PrintBullCowCount(FBullCowCount bullCowCount);

void PrintGameResult();

bool AskToPlayAgain();

// Entry point
int main(int32 argc, const char *argv[]) {

    PlayGame();

    return 0;


}

void PrintGameIntro() {
    int32 HiddenWordLength = BCGame.GetHiddenWordLength();

    std::cout << std::endl;
    std::cout << "Welcome to Bulls and Cows, a fun word game\n";
    std::cout << "Can you guess the " << HiddenWordLength << " letters isogram I'm thinking of\n";
    std::cout << std::endl;
    return;
}

void LoopThroughGuesses(int32 limit) {

    while (BCGame.IsGameWon() != true && BCGame.GetCurrentTry() <= limit) {
        FText Guess = GetValidGuessFromPlayer(BCGame.GetCurrentTry()); // TODO make loop checking valid
        FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);
        PrintBullCowCount(BullCowCount);
    }
}

FText GetValidGuessFromPlayer(int32 currentTry) {
    // cin >> Guess;// by default cin stops after whitespace. To get the entire line we need to use getline

    EGuessStatus Status = EGuessStatus::Invalid_Status;
    FText Guess = "";

    do {

        std::cout << "Trial n'" << currentTry << ". Enter your guess: ";
        std::getline(std::cin, Guess);
        Status = BCGame.CheckGuessValidity(Guess);

        switch (Status) {
            case EGuessStatus::Wrong_Number_Of_Letters:
                std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word.\n";
                break;
            case EGuessStatus::Not_Isogram:
                std::cout << "Please enter a word with not repeating letters (an isogram).\n";
                break;
            case EGuessStatus::Not_Lowercase:
                std::cout << "Your word must be all lowercase.\n";
                break;
            default:
                //assuming Guess is valid
                break;
        }

    } while (Status != EGuessStatus::OK);

    return Guess;
}

void PrintBullCowCount(FBullCowCount bullCowCount) {
    std::cout << "Bulls = " << bullCowCount.Bulls;
    std::cout << " Cows = " << bullCowCount.Cows;
    std::cout << std::endl << std::endl;
}

void PrintGameResult() {

    if (BCGame.IsGameWon()) {
        std::cout << "Well done, victor.\n";
    } else {
        std::cout << "You did not guess the word, maybe next time.\n";
    }

}

bool AskToPlayAgain() {
    bool playAgain = false;
    FText Response = "";


    std::cout << "Do you want to play again with the same word ? [y,n]";
    std::getline(std::cin, Response);
    char FirstLetter = Response[0];

    if (FirstLetter == 'y' || FirstLetter == 'Y') {
        playAgain = true;
    }

    return playAgain;
}

void PlayGame() {


    bool bPlayAgain = false;
    do {

        BCGame.Reset(); // Reset the game to base settings.

        int32 MaxTries = BCGame.GetMaxTries();

        PrintGameIntro();
        LoopThroughGuesses(MaxTries);
        PrintGameResult();
        bPlayAgain = AskToPlayAgain();
    } while (bPlayAgain);

}
