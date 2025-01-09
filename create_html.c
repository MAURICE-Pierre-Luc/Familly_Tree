#include "create_html.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "population.h"


char* replace(char* html_content, const char* tag, const char* lenght) {
    char* pos = strstr(html_content, tag); //cherche la position de la premiere occurence de la balise html pour pouvoir ensuite la remplacer
    if (pos == NULL) { //si le tag n'existe pas
        return html_content;
    }

    unsigned int new_size = strlen(html_content) + strlen(lenght) - strlen(tag) + 1; //on prend donc la taille du fichier html + la taille du buffer - la taille de la balise(tag)
    char* new_html = malloc(new_size);
    if (new_html == NULL) {
        return html_content;
    }

    unsigned int before = pos - html_content;  //calcule la longueur du doc html avant la balise
    strncpy(new_html, html_content, before); //on copie toute la partie avant la balise
    strcpy(new_html + before, lenght); // on change remplace la balise rechercher par le tag
    strcpy(new_html + before + strlen(lenght), pos + strlen(tag));// //puis on copie la suite du doc html

    free(html_content);
    return new_html;
}

void generate_html(struct Population* pop) {
    char* template = "../source/projetCIR1.html";
    FILE* template_file = fopen(template, "r");
    if (template_file == NULL) {
        printf("Error opening template file\n");
        return;
    }

    // lis le fichier
    fseek(template_file, 0, SEEK_END);
    long template_size = ftell(template_file);
    fseek(template_file, 0, SEEK_SET);
    char* template_content = malloc(template_size + 1);
    fread(template_content, 1, template_size, template_file);
    template_content[template_size] = '\0';
    fclose(template_file);

    // parcour chaque personne de la population
    struct Person* iter = getHead(pop);
    //crée un fichier html pour chaque personne dans le dossier export
    char* personnal_date;
    while (iter != NULL) {
        char filename[MAX_FILE_NAME_SIZE];
        snprintf(filename, sizeof(filename), "../export/%d.html", getId(iter));
        FILE* html_file = fopen(filename, "w");
        if (html_file == NULL) {
            printf("Error creating HTML file for person ID %d\n", getId(iter));
            iter = getNext(iter);
            continue;
        }

        // remplace les templates du fichier html par les données de la personne
        char* html_content = strdup(template_content); //duplique le contenue de l'html
        char buffer[BUFFER_SIZE];

        snprintf(buffer, sizeof(buffer), "%d", getId(iter) );
        html_content = replace(html_content, "{{lien}}", buffer);

        snprintf(buffer, sizeof(buffer), "%d", getId(iter) );
        html_content = replace(html_content, "{{lien}}", buffer);

        snprintf(buffer, sizeof(buffer), "%s %s", getName(iter), getLast_name(iter));
        html_content = replace(html_content, "{{name}}", buffer);

        snprintf(buffer, sizeof(buffer), "%s %s", getName(iter), getLast_name(iter));
        html_content = replace(html_content, "{{name}}", buffer);

        personnal_date = getDate(iter);
        snprintf(buffer, sizeof(buffer), "%s :%s","Date of birth", personnal_date);
        html_content = replace(html_content, "{{birth_date}}", buffer);
        free(personnal_date);

        snprintf(buffer, sizeof(buffer), "%s :%s","Region" ,getRegion(iter));
        html_content = replace(html_content, "{{region}}", buffer);

        snprintf(buffer, sizeof(buffer), "%d", getFather_id(iter));
        html_content = replace(html_content, "{{father_id}}", buffer);

        snprintf(buffer, sizeof(buffer), "%d", getMother_id(iter));
        html_content = replace(html_content, "{{mother_id}}", buffer);
        //pere
        if(getFather_id(iter) != 0 && getFather(iter) != NULL){ //verifie si on connait l'id du pere
            snprintf(buffer, sizeof(buffer), "%s %s", getName(getFather(iter)), getLast_name(getFather(iter)));
            html_content = replace(html_content, "{{father_name}}", buffer);
            personnal_date = getDate(getFather(iter));
            snprintf(buffer, sizeof(buffer), "%s :%s","Date of birth", personnal_date);
            html_content = replace(html_content, "{{father_date}}", buffer);
            free(personnal_date);
            snprintf(buffer, sizeof(buffer), "%s%s","Region :", getRegion(getFather(iter)));
            html_content = replace(html_content, "{{father_region}}", buffer);
        } else{
            snprintf(buffer, sizeof(buffer), "%s","unknown");//on remplace par unkwown lorsqu'on ne connait pas le nom
            html_content = replace(html_content, "{{father_name}}", buffer);
            //on remplace par unkwown lorsqu'on ne connait pas la date
            html_content = replace(html_content, "{{father_date}}", "");
            //on remplace par unkwown lorsqu'on ne connait pas la region
            html_content = replace(html_content, "{{father_region}}", "");
        }
        // mere
        if(getMother_id(iter) != 0 && getMother(iter) != NULL) { // Vérifie si on connaît l'ID de la mère et que le pointeur n'est pas NULL
            snprintf(buffer, sizeof(buffer), "%s %s", getName(getMother(iter)), getLast_name(getMother(iter)));
            html_content = replace(html_content, "{{mother_name}}", buffer);
            personnal_date = getDate(getMother(iter));
            snprintf(buffer, sizeof(buffer), "%s:%s","Date of birth", personnal_date);
            html_content = replace(html_content, "{{mother_date}}", buffer);
            free(personnal_date);
            snprintf(buffer, sizeof(buffer), "%s :%s","Region", getRegion(getMother(iter)));
            html_content = replace(html_content, "{{mother_region}}", buffer);
        } else {
            snprintf(buffer, sizeof(buffer), "%s", "unknown"); // Remplace par "unknown" lorsqu'on ne connaît pas l'ID
            html_content = replace(html_content, "{{mother_name}}", buffer);
            html_content = replace(html_content, "{{mother_date}}", "");
            html_content = replace(html_content, "{{mother_region}}", "");
        }

        // grands-parents paternel
        //ID nom date region du grand-pere paternel
        if(getFather(iter) != NULL && getFather(getFather(iter)) != NULL && getFather_id(iter) !=0 && getFather_id(getFather(iter)) !=0)  {
            snprintf(buffer, sizeof(buffer), "%d", getFather_id(getFather(iter)));
            html_content = replace(html_content, "{{paternal_grandfather_id}}", buffer);

            snprintf(buffer, sizeof(buffer), "%s %s", getName(getFather(getFather(iter))), getLast_name(getFather(getFather(iter))));
            html_content = replace(html_content, "{{paternal_grandfather_name}}", buffer);

            personnal_date = getDate(getFather(getFather(iter)));
            snprintf(buffer, sizeof(buffer), "%s :%s","Date of birth", personnal_date);
            html_content = replace(html_content, "{{paternal_grandfather_date}}", buffer);
            free(personnal_date);

            snprintf(buffer, sizeof(buffer), "%s %s", "Region", getRegion(getFather(getFather(iter))));
            html_content = replace(html_content, "{{paternal_grandfather_region}}", buffer);
        } else {
            snprintf(buffer, sizeof(buffer), "%d", 0);
            html_content = replace(html_content, "{{paternal_grandfather_id}}", buffer);
            snprintf(buffer, sizeof(buffer), "%s","unknown");//on remplace par unkwown lorsqu'on ne connait pas le nom
            html_content = replace(html_content, "{{paternal_grandfather_name}}", buffer);
            html_content = replace(html_content, "{{paternal_grandfather_date}}", "");
            html_content = replace(html_content, "{{paternal_grandfather_region}}", "");
        }
        //ID nom date region de grand-mere paternel
        if(getFather(iter) != NULL && getMother(getFather(iter)) != NULL && getName(iter)!=0 && getMother_id(getFather(iter)) !=0) {
            snprintf(buffer, sizeof(buffer), "%d", getId(getMother(getFather(iter))));
            html_content = replace(html_content, "{{paternal_grandmother_id}}", buffer);

            snprintf(buffer, sizeof(buffer), "%s %s", getName(getMother(getFather(iter))), getLast_name(getMother(getFather(iter))));
            html_content = replace(html_content, "{{paternal_grandmother_name}}", buffer);

            personnal_date = getDate(getMother(getFather(iter)));
            snprintf(buffer, sizeof(buffer), "%s :%s","Date of birth", personnal_date);
            html_content = replace(html_content, "{{paternal_grandmother_date}}", buffer);
            free(personnal_date);

            snprintf(buffer, sizeof(buffer), "%s :%s","Region", getRegion(getMother(getFather(iter))));
            html_content = replace(html_content, "{{paternal_grandmother_region}}", buffer);
        } else {
            snprintf(buffer, sizeof(buffer), "%d", 0);
            html_content = replace(html_content, "{{paternal_grandmother_id}}", buffer);
            snprintf(buffer, sizeof(buffer), "%s","unknown");//on remplace par unkwown lorsqu'on ne connait pas le nom
            html_content = replace(html_content, "{{paternal_grandmother_name}}", buffer);
            html_content = replace(html_content, "{{paternal_grandmother_date}}", "");
            html_content = replace(html_content, "{{paternal_grandmother_region}}", "");
        }

        // Grands-parents maternel
        //ID nom date region grand-pere maternel
        if(getMother(iter) != NULL && getFather(getMother(iter)) != NULL && getFather_id(iter)!=0 && getFather_id(getMother(iter)) !=0) {
            snprintf(buffer, sizeof(buffer), "%d", getFather_id(getMother(iter)));
            html_content = replace(html_content, "{{maternal_grandfather_id}}", buffer);

            snprintf(buffer, sizeof(buffer), "%s %s", getName(getFather(getMother(iter))), getLast_name(getFather(getMother(iter))));
            html_content = replace(html_content, "{{maternal_grandfather_name}}", buffer);

            personnal_date = getDate(getFather(getMother(iter)));
            snprintf(buffer, sizeof(buffer), "%s :%s","Date of birth", personnal_date);
            html_content = replace(html_content, "{{maternal_grandfather_date}}", buffer);
            free(personnal_date);

            snprintf(buffer, sizeof(buffer), "%s :%s","Region", getRegion(getFather(getMother(iter))));
            html_content = replace(html_content, "{{maternal_grandfather_region}}", buffer);
        } else {
            snprintf(buffer, sizeof(buffer), "%d", 0);
            html_content = replace(html_content, "{{maternal_grandfather_id}}", buffer);
            snprintf(buffer, sizeof(buffer), "%s","unknown");//on remplace par unkwown lorsqu'on ne connait pas le nom
            html_content = replace(html_content, "{{maternal_grandfather_name}}", buffer);
            html_content = replace(html_content, "{{maternal_grandfather_date}}", "");
            html_content = replace(html_content, "{{maternal_grandfather_region}}", "");
        }
        //ID nom date region grand-mere maternel
        if(getMother(iter) != NULL && getMother(getMother(iter)) != NULL && getFather_id(iter)!=0 && getMother_id(getMother(iter)) != 0) {
            snprintf(buffer, sizeof(buffer), "%d", getMother_id(getMother(iter)));
            html_content = replace(html_content, "{{maternal_grandmother_id}}", buffer);

            snprintf(buffer, sizeof(buffer), "%s %s", getName(getMother(getMother(iter))), getLast_name(getMother(getMother(iter))));
            html_content = replace(html_content, "{{maternal_grandmother_name}}", buffer);

            personnal_date=getDate(getMother(getMother(iter)));
            snprintf(buffer, sizeof(buffer), "%s :%s","Date of birth" , personnal_date);
            html_content = replace(html_content, "{{maternal_grandmother_date}}", buffer);
            free(personnal_date);

            snprintf(buffer, sizeof(buffer), "%s :%s","Region", getRegion(getMother(getMother(iter))));
            html_content = replace(html_content, "{{maternal_grandmother_region}}", buffer);
        } else {
            snprintf(buffer, sizeof(buffer), "%d", 0);
            html_content = replace(html_content, "{{maternal_grandmother_id}}", buffer);
            snprintf(buffer, sizeof(buffer), "%s","unknown");//on remplace par unkwown lorsqu'on ne connait pas le nom
            html_content = replace(html_content, "{{maternal_grandmother_name}}", buffer);
            html_content = replace(html_content, "{{maternal_grandmother_date}}", "");
            html_content = replace(html_content, "{{maternal_grandmother_region}}", "");
        }

        snprintf(buffer, sizeof(buffer), "%d", getPopulationSize(pop));
        html_content = replace(html_content, "{{sizepop}}", buffer);

        // ecrie le contenu html dans le fichier
        fwrite(html_content, 1, strlen(html_content), html_file);
        fclose(html_file);

        free(html_content);
        iter = getNext(iter);
    }

    free(template_content);
}

void info_tree(struct Population* pop){
    char* template = "../source/infosTree.html";
    FILE* template_file = fopen(template, "r");
    if (template_file == NULL) {
        printf("Error opening template file\n");
        return;
    }

    // lis le fichier
    fseek(template_file, 0, SEEK_END);
    long template_size = ftell(template_file);
    fseek(template_file, 0, SEEK_SET);
    char* template_content = malloc(template_size + 1);
    fread(template_content, 1, template_size, template_file);
    template_content[template_size] = '\0';
    fclose(template_file);

    // parcour chaque personne de la population
    //crée un fichier html pour chaque personne dans le dossier export

    char filename[MAX_FILE_NAME_SIZE];
    snprintf(filename, sizeof(filename), "../export/%s.html", "infosTree");
    FILE* html_file = fopen(filename, "w");
    if (html_file == NULL) {
        printf("Error creating HTML file for infos_Tree\n");
    }

    // remplace les templates du fichier html par les données de la personne
    char* html_content = strdup(template_content); //duplique le contenue de l'html
    char buffer[BUFFER_SIZE];


    html_content = replace(html_content, "{{lien}}", "infos_Tree");

    snprintf(buffer, sizeof(buffer), "%d", getPopulationSize(pop));
    html_content = replace(html_content, "{{size}}", buffer);

    snprintf(buffer, sizeof(buffer), "%s %s", getName(getOldest(pop)), getLast_name(getOldest(pop)));
    html_content = replace(html_content, "{{oldest}}", buffer);

    snprintf(buffer, sizeof(buffer), "%d", getId(getOldest(pop)));
    html_content = replace(html_content, "{{oldest_lien}}", buffer);

    snprintf(buffer, sizeof(buffer), "%s %s", getName(getYoungest(pop)), getLast_name(getYoungest(pop)));
    html_content = replace(html_content, "{{youngest}}", buffer);

    snprintf(buffer, sizeof(buffer), "%d", getId(getYoungest(pop)));
    html_content = replace(html_content, "{{youngest_lien}}", buffer);

    snprintf(buffer, sizeof(buffer), "%d", getFemales(pop));
    html_content = replace(html_content, "{{females}}", buffer);

    snprintf(buffer, sizeof(buffer), "%d", getMales(pop));
    html_content = replace(html_content, "{{males}}", buffer);

    snprintf(buffer, sizeof(buffer), "%d", getUnknownSex(pop));
    html_content = replace(html_content, "{{unknownsex}}", buffer);

    snprintf(buffer, sizeof(buffer), "%d", getPopulationSize(pop));
    html_content = replace(html_content, "{{sizepop}}", buffer);

    // ecrie le contenu html dans le fichier
    fwrite(html_content, 1, strlen(html_content), html_file);
    fclose(html_file);

    free(html_content);

    free(template_content);
}

void query(struct Population* pop, char regionname[WORD_MAX_SIZE], struct Person* queryperson,char* querydate,char* most_births,bool old, bool young,char* father_name, char* mother_name, char* father_lastname, char* mother_lastname){
    FILE* template_file = fopen("../source/query.html", "r");
    if (template_file == NULL) {
        printf("Error opening template file\n");
        return;
    }

    // lis le fichier
    fseek(template_file, 0, SEEK_END);
    long template_size = ftell(template_file);
    fseek(template_file, 0, SEEK_SET);
    char* template_content = malloc(template_size + 1);
    fread(template_content, 1, template_size, template_file);
    template_content[template_size] = '\0';
    fclose(template_file);

    char filename[MAX_FILE_NAME_SIZE];
    snprintf(filename, sizeof(filename), "../export/%s.html", "query");
    FILE *html_file = fopen(filename, "w");
    if (html_file == NULL) {
        printf("Error creating HTML file for query");
    }

    // remplace les templates du fichier html par les données de la personne
    char *html_content = strdup(template_content); //duplique le contenue de l'html
    char buffer[BUFFER_SIZE];


    html_content = replace(html_content, "{{lien}}", "Query");

    if(old) {
        snprintf(buffer, sizeof(buffer), "%s %s", getName(getOldest(pop)), getLast_name(getOldest(pop)));
        html_content = replace(html_content, "{{old}}", buffer);

        snprintf(buffer, sizeof(buffer), "%d", getId(getOldest(pop)));
        html_content = replace(html_content, "{{oldest_lien}}", buffer);
    } else{
        html_content = replace(html_content, "{{old}}", "unknown");
        html_content = replace(html_content, "{{oldest_lien}}", "0");
    }
    if(young) {
        snprintf(buffer, sizeof(buffer), "%s %s", getName(getYoungest(pop)), getLast_name(getYoungest(pop)));
        html_content = replace(html_content, "{{young}}", buffer);

        snprintf(buffer, sizeof(buffer), "%d", getId(getYoungest(pop)));
        html_content = replace(html_content, "{{youngest_lien}}", buffer);
    } else {
        html_content = replace(html_content, "{{young}}", "unknown");
        html_content = replace(html_content, "{{youngest_lien}}", "0");
    }

    if(strlen(regionname)!=0) {
        snprintf(buffer, sizeof(buffer), "%s", regionname);
        html_content = replace(html_content, "{{queryregionname}}", buffer);
        snprintf(buffer, sizeof(buffer), "%d", regionBirths(getGlobalRegion(pop), regionname));
        html_content = replace(html_content, "{{regionbirths}}", buffer);
    } else{
        html_content = replace(html_content, "{{queryregionname}}", "unknown");
        html_content = replace(html_content, "{{regionbirths}}", "NA");
    }

    if(most_births!=NULL) {
        snprintf(buffer, sizeof(buffer), "%s", most_births);
        html_content = replace(html_content, "{{mostbirthsregion}}", buffer);
        snprintf(buffer, sizeof(buffer), "%d", getMostBirths(getGlobalRegion(pop)));
        html_content = replace(html_content, "{{numberofbirthsmostbirthsregion}}", buffer);
    } else{
        html_content = replace(html_content, "{{mostbirthsregion}}", "unknown");
        html_content = replace(html_content, "{{numberofbirthsmostbirthsregion}}", "NA");
    }

    if(strlen(querydate)!= 0) {
        unsigned int amountofbirths = getDateBirths(getCalendar(pop), querydate);
        snprintf(buffer, sizeof(buffer), "%s", querydate);
        html_content = replace(html_content, "{{querydate}}", buffer);
        snprintf(buffer, sizeof(buffer), "%d", amountofbirths);
        html_content = replace(html_content, "{{datesbirths}}", buffer);
    } else{
        html_content = replace(html_content, "{{querydate}}", "unknown");
        html_content = replace(html_content, "{{datesbirths}}", "NA");
    }

    if(father_name!=NULL) {
        snprintf(buffer, sizeof(buffer), "%s %s", father_name,father_lastname);
        html_content = replace(html_content, "{{mostchildrenfathername}}", buffer);
    } else{
        html_content = replace(html_content, "{{mostchildrenfathername}}", "unknown");
    }

    if(mother_name!=NULL) {
        snprintf(buffer, sizeof(buffer), "%s %s", mother_name,mother_lastname);
        html_content = replace(html_content, "{{mostchildrenmothername}}", buffer);
    } else{
        html_content = replace(html_content, "{{mostchildrenmothername}}", "unknown");
    }

    if(queryperson!=NULL) {
        snprintf(buffer, sizeof(buffer), "%s %s", getName(queryperson), getLast_name(queryperson));
        html_content = replace(html_content, "{{querypersonname}}", buffer);

        snprintf(buffer, sizeof(buffer), "%d", getId(queryperson));
        html_content = replace(html_content, "{{querypersonid}}", buffer);
    } else{
        html_content = replace(html_content, "{{querypersonname}}", "unknown");
        html_content = replace(html_content, "{{querypersonid}}", "0");
    }

    snprintf(buffer, sizeof(buffer), "%d", getPopulationSize(pop));
    html_content = replace(html_content, "{{sizepop}}", buffer);

    // ecrie le contenu html dans le fichier
    fwrite(html_content, 1, strlen(html_content), html_file);
    fclose(html_file);

    free(html_content);
    free(template_content);
}

void createunknown_html(struct Population* pop){
    FILE* template_file = fopen("../source/0.html", "r");
    if (template_file == NULL) {
        printf("Error opening template file\n");
        return;
    }

    // lis le fichier
    fseek(template_file, 0, SEEK_END);
    long template_size = ftell(template_file);
    fseek(template_file, 0, SEEK_SET);
    char* template_content = malloc(template_size + 1);
    fread(template_content, 1, template_size, template_file);
    template_content[template_size] = '\0';
    fclose(template_file);

    char filename[MAX_FILE_NAME_SIZE];
    snprintf(filename, sizeof(filename), "../export/%s.html", "0");
    FILE* html_file = fopen(filename, "w");
    if (html_file == NULL) {
        printf("Error creating HTML file for infos_Tree\n");
    }

    char* html_content = strdup(template_content); //duplique le contenue de l'html
    char buffer[BUFFER_SIZE];

    snprintf(buffer, sizeof(buffer), "%d", getPopulationSize(pop));
    html_content = replace(html_content, "{{sizepop}}", buffer);

    fwrite(html_content, 1, strlen(html_content), html_file);
    fclose(html_file);

    free(html_content);
    free(template_content);
}