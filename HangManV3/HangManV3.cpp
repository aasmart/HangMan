// HangManV3.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include <iostream>
#include <ctime>
#include <random>
#include <cctype>

static std::string word;				// Word being guessed
static char guess;						// The character guessed
static int totalCorrect = 0;			// Total correct words
static int totalTries = 0;				// Total guessed words
static const double versionNum = 3.2;	// Hangman version number

// Mersenne seed
namespace random {
	std::mt19937 mersenne(static_cast<std::mt19937::result_type>(std::time(nullptr)));
}	

// Guessed letters
char letters[26][2] = {
	{'a', '0'},
	{'b', '0'},
	{'c', '0'},
	{'d', '0'},
	{'e', '0'},
	{'f', '0'},
	{'g', '0'},
	{'h', '0'},
	{'i', '0'},
	{'j', '0'},
	{'k', '0'},
	{'l', '0'},
	{'m', '0'},
	{'n', '0'},
	{'o', '0'},
	{'p', '0'},
	{'q', '0'},
	{'r', '0'},
	{'s', '0'},
	{'t', '0'},
	{'u', '0'},
	{'v', '0'},
	{'w', '0'},
	{'x', '0'},
	{'y', '0'},
	{'z', '0'},

};

// Words to guess
std::string words[] = {
	{"dog"},
	{"computer"},
	{"mathematics"},
	{"transcendentalism"},
	{"specifically"},
	{"partisan"},
	{"despicable"},
	{"whiteboard"},
	{"neuron"},
	{"integral"},
	{"valedictorian"},
	{"pie"},
	{"nonchalant"},
	{"irresistible"},
	{"spider"},
	{"realm"},
	{"helicopter"},
	{"giraffe"},
	{"program"},
	{"stupid"},
	{"heroism"},
	{"satisfactory"},
	{"whiteboard"},
	{"fish"},

};

// 'Clears' the console
void clearConsole() {
	std::cout << "\x1B[2J\x1B[H";
}

// Method for writing out the word & getting the guess
void write() {
	for (int i{ 0 }; i < 26; ++i) {	// Resets all letters guessed to false at method call
		letters[i][1] = '0';
	}

	std::string output{ "" };			// The printed word data
	std::string guessedLetters{ "" };	// The letters currently guessed
	unsigned int correct{ 0 };			// Correct number of characters in the word
	unsigned int guesses{ 0 };			// Total guesses

	do {
		clearConsole();			// clr console
		correct = 0;			// Resets correct chars
		guessedLetters = "";	// Resets gussed letters
		output = "";			// Resets output

		// Finds the letters that have been guessed
		for (int i{ 0 }; i < 26; ++i) {	// Runs through alphabet
			int col{0};

			if (letters[i][1] == '1') {
				guessedLetters += std::toupper(letters[i][0]);	// Converts chars to upper then adds them to guessed letters
				guessedLetters += " ";							// Space
			}	
		}

		std::cout << " | Current Incorrect Guesses: " << guesses << "/" << "8 \n";
		std::cout << " | Guessed Letters: " << guessedLetters;

		// Runs through and outputs the word based on guessed letters 
		for (unsigned int i{ 0 }; i < (word.length()); ++i) {	// Runs through the word
			int log = 0;											// checks if a letter is logged
			for (int ii{ 0 }; ii < 26; ++ii) {
				if (word[i] == letters[ii][0] && letters[ii][1] == '1') {	// If letter is active & in word add it to data
					log = 1;					// Set logged to true
					output += letters[ii][0];	// Add letter
					correct++;					// Increase correct
					break;
				}
			}
			if (word[i] == ' ') {	// Checks for spaces
				output += " ";
				correct++;
			}
			else if (log != 1) { // Sets the char to no character if a letter has not been found
				output += "*";
			}
		}

		std::cout << "\n | Word to Guess: " << output;
		
		// Asks for a guess from the user
		std::cout << "\n |\n | Please Enter a Guess: ";
		std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');	// Clears any extra input
		std::cin >> guess;

		// Finds the input in the array & sets its value to 1
		for (int i{ 0 }; i < 26; ++i) {	// Runs through alphabet
			if (std::tolower(guess) == letters[i][0]) {	// lowercases gues & compares to the letters 
				if (letters[i][1] != '1') {	// System to prevent double guessing & check if the letter is in the word
					for (unsigned int ii{ 0 }; ii < (word.length()); ++ii) {
						if (std::tolower(guess) == word[ii]) {	// If the current guess is in the word dont inc guesses
							break;
						}
						else if (ii >= word.length() - 1) {	// Inc guesses if guess is not in word
							std::cout << '\a';
							guesses++;
							break;
						}
					}
				}
				letters[i][1] = '1';	// Sets the guess letter to active
				break;
			}
		}
		
		clearConsole();	// clr console

	} while (correct < word.length() - 1 && guesses < 8);	// Runs under these conditions

	// Checks if word was within the guess limit
	if (guesses < 8) {
		std::cout << " | You Guessed the Word, \"" << word << "\", with " << guesses << " incorrect guess(s)\n | \n";
		totalCorrect++;
	}
	else {
		std::cout << " | You did not Guess the Word, \"" << word << "\", within the 8 incorrect guess limit, better luck next time!\n | \n";
	}
}

void pickWord() {
	std::uniform_int_distribution<> die(0, std::size(words) - 1);
	word = words[die(random::mersenne)];
}

bool play() {
	std::string play;
	std::cout << " | Would you Like to Play Hangman: ";
	std::cin >> play;

	if (std::cin.fail()) {
		std::cin.clear();
		std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
	}

	else {
		if (play == "Yes" || play == "yes") {
			return true;
		}
		else {
			return false;
		}
	}
	return false;
}

int main()
{
	std::cout << " | HANGMAN V" << versionNum << "\n | \n";

	while (play() == true) {
		totalTries++;
		std::cout << "Generating! ";
		pickWord();
		write();
	}

	std::cout << "\n | You Correctly Guessed " << totalCorrect << "/" << totalTries << " Words! Play again later!";

	return 0;
}