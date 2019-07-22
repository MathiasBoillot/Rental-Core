#include "chained_list.h"

maillon *searchCar(maillon *ptrtete, reservation* Car_reserv, int *upgraded);
predict *createTabPrediction(maillon *ptrtete, int *compteur);
int milePrediction(maillon **ptrTete , date begin, date end);
int errorPrediction(predict *tabVal,int cpt);
