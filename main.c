#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define MAX_WORDS 6000 //a constant that sets the maximum of words we can load
#define WORD_LENGTH 5 //the length of each valid word

int ReadDictionary(char dictionary[][WORD_LENGTH + 1]){
    File *file = fopen("words.txt", "r");
    if(!file){
        printf("error : can not open the text file");
        return 0;
    }
    int count = 0; //count for how many dictionary enteries we stored
    char buffer[100]; //to hold the user's input temporarly
    
    while (fgets(buffer, sizeof(buffer), file)){ //fgets reads one line from the fle into buffer including the newline
        buffer[strcspn(buffer, '\n')] = '\0'; //remove newline
           if (strlen (buffer) == WoORD_LENGTH){ //filters out blank lines or words with incorrect length
             strcpy(dictionary[count], buffer); //copies the 5 letter word into dicionary the 2D array with index count
             count++; //increament word stored count
          }
    }i
    fclose(file); //close the file and return how many words were loaded
    return count;
}

int main(){
    char dictionary[MAX_WORDS][WORD_LENGTH + 1]; //strings of Max_Words each string has Word_Length length + 1 for the terminator
    int LoadedWords = ReadDictionary(dictionary); //call the function to load the word in the array
    //print how many valide 5-letters words we loaded from words.txt
    printf("loaded %d words.\n", LoadedWords); 

    for(int i = 0; i < 5; i++){
        printf("%s\n", dictionary[i]); //print the first five words as a quick test
    }
    return 0; //standard success exit code
}
//choose a random word in the dictionary
void ChooseRandomWord(char dicionary[] [WORD_LENGTH + 1], int count, char* secret){
    int index = rand() % count; //rand() generates a random integer, and modulo count ensures the index falls within the valid range of the dicionary array
strcpy(secret, dictionary[index]);
}
//verefication if the word is valid : good size + presented in the dictionary 
int IsValidWord(const char* word, char dictionary[] [WORD_LENGTH + 1], int count){
    //check if the word length matches the required word length 
    if (strlen(word) != WORD_LENGTH)
        return 0;
    //loop through each word in the dictionary
for (int i = 0; i <count; i++) {
    //compare the input word to the dictionary word
 if (strcmp(word, dictionary[i] == 0)
     return 1;//word found in the dictionary, valid
}
return 0; // word not founf in the dictionary, invalid
}
//simple function to get a user entered word with basic validation 
void GetUserGuess (char* guess, char dictionary [] [WORD_LENGTH + 1], int count) {
    do {
        //prompt the user to enter a word of required length
    printf("enter a word with %d letters :", WORD_LENGTH);
        //read user input from standard input
if (fgets(guess, WORD_LENGTH + 10, stdin) == NULL) {
printf ("error  of reading.\n");
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
