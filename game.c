#include "wordl.h"

//Read Dictionary File
int ReadDictionary(char dictionary[][WORD_LENGTH + 1]{
  FILE *file = fopen("words.txt", "r");
if(!File){
printf("Error! can not open words.txt\n");
return 0;
}
int count = 0;
int buffer[100];

while (fgets(buffer, sizeof(buffer), file)) {
        buffer[strcspn(buffer, "\n")] = '\0';
        if (strlen(buffer) == WORD_LENGTH) {
            strcpy(dictionary[count], buffer);
            count++;
        }
    }

    fclose(file);
    return count;
}

// Choose random secret word
void ChooseRandomWord(char dictionary[][WORD_LENGTH + 1], int count, char *secret) {
    int index = rand() % count;
    strcpy(secret, dictionary[index]);
}

// Check if a word is valid
int IsValidWord(const char *word, char dictionary[][WORD_LENGTH + 1], int count) {
    if (strlen(word) != WORD_LENGTH)
        return 0;

    for (int i = 0; i < count; i++) {
        if (strcmp(word, dictionary[i]) == 0)
            return 1;
    }
    return 0;
}

// Ask user for guess
void GetUserGuess(char *guess, char dictionary[][WORD_LENGTH + 1], int count) {
    do {
        printf("Enter a %d-letter word: ", WORD_LENGTH);

        if (fgets(guess, WORD_LENGTH + 10, stdin) == NULL)
            continue;

        guess[strcspn(guess, "\n")] = '\0';

        if (!IsValidWord(guess, dictionary, count))
            printf("Invalid word, try again.\n");
        else
            break;

    } while (1);
}

// Generate feedback for user
void GiveFeedback(char guess[], char secret[], char feedback[]) {
    int match[WORD_LENGTH] = {0};

    for (int i = 0; i < WORD_LENGTH; i++) {
        if (guess[i] == secret[i]) {
            feedback[i] = 'G';
            match[i] = 1;
        } else {
            feedback[i] = 'B';
        }
    }

    for (int i = 0; i < WORD_LENGTH; i++) {
        if (feedback[i] == 'B') {
            for (int j = 0; j < WORD_LENGTH; j++) {
                if (!match[j] && guess[i] == secret[j]) {
                    feedback[i] = 'Y';
                    match[j] = 1;
                    break;
                }
            }
        }
    }

    feedback[WORD_LENGTH] = '\0';
}

// Main game function (Part 1)
void PlayGame(char dictionary[][WORD_LENGTH + 1], int LoadedWords, char *secret) {
    char guess[100];
    char feedback[WORD_LENGTH + 1];
    int attempts = MAX_ATTEMPTS;

    printf("\n----- WORDLE (Part 1) -----\n");

    while (attempts > 0) {
        printf("\n%d attempts left.\n", attempts);
        GetUserGuess(guess, dictionary, LoadedWords);
        GiveFeedback(guess, secret, feedback);

        or (int i = 0; i < WORD_LENGTH; i++) {
    if (feedback[i] == 'G')
        printf(COLOR_GREEN " %c " COLOR_RESET, guess[i]);
    else if (feedback[i] == 'Y')
        printf(COLOR_YELLOW " %c " COLOR_RESET, guess[i]);
    else
        printf(COLOR_BLACK " %c " COLOR_RESET, guess[i]);
}
printf("\n");

        if (strcmp(guess, secret) == 0) {
            printf("\nCongratulations! You guessed the word.\n");
            return;
        }

        attempts--;
    }

    printf("\nOut of attempts! The word was: %s\n", secret);
}
