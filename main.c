#include<stdio.h>
#include<string.h>
#define Max_Words 6000; //a constant that sets the maximum of words we can load
#define Word_Length 5; //the length of each valid word

int ReadDictionary(char dictionary[][Word_Length+1]){
    File *file = fopen("words.txt", "r");
    if(!file){
        printf("error : can not open the text file");
        return 0;
    }
    int count = 0; //count for how many dictionary enteries we stored
    char buffer[100]; //to hold the user's input temporarly
    
    while (fgets(buffer, sizeof(buffer), file)){ //fgets reads one line from the file into buffer including the newline
        buffer[strcspn(buffer, '\n')] = '\0'; //remove newline
           if (strlen (buffer) == Word_Length){ /filters out blank lines or words with incorrect length
             strcpy(dictionary[count], buffer); //copies the 5 letter word into dicionary the 2D array with index count
             count++; //increament word stored count
          }
    }
    fclose(file); //close the file and return how many words were loaded
    return count;
}

int main(){
    char dictionary[Max_Words][Word_Length + 1]; //strings of Max_Words each string has Word_Length length + 1 for the terminator
    int LoadedWords = ReadDictionary(dictionary); /call the function to load the word in the array
    printf("load %n words.\n", LoadedWords); print how many valide 5-letters words we loaded from words.txt

    for(i = 0; i < 5; i++){
        printf("%s\n", dictionary[i]); //print the first five words as a quick test
    }
    return 0; standard success exit code
}
