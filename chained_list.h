//
// Created by yncrea-hugo on 26/03/19.
//

#ifndef PROJET_CHAINED_LIST_H
#define PROJET_CHAINED_LIST_H

#include <stdbool.h>

typedef struct date{
    int day;
    int year;
    int month;
    int hour;
}date;

typedef struct client{
    char *client_name;
    char *driving_license_type;
    int phone_number;
}client;

enum typeMaintenance {CT,REPAIR,REVISION};
typedef struct maintenance{
    enum typeMaintenance type;
    date date_maintenance;
    float coast;
    struct maintenance *suivant;
}maintenance;

typedef struct reservation{
    int number; //numero reservation
    date begining;
    date end;
    char category;
    int km;
    client* client_info;

}reservation;

typedef struct history{
    reservation* reserv;
    struct history* suivant;
}history;

typedef struct car{
    char *plate_number;
    char *brand_name;
    char *brand_model;
    int car_year;
    int km;
    char category;
    float price;
    bool gearbox;
    maintenance *car_maint;
    history *history_rent;

}car;



//functions pointers
enum type {CAR,HISTORY,RESERVATION,CLIENT,MAINTENANCE};
typedef struct data{
    enum type typ_val; //indique ce qu'il y a dans u
    union{
        car* value_car;
        history* value_hist;
        reservation* value_reserv;
        client* value_client;
        maintenance* value_maintenance;
    }u;
}data;

typedef struct maillon{
    data *rent;
    struct maillon *suivant;
}maillon;

typedef struct predict{
  int jour;
  int km;

}predict;

void afficheListe(maillon **ptrTete);
maillon* creationMaillon(data *rent);
maillon* rechercheMaillonPrecedent(maillon **ptrTete, data *data1);
void insertionMaillon(maillon **ptrTete, maillon *insert);
void insertionValeur(data *rent, maillon **ptrTete);
void suppressionMaillon(maillon **ptrTete, maillon *del);
maillon* rechercheMaillon(maillon *ptrTete, data* data1);
maillon* suppressionValeur(maillon *ptrTete, data* rent);
bool dateCompare(date inf, date sup);
bool dateEqual(date d1, date d2);
void suppressionListe(maillon **ptrTete);
void inversionListe(maillon **ptrTete);
data* rechercheSousChainePrecedent(data *ptrTete, data *data1);
void insertionSousChaine(data **ptrTete, data *insert);

#endif //PROJET_CHAINED_LIST_H
