#ifndef GROUPE5PROJETCCIR1_PERSO_CREATE_HTML_H
#define GROUPE5PROJETCCIR1_PERSO_CREATE_HTML_H


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "population.h"
#include "region.h"
#include "date_and_birth.h"

#define MAX_FILE_NAME_SIZE 1024
#define BUFFER_SIZE 1024

// Structure pour les informations de la personne

char* replace(char* html_content, const char* tag, const char* value);
void generate_html(struct Population* pop);
void info_tree(struct Population* pop);
void query(struct Population* pop,char regionname[WORD_MAX_SIZE], struct Person* queryperson,char* querydate,char* most_births,bool old, bool young,char* father_name, char* mother_name, char* father_lastname, char* mother_lastname);
void createunknown_html(struct Population* pop);

#endif
