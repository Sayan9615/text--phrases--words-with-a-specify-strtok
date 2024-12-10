#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>
char* get_txt() 
{
    char* text = NULL;
    int cnt = 0;
    char ch;
    while ((ch = getchar()) != '\n') 
    {
        char* aux = (char*)realloc(text, (cnt + 1) * sizeof(char) + 1);
        if (aux == NULL) {
            printf("Memory allocation failed!\n");
            free(text);
            exit(-1);
        }
        text = aux;
        text[cnt++] = ch;
    }
    if (text) 
    {
        text[cnt] = '\0'; 
    }
    return text;
}

char** split(char* string, const char* delim, int* n) 
{
    *n = 0;
    char** words = NULL;
    char* p = strtok(string, delim);

    while (p) {
        char** aux = (char**)realloc(words, (*n + 1) * sizeof(char*));
        if (aux == NULL) {
            printf("Memory allocation failed!\n");
            for (int i = 0; i < *n; i++) {
                free(words[i]);
            }
            free(words);
            exit(-1);
        }
        words = aux;

        words[*n] = (char*)malloc(strlen(p) + 1);
        if (words[*n] == NULL) {
            printf("Memory allocation failed!\n");
            for (int i = 0; i < *n; i++) {
                free(words[i]);
            }
            free(words);
            exit(-1);
        }

        strcpy(words[(*n)++], p);
        p = strtok(NULL, delim);
    }
    return words;
}

int main(void) {
    char* text = get_txt();
    char** phrases = NULL;
    int n = 0;
    char delim_ph[] = ".!";
    phrases = split(text, delim_ph, &n);
    for (int i = 0; i < n; i++) 
    {
        printf("Phrase [%d]: %s\n", i, phrases[i]);
    }
    printf("\n");
    char*** words = (char***)malloc(n * sizeof(char**));
    char delim_words[] = " ";
    int* number_words = (int*)malloc(n * sizeof(int));

    for (int i = 0; i < n; i++) 
    {
        words[i] = split(phrases[i], delim_words, &number_words[i]);
    }

 
    for (int i = 0; i < n; i++) {
        printf("Words from phrase [%d]:\n", i);
        for (int j = 0; j < number_words[i]; j++) {
            printf("  %s\n", words[i][j]);
        }
        printf("\n");
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < number_words[i]; j++) {
            free(words[i][j]);
        }
        free(words[i]);
        free(phrases[i]);
    }
    free(words);
    free(phrases);
    free(number_words);
    free(text);

    return 0;
}
