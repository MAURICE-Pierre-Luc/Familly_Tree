#ifndef PROJETCIR1_GROUPE_5_REGION_H
#define PROJETCIR1_GROUPE_5_REGION_H
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#define TABLE_SIZE 53  // Taille de la table pour stocker les régions par lettre de l'alphabet (majuscules, minuscules et ' ')
#define WORD_MAX_SIZE 40  // Taille maximale d'un nom de région

// Structure représentant l'ensemble des régions
struct Regions {
    unsigned int most_births;  // Nombre de naissances dans la région avec le plus de naissances
    struct Region* alphabet[TABLE_SIZE];  // Tableau de pointeurs vers les régions, indexé par lettre
    char* region_most_births;  // Nom de la région avec le plus de naissances
};

// Structure représentant une région
struct Region {
    struct Region* alphabet[TABLE_SIZE];  // Tableau de pointeurs vers les sous-régions, indexé par lettre
    bool word;  // Indique si une région est un mot complet
    unsigned int births;  // Nombre de naissances dans la région
};

struct Regions* createEmptyRegions();
struct Region* createEmptyRegion();

bool isEmptyRegions(struct Regions* R);
bool isWord(struct Region* r);
char* getMostBirthsRegion(struct Regions* R);
struct Region* getChild(struct Region* r, unsigned int who);
struct Region* getFirstRegion(struct Regions* R,unsigned int who);
void addBirth(struct Region* r);
unsigned int getBirths(struct Region* r);
unsigned int getMostBirths(struct Regions* R);
void updateMostBirths(struct Regions* R, struct Region* r);
void updateRegionMostBirths(struct Regions* R, char* region);
void updateFirstRegion(struct Regions* R,unsigned int who);
void updateWord(struct Region* r, bool val);
struct Region* addLetter(struct Region* r, unsigned int who);
unsigned int getIndex(char letter);

bool findRegion(struct Regions* R, char* region);

void addRegion(struct Regions* R, char* region);

unsigned int regionBirths(struct Regions* R, char* region);

void addBirthRegion(struct Regions* R, char* region);

void displayRegionsRec(struct Region* r, char* acc, bool upperCase, unsigned int* count);
void displayRegions(struct Regions* R);

void deleteRegions(struct Regions* R);
void deleteRegion(struct Region* R);
char to_lower(char c);
char to_upper(char c);




#endif
