#include <stio.h>
#include <string.h>
#include "MYLIB.H"
#include <stdlib.h>
#include <time.h>

int ReadDictionary(char dictionary[][WORD_LENGTH + 1]){
    FILE *file = fopen("words.txt", "r");
    if(!file){
        printf("error : can not open the text file");
        return 0;
    }
    int count = 0; //count for how many dictionary enteries we stored
    char buffer[100]; //to hold the user's input temporarly
    
    while (fgets(buffer, sizeof(buffer), file)){ //fgets reads one line from the file into buffer including the newline
        buffer[strcspn(buffer, '\n')] = '\0'; //remove newline
           if (strlen (buffer) == WORD_LENGTH){ //filters out blank lines or words with incorrect length
             strcpy(dictionary[count], buffer); //copies the 5 letter word into dicionary the 2D array with index count
             count++; //increament word stored count
          }
    }
    fclose(file); //close the file and return how many words were loaded
    return count;
}
//choose a random word in the dictionary
void ChooseRandomWord(char dictionary[] [WORD_LENGTH + 1], int count, char* secret){
    int index = rand() % count; //rand() generates a random integer, and modulo count ensures the index falls within the valid range of the dicionary array
strcpy(secret, dictionary[index]);
}
//verefication if the word is valid : good size + presented in the dictionary 
int IsValidWord(const char *word, char dictionary[] [WORD_LENGTH + 1], int count){
    //check if the word length matches the required word length 
    if (strlen(word) != WORD_LENGTH)
        return 0;
    //loop through each word in the dictionary
for (int i = 0; i < count; i++) {
    //compare the input word to the dictionary word
 if (strcmp(word, dictionary[i]) == 0)
     return 1;//word found in the dictionary, valid
}
return 0; // word not founf in the dictionary, invalid
}
//simple function to get a user entered word with basic validation 
void GetUserGuess (char *guess, char dictionary [] [WORD_LENGTH + 1], int count) {
    do {
        //prompt the user to enter a word of required length
    printf("enter a word with %d letters :", WORD_LENGTH);
        //read user input from standard input
if (fgets(guess, WORD_LENGTH + 10, stdin) == NULL) {
printf ("error  of reading input.\n");
continue; //input error, retry
}
        //remove newline character at end
guess[strcspn(guess, "\n")] = '\0'; //delete \n
        //check if the word is valid (proper length and in the dictionary)
if (!IsValidWord(guess, dictionary, count)) {
 printf ("invalid word try again.\n"); //invalid word, ask again
} else {
break; //valid input, exit loop
}
} while (1);
}
// Compare the user's guess to the secret word and generate feedback
// G = correct letter and correct position
// Y = correct letter but wrong position
// B = letter not in the secret word
void GiveFeedback(char guess[100], char secret[WORD_LENGTH + 1], feedback[WORD_LENGTH + 1]){
int match[WORD_LENGTH] = {0}; //mark the caracters that are a match 
int i, j;
//1. first pass mark greens (correct letter and position)
for(i = 0; i < WORD_LENGTH; i++){
if(guess[i] == secret[i]){
feedback[i] = 'G';
match[i] = 1;
}else{
feedback[i] = 'B'; //default to B it may change to Y
}
}
//2. second pass (correct letter, wrong position)
for(i = 0; i < WORD_LENGTH; i++){
if(feedback[i] == 'B'){ //only check letters not already green
for(j = 0; j < WORD_LENGTH; j++){
if(!match[j] && guess[i] == secret[j]){
feedback[i] = 'Y';
match[j] = 1; //mark this letter as used
break; //stop after first match
}
}
}
}
feedback[WORD_LENGTH] = '\0'; //ensure the string is null-terminated
