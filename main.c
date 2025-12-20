#include "wordle.h"

#ifdef _WIN32
#include <windows.h>
void EnableANSIColors() {
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hOut == INVALID_HANDLE_VALUE) return;

    DWORD dwMode = 0;
    if (!GetConsoleMode(hOut, &dwMode)) return;

    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(hOut, dwMode);
}
#endif

int main() {

    #ifdef _WIN32
    EnableANSIColors();
#endif

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
