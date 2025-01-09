#ifndef PROJETCIR1_GROUPE_5_DATE_AND_BIRTH_H
#define PROJETCIR1_GROUPE_5_DATE_AND_BIRTH_H
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>


struct Date_and_Births {
    unsigned int date[12][31];              // Tableau statique de mois et de jours, le contenu est le nombre de naissances par mois et par jour
};

struct Date_and_Births* createCalendar();
void deleteCalendar(struct Date_and_Births* calendar);
void addBirthCalendar(struct Date_and_Births* calendar, unsigned int month,unsigned int day);
unsigned int getDateBirths(struct Date_and_Births* calendar, char querydate[]);
void printCalendar(struct Date_and_Births* calendar);
unsigned int daysInMonth(unsigned int month);
#endif
