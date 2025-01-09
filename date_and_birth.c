#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include "date_and_birth.h"

/**
 * Fonction pour créer un nouveau calendrier de dates et naissances.
 * Alloue de la mémoire pour la structure et initialise les valeurs à 0.
 *
 * @return Un pointeur vers la structure Date_and_Births nouvellement allouée.
 */
struct Date_and_Births* createCalendar(){
    struct Date_and_Births* calendar = malloc(sizeof(struct Date_and_Births));
    if(calendar != NULL){
        // Initialisation de toutes les dates à 0
        for(int i = 0; i < 12; i++){
            for(int j = 0; j < 31; j++){
                calendar->date[i][j] = 0;
            }
        }
    }
    return calendar;
}

/**
 * Fonction pour supprimer un calendrier existant.
 * Libère la mémoire allouée pour la structure et la met à NULL.
 *
 * @param calendar Un pointeur vers la structure Date_and_Births à supprimer.
 */
void deleteCalendar(struct Date_and_Births* calendar){
    if(calendar != NULL) {
        free(calendar->date);
        calendar = NULL;
    }
}

/**
 * Fonction pour ajouter une naissance à une date spécifique dans le calendrier.
 * Incrémente le compteur de naissances pour le jour et le mois donnés.
 *
 * @param calendar Un pointeur vers la structure Date_and_Births.
 * @param month Le mois de la naissance (1-12).
 * @param day Le jour de la naissance (1-31).
 */
void addBirthCalendar(struct Date_and_Births* calendar, unsigned int month, unsigned int day){
    calendar->date[month-1][day-1]++;
}

/**
 * Fonction pour obtenir le nombre de naissances à une date spécifique.
 * Convertit la date fournie en jour et mois et retourne le nombre de naissances.
 *
 * @param calendar Un pointeur vers la structure Date_and_Births.
 * @param querydate Une chaîne de caractères représentant la date au format "jj/mm".
 * @return Le nombre de naissances à la date spécifiée ou -1 en cas d'erreur.
 */
unsigned int getDateBirths(struct Date_and_Births* calendar, char querydate[]){
    if(calendar != NULL) {
        char *tempsdate = malloc(sizeof(char) * strlen(querydate) + 1);
        strcpy(tempsdate, querydate);
        char *token;
        unsigned int day;
        unsigned int month;

        // Extraction du jour
        token = strtok(tempsdate, "/");
        day = atoi(token);

        // Extraction du mois
        token = strtok(NULL, "\0");
        month = atoi(token);

        // Vérification de la validité du mois
        if (month < 1 || month > 12) {
            printf("Invalid month provided.\n");
            return -1;
        }

        // Vérification de la validité du jour
        if (day < 1 || day > daysInMonth(month)) {
            printf("Invalid day provided for month %d.\n", month);
            return -1;
        }

        free(tempsdate);
        return calendar->date[month - 1][day - 1];
    }
    return -1;
}

/**
 * Fonction pour afficher le calendrier complet.
 * Affiche le nombre de naissances pour chaque jour de chaque mois.
 *
 * @param calendar Un pointeur vers la structure Date_and_Births à afficher.
 */
void printCalendar(struct Date_and_Births* calendar){
    if(calendar != NULL){
        for(int i = 0; i < 12; i++){
            for(int j = 0; j < 31; j++){
                printf("%d\t", calendar->date[i][j]);
            }
            printf("\n");
        }
    }
}

/**
 * Fonction pour obtenir le nombre de jours dans un mois donné.
 * Gère les mois de 1 à 12 avec une considération pour février.
 *
 * @param month Le mois pour lequel obtenir le nombre de jours.
 * @return Le nombre de jours dans le mois spécifié.
 */
unsigned int daysInMonth(unsigned int month) {
    switch (month) {
        case 1:
        case 3:
        case 5:
        case 7:
        case 8:
        case 10:
        case 12:
            return 31;
        case 4:
        case 6:
        case 9:
        case 11:
            return 30;
        case 2:
            return 29;
        default:
            return 0;
    }
}