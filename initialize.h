//
// Created by yncrea-hugo on 08/04/19.
//

#ifndef PROJECT_INITIALIZE_H
#define PROJECT_INITIALIZE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "chained_list.h"
#include "file.h"
#include "chaine.h"

maillon* initializeCar(char* fileName, maillon *reservation);
maillon* initializeClients(char* fileName);
maillon* initializeReservation(char* fileName, maillon* client);
data* initializeHistory(char* fileName, maillon* reservation, char *plateNumber);
data* initializeMaintenance(char* fileName, char *plateNumber);
void freeDataInitialize(data* data1);

#endif //PROJECT_INITIALIZE_H
