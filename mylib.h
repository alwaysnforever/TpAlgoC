#ifndef MYLIB_H
#define MYLIB_H

#define MAX_WORDS 6000
#define WORD_LENGTH 5
#define ATTEMPTS 6

//functions prototype
int ReadDictionary(char dictionary[][WORD_LENGTH + 1]);
//choose a random word in the dictionary
void ChooseRandomWord(char dictionary[] [WORD_LENGTH + 1], int count, char* secret);
//verefication if the word is valid : good size + presented in the dictionary 
int IsValidWord(const char *word, char dictionary[] [WORD_LENGTH + 1], int count)
//simple function to get a user entered word with basic validation 
void GetUserGuess (char *guess, char dictionary [] [WORD_LENGTH + 1], int count);
//function to give feedback about the word (correct letter or not in position, or do not exist)
void GiveFeedback(char guess[100], char secret[WORD_LENGTH + 1], feedback[WORD_LENGTH + 1]);
