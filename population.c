#include "population.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>

/**
 * Crée et initialise une nouvelle population vide.
 *
 * @return Un pointeur vers la structure Population nouvellement allouée.
 */
struct Population* createEmptyPopulation(){
    struct Population* pop = malloc(sizeof (struct Population));
    if(pop != NULL){
        pop->size = 0;
        pop->head = NULL;
        pop->unknown = NULL;
        pop->oldest = NULL;
        pop->youngest = NULL;
        pop->males = 0;
        pop->females = 0;
        pop->unknownsex = 0;
        pop->r =createEmptyRegions();
        pop->calendar = createCalendar();
    }
    return pop;
}

/**
 * Crée et initialise une nouvelle personne.
 *
 * @param id L'identifiant unique de la personne.
 * @param father_id L'identifiant du père.
 * @param mother_id L'identifiant de la mère.
 * @param name Le prénom de la personne.
 * @param last_name Le nom de famille de la personne.
 * @param date Un tableau contenant la date de naissance (jour, mois, année).
 * @param region La région de naissance de la personne.
 * @return Un pointeur vers la structure Person nouvellement allouée.
 */
struct Person* createPerson(unsigned int id,unsigned int father_id, unsigned int mother_id, char* name, char* last_name, unsigned int date[3], char* region){
    struct Person* p = malloc(sizeof (struct Person));
    if(p != NULL){
        p->id = id;
        p->father_id = father_id;
        p->father = NULL;
        p->mother_id = mother_id;
        p->mother = NULL;
        p->name = malloc(sizeof (char)* strlen(name)+1);
        if(p->name == NULL){
            return NULL;
        }
        strcpy(p->name,name);
        p->last_name = malloc(sizeof (char)* strlen(last_name)+1);
        if(p->last_name == NULL){
            return NULL;
        }
        strcpy(p->last_name,last_name);
        p->date[0] = date[0];
        p->date[1] = date[1];
        p->date[2] = date[2];
        p->region = malloc(sizeof (char)* strlen(region)+1);
        if(p->region == NULL){
            return NULL;
        }
        strcpy(p->region, region);
        p->sex = 'u';
        p->next = NULL;
    }
    return p;
}

/**
 * Récupère l'identifiant de la personne.
 *
 * @param p Un pointeur vers la structure Person.
 * @return L'identifiant de la personne.
 */
unsigned int getId(struct Person* p){
    return p->id;
}

/**
 * Récupère l'identifiant du père de la personne.
 *
 * @param p Un pointeur vers la structure Person.
 * @return L'identifiant du père de la personne.
 */
unsigned int getFather_id(struct Person* p){
    return p->father_id;
}

/**
 * Récupère l'identifiant de la mère de la personne.
 *
 * @param p Un pointeur vers la structure Person.
 * @return L'identifiant de la mère de la personne.
 */
unsigned int getMother_id(struct Person* p){
    return p->mother_id;
}

/**
 * Récupère le père de la personne.
 *
 * @param p Un pointeur vers la structure Person.
 * @return Un pointeur vers la structure Person représentant le père.
 */
struct Person* getFather(struct Person* p){
    return p->father;
}

/**
 * Récupère la mère de la personne.
 *
 * @param p Un pointeur vers la structure Person.
 * @return Un pointeur vers la structure Person représentant la mère.
 */
struct Person* getMother(struct Person* p){
    return p->mother;
}

/**
 * Récupère le prénom de la personne.
 *
 * @param p Un pointeur vers la structure Person.
 * @return Le prénom de la personne.
 */
char* getName(struct Person* p){
    return p->name;
}

/**
 * Récupère la date de naissance de la personne au format chaîne de caractères.
 *
 * @param p Un pointeur vers la structure Person.
 * @return Une chaîne de caractères représentant la date de naissance.
 */
char* getDate(struct Person* p){
    char* finalDate = malloc(sizeof(char)*11);
    if(finalDate == NULL){
        return NULL;
    }
    sprintf(finalDate, "%02d/%02d/%04d", p->date[0], p->date[1], p->date[2]);
    return finalDate;
}

/**
 * Récupère le nom de famille de la personne.
 *
 * @param p Un pointeur vers la structure Person.
 * @return Le nom de famille de la personne.
 */
char* getLast_name(struct Person* p){
    return p->last_name;
}

/**
 * Récupère la région de naissance de la personne.
 *
 * @param p Un pointeur vers la structure Person.
 * @return La région de naissance de la personne.
 */
char* getRegion(struct Person* p){
    return p->region;
}

/**
 * Récupère la plus jeune personne de la population.
 *
 * @param pop Un pointeur vers la structure Population.
 * @return Un pointeur vers la structure Person représentant la plus jeune personne.
 */
struct Person* getYoungest(struct Population* pop){
    return pop->youngest;
}

/**
 * Récupère la personne la plus âgée de la population.
 *
 * @param pop Un pointeur vers la structure Population.
 * @return Un pointeur vers la structure Person représentant la personne la plus âgée.
 */
struct Person* getOldest(struct Population* pop){
    return pop->oldest;
}

/**
 * Récupère la taille de la population.
 *
 * @param pop Un pointeur vers la structure Population.
 * @return La taille de la population.
 */
unsigned int getPopulationSize(struct Population* pop){
    return pop->size;
}

/**
 * Récupère la structure Regions de la population.
 *
 * @param pop Un pointeur vers la structure Population.
 * @return Un pointeur vers la structure Regions.
 */
struct Regions* getGlobalRegion(struct Population* pop){
    return pop->r;
}

/**
 * Récupère la tête de la liste des personnes de la population.
 *
 * @param pop Un pointeur vers la structure Population.
 * @return Un pointeur vers la structure Person représentant la tête de la liste.
 */
struct Person* getHead(struct Population* pop){
    return pop->head;
}

/**
 * Récupère la personne suivante dans la liste des personnes.
 *
 * @param p Un pointeur vers la structure Person.
 * @return Un pointeur vers la structure Person représentant la personne suivante.
 */
struct Person* getNext(struct Person* p){
    return p->next;
}

/**
 * Récupère le nombre de hommes dans la population.
 *
 * @param pop Un pointeur vers la structure Population.
 * @return Le nombre de mâles dans la population.
 */
unsigned int getMales(struct Population* pop){
    return pop->males;
}

/**
 * Récupère le nombre de femmes dans la population.
 *
 * @param pop Un pointeur vers la structure Population.
 * @return Le nombre de femelles dans la population.
 */
unsigned int getFemales(struct Population* pop){
    return pop->females;
}

/**
 * Récupère le nombre de personnes de sexe inconnu dans la population.
 *
 * @param pop Un pointeur vers la structure Population.
 * @return Le nombre de personnes de sexe inconnu dans la population.
 */
unsigned int getUnknownSex(struct Population* pop){
    return pop->unknownsex;
}

/**
 * Récupère le calendrier des dates de naissance de la population.
 *
 * @param pop Un pointeur vers la structure Population.
 * @return Un pointeur vers la structure Date_and_Births représentant le calendrier.
 */
struct Date_and_Births* getCalendar(struct Population* pop){
    return pop->calendar;
}

/**
 * Vérifie si la population est vide.
 *
 * @param pop Un pointeur vers la structure Population.
 * @return true si la population est vide, sinon false.
 */
bool isPopulaionEmpty(struct Population* pop){
    return pop->size == 0;
}

/**
 * Récupère le sexe de la personne.
 *
 * @param p Un pointeur vers la structure Person.
 * @return Le sexe de la personne.
 */
bool getSex(struct Person* p){
    return p->sex;
}

/**
 * Trouve la personne ayant le plus de frères et sœurs dans une population donnée.
 * Si la population est vide, retourne NULL.
 * @param pop Pointeur vers la structure Population.
 * @return Pointeur vers la personne ayant le plus de frères et sœurs, ou NULL si la population est vide.
 */
struct Person* mostBrotherAndSister(struct Population* pop) {
    if(pop == NULL){
        return NULL;
    }

    struct Person* current = getHead(pop);
    struct Person* max = NULL;
    int most = 0;
    int counter = 0;
    while(current != NULL){

        struct Person* iter = getHead(pop);

        // Si la personne n'a ni père ni mère, passer à la suivante
        if(getFather(current) == 0 && getMother(current) == 0){
            current = getNext(current);
            continue;
        }

        // Compter le nombre de frères et sœurs de la personne actuelle
        while(iter != NULL){
            if(current != iter && getFather_id(iter) != 0 && getMother_id(iter) != 0
               && getFather_id(current) == getFather_id(iter)
               && getMother_id(current) == getMother_id(iter)){
                counter++;
            }
            iter = getNext(iter);
        }

        // Mettre à jour la personne avec le plus de frères et sœurs si nécessaire
        if(counter > most){
            most = counter;
            max = current;
        }

        current = getNext(current);

    }
    return max;
}

/**
 * Recherche une personne dans une population par son nom et prénom.
 * Si la population est vide, affiche un message et retourne NULL.
 * @param pop Pointeur vers la structure Population.
 * @param name Prénom de la personne recherchée.
 * @param lastName Nom de famille de la personne recherchée.
 * @return Pointeur vers la personne trouvée, ou NULL si elle n'est pas trouvée.
 */
struct Person* searchPerson(struct Population* pop, char* name, char* lastName) {
    if(pop == NULL){
        printf("\nThe population is empty !\n");
        return NULL;
    }
    struct Person* iter = getHead(pop);
    while(iter != NULL){
        // Comparaison insensible à la casse du prénom et du nom de famille
        if(strcasecmp(getName(iter), name) == 0 && strcasecmp(getLast_name(iter), lastName) == 0){
            return iter;
        }
        iter = getNext(iter);
    }
    return NULL;
}


/**
 * Ajoute une nouvelle personne à la population.
 *
 * @param pop Un pointeur vers la structure Population.
 * @param id L'identifiant unique de la personne.
 * @param father_id L'identifiant du père.
 * @param mother_id L'identifiant de la mère.
 * @param name Le prénom de la personne.
 * @param last_name Le nom de famille de la personne.
 * @param date Un tableau contenant la date de naissance (jour, mois, année).
 * @param region La région de naissance de la personne.
 */
void addPerson(struct Population* pop, unsigned int id,unsigned int father_id, unsigned int mother_id, char* name, char* last_name, unsigned int date[3], char* region) {
    struct Person *newhead = createPerson(id, father_id, mother_id, name, last_name, date, region);
    if (newhead != NULL) {
        newhead->next = pop->head;
        pop

                ->head = newhead;
        pop->size++;
        pop->unknownsex++;
        if(pop->youngest!=NULL && pop->oldest!=NULL) {

            if (newhead->date[2] < pop->oldest->date[2] ) {
                pop->oldest = newhead;
            }
            if(newhead->date[2] == pop->oldest->date[2]){
                if(newhead->date[1] < pop->oldest->date[1]) {
                    pop->oldest = newhead;
                }
                if(newhead->date[1] == pop->oldest->date[1]) {
                    if( newhead->date[0] < pop->oldest->date[0]){
                        pop->oldest = newhead;
                    }
                }

            }
            if (newhead->date[2] > pop->youngest->date[2] ) {
                pop->youngest = newhead;
            }
            if(newhead->date[2] == pop->youngest->date[2]){
                if(newhead->date[1] > pop->youngest->date[1]) {
                    pop->youngest = newhead;
                }
                if(newhead->date[1] == pop->youngest->date[1]) {
                    if( newhead->date[0] > pop->youngest->date[0]){
                        pop->youngest = newhead;
                    }
                }

            }

        } else{
            pop->oldest = newhead;
            pop->youngest = newhead;
        }
        addRegion(pop->r,region);
        addBirthCalendar(pop->calendar, date[1], date[0]);
    }
}

/**
 * Ajoute les parents pour chaque personne dans la population.
 *
 * @param pop Un pointeur vers la structure Population.
 */
void addParents(struct Population* pop){
    if(pop==NULL || pop->head == NULL){
        return;
    }
    struct Person* iterchild = pop->head;
    struct Person* iterfather = pop->head;
    struct Person* itermother = pop->head;
    for(int i = 0; i<=pop->size-1;i++){
        if(iterchild->father_id != 0){
            for(int j = 0; j<pop->size;j++){
                if(iterfather->id == iterchild->father_id){
                    iterchild->father = iterfather;
                    if(iterfather->sex == 'u') {
                        iterfather->sex = 'm';
                        pop->males++;
                        pop->unknownsex--;
                    }
                }
                iterfather = iterfather->next;
            }
        } else{
            if(iterchild->father_id==0) {
                iterchild->father = pop->unknown;
            }
        }
        if(iterchild->mother_id != 0){
            for(int k = 0; k<pop->size;k++){
                if(itermother->id == iterchild->mother_id){
                    iterchild->mother = itermother;
                    if(itermother->sex == 'u') {
                        itermother->sex = 'f';
                        pop->females++;
                        pop->unknownsex--;
                    }
                }
                itermother = itermother->next;
            }
        } else{
            if(iterchild->mother_id==0) {
                iterchild->mother = pop->unknown;
            }
        }
        iterchild = iterchild->next;
        itermother = pop->head;
        iterfather = pop->head;
    }
}

/**
 * Ajoute la personne inconnue à la population.
 *
 * @param pop Un pointeur vers la structure Population.
 * @param p Un pointeur vers la structure Person représentant la personne inconnue.
 */
void addUnknown(struct Population* pop, struct Person* p){
    if(pop==NULL || p==NULL){
        return;
    }
    pop->unknown = p;
    p->mother = pop->unknown;
    p->father = pop->unknown;
}

/**
 * Supprime la première personne de la population.
 *
 * @param pop Un pointeur vers la structure Population.
 */
void deletePerson(struct Population* pop) {
    if(pop==NULL || pop->head == NULL){
        return;
    }
    struct Person* iter = pop->head;
    pop->head = pop->head->next;
    free(iter->name);
    free(iter->region);
    free(iter->last_name);
    free(iter);
}

/**
 * Supprime toute la population et libère la mémoire allouée.
 *
 * @param pop Un pointeur vers la structure Population.
 */
void deletePopulation(struct Population* pop){
    if (pop == NULL) {
        return;
    }
    while (pop->head != NULL) {
        deletePerson(pop);
    }
    if (pop->unknown != NULL) {
        free(pop->unknown->name);
        free(pop->unknown->last_name);
        free(pop->unknown->region);
        free(pop->unknown);
    }
    deleteRegions(pop->r);
    deleteCalendar(pop->calendar);
    free(pop);
    pop=NULL;
}

/**
 * Affiche les informations de la population.
 *
 * @param pop Un pointeur vers la structure Population.
 */
void printPopulationInfo(struct Population* pop){
    if (pop == NULL) {
        return;
    }
    printf("Size=%d\n",pop->size);
    printf("Oldest=%s\n", pop->oldest->name);
    printf("Youngest=%s\n",pop->youngest->name);
    printf("F=%d\n",pop->females);
    printf("M=%d\n",pop->males);
    printf("U=%d\n",pop->unknownsex);
}

/**
 * Affiche les informations détaillées d'une personne.
 *
 * @param p Un pointeur vers la structure Person.
 */
void printPerson(struct Person* p) {
    if (p != NULL) {
        if (p->sex == 'm') {
            printf("\tSex: Male\n");
        }
        if (p->sex == 'f') {
            printf("\tSex: Female\n");
        }
        if (p->sex == 'u') {
            printf("\tSex: Unknown\n");
        }
        printf("\tName: %s\n", p->name);
        printf("\tLast name: %s\n", p->last_name);
        printf("\tBorn the : %d/%d/%d\n", p->date[0], p->date[1], p->date[2]);
        printf("\tFrom :\n");
        printf("\t\tFather: %s\n", (p->father_id != 0) ? p->father->name :"unknwon");
        printf("\t\tMother: %s\n", (p->mother_id != 0) ? p->mother->name :"unknwon");
        printf("\tAt: %s\n", p->region);
    }
}