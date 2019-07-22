#ifndef PROJET_FILE_H
#define PROJET_FILE_H

int reservationTotal;

int nbCaracPerLines(char *fileNameExt);
int calculateNumberOfSeparator(char *fileNameExt);
data *readingData(char indiceColonnes[150], FILE *f, int typeNum, maillon* clients, char* plateNumber);
void saveData(maillon *ptrtete);
int convertTypeMaintenance(char* chaineType);
void saveChaine(data *ptrtete, char* plate, FILE *f);

#endif