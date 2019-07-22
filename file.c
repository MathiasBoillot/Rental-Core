#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "chained_list.h"
#include "file.h"
#include "chaine.h"
#include "initialize.h"



/**
 * Function to read a file and assign them to a maillon
 * @param char fileName, int typeNum
 * typeNum is the type of enumeration
 * @return data*
 */
data *readingData(char indiceColonnes[150], FILE *f, int typeNum, maillon *maillonResearch, char *plateNumber) {

    data *data1 = malloc(sizeof(data));
    maillon *link = NULL;
    char *chaineRecup = NULL;
    int nbCarac = 0;
    char **tabChaineRecup = NULL;
    int nbSeparator = 0;
        //dynamique allocation
        fscanf(f,"%s",indiceColonnes);
        nbCarac = strlen(indiceColonnes);
        chaineRecup = (char*) malloc(sizeof(char)*(nbCarac+1));
        strcpy(chaineRecup,indiceColonnes);

    //divide the line in tabs
    fonct(chaineRecup, &tabChaineRecup, &nbSeparator, ';');
    char **dateTmp = NULL;
    int dateNB = 4;
    switch (typeNum) {
        case CAR:

            data1->typ_val = CAR;
            data1->u.value_car = malloc(sizeof(car));
            data1->u.value_car->plate_number = malloc(sizeof(char) * (strlen(tabChaineRecup[0])+1));
            data1->u.value_car->brand_name = malloc(sizeof(char) * (strlen(tabChaineRecup[1])+1));
            data1->u.value_car->brand_model = malloc(sizeof(char) * (strlen(tabChaineRecup[2])+1));

            strcpy(data1->u.value_car->plate_number,tabChaineRecup[0]);
            strcpy(data1->u.value_car->brand_name,tabChaineRecup[1]);
            strcpy(data1->u.value_car->brand_model,tabChaineRecup[2]);

            data1->u.value_car->car_year = atoi(tabChaineRecup[3]);
            data1->u.value_car->km = atoi(tabChaineRecup[4]);
            data1->u.value_car->category = *tabChaineRecup[5];
            data1->u.value_car->price = atoi(tabChaineRecup[6]);
            data1->u.value_car->gearbox = atoi(tabChaineRecup[7]) != 0;

            data* data3 = initializeMaintenance("files/maintenances.csv",tabChaineRecup[0]);

            if(data3 != NULL){
                data1->u.value_car->car_maint = data3->u.value_maintenance;
            } else {
                data1->u.value_car->car_maint = NULL;
            }
            free(data3);

            data3 = initializeHistory("files/booking.csv", maillonResearch, tabChaineRecup[0]);

            if(data3 != NULL){
                data1->u.value_car->history_rent = data3->u.value_hist ;
            } else {
                data1->u.value_car->history_rent = NULL;
            }
            free(data3);


            break;
        case HISTORY:

                if(strcmp(plateNumber, tabChaineRecup[6])== 0){
                    data *data2 = malloc(sizeof(data));
                    data1->typ_val = HISTORY;
                    data1->u.value_hist = malloc(sizeof(history));
                    data2->typ_val = RESERVATION;
                    data2->u.value_reserv = malloc(sizeof(reservation));
                    data2->u.value_reserv->number = atoi(tabChaineRecup[0]);
                    link = rechercheMaillon(maillonResearch, data2);
                    data1->u.value_hist->reserv = link->rent->u.value_reserv;
                    free(data2->u.value_reserv);
                    free(data2);
                    data1->u.value_hist->suivant = NULL;
                } else {
                    free(data1);
                    data1 = NULL;
                }


            break;
        case RESERVATION:

            data1->typ_val = RESERVATION;
            data1->u.value_reserv = malloc(sizeof(reservation));

            data1->u.value_reserv->number = atoi(tabChaineRecup[0]);

            fonct(tabChaineRecup[1], &dateTmp, &dateNB, '-');
            data1->u.value_reserv->begining.day = atoi(dateTmp[0]);
            data1->u.value_reserv->begining.month = atoi(dateTmp[1]);
            data1->u.value_reserv->begining.year = atoi(dateTmp[2]);
            data1->u.value_reserv->begining.hour = atoi(dateTmp[3]);

            fonct(tabChaineRecup[2], &dateTmp, &dateNB, '-');
            data1->u.value_reserv->end.day = atoi(dateTmp[0]);
            data1->u.value_reserv->end.month = atoi(dateTmp[1]);
            data1->u.value_reserv->end.year = atoi(dateTmp[2]);
            data1->u.value_reserv->end.hour = atoi(dateTmp[3]);

            for (int i = 0; i < dateNB; ++i) {
                free(dateTmp[i]);
            }
            free(dateTmp);

            data1->u.value_reserv->category = *tabChaineRecup[3];
            data1->u.value_reserv->km = atoi(tabChaineRecup[4]);

            data *data2 = malloc(sizeof(data));
            data2->typ_val = CLIENT;
            data2->u.value_client = malloc(sizeof(reservation));
            data2->u.value_client->phone_number = atoi(tabChaineRecup[5]);

            link = rechercheMaillon(maillonResearch, data2);


            if(link != NULL){
                data1->u.value_reserv->client_info = link->rent->u.value_client;
            } else {
                data1->u.value_reserv->client_info = NULL;
            }


            free(data2->u.value_client);
            free(data2);
            break;

        case CLIENT:
            data1->typ_val = CLIENT;
            data1->u.value_client = (client*) malloc(sizeof(client));
            data1->u.value_client->client_name = (char*) malloc(sizeof(char) * (strlen(tabChaineRecup[0])+1));
            data1->u.value_client->driving_license_type = (char*) malloc(sizeof(char) * (strlen(tabChaineRecup[1])+1));

            strcpy(data1->u.value_client->client_name,tabChaineRecup[0]);
            strcpy(data1->u.value_client->driving_license_type,tabChaineRecup[1]);
            data1->u.value_client->phone_number = atoi(tabChaineRecup[2]);
            break;
        case MAINTENANCE:
            if (strcmp(plateNumber, tabChaineRecup[0]) == 0) {
                data1->typ_val = MAINTENANCE;
                data1->u.value_maintenance = malloc(sizeof(maintenance));
                data1->u.value_maintenance->type = convertTypeMaintenance(tabChaineRecup[1]);
                fonct(tabChaineRecup[2], &dateTmp, &dateNB, '-');
                data1->u.value_maintenance->date_maintenance.hour = atoi(dateTmp[3]);
                data1->u.value_maintenance->date_maintenance.day = atoi(dateTmp[0]);
                data1->u.value_maintenance->date_maintenance.month = atoi(dateTmp[1]);
                data1->u.value_maintenance->date_maintenance.year = atoi(dateTmp[2]);
                data1->u.value_maintenance->coast = atof(tabChaineRecup[3]);
            } else {
                free(data1);
                data1 = NULL;
            }
            break;
        default:
            printf("ERROR ! ENUM TYPE NOT DEFINE\n");
            break;
    }
    for (int i = 0; i < nbSeparator+1; ++i) {
        free(tabChaineRecup[i]);
    }
    free(tabChaineRecup);
    free(chaineRecup);

    return data1;
}


char* prepareCSV(maillon *save) {
    char *csv = malloc(sizeof(char) * 100);
    char *Ctmp = malloc(sizeof(char) * 20);
    switch (save->rent->typ_val) {
        case 0:
            strcpy(csv,save->rent->u.value_car->plate_number);
            strcat(csv, ";");
            strcat(csv, save->rent->u.value_car->brand_name);
            strcat(csv, ";");
            strcat(csv, save->rent->u.value_car->brand_model);
            strcat(csv, ";");
            sprintf(Ctmp, "%d", save->rent->u.value_car->car_year);
            strcat(csv, Ctmp);
            strcat(csv, ";");
            sprintf(Ctmp, "%d", save->rent->u.value_car->km);
            strcat(csv, Ctmp);
            strcat(csv, ";");
            strcat(csv, &save->rent->u.value_car->category);
            strcat(csv, ";");
            sprintf(Ctmp, "%.2f", save->rent->u.value_car->price);
            strcat(csv, Ctmp);
            strcat(csv, ";");
            sprintf(Ctmp, "%d", save->rent->u.value_car->gearbox);
            strcat(csv, Ctmp);
            free(Ctmp);
            break;
        case 1:
            break;
        case 2:
            break;
        case CLIENT:
            strcpy(csv,save->rent->u.value_client->client_name);
            strcat(csv, ";");
            strcat(csv, save->rent->u.value_client->driving_license_type);
            strcat(csv, ";0");
            sprintf(Ctmp, "%d", save->rent->u.value_client->phone_number);
            strcat(csv, Ctmp);
            free(Ctmp);
            break;
        default:
            break;
    }
    strcat(csv, "\n");
    return csv;
}

void saveChaine(data *ptrtete, char *plate, FILE *f) {
    data *save = ptrtete;
    int nbData = 0;
    char *csv = (char*) malloc(sizeof(char) * 150);
    char *tmp = (char*) malloc(sizeof(char) * 50);
    const char *typeNames[] = {"CT", "REPAIR", "REVISION"};
    fscanf(f, "%d", &nbData);
    fscanf(f, "%s", tmp);
    fseek(f, 1, SEEK_CUR);
    if (save->typ_val == MAINTENANCE) {
        while (save->u.value_maintenance != NULL) {
            strcpy(csv,plate);
            strcat(csv, ";");
            strcat(csv, typeNames[save->u.value_maintenance->type]);
            strcat(csv, ";");
            sprintf(tmp, "%d", save->u.value_maintenance->date_maintenance.day);
            strcat(csv, tmp);
            strcat(csv, "-");
            sprintf(tmp, "%d", save->u.value_maintenance->date_maintenance.month);
            strcat(csv, tmp);
            strcat(csv, "-");
            sprintf(tmp, "%d", save->u.value_maintenance->date_maintenance.year);
            strcat(csv, tmp);
            strcat(csv, "-");
            sprintf(tmp, "%d", save->u.value_maintenance->date_maintenance.hour);
            strcat(csv, tmp);
            strcat(csv, "\n");
            fprintf(f, "%s", csv);
            nbData++;
            save->u.value_maintenance = save->u.value_maintenance->suivant;
        }
    } else if (save->typ_val == HISTORY) {
        while (save->u.value_hist != NULL) {
            sprintf(tmp, "%d", save->u.value_hist->reserv->number);
            strcpy(csv, tmp);
            strcat(csv, ";");
            sprintf(tmp, "%d", save->u.value_hist->reserv->begining.day);
            strcat(csv, tmp);
            strcat(csv, "-");
            sprintf(tmp, "%d", save->u.value_hist->reserv->begining.month);
            strcat(csv, tmp);
            strcat(csv, "-");
            sprintf(tmp, "%d", save->u.value_hist->reserv->begining.year);
            strcat(csv, tmp);
            strcat(csv, "-");
            sprintf(tmp, "%d", save->u.value_hist->reserv->begining.hour);
            strcat(csv, tmp);
            strcat(csv, ";");
            sprintf(tmp, "%d", save->u.value_hist->reserv->end.day);
            strcat(csv, tmp);
            strcat(csv, "-");
            sprintf(tmp, "%d", save->u.value_hist->reserv->end.month);
            strcat(csv, tmp);
            strcat(csv, "-");
            sprintf(tmp, "%d", save->u.value_hist->reserv->end.year);
            strcat(csv, tmp);
            strcat(csv, "-");
            sprintf(tmp, "%d", save->u.value_hist->reserv->end.hour);
            strcat(csv, tmp);
            strcat(csv, ";");
            strcat(csv, &save->u.value_hist->reserv->category);
            strcat(csv, ";0");
            sprintf(tmp, "%d", save->u.value_hist->reserv->client_info->phone_number);
            strcat(csv, tmp);
            strcat(csv, ";");
            strcat(csv, plate);
            strcat(csv, "\n");
            fprintf(f, "%s", csv);
            nbData++;
            save->u.value_hist = save->u.value_hist->suivant;
        }
    }
    free(tmp);
    rewind(f);
    fprintf(f, "%d", nbData+1);
}

void saveData(maillon *ptrtete) {
    maillon *save = ptrtete;
    FILE *f, *mtn = NULL, *hist = NULL;
    char *tmp = malloc(sizeof(char) * 50);
    int nbData = 1;
    switch (save->rent->typ_val) {
        case 0:
            f = fopen("files/vehicules2.csv", "r+");
            mtn = fopen("files/maintenances2.csv", "r+");
            hist = fopen("files/booking2.csv", "r+");
            break;
        case 1:
            break;
        case 2:
            f = fopen("files/booking2.csv", "r+");
            break;
        case CLIENT:
            f = fopen("files/clients2.csv", "r+");
            break;
        default:
            break;
    }
    fscanf(f, "%s", tmp);
    fscanf(f, "%s", tmp);
    fseek(f, 1, SEEK_CUR);
    while (save->suivant != NULL) {
        fprintf(f, "%s", prepareCSV(save));
        if (save->rent->typ_val == CAR) {
            data* dataTmp1 =(data*) malloc(sizeof(data));
            dataTmp1->typ_val = MAINTENANCE;
            dataTmp1->u.value_maintenance = save->rent->u.value_car->car_maint;
            saveChaine(dataTmp1, save->rent->u.value_car->plate_number, mtn);
            free(dataTmp1);
            data* dataTmp2 =(data*) malloc(sizeof(data));
            dataTmp2->typ_val = HISTORY;
            dataTmp2->u.value_hist = save->rent->u.value_car->history_rent;
            saveChaine(dataTmp2, save->rent->u.value_car->plate_number, hist);
            free(dataTmp2);
        }
        nbData++;
        save = save->suivant;
    }
    rewind(f);
    fprintf(f, "%d", nbData);
    if (mtn != NULL) {
        fclose(mtn);
    }
    if (hist != NULL) {
        fclose(hist);
    }
    fclose(f);
    free(tmp);
}

int convertTypeMaintenance(char *chaineType) {
    if (strcmp(chaineType, "CT") == 0) {
        return 0;
    } else if (strcmp(chaineType, "REPAIR") == 0) {
        return 1;
    } else if (strcmp(chaineType, "REVISION") == 0) {
        return 2;
    } else {
        exit(-1);
    }
}
