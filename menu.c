#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "menu.h"
#include "region.h"
#include "read_csv.h"
#include "population.h"
#include "create_html.h"



/**
 * Fonction principale du menu de l'application.
 * Permet à l'utilisateur de lire un fichier CSV et d'en exporter les données utiles ou de quitter le programme.
 */
void menu() {
    bool valid1 = true;  // Indicateur de boucle pour le menu principal
    bool valid3 = true;  // Indicateur de boucle pour le sous-menu de requêtes
    bool valid4 = true;  // Indicateur de boucle pour la saisie de la région
    bool young = false;
    bool old = false;
    char* father_name = NULL;
    char* mother_name =  NULL;
    char* father_lastname = NULL;
    char* mother_lastname = NULL;
    unsigned int region_births = 0;
    char regionname[WORD_MAX_SIZE] = "";
    unsigned int date_births = 0;
    char* most_births=NULL;
    char querydate[DATE_SIZE] = "";
    struct Person* found = NULL;
    struct Person* mostbrosandsis = NULL;

    while (valid1) {
        printf("What do you want to do\n");
        printf("------------------------\n");
        printf("1. Read CSV file\n");
        printf("2. Exit\n");
        printf("------------------------\n");
        printf("Your choice: ");
        int exitOrRead = 0;
        scanf("%d", &exitOrRead);

        switch (exitOrRead) {
            case 1:
                printf("\nRead CSV file\n");
                printf("------------------------\n");
                printf("Enter CSV file name: ");
                char filename[FILENAME_SIZE];
                scanf("%s", filename);

                // Lecture du fichier CSV
                struct Population* pop = readfile(filename);
                if (pop == NULL) {
                    break;  // Sortir si la lecture du fichier échoue
                }

                printf("\nFile \"%s\" read successfully!\n\n", filename);
                bool valid2 = true;  // Indicateur de boucle pour le sous-menu après lecture du fichier

                while (valid2) {
                    printf("What do you want to do\n");
                    printf("------------------------\n");
                    printf("1. Show family tree info\n");
                    printf("2. Export HTML family tree files\n");
                    printf("3. Export HTML info file\n");
                    printf("4. Export all files\n");
                    printf("5. Query family tree\n");
                    printf("6. Go back to principal menu\n");
                    printf("------------------------\n");
                    printf("Your choice: ");
                    int choice = 0;
                    scanf("%d", &choice);

                    switch (choice) {
                        case 1:
                            printf("Information about the tree\n");
                            printPopulationInfo(pop);  // Afficher les informations de l'arbre généalogique
                            break;
                        case 2:
                            generate_html(pop);  // Générer un fichier HTML pour chaque arbre
                            createunknown_html(pop);
                            printf("Exporting individual trees was successful\n");
                            break;
                        case 3:
                            info_tree(pop); //Générer un fichier HTML avec les informations de l'arbre généalogique
                            createunknown_html(pop);
                            printf("Informations about the tree were successfully exported\n");
                            break;
                        case 4:// Générer tous les fichiers HTML
                            generate_html(pop);
                            info_tree(pop);
                            createunknown_html(pop);
                            printf("All exports were successful\n");
                            break;
                        case 5:
                            valid3 = true;
                            while (valid3) {
                                printf("What do you want to do\n");
                                printf("------------------------\n");
                                printf("1. Get first born in the database\n");
                                printf("2. Get last born in the database\n");
                                printf("3. Get number of people born in a region\n");
                                printf("4. Get the region with the highest number of births\n");
                                printf("5. Get the number of people born on a given day and month\n");
                                printf("6. Get the name of the parents withs the most children\n");
                                printf("7. Get the informations of a given person\n");
                                printf("8. Export all query results to HTML file\n");
                                printf("9. Go back to previous menu\n");
                                printf("------------------------\n");
                                printf("Your choice: ");
                                int subchoice = 0;
                                scanf("%d", &subchoice);

                                switch (subchoice) {
                                    case 1:
                                        printf("The first person born in the database is :\n");
                                        struct Person* oldest = getOldest(pop);  // Obtenir la personne la plus âgée
                                        old = true;
                                        if(oldest !=  NULL) {
                                            printPerson(oldest);  // Afficher les détails de la personne la plus âgée
                                        }
                                        printf("\n\n\n");
                                        break;
                                    case 2:
                                        printf("The last person born in the database is :\n");
                                        struct Person* youngest = getYoungest(pop);  // Obtenir la personne la plus jeune
                                        young = true;
                                        if(youngest !=  NULL) {
                                            printPerson(youngest);  // Afficher les détails de la personne la plus jeune
                                        }
                                        printf("\n\n\n");
                                        break;
                                    case 3:
                                        valid4 = true;
                                        while (valid4) {
                                            printf("The available regions are :\n");
                                            printf("------------------------\n");
                                            displayRegions(getGlobalRegion(pop));  // Afficher toutes les régions disponibles
                                            printf("\n------------------------\n");
                                            printf("Please enter the region of your choice from the list above \n");
                                            printf("------------------------\n");
                                            printf("Your choice:");
                                            clearInputBuffer();// Vider le buffer
                                            fgets(regionname, WORD_MAX_SIZE, stdin);
                                            regionname[strcspn(regionname, "\n")] = 0;
                                            if (findRegion(getGlobalRegion(pop), regionname)) {
                                                region_births = regionBirths(getGlobalRegion(pop), regionname);  // Obtenir le nombre de naissances pour la région
                                                printf("The amount of birth in \"%s\" is %d\n", regionname,region_births);
                                                valid4 = false;
                                            } else {
                                                printf("Invalid region name\n");
                                                printf("\n\n");
                                                valid4 = false;
                                            }
                                        }
                                        break;
                                    case 4:
                                        most_births = getMostBirthsRegion(getGlobalRegion(pop));  // Obtenir la région avec le plus de naissances
                                        printf("The region with the highest number of births is: %s\n",most_births);
                                        break;
                                    case 5:
                                        printf("Enter the day and month repecting the format: dd/mm (can be d/m)\n");
                                        printf("------------------------\n");
                                        printf("Your choice:");
                                        scanf("%s", querydate);
                                        date_births = getDateBirths(getCalendar(pop), querydate);  // Obtenir le nombre de naissances à une date donnée
                                        printf("The number of people born on the %s is : %d\n", querydate, date_births);
                                        break;
                                    case 6:
                                        printf("");
                                        mostbrosandsis = mostBrotherAndSister(pop);
                                        father_name = getName(getFather(mostbrosandsis));
                                        mother_name = getName(getMother(mostbrosandsis));
                                        father_lastname = getLast_name(getFather(mostbrosandsis));
                                        mother_lastname = getLast_name(getMother(mostbrosandsis));
                                        printf("The parents who have the most children are : %s %s and %s %s\n", father_name,father_lastname, mother_name, mother_lastname);
                                        break; // Obtenir le nom et le prénom des parents ayant le plus d'enfants
                                    case 7:
                                        printf("");
                                        char name[WORD_MAX_SIZE];
                                        char lastName[WORD_MAX_SIZE];
                                        printf("Please enter the last name of the person :");
                                        scanf("%s",lastName);
                                        printf("Please enter the name of the person :");
                                        scanf("%s",name);
                                        found = searchPerson(pop,name,lastName); // Obtenir les informations d'une personne dont on donne le nom
                                        if(found == NULL){
                                            printf("The person doesn't exist or, name or last name is wrong\n");
                                        }
                                        printPerson(found);
                                        break;
                                    case 8:
                                        query(pop,regionname, found,querydate,most_births, old,young, father_name, mother_name, father_lastname, mother_lastname);  // Exporter toutes les requêtes en HTML
                                        createunknown_html(pop);
                                        printf("Successfully exported all queries\n");
                                        break;
                                    case 9:
                                        valid3 = false;  // Revenir au menu précédent
                                        break;
                                    default:
                                        printf("Invalid choice, please try again\n");
                                        clearInputBuffer();  // Vider le buffer d'entrée en cas de choix invalide
                                }
                            }
                            break;
                        case 6:
                            valid2 = false;  // Revenir au menu principal
                            break;
                        default:
                            printf("Invalid choice, please try again\n");
                            clearInputBuffer();  // Vider le buffer d'entrée en cas de choix invalide
                    }
                }
                deletePopulation(pop);  // Supprimer la population lue après utilisation
                break;
            case 2:
                valid1 = false;  // Quitter l'application
                break;
            default:
                printf("Invalid choice, please try again\n");
                clearInputBuffer();  // Vider le buffer d'entrée en cas de choix invalide
                break;
        }
    }
    printf("\nExited successfully...\n");
}

/**
 * Fonction pour vider le buffer d'entrée.
 * Permet de gérer les entrées invalides de l'utilisateur.
 */
void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}