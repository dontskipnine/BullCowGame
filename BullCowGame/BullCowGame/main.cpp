//
//  main.cpp
//  BullCowGame
//
//  Created by Zachary Taylor on 11/25/18.
//  Credit to Ben Tristem
//  Copyright © 2018 Zachary Taylor. All rights reserved.
//
#pragma once
#include <iostream>
#include <string>
#include "FBullCowGame.hpp"

// Changes made to prep for Unreal
using FText = std::string;
using int32 = int;

// Prototypes
void PrintIntro();
void PrintGameSummary();
void PlayGame();
FText GetValidGuess();
bool AskToPlayAgain();

FBullCowGame BCGame;

// Entry Point
int main()
{
    do
    {
        PrintIntro();
        PlayGame();
        //AskToPlayAgain();
    } while (AskToPlayAgain() == true);
    return 0; // Exit App
}

void PlayGame()
{
    // Ask for guesses.
    BCGame.Reset();
    int32 MaxTries = BCGame.GetMaxTries();
    
    while (!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries)
    {
        FText Guess = GetValidGuess();
        
        FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);

        std::cout << "Bulls = " << BullCowCount.Bulls;
        std::cout << ". Cows = " << BullCowCount.Cows << "\n\n";
    }
    
    PrintGameSummary();
    return;
}

void PrintIntro()
{
    // Introduce the game.
    std::cout << "\n\nWelcome to Bulls and Cows, a fun word game.\n";
    std::cout << std::endl;
    std::cout << "          }   {         ___ " << std::endl;
    std::cout << "          (o o)        (o o) " << std::endl;
    std::cout << "   /-------\\ /          \\ /-------\\ " << std::endl;
    std::cout << "  / | BULL |O            O| COW  | \\ " << std::endl;
    std::cout << " *  |-,--- |              |------|  * " << std::endl;
    std::cout << "    ^      ^              ^      ^ " << std::endl;
    std::cout << "Can you guess the " << BCGame.GetHiddenWordLength() << " letter isogram that I'm thinking of?\n";
    std::cout << std::endl;
    return;
}

void PrintGameSummary()
{
    if (BCGame.IsGameWon())
    {
        std::cout << "Congratulations on your victory!\n";
    }
    else
    {
        std::cout << "Better luck next time!\n";
    }
    
    return;
}

FText GetValidGuess()
{
    FText Guess = "";
    EGuessStatus Status = EGuessStatus::Invalid_Status;
    do {
        // Get Player's Guess.
        std::cout << "Try " << BCGame.GetCurrentTry() << " of "<< BCGame.GetMaxTries() << ". Enter your guess: ";
        getline(std::cin, Guess);
        
        Status = BCGame.CheckGuessValidity(Guess);
        switch (Status)
        {
            case EGuessStatus::Wrong_Length:
                std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word.\n\n";
                break;
            case EGuessStatus::Not_Isogram:
                std::cout << "Guess is not an isogram, please enter an isogram.\n\n";
                break;
            case EGuessStatus::Not_Lowercase:
                std::cout << "Please enter your guess entirely in lowercase letters.\n\n";
                break;
            default:
                break;
        }
        //std::cout << std::endl;
    } while (Status != EGuessStatus::OK);
    
    return Guess;
}

bool AskToPlayAgain()
{
    std::cout << "Do you want to play again with the same hidden word? \n";
    FText Reponse = "";
    getline(std::cin, Reponse);
    
    return (Reponse[0] == 'y') || (Reponse[0] == 'Y');
}
