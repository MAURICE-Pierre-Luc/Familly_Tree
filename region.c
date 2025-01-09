#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include "region.h"

/**
 * Crée et initialise une structure Regions vide.
 *
 * @return Pointeur vers la structure Regions nouvellement créée.
 */
struct Regions* createEmptyRegions(){
    struct Regions* R = malloc(sizeof(struct Regions));
    if(R != NULL) {
        R->most_births = 0;
        R->region_most_births = NULL;
        for(int i=0; i < TABLE_SIZE; i++) {
            R->alphabet[i] = NULL;
        }
    }
    return R;
}

/**
 * Crée et initialise une structure Region vide.
 *
 * @return Pointeur vers la structure Region nouvellement créée.
 */
struct Region* createEmptyRegion(){
    struct Region* r = malloc(sizeof(struct Region));
    if(r != NULL) {
        r->word = 0;
        r->births = 0;
        for(int i=0; i < TABLE_SIZE; i++) {
            r->alphabet[i] = NULL;
        }
    }
    return r;
}

/**
 * Vérifie si une structure Regions est vide.
 *
 * @param R Pointeur vers la structure Regions à vérifier.
 * @return true si la structure Regions est vide, false sinon.
 */
bool isEmptyRegions(struct Regions* R) {
    return R == NULL;
}

/**
 * Vérifie si une structure Region est la fin d'un mot.
 *
 * @param r Pointeur vers la structure Region à vérifier.
 * @return true si la structure Region représente un mot, false sinon.
 */
bool isWord(struct Region* r){
    return r->word;
}

/**
 * Récupère le nom de la région avec le plus de naissances.
 *
 * @param R Pointeur vers la structure Regions.
 * @return Pointeur vers le nom de la région avec le plus de naissances.
 */
char* getMostBirthsRegion(struct Regions* R){
    return R->region_most_births;
}

/**
 * Récupère la structure Région suivante donné un indice, depuis une structure Région.
 *
 * @param r Pointeur vers la structure Region parente.
 * @param who Indice de l'enfant à récupérer.
 * @return Pointeur vers la structure Region enfant.
 */
struct Region* getChild(struct Region* r, unsigned int who){
    return r->alphabet[who];
}

/**
 * Récupère la première Région d'une structure Regions donné un indice.
 *
 * @param R Pointeur vers la structure Regions.
 * @param who Indice de la première région à récupérer.
 * @return Pointeur vers la structure Region correspondante.
 */
struct Region* getFirstRegion(struct Regions* R, unsigned int who){
    return R->alphabet[who];
}

/**
 * Ajoute une naissance à une structure Région.
 *
 * @param r Pointeur vers la structure Region où ajouter une naissance.
 */
void addBirth(struct Region* r){
    r->births++;
}

/**
 * Récupère le nombre de naissances d'une structure Région.
 *
 * @param r Pointeur vers la structure Region.
 * @return Nombre de naissances.
 */
unsigned int getBirths(struct Region* r){
    return r->births;
}

/**
 * Récupère le nombre de naissances le plus élevé dans une structure Regions.
 *
 * @param R Pointeur vers la structure Regions.
 * @return Nombre de naissances le plus élevé.
 */
unsigned int getMostBirths(struct Regions* R){
    return R->most_births;
}

/**
 * Met à jour le nombre de naissances le plus élevé dans une structure Regions.
 *
 * @param R Pointeur vers la structure Regions.
 * @param r Pointeur vers la structure Region avec le nouveau nombre de naissances le plus élevé.
 */
void updateMostBirths(struct Regions* R, struct Region* r){
    R->most_births = r->births;
}

/**
 * Met à jour le nom de la région avec le plus de naissances dans une structure Regions.
 *
 * @param R Pointeur vers la structure Regions.
 * @param region Nom de la région à mettre à jour.
 */
void updateRegionMostBirths(struct Regions* R,char* region){
    R->region_most_births = malloc((strlen(region) + 1) * sizeof(char));
    if (R->region_most_births == NULL) {
        return;
    }
    strcpy(R->region_most_births, region);
}

/**
 * Met à jour la première région dans une structure Regions donné un indice.
 *
 * @param R Pointeur vers la structure Regions.
 * @param who Indice de la première région à mettre à jour.
 */
void updateFirstRegion(struct Regions* R,unsigned int who){
    R->alphabet[who] = createEmptyRegion();
}

/**
 * Met à jour le statut de mot d'une région.
 *
 * @param r Pointeur vers la structure Region à mettre à jour.
 * @param val Valeur à attribuer au statut de mot.
 */
void updateWord(struct Region* r, bool val){
    r->word = val;
}

/**
 * Ajoute une lettre à une structure Région donné un indice.
 *
 * @param r Pointeur vers la structure Region.
 * @param who Indice de la lettre à ajouter.
 * @return Pointeur vers la structure Region mise à jour.
 */
struct Region* addLetter(struct Region* r, unsigned int who){
    return r->alphabet[who]= createEmptyRegion();
}

/**
 * Récupère l'indice d'une lettre.
 *
 * @param letter Lettre dont l'indice est à récupérer.
 * @return Indice de la lettre.
 */
unsigned int getIndex(char letter){
    unsigned int index;
    if(letter ==' '){
        index = TABLE_SIZE-1;
    } else {
        if (letter >= 'A' && letter <= 'Z'){
            index = letter - 'A';
        } else{
            if (letter >= 'a' && letter <= 'z'){
                index = letter - 'a';
            } else{
                return -1;
            }
        }
    }
    return index;
}

/**
 * Trouve une région dans une structure Regions.
 *
 * @param R Pointeur vers la structure Regions.
 * @param region Nom de la région à trouver.
 * @return true si la région est trouvée, false sinon.
 */
bool findRegion(struct Regions* R, char* region) {
    if(isEmptyRegions(R) || region == NULL){
        return false;
    }
    unsigned int index = getIndex(region[0]);
    if(index == -1){
        return false;
    }
    struct Region* iter = getFirstRegion(R, index);
    if(iter == NULL) {
        return false;
    }
    unsigned int n = strlen(region);
    for(int i = 1; i < n; i++){
        index = getIndex(region[i]);
        if(index == -1){
            return false;
        }
        iter = getChild(iter, index);
        if(iter == NULL) {
            return false;
        }
    }
    return isWord(iter);
}

/**
 * Ajoute une région à une structure Regions.
 *
 * @param R Pointeur vers la structure Regions.
 * @param region Nom de la région à ajouter.
 */
void addRegion(struct Regions* R, char* region){
    if(R == NULL || region == NULL){
        return;
    }
    if(findRegion(R, region)){
        addBirthRegion(R, region);
        return;
    }
    unsigned int n = strlen(region);
    struct Region* iter;

    unsigned int index = getIndex(region[0]);
    if (getFirstRegion(R, index) == NULL) {
        updateFirstRegion(R, index);
    }
    iter = getFirstRegion(R, index);
    if(iter == NULL){
        return;
    }
    struct Region* child;
    for(int i = 1; i < n; i++){
        index = getIndex(region[i]);
        child = getChild(iter,index);
        if(child == NULL){
            addLetter(iter, index);
        }
        iter = getChild(iter, index);

    }
    addBirth(iter);
    if(getBirths(iter) > getMostBirths(R)){
        free(getMostBirthsRegion(R));
        updateMostBirths(R, iter);
        updateRegionMostBirths(R, region);
    }
    updateWord(iter, true);
}

/**
 * Ajoute une naissance à une région dans une structure Regions.
 *
 * @param R Pointeur vers la structure Regions.
 * @param region Nom de la région où ajouter une naissance.
 */
void addBirthRegion(struct Regions* R, char* region) {
    if (isEmptyRegions(R) || region == NULL) {
        return;
    }

    unsigned int index = getIndex(region[0]);;
    unsigned int n = strlen(region);
    struct Region* iter = getFirstRegion(R,index);
    for (int i = 1; i < n; i++) {
        index = getIndex(region[i]);
        if (getChild(iter,index)!= NULL) {
            iter = getChild(iter, index);
        } else {
            return;
        }
    }
    if (isWord(iter)) {
        addBirth(iter);
        if (getBirths(iter) > getMostBirths(R)) {
            if (getMostBirthsRegion(R)!= NULL) {
                free(getMostBirthsRegion(R));
            }
            updateMostBirths(R,iter);
            updateRegionMostBirths(R, region);
        }
    }
}

/**
 * Récupère le nombre de naissances pour une région donnée.
 *
 * @param R Pointeur vers la structure Regions.
 * @param region Nom de la région dont le nombre de naissances est à récupérer.
 * @return Nombre de naissances de la région.
 */
unsigned int regionBirths(struct Regions* R, char* region) {
    if (isEmptyRegions(R) || region == NULL) {
        return -1;
    }
    unsigned int index = getIndex(region[0]);
    unsigned int n = strlen(region);
    struct Region* iter = getFirstRegion(R,index);
    for (int i = 1; i < n; i++) {
        index = getIndex(region[i]);
        if (getChild(iter, index) != NULL) {
            iter = getChild(iter, index);
        } else {
            return 0;
        }
    }
    return getBirths(iter);
}

/**
 * Affiche récursivement les régions.
 *
 * @param r Pointeur vers la structure Region à afficher.
 * @param acc Accumulateur de nom de région.
 * @param upperCase Indique si la région est en majuscule.
 * @param count Compteur de régions affichées.
 */
void displayRegionsRec(struct Region* r, char* acc, bool upperCase, unsigned int* count) {
    if (isWord(r)) {
        (*count)++;
        printf("%s, ", acc);
        if ((*count) % 4 == 0 && (*count) != 0) {
            printf("\n");
        }
    }
    for (unsigned int i = 0; i < TABLE_SIZE; i++) {
        if (getChild(r, i) != NULL) {
            char letter;
            char newAcc[WORD_MAX_SIZE];
            strcpy(newAcc, acc);
            if (upperCase) {
                if (i == TABLE_SIZE - 1) {
                    letter = ' ';
                    if (strlen(acc) < WORD_MAX_SIZE - 1) {
                        newAcc[strlen(acc)] = letter;
                        newAcc[strlen(acc) + 1] = '\0';
                    }
                    displayRegionsRec(getChild(r,i), newAcc, 1, count);
                } else {
                    letter = 'A' + i;
                    letter = to_upper(letter);
                    if (strlen(acc) < WORD_MAX_SIZE - 1) {
                        newAcc[strlen(acc)] = letter;
                        newAcc[strlen(acc) + 1] = '\0';
                    }
                    displayRegionsRec(getChild(r,i), newAcc, 0, count);
                }
            } else {
                if (i == TABLE_SIZE - 1) {
                    letter = ' ';
                    if (strlen(acc) < WORD_MAX_SIZE - 1) {
                        newAcc[strlen(acc)] = letter;
                        newAcc[strlen(acc) + 1] = '\0';
                    }
                    displayRegionsRec(getChild(r,i), newAcc, 1, count);
                } else {
                    letter = 'a' + i;
                    letter = to_lower(letter);
                    if (strlen(acc) < WORD_MAX_SIZE - 1) {
                        newAcc[strlen(acc)] = letter;
                        newAcc[strlen(acc) + 1] = '\0';
                    }
                    displayRegionsRec(getChild(r,i), newAcc, 0, count);
                }
            }
        }
    }
}

/**
 * Affiche toutes les régions
 *
 * @param R Pointeur vers la structure Regions à afficher.
 */
void displayRegions(struct Regions* R) {
    char acc[WORD_MAX_SIZE];
    for (unsigned int i = 0; i < TABLE_SIZE; ++i) {
        struct Region* firstRegion = getFirstRegion(R, i);
        if (firstRegion != NULL) {
            char letter;
            unsigned int count = 0;
            if (i == TABLE_SIZE - 1) {
                letter = ' ';
            } else if (i < 26) {
                letter = 'A' + i;
            } else {
                letter = 'a' + i - 26;
            }
            acc[0] = letter;
            acc[1] = '\0';
            displayRegionsRec(firstRegion, acc, 0, &count);
        }
    }
}

/**
 * Supprime et libère la mémoire allouée pour une structure Regions.
 *
 * @param R Pointeur vers la structure Regions à supprimer.
 */
void deleteRegions(struct Regions* R){
    if (isEmptyRegions(R)) {
        return;
    }
    free(R->region_most_births);
    for (int i = 0; i < TABLE_SIZE-1; ++i) {
        if(R->alphabet[i] != NULL) {
            deleteRegion(R->alphabet[i]);
        }
    }
    free(R);
    R = NULL;
}

/**
 * Supprime et libère la mémoire allouée pour une structure Region.
 *
 * @param r Pointeur vers la structure Region à supprimer.
 */
void deleteRegion(struct Region* r){
    for (int i = 0; i < TABLE_SIZE; ++i) {
        if(r->alphabet[i] != NULL) {
            deleteRegion(r->alphabet[i]);
        }
    }
    free(r);
    r = NULL;
}

/**
 * Convertit une lettre majuscule en minuscule.
 *
 * @param c Lettre à convertir.
 * @return Lettre convertie en minuscule.
 */
char to_lower(char c) {
    if (c >= 'A' && c <= 'Z') {
        return (char)(c + ('a' - 'A'));
    } else {
        return c;
    }
}

/**
 * Convertit une lettre minuscule en majuscule.
 *
 * @param c Lettre à convertir.
 * @return Lettre convertie en majuscule.
 */
char to_upper(char c) {
    if (c >= 'a' && c <= 'z') {
        return (char)(c - ('a' - 'A'));
    } else {
        return c;
    }
}