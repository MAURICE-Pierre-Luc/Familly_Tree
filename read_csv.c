#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "population.h"
#include "read_csv.h"

/**
 * Lit un fichier CSV contenant des données de population et les charge dans une structure Population.
 *
 *
 * @param filename Nom du fichier à lire.
 * @return Un pointeur vers une structure Population si le fichier est lu avec succès, sinon NULL.
 */
struct Population* readfile(const char* filename) {
    // Construit le chemin complet du fichier à partir du répertoire source.
    char full_filename[MAX_FILE_NAME_SIZE];
    strcpy(full_filename, "../source/");
    strcat(full_filename, filename);

    // Ouvre le fichier en mode lecture.
    FILE* file = fopen(full_filename, "r");
    if (file == NULL) {
        printf("Error opening \"%s\", file does not exist\n", filename);
        return NULL;
    }

    // Variables pour stocker les données lues.
    char line[MAX_LINE_SIZE];
    unsigned int total_population;
    unsigned int date[3] = {0};
    unsigned int id;
    unsigned int father_id;
    unsigned int mother_id;
    char* name = NULL;
    char* last_name = NULL;
    char* region = NULL;
    char* copiedline = NULL;

    // Crée une population vide.
    struct Population* pop = createEmptyPopulation();

    // Lit la première ligne pour obtenir le nombre total de personnes.
    if (fgets(line, sizeof(line), file) == NULL) {
        fclose(file);
        return NULL;
    }
    copiedline = malloc(strlen(line) + 1);
    if (copiedline == NULL) {
        fclose(file);
        return NULL;
    }
    strcpy(copiedline, line);
    total_population = getTotalPop(copiedline);
    free(copiedline);

    // Lit la deuxième ligne pour ajouter une personne inconnue à la population.
    if (fgets(line, sizeof(line), file) == NULL) {
        fclose(file);
        return NULL;
    }
    copiedline = malloc(strlen(line) + 1);
    if (copiedline == NULL) {
        fclose(file);
        return NULL;
    }
    strcpy(copiedline, line);
    unknownPerson(pop, copiedline);
    free(copiedline);

    // Lit les lignes restantes pour ajouter chaque personne à la population.
    for (int i = 0; i < total_population; i++) {
        if (fgets(line, sizeof(line), file) == NULL) {
            fclose(file);
            return NULL;
        }
        copiedline = malloc(strlen(line) + 1);
        if (copiedline == NULL) {
            fclose(file);
            return NULL;
        }
        strcpy(copiedline, line);

        // Sépare les données de la ligne en tokens.
        char *token;
        token = strtok(copiedline, ",");
        id = atoi(token);
        token = strtok(NULL, ",");
        father_id = atoi(token);
        token = strtok(NULL, ",");
        mother_id = atoi(token);
        token = strtok(NULL, ",");

        last_name = malloc(sizeof(char) * strlen(token) + 1);
        if (last_name == NULL) {
            fclose(file);
            free(copiedline);
            free(name);
            free(region);
            return NULL;
        }
        strcpy(last_name, token);
        token = strtok(NULL, ",");

        name = malloc(sizeof(char) * strlen(token) + 1);
        if (name == NULL) {
            fclose(file);
            free(copiedline);
            free(name);
            free(last_name);
            free(region);
            return NULL;
        }
        strcpy(name, token);
        token = strtok(NULL, "/");
        date[0] = atoi(token);
        token = strtok(NULL, "/");
        date[1] = atoi(token);
        token = strtok(NULL, ",");
        date[2] = atoi(token);
        token = strtok(NULL, "\n");

        region = malloc(sizeof(char) * (strlen(token) + 1));
        if (region == NULL) {
            fclose(file);
            free(copiedline);
            free(name);
            free(last_name);
            return NULL;
        }
        strcpy(region, token);

        // Supprime les caractères de retour à la ligne du champ région.
        char* cleanedRegion = removeBSR(region);
        if (cleanedRegion == NULL) {
            fclose(file);
            free(copiedline);
            free(name);
            free(last_name);
            free(cleanedRegion);
            free(region);
            return NULL;
        }

        // Ajoute la personne à la population.
        addPerson(pop, id, father_id, mother_id, name, last_name, date, cleanedRegion);

        // Libère la mémoire allouée pour cette itération.
        free(copiedline);
        free(name);
        free(last_name);
        free(region);
        free(cleanedRegion);
    }

    // Ajoute les parents à chaque personne.
    addParents(pop);

    if (fclose(file)!= 0) {
        printf("Error closing file\n");
    // Ferme le fichier.
        return NULL;
    } else {
        return pop;
    }
}

/**
 * Ajoute une personne inconnue à la population à partir d'une ligne de données CSV.
 *
 * @param pop Pointeur vers la structure Population.
 * @param copiedline Ligne de données CSV à traiter.
 */
void unknownPerson(struct Population* pop, char* copiedline) {
    unsigned int date[3] = {0};
    unsigned int id;
    unsigned int father_id;
    unsigned int mother_id;
    char* name = NULL;
    char* last_name = NULL;
    char* region = NULL;
    char *token = NULL;
    char* cdate = NULL;

    // Sépare les données de la ligne en tokens.
    token = strtok(copiedline, ",");
    id = atoi(token);
    token = strtok(NULL, ",");
    father_id = atoi(token);
    token = strtok(NULL, ",");
    mother_id = atoi(token);
    token = strtok(NULL, ",");

    last_name = malloc(sizeof(char) * strlen(token) + 1);
    if (last_name == NULL) {
        free(copiedline);
        free(name);
        free(region);
        return ;
    }
    strcpy(last_name, token);
    token = strtok(NULL, ",");

    name = malloc(sizeof(char) * strlen(token) + 1);
    if (name == NULL) {
        free(copiedline);
        free(name);
        free(last_name);
        free(region);
        return ;
    }
    strcpy(name, token);
    token = strtok(NULL, ",");
    date[0] = atoi(token);
    date[1] = date[0];
    date[2] = date[0];
    token = strtok(NULL, "\n");

    region = malloc(sizeof(char) * (strlen(token) + 1));
    if (region == NULL) {
        free(copiedline);
        free(name);
        free(last_name);
        free(region);
        return ;
    }
    strcpy(region, token);

    // Supprime les caractères de retour à la ligne du champ région.
    char* cleanedRegion = removeBSR(region);
    if (cleanedRegion == NULL) {
        free(copiedline);
        free(name);
        free(last_name);
        free(region);
        return ;
    }

    // Crée une structure Personne et l'ajoute à la population en tant que personne inconnue.
    struct Person* unknown = createPerson(id, father_id, mother_id, name, last_name,  date, cleanedRegion);
    addUnknown(pop,unknown);

    // Libère la mémoire allouée.
    free(cleanedRegion);
    free(name);
    free(last_name);
    free(region);
    free(cdate);
}

/**
 * Extrait et retourne la population totale à partir d'une ligne de données CSV.
 *
 * @param copiedline Ligne de données CSV contenant la population totale.
 * @return La population totale extraite.
 */
unsigned int getTotalPop(char* copiedline) {
    return atoi(copiedline);
}

/**
 * Supprime les caractères de retour à la ligne d'une chaîne de caractères.
 *
 * @param str Chaîne de caractères à nettoyer.
 * @return La chaîne nettoyée.
 */
char* removeBSR(char* str) {
    unsigned int n = strlen(str);
    char* output = malloc(sizeof(char) * n + 1);
    if (output == NULL) {
        return NULL;
    }
    int j = 0;
    for (int i = 0; i < n; i++) {
        if (str[i] != '\r') {
            output[j] = str[i];
            j++;
        }
    }
    output[j] = '\0';
    return output;
}
