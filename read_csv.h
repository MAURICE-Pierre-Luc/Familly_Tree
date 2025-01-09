#ifndef PROJETCIR1_GROUPE_5_READ_CSV_H
#define PROJETCIR1_GROUPE_5_READ_CSV_H
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include "population.h"

#define MAX_FILE_NAME_SIZE 1024
#define MAX_LINE_SIZE 1024

struct Population* readfile(const char* filename);
void unknownPerson(struct Population* pop,char* copiedline);
unsigned int getTotalPop(char* copiedline);
char* removeBSR(char* string);

#endif
