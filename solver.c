#include "wordle.h"

// Compute feedback without printing (for solver)
void ComputeFeedback(const char *guess, const char *secret, char *feedback) {
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

// Check if candidate matches feedback rules
int IsCompatible(const char *candidate, const char *guess, const char *feedback_target) {
    char tmp[WORD_LENGTH + 1];
    ComputeFeedback(guess, candidate, tmp);
    return strcmp(tmp, feedback_target) == 0;
}

// Filter remaining candidates
int FilterCandidates(char candidates[][WORD_LENGTH + 1], int count,
                     const char *guess, const char *feedback_target) {

    int newCount = 0;

    for (int i = 0; i < count; i++) {
        if (IsCompatible(candidates[i], guess, feedback_target)) {
            strcpy(candidates[newCount], candidates[i]);
            newCount++;
        }
    }
    return newCount;
}

// Copy dictionary -> candidates
void InitializeCandidates(char candidates[][WORD_LENGTH + 1],
                          char dictionary[][WORD_LENGTH + 1], int count) {

    for (int i = 0; i < count; i++) {
        strcpy(candidates[i], dictionary[i]);
    }
}

// Solver main function
void Solver(char dictionary[][WORD_LENGTH + 1], int dictCount, const char *secret_word) {

    char candidates[MAX_WORDS][WORD_LENGTH + 1];
    InitializeCandidates(candidates, dictionary, dictCount);

    int candidateCount = dictCount;

    char guess[WORD_LENGTH + 1];
    char feedback[WORD_LENGTH + 1];

    strcpy(guess, "arise"); // First guess

    printf("\n----- SOLVER (Part 2) -----\n");

    for (int attempt = 1; attempt <= MAX_ATTEMPTS; attempt++) {

        ComputeFeedback(guess, secret_word, feedback);
        printf("Attempt %d: %s -> %s\n", attempt, guess, feedback);

        if (strcmp(guess, secret_word) == 0) {
            printf("\nSolver found the word in %d attempts!\n", attempt);
            return;
        }

        candidateCount =
            FilterCandidates(candidates, candidateCount, guess, feedback);

        if (candidateCount == 0) {
            printf("Solver failed! No candidates left.\n");
            return;
        }

        strcpy(guess, candidates[0]); // Next guess
    }

    printf("Solver could not find the word.\n");
}
