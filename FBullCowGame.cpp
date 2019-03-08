#include "FBullCowGame.h"
#include <map>
#include <locale>
#define TMap std::map

using FString = std::string;
using int32 = int;

FBullCowGame::FBullCowGame(){
	Reset();
}

void FBullCowGame::Reset(){
	MyCurrentTry = 1;
	bGameIsWon = false;
	return;
}

//receives a valid guess, increments turn, and returns count
FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess){
	MyCurrentTry++;
	FBullCowCount BullCowCount;
	
	int32 HiddenWordLength = MyHiddenWord.length();
	int32 GuessWordLength = Guess.length();

	//loop through all letters in the guess
	for (int32 i = 0; i < GuessWordLength; i++) {
		//compare letters against the hidden word
		for (int32 j = 0; j < HiddenWordLength; j++) {
			//if they match then
			if (Guess[i] == MyHiddenWord[j]) {
				if (i == j) {
					BullCowCount.Bulls++; //increment bulls if in the same place
				}
				else {
					BullCowCount.Cows++; //increment cows if they aren't
				}
			}	
		}
	}
	if (BullCowCount.Bulls == HiddenWordLength) {
		bGameIsWon = true;
	}
	else {
		bGameIsWon = false;
	}
	return BullCowCount;
}

bool FBullCowGame::IsIsogram(FString Word) const{
	if (Word.length() <= 1) { return true; }
	TMap<char, bool>  LetterSeen;
	for (auto Letter : Word) {
		Letter = tolower(Letter); //handle mixed case
		if (LetterSeen[Letter]) { return false; }
		else {
			LetterSeen[Letter] = true;
		}
	}
	
	return true;
}

int32 FBullCowGame::GetMaxTries() const{
	TMap<int32, int32> WordLengthToMaxTries{ {3,4}, {4,7}, {5,10}, {6,15}, {7,20} };
	return WordLengthToMaxTries[MyHiddenWord.length()];
}
int32 FBullCowGame::GetCurrentTry() const{
	return MyCurrentTry;
}
int32 FBullCowGame::GetHiddenWordLength() const
{
	return MyHiddenWord.length();
}
bool FBullCowGame::IsGameWon() const{
	return bGameIsWon;
}
EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const {
	if (!IsIsogram(Guess)) {
		return EGuessStatus::Not_Isogram;
	}
	else if (!IsLowercase(Guess)) {
		return EGuessStatus::Not_Lowercase;
	}
	else if (Guess.length() != GetHiddenWordLength()) {
		return EGuessStatus::Wrong_Length;
	}
	else {
		return EGuessStatus::OK;
	}
	

}

void FBullCowGame::ChooseWord(FString Word){
	FString HIDDEN_WORD;
	if (Word == "3") {
		HIDDEN_WORD = "ant";
	} else if (Word == "4") {
		HIDDEN_WORD = "fork";
	} else if (Word == "5") {
		HIDDEN_WORD = "earth";
	} else if (Word == "6") {
		HIDDEN_WORD = "planet";
	}else {
		HIDDEN_WORD = "monkeys";
	}

	MyHiddenWord = HIDDEN_WORD;
}

bool FBullCowGame::IsLowercase(FString Word) const {
	std::locale loc;
	for (auto Letter : Word) {
		if (std::isupper(Letter, loc)) { return false; }
	}
	return true;
}
