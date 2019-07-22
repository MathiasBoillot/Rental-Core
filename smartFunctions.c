#include <stdlib.h>
#include <stdio.h>
#include "smartFunctions.h"
#include "calculus.h"


/**
 * [searchCar give a car free with the less mileage]
 * @param  ptrtete    [maillon **]
 * @param  Car_reserv [reservation *]
 * @param upgraded    [int *, 0 not upgraded, 1 carUpgraded by +1, 2 carUpgraded by +2, 3 none cars are available]
 * @return            [maillon *]
 */
maillon *searchCar(maillon *ptrtete, reservation* Car_reserv, int *upgraded){
	maillon *ptrtrans = ptrtete;
	maillon *carFound, *carUpgrade, *carUpgrade2;
	carFound = carUpgrade = carUpgrade2 = NULL;
	int i = 0;

	if (ptrtrans->rent->typ_val == CAR){

		//travel int the car chained list
		while(ptrtrans !=  NULL){

			//check if the car is free and if it's a car request
			if (isCarFree(ptrtrans->rent->u.value_car->history_rent) == 0 && Car_reserv->category == ptrtrans->rent->u.value_car->category){

				//check if the mileage is inferior at the carFound before
				if (i > 0 && carFound != NULL && ptrtrans->rent->u.value_car->km < carFound->rent->u.value_car->km){
					carFound = ptrtrans;
				}else if(carFound == NULL){
					carFound = ptrtrans;
				}

				ptrtrans = ptrtrans->suivant;

			}else{

				//upgrading car +1 in case of carFound is NULL
				if(isCarFree(ptrtrans->rent->u.value_car->history_rent) == 0 && Car_reserv->category+1 == ptrtrans->rent->u.value_car->category){

					//check if the mileage is inferior at the carFound before
					if (i > 0 && carUpgrade != NULL && ptrtrans->rent->u.value_car->km < carUpgrade->rent->u.value_car->km){
						carUpgrade = ptrtrans;
					}else if(carUpgrade == NULL){
						carUpgrade = ptrtrans;
					}

				}
				//upgrading car +2 in case of carUpgrade is NULL
				if (isCarFree(ptrtrans->rent->u.value_car->history_rent) == 0 && Car_reserv->category+2 == ptrtrans->rent->u.value_car->category){
						//check if the mileage is inferior at the carFound before
					if (i > 0 && carUpgrade2 != NULL && ptrtrans->rent->u.value_car->km < carUpgrade2->rent->u.value_car->km){
						carUpgrade2 = ptrtrans;
					}else if(carUpgrade2 == NULL){
						carUpgrade2 = ptrtrans;
					}

				}
				ptrtrans = ptrtrans->suivant;
			}
			i++;
		}

	}else{
		printf("It's not a car !\n");
		return 0;
	}


	//return the good car
	if (carFound == NULL){

		*upgraded = 1;
		return carUpgrade;

	}if(carUpgrade == NULL){

		*upgraded = 2;
		return carUpgrade2;

	}if(carUpgrade2 == NULL){

		*upgraded = 3;
		return carFound;

	}else{
		*upgraded = 0;
		return carFound;
	}



}

/**
 * [createTabPrediction create a tab with nbdays and nbKm]
 * @param ptrtete  [Reservation]
 * @param tabRecup [the array to get]
 */
predict *createTabPrediction(maillon *ptrTete, int *compteur){

	//initialize tabRecup
	maillon *ptrtrans = ptrTete;
	predict *tabRecup = malloc(sizeof(predict)*1);
	int cpt =0;


	//check if the ptrtete is reservation
	if (ptrtrans->rent->typ_val == RESERVATION) {


		//assignation des valeurs au tableau tabRecup
		while (ptrtrans != NULL ) {


			tabRecup[cpt].km  = ptrtrans->rent->u.value_reserv->km;
			tabRecup[cpt].jour = calculusDate(ptrtrans->rent->u.value_reserv->begining, ptrtrans->rent->u.value_reserv->end);

			cpt++;
			//realloc to have more space
			tabRecup = realloc(tabRecup, (cpt+1)*sizeof(predict));

			ptrtrans = ptrtrans->suivant;
		}
		*compteur = cpt;
		return tabRecup;
	}
	return 0;
}

/**
 * [errorPrediction  caculus for the error model]
 * @param tabVal
 * @param cpt
 * @return
 */
int errorPrediction(predict *tabVal,int cpt){
		int cptE = 0;
		float error =0;
		predict *tabTrans = tabVal;

		for (int i = 0; i < cpt; i++) {
			for (int j = i; j < cpt; j++) {
				if (tabVal[i].jour == tabTrans[j].jour ) {
						error =  tabVal[i].km / tabTrans[j].km + error;

						cptE++;
						}
			}
		}


		error =	error/cptE;


		return error;
}

/**
 * [milePrediction predict mile for a reservation based on date]
 * @param  ptrTete [Reservation]
 * @param  begin   [date begin]
 * @param  end     [date end]
 * @return         [prediction]
 */
int milePrediction(maillon **ptrTete , date begin, date end){

	maillon *ptrtrans = *ptrTete;
	predict *tabVal = NULL;
	int cpt=0, delayT, error;
	float temp=0, b1=0, b0=0, moyX=0,moyY=0, valP=0;

	tabVal = createTabPrediction(ptrtrans,&cpt);
	delayT = calculusDate(begin,end);

	//moyenne empirique
	for (int h = 0; h < cpt; h++) {
		moyX = tabVal[h].jour+moyX;
		moyY = tabVal[h].km+moyY;

	}
	moyX = (1/cpt)*moyX;
	moyY = (1/cpt)*moyY;

	//calculus of the coeff like b1X +b0
	for (int i = 0; i < cpt; i++) {

			b1 = (tabVal[i].km-moyY)*(tabVal[i].jour-moyX) +b1;
			temp = (tabVal[i].jour-moyX)*(tabVal[i].jour-moyX) + temp;

	}
	b1 = b1/temp;
	b0 = moyY - (b1*moyX);
	error = errorPrediction(tabVal,cpt);
	printf("Erreur: %d\n",error );
	//using the function to calculate a prediction
	valP = b1*delayT +b0 + error;

	free(tabVal);

	return valP;

}
