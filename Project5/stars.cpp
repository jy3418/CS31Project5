#define _CRT_SECURE_NO_DEPRECATE
#include "utilities.h"
#include <iostream>
#include <cstring>
#include <cctype>
using namespace std;

const char WORDFILENAME[] = "C:/Users/jy341/Desktop/smallwords.txt";
const int MAXWORDSIZE = 6;
const int MINWORDSIZE = 4;
const int MAXNUMWORDS = 9000;

int runOneRound(const char words[][7], int nWords, int wordnum);
bool hasWordInArray(const char wordList[][7], int nWords, const char word[7]);
bool isLowerCase(const char word[7]);

int main()
{
	char wordList[MAXNUMWORDS][MAXWORDSIZE+1];
	int nWords = getWords(wordList, MAXNUMWORDS, WORDFILENAME);

	//Write out and end program if number of words are less than 1
	if (nWords < 1)
	{
		cout << "No words were loaded, so I can't play the game.";
		return 0;
	}
	//Terminate since nWords cannot be greater than maximum number of words
	if (nWords > MAXNUMWORDS)
	{
		return 0;
	}

	//Take in the number of rounds wanted to be played and check validity of the input
	cout << "How many rounds do you want to play? ";
	int numRounds;
	cin >> numRounds;
	cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');	//Ignore new line characters

	if (numRounds < 0)
	{
		cout << "The number of rounds must be positive.";
		return 0;
	}

	//Modify cout to only print out 2 decimals for the average scores
	cout.setf(ios::fixed);
	cout.precision(2);

	int minTries = INT_MAX;
	int maxTries = INT_MIN;
	int currentScore;
	int totalScore = 0;
	//Main loop of the program
	for (int i = 0; i < numRounds; i++)
	{
		cout << endl << "Round " << i + 1 << endl;
		int randomNum = randInt(0, nWords - 1);	//Generate a random integer for the index of the secret word that will be used
		cout << "The secret word is " << strlen(wordList[randomNum]) << " letters long." << endl;
		//Run one round and calculate the score average, max tries, and min tries
		currentScore = runOneRound(wordList, nWords, randomNum);
		if (currentScore == -1)
		{
			cerr << "Error: bad parameters for runOneRound()." << endl;
			return 0;
		}
		totalScore += currentScore;
		if (currentScore > maxTries)
			maxTries = currentScore;
		if (currentScore < minTries)
			minTries = currentScore;

		//Print out results of the round
		if(currentScore == 1)	//Requires different formatting if player gets answer in 1 try.
			cout << "You got it in 1 try." << endl;
		else 
			cout << "You got it in " << currentScore << " tries." << endl;
		cout << "Average: " << static_cast<double>(totalScore) / (i + 1) << ", minimum: " << minTries << ", maximum: " << maxTries << endl;
	}
	return 0;
}

int runOneRound(const char words[][7], int nWords, int wordnum)
{
	if (nWords < 0 || wordnum < 0 || wordnum >= nWords)
		return -1;
	
	//Initialize necessary variables
	int numAttempts = 0;
	char probeWord[101];
	int stars; 
	int planets;

	//Run loop until it is necessary to stop (unknown number)
	for (;;)
	{
		//Reset values of stars and planets
		stars = 0;
		planets = 0;

		cout << "Probe word: ";
		cin.getline(probeWord, 101);

		//Check the validity of the probe word
		if (strlen(probeWord) > 6 || strlen(probeWord) < 4 || ! isLowerCase(probeWord))
		{
			cout << "Your probe word must be a word of 4 to 6 lower case letters." << endl;
			continue;
		} else if (! hasWordInArray(words, nWords, probeWord))
		{
			cout << "I don't know that word." << endl;
			continue;
		}
		else
			numAttempts++;	//Add to the number of attempts since it's a valid probe word

		bool letterMarker[6] = { false };	//A variable to catch duplicate stars and planets for the same letter
		//Run a for loop to check for stars first
		for (int i = 0; i < strlen(probeWord); i++)
		{
			//Check if the letter is a star
			if (words[wordnum][i] != '\0' && probeWord[i] == words[wordnum][i])
			{
				stars++;
				letterMarker[i] = true;	//Set up a flag so that same letter of the word cannot be used for multiple stars/planets
			}
		}

		//Run a for loop to check if the letter is a planet
		for (int i = 0; i < strlen(probeWord); i++)
		{
			for (int j = 0; j < strlen(words[wordnum]); j++)
			{
				//Check if the letter is planet
				if (probeWord[i] == words[wordnum][j] && i != j && !letterMarker[j])
				{
					planets++;
					letterMarker[j] = true;
					break;	//Break out of loop since it found a planet
				}
			}
		}
		//Break loop if the words are the same, or print out the result
		if (stars == strlen(words[wordnum]))
			return numAttempts;
		else
		{
			cout << "Stars: " << stars << ", Planets: " << planets << endl;
		}
	}
	return -1;
}

//Function to check to see if the word is in the array
bool hasWordInArray(const char wordList[][7], int nWords, const char word[7])
{
	for (int i = 0; i < nWords; i++)
	{
		if (strcmp(word, wordList[i]) == 0)
			return true;
	}
	return false;
}

//Function to check there are only lower cased letters in the cstring
bool isLowerCase(const char word[7])
{
	for (int i = 0; word[i] != '\0'; i++)
	{
		if (! islower(word[i]))
			return false;
	}
	return true;
}