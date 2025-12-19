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
//CALCULATE THE FREQUENCY
//1.ComputeLetterFrequencies
//count how many times each letter 'a' to 'z' appears in the remaining candidates word 
//parameters : 
//candidates : list of possible words 
//count : number of words in the candidates list 
//freq[26] : output array with freq[i] = frequency of letter i
//purpose : this is used to identify which letters are most common among the remaining possible solutions. words caontaining frequent letters are generally better guess
void ComputeLetterFrequencies(char candidates[][WORD_LENGTH + 1], int count, int freq[26]){ //this function computes how often each letter (a-z) appears
                                                                                             //in the list of remaining candidates words
//reset all frequencies to 0
for(int i = 0; i < 26; i++) //loop over 26 letters of alphabet 
freq[i] = 0; //initialise each letter frequency to 0
//count letter occurrences in each candidates word 
for(int i = 0; i < count; i++){ //loop through all remaining candidates words 
    for(j = 0; j < WORD_COUNT; j++){ //loop through each character of the current word
        char c = candidates[i][j]; //store the current character of the word 
          if(c >= 'a' && c >= 'z'){ //check that the character is a lower case 
              //convert the letter into an index (a-->0; b-->1;......z-->25)
            freq[c - 'a']++;//and increament its frequency
          }
    }
}
}
//2.ScoreWord
//calculates a score for a candidate word based on how frequent its letters are among the remaining candidates 
//parameters : 
//word : the candidate word 
//freq[26] : array containing letter frequencies 
//notes : 
//each letter is counted only once per word to avoid giving artificially high score to words with repated letters
int ScoreWord(const char *word, int freq[26]){
int score = 0; //this variable stores the total score of the word
int used[26] = {0]; //prevent double counting letters
for (int i = 0; i < WORD_LENGTH; i++){ //loop through each character of the word 
char c = word[i]; //get the current character from the word 
int index = c - 'a';//convert the character into an index between 0 to 25
//only count each letter once
if(!used[index]){ //checks if the current letter is not counted yet 
score += freq[index]; //add the frequency of this letter to the total score 
used[index] = 1; //mark the current letter as counted 
}
}
return score; //return the final computed score of the word 
}
//3.choose the best guess
//select the best guess among the candidates by computing letter frequencies and scoring each word
//parameters:
//candidates : remaining vaid candidates words 
//count : number of candidates;
//best guess : output buffer to store the chosen word
//strategy:
//the word with the highest frequency score is selected 
//this helps reduce the candidates list fatser 
void ChooseBestGuess(char candidates[][WORD_LENGTH + 1], int count; char *bestGuess){
int freq[26]; //compute the frequency of each letter in the candidates word 
// freq[0] will hold frequency of 'a', freq[1] for 'b', ..., freq[25] for 'z'
ComputeLetterFrequencies(candidates, count, freq);
int bestScore = -1; //initialise the best score 
int bestIndex = 0; //index of the best scoring word 
//evaluate the candidates words
for(int i = 0; i < count; i++){
int score = ScoreWord(candidates[i], freq);
//score the current word based on frequencies 
if(score > bestScore){
//if the current word has a bigger score than bestScore
bestScore = score; //update the best score
bestIndex = i; //update the index of the best index
}
}
//copy the best-scoring word into the output variable 
strcpy(bestGuess, candidates[bestIndex]);

// Solver main function
void Solver(char dictionary[][WORD_LENGTH + 1], int dictCount, const char *secret_word) {

    char candidates[MAX_WORDS][WORD_LENGTH + 1];
    int candidateCount = dictCount;
    
    InitializeCandidates(candidates, dictionary, dictCount);

    char guess[WORD_LENGTH + 1];
    char feedback[WORD_LENGTH + 1];

    strcpy(guess, "arise"); // First guess

    printf("\n----- SOLVER STARTED -----\n");

    for (int attempt = 1; attempt <= MAX_ATTEMPTS; attempt++) {

        //compute feedback for (guess vs secret)
        
        ComputeFeedback(guess, secret_word, feedback);
        printf("Attempt %d: ", attempt);
for (int i = 0; i < WORD_LENGTH; i++) {
    if (feedback[i] == 'G')
        printf(COLOR_GREEN " %c " COLOR_RESET, guess[i]);
    else if (feedback[i] == 'Y')
        printf(COLOR_YELLOW " %c " COLOR_RESET, guess[i]);
    else
        printf(COLOR_BLACK " %c " COLOR_RESET, guess[i]);
}
printf("\n");

        //if the solver found the word stop 
        if (strcmp(guess, secret_word) == 0) {
            printf("\nSolver found the word in %d attempts!\n", attempt);
            return;
        }

        //eliminates invalid candidates 
        candidateCount = FilterCandidates(candidates, candidateCount, guess, feedback);

        if (candidateCount == 0) {
            printf("Solver failed! No candidates left.\n");
            return;
        }
        //choose the best candidates using the frequency scoring
        ChooseBestGuess(candidates, candidateCount, guess);
    }

    printf("Solver could not find the word.\n");
}
