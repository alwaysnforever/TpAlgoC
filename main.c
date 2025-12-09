#include "wordle.h"

int main() {

    srand(time(NULL));   // initialiser le générateur aléatoire

    char dictionary[MAX_WORDS][WORD_LENGTH + 1];

    // Charger les mots du dictionnaire
    int LoadedWords = ReadDictionary(dictionary);

    if (LoadedWords == 0) {
        printf("Aucun mot chargé, arrêt du programme.\n");
        return 1;
    }

    printf("Nombre de mots chargés : %d\n", LoadedWords);

    char secret[WORD_LENGTH + 1];
    ChooseRandomWord(dictionary, LoadedWords, secret);

    // ---- Partie 1 : Jeu pour l'utilisateur ----
    PlayGame(dictionary, LoadedWords, secret);

    // ---- Partie 2 : Solver automatique ----
    Solver(dictionary, LoadedWords, secret);

    return 0;
}
