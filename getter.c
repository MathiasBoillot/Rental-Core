//
// Created by hugo on 18/06/19.
//

#include <stdlib.h>
#include <stdio.h>
#include "calculus.h"
#include "chained_list.h"
#include "initialize.h"

char* convertDateShow(date date1){
    char* dateChar= malloc(14 * sizeof(char)) ;
    sprintf(dateChar,"%d/%d/%d:%d",date1.day,date1.month,date1.year,date1.hour);
    return dateChar;
}

maillon* rechercheReservationJour(date date1, maillon **reservation){
    maillon* ptr = *reservation;
    maillon* resultat = NULL;

    while(ptr != NULL){
        if(resultat == NULL && dateCompare(ptr->rent->u.value_reserv->begining,date1)== true && dateCompare(date1,ptr->rent->u.value_reserv->begining) == true){
            resultat = ptr;
        } else if(resultat == NULL && dateCompare(ptr->rent->u.value_reserv->begining,date1)== true && dateCompare(date1,ptr->rent->u.value_reserv->begining) == true){
            maillon* tmp = NULL;
            tmp = ptr;
            tmp->suivant = resultat;
            resultat = tmp;
        }
    }
    return resultat;
}