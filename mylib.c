#include <stio.h>
#include <string.h>
#include "MYLIB.H"

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
