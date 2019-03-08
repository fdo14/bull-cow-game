/* This is the console executable, that makes use of the BullCow class.
This acts as the view in a MVC patter, and is responsible for all user
interaction. For game logic see FBullCowGame class.
*/


#include <iostream>
#include <string>
#include "FBullCowGame.h"

using FText = std::string;
using int32 = int;

void PrintIntro();
FText GetValidGuess();
void PlayGame();
bool AskToPlayAgain();
void PrintGameSummary();


FBullCowGame BCGame;

//The entry point for our application
int main() {
	bool WantsToPlayAgain = false;
	do {
		PrintIntro();
		PlayGame();
		WantsToPlayAgain = AskToPlayAgain();
	} while (WantsToPlayAgain);
	
	return 0;
}

void PrintIntro() {
	//introduce the game
	FString NumberOfLetters = "";
	bool ValidNumber = false;

	std::cout << "Welcome to Bulls and Cows, a fun word game.\n";
	std::cout << std::endl;
	std::cout << "          }   {         ___ " << std::endl;
	std::cout << "          (o o)        (o o) " << std::endl;
	std::cout << "   /-------\\ /          \\ /-------\\ " << std::endl;
	std::cout << "  / | BULL |O            O| COW  | \\ " << std::endl;
	std::cout << " *  |-,--- |              |------|  * " << std::endl;
	std::cout << "    ^      ^              ^      ^ " << std::endl;

	std::cout << "Would you like a 3, 4, 5, 6, or 7 letter word to guess?  ";
	std::getline(std::cin, NumberOfLetters);
	while (!ValidNumber) {
		if (NumberOfLetters == "3" || NumberOfLetters == "4" || NumberOfLetters == "5" || NumberOfLetters == "6" || NumberOfLetters == "7") {
			BCGame.ChooseWord(NumberOfLetters);
			std::cout << "Can you guess the " << BCGame.GetHiddenWordLength() << " letter word I'm thinking of?\n";
			ValidNumber = true;
		}
		else {
			std::cout << "Please choose a 3, 4, 5, 6, or 7 letter word ";
			std::getline(std::cin, NumberOfLetters);
		}
	}
	std::cout << std::endl;
	return;
}


void PlayGame() {
	BCGame.Reset();
	int32 MaxTries = BCGame.GetMaxTries();

	//loop for the number of turns asking for guesses and if not won
	while(!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries) {
		FText Guess = GetValidGuess(); //TODO validate guessing

		//Submit valid guess to game, and receive counts
		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);

		std::cout << "Bulls = " << BullCowCount.Bulls;
		std::cout << ". Cows = " << BullCowCount.Cows << "\n\n";

	}
	PrintGameSummary();

	//TODO Summarize the game
}

bool AskToPlayAgain(){
	std::cout << "Do you want to play again?(y/n) ";
	FText Response = "";
	std::getline(std::cin, Response);

	if (Response[0] == 'y' || Response[0] == 'Y') {
		return true;
	} else return false;

}

void PrintGameSummary() {
	if (BCGame.IsGameWon()) {
		std::cout << "Well Done -- You Win!\n";
	}
	else {
		std::cout << "Better Luck Next Time!\n";
	}
}

FText GetValidGuess() {
	FText Guess = "";
	EGuessStatus Status = EGuessStatus::Invalid_Status;
	do {
		// get a guess from a user
		int32 CurrentTry = BCGame.GetCurrentTry();
		std::cout << "Try " << CurrentTry << " of " << BCGame.GetMaxTries() << ". Enter your guess: ";
		std::getline(std::cin, Guess);

		Status = BCGame.CheckGuessValidity(Guess);
		switch (Status) {
		case EGuessStatus::Wrong_Length:
			std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word.\n\n";
			break;
		case EGuessStatus::Not_Isogram:
			std::cout << "Please enter a word without repeating letters.\n\n";
			break;
		case EGuessStatus::Not_Lowercase:
			std::cout << "Please enter your word in lowercase letters.\n\n";
			break;
		default:
			break;
		}

	} while (Status != EGuessStatus::OK);
	return Guess;

}

