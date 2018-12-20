//
//  FBullCowGame.cpp
//  BullCowGame
//
//  Created by Zachary Taylor on 11/29/18.
//  Credit to Ben Tristem
//  Copyright © 2018 Zachary Taylor. All rights reserved.
//
#pragma once
#include "FBullCowGame.hpp"
#include <map>
#define TMap std::map

// Changes made to prep for Unreal
using FString = std::string;
using int32 = int;

// Constructor
FBullCowGame::FBullCowGame() { Reset(); }

// Getters
int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }
bool FBullCowGame::IsGameWon() const { return bGameIsWon; }
int32 FBullCowGame::GetHiddenWordLength() const { return MyHiddenWord.length(); }

int32 FBullCowGame::GetMaxTries() const
{
    TMap<int32, int32> WordLengthMaxTries { {3,4}, {4,7}, {5,10}, {5,16}, {7,20} };
    
    return WordLengthMaxTries[MyHiddenWord.length()];
}

void FBullCowGame::Reset()
{
    const FString HIDDEN_WORD = "plant"; // Must be an isogram.
    MyHiddenWord = HIDDEN_WORD;
    
    bGameIsWon = false;
    MyCurrentTry = 1;
    return;
}

EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const
{
    if (!IsIsogram(Guess)) // not an isogram
    {
        return EGuessStatus::Not_Isogram;
    }
    else if (!IsLowercase(Guess)) // not all lowercase
    {
        return EGuessStatus::Not_Lowercase;
    }
    else if (Guess.length() != GetHiddenWordLength()) // if guess is wrong length
    {
        return EGuessStatus::Wrong_Length;
    }
    else
    {
        return EGuessStatus::OK;
    }
}

FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess)
{
    MyCurrentTry++;
    FBullCowCount BullCowCount;
    int32 WordLength = MyHiddenWord.length();
    
    for (int32 MHWChar = 0; MHWChar < WordLength; MHWChar++)
    {
        for(int32 GChar = 0; GChar < WordLength; GChar++)
        {
            if(Guess[GChar] == MyHiddenWord[MHWChar])
            {
                if (MHWChar == GChar)
                {
                    BullCowCount.Bulls++;
                }
                else
                {
                    BullCowCount.Cows++;
                }
            }
        }
    }
    if (BullCowCount.Bulls == WordLength)
    {
        bGameIsWon = true;
    }
    else
    {
        bGameIsWon = false;
    }
    return BullCowCount;
}

bool FBullCowGame::IsIsogram(FString Word) const
{
    if (Word.length() <= 1) { return true; }
    
    TMap<char, bool> LetterSeen;
    for (auto Letter : Word)
    {
        Letter = tolower(Letter);
        // Ben has this V flipped, thus sans !
        if (!LetterSeen[Letter])
        {
            LetterSeen[Letter] = true;
        }
        else
        {
            return false;
        }
    }
    return true;
}

bool FBullCowGame::IsLowercase(FString Word) const
{
    
    
    for (auto Letter : Word)
    {
        if (!islower(Letter))
        {
            return false;
        }
    }
    return true;
}
