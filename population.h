#ifndef PROJETCIR1_GROUPE_5_POPULATION_H
#define PROJETCIR1_GROUPE_5_POPULATION_H

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include "region.h"
#include "date_and_birth.h"

struct Population{
    struct Person* head;        // Permet l'accès à la première personne stockée dans la base de données
    struct Person* unknown;     // Permet l'accès à la personne inconnue
    struct Person* youngest;    // Permet un accès rapide à la dernière personne née
    struct Person* oldest;      // Permet un accès rapide à la première personne née
    unsigned int males;         // Compteur du nombre d'hommes dans la population
    unsigned int females;       // Compteur du nombre de femmes dans la population
    unsigned int unknownsex;    // Compteur du nombre de personnes dont le sexe est inconnu
    unsigned int size;          // Taille totale de la population
    struct Regions* r;          // Pointeur vers la structure contenant les régions
    struct Date_and_Births* calendar; // Pointeur vers la structure contenant les dates de naissance
};

struct Person{
    unsigned int id;            // Stocke l'id de la personne
    unsigned int date[3];       // Date de naissance, format [jour, mois, année]
    unsigned int father_id;     // Stocke l'ID du père
    unsigned int mother_id;     // Stocke l'ID de la mère
    struct Person* father;      // Pointeur vers le père de la personne
    struct Person* mother;      // Pointeur vers la mère de la personne
    struct Person* next;        // Permet l'accès à la personne suivante dans la base de données
    char* name;                 // Stocke le prénom de la personne
    char* last_name;            // Stocke le nom de famille de la personne
    char* region;               // Stocke le nom de la région où la personne est née
    char sex;                   // Stocke le sexe de la personne ('m' pour masculin, 'f' pour féminin, 'u' pour inconnu)
};



struct Population* createEmptyPopulation();
struct Person* createPerson(unsigned int id,unsigned int father_id, unsigned int mother_id, char* name, char* last_name, unsigned int date[3], char* region);

unsigned int getId(struct Person* p);
char* getDate(struct Person* p);
unsigned int getFather_id(struct Person* p);
unsigned int getMother_id(struct Person* p);
struct Person* getFather(struct Person* p);
struct Person* getMother(struct Person* p);
char* getName(struct Person* p);
//int numberOfMales(struct population* pop);
//int numberOfFemales(struct population* pop);
char* getLast_name(struct Person* p);
char* getRegion(struct Person* p);
struct Person* getYoungest(struct Population* pop);
struct Person* getOldest(struct Population* pop);
struct Regions* getGlobalRegion(struct Population* pop);
struct Date_and_Births* getCalendar(struct Population* pop);
struct Regions* getGlobalRegion(struct Population* pop);
struct Person* getHead(struct Population* pop);
struct Person* getNext(struct Person* p);
unsigned int getPopulationSize(struct Population* pop);
unsigned int getMales(struct Population* pop);
unsigned int getFemales(struct Population* pop);
unsigned int getUnknownSex(struct Population* pop);
bool getSex(struct Person* p);
bool isPopulationEmpty(struct Population* pop);
struct Person* mostBrotherAndSister(struct Population* pop);
struct Person* searchPerson(struct Population* pop, char* name, char* lastName);
void addParents(struct Population* pop);

void addUnknown(struct Population* pop, struct Person* p);
void addPerson(struct Population* pop, unsigned int id,unsigned int father_id, unsigned int mother_id, char* name, char* last_name, unsigned int date[3], char* region);

void deletePerson(struct Population* pop);
void deletePopulation(struct Population* pop);

void printPopulation(struct Population* pop);
void printPopulationInfo(struct Population* pop);
void printPerson(struct Person* p);




#endif

