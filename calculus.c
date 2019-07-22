#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "calculus.h"
#include "chained_list.h"

//const price for a daily rent per categories
const float pA  = 64.98, pB = 108.98, pC = 178.98;

/**
 * [actualDate give the local date in a structure date]
 * @return [date]
 */
date actualDate(){
	//define a t at cpu time
	time_t secondes;
	struct tm instant;
	date actual;
	time(&secondes);
	instant=*localtime(&secondes);
	actual.day = instant.tm_mday+1;
	actual.month = instant.tm_mon+1;
	actual.year = instant.tm_year+1900;
	actual.hour = instant.tm_hour+1;
	return actual;


}

/**
 * [isCarFree check if a car is free]
 * @param  ptrtete [history]
 * @return         [0 car free , 1 car is reserv]
 */
int isCarFree(history *ptrtete){

	history *ptrtrans = ptrtete;
	bool cmpB, cmpE;
	date actual = actualDate();


		while(ptrtrans != NULL && ptrtrans->reserv->number != NULL){
			cmpB = dateCompare(ptrtrans->reserv->begining, actual);
			cmpE = dateCompare(ptrtrans->reserv->end, actual);

			if (cmpE == false && cmpB == true){
				return 1;
			}else{
				ptrtrans = ptrtrans->suivant;
			}


		}

	return 0;

}

/**
 * [checkRentPrice calculus price rent]
 * @param  constClass [float]
 * @param  nbday      [int]
 * @return            [float]
 */
float checkRentPrice(float constClass, int nbday){
	float price;
				printf("%d\n", nbday );
				if (nbday == 1){

					price = constClass;
				}else if( nbday >= 2 && nbday < 7){

					price = nbday * (constClass - (constClass*10)/100);

				}else if (nbday >= 7 && nbday < 30){

					price = nbday *(constClass - (constClass*30)/100);

				}else if (nbday >= 30 && nbday < 365){

					price =nbday *( constClass - (constClass*50)/100);

				}else if (nbday >= 365){

					price = nbday *(constClass - (constClass*60)/100);

				}

			printf("Prix par jour: %f\n",price/nbday );

	return price;

}

/**
 * [calculusDate calculus of days between two dates]
 * @param  begining [date]
 * @param  end      [date]
 * @return          [int]
 */
int calculusDate(date begining, date end){
	int nbday;
	struct tm d1 = {0};
   	struct tm d2 = {0};
   	d1.tm_mday = begining.day;
   	d1.tm_mon  = begining.month - 1;
   	d1.tm_year = begining.year - 1900;
   	d1.tm_hour = begining.hour-1;

   	d2.tm_mday = end.day;
   	d2.tm_mon  = end.month - 1;
   	d2.tm_year = end.year - 1900;
  	d2.tm_hour = end.hour-1;


   	nbday = difftime(mktime(&d2), mktime(&d1)) / 86400;

	return nbday;
}

/**
 * [delayTime Check if the rental time has been delayed,]
 * @param  Car_reserv [reservation]
 * @return            [the days of delayed , return 0 if it hasn't been delayed]
 */
int delayTime(reservation *Car_reserv){

	date today = actualDate();
	int delayedDays =  calculusDate(Car_reserv->end, today);

	if(delayedDays > 0){

		return delayedDays;

	}else{

		return 0;
	}
}

/**
 * [dailyPrice give the daily Price for a car Category]
 * @param  category [char]
 * @return          [float]
 */
float dailyPrice(char category){
	float price;

	switch(category){

		case 'A':
			price = pA;
		break;

		case 'B':
			price = pB;
		break;

		case 'C':
			price = pC;
		break;
	}

	return price;
}

/**
 * [rentalPrice return the price to rent a car depend on the day number]
 * @param  val        [car]
 * @param  Car_reserv [reservation]
 * @return            [float]
 */
float rentalPrice(data *val, reservation* Car_reserv){
	float price;
	int nbday;
	nbday = calculusDate(Car_reserv->begining, Car_reserv->end);

	if((val->typ_val) == 0){

		//management for upgrading classe
		//check if the car given is superior of the car reserved in this case we give the price of what he asked for

		if (val->u.value_car->category > Car_reserv->category){

			switch(Car_reserv->category){

			case 'A':

				price =  checkRentPrice(pA,nbday);
			break;
			case 'B':
				price =  checkRentPrice(pB,nbday);
			break;
			case 'C':
				price =  checkRentPrice(pC,nbday);
			break;
		}



		}else{


			switch(val->u.value_car->category){
			case 'A':

				price =  checkRentPrice(pA,nbday);
			break;
			case 'B':
				price =  checkRentPrice(pB,nbday);
			break;
			case 'C':
				price =  checkRentPrice(pC,nbday);
			break;


		}

		}

	}
	else{
		printf("It's not a car!\n");
		return 0;
	}

	return price;
}

/**
 * [sellingCar give a price for selling a car]
 * @param  val [take a data]
 * @return int [price of a car]
 */
float sellingCar(data *val){
	float prix = 0;
	int annee;
	date actual = actualDate();

	if (val->typ_val == 0)
	{

		annee = actual.year - val->u.value_car->car_year;

		switch(val->u.value_car->category){

			case 'A':

					if (annee == 1){
						prix = val->u.value_car->price - (val->u.value_car->price*30)/100;

					}else if (annee == 2 && annee == 3){

						prix = val->u.value_car->price - (val->u.value_car->price*15)/100;

					}else if (annee >= 3 && annee < 11){

						prix = val->u.value_car->price - (val->u.value_car->price*(12-annee))/100;
					}
					else if (annee >= 11){

						prix = val->u.value_car->price - (val->u.value_car->price*(2))/100;

					}

			break;

			case 'B':
				if (annee == 1){
						prix = val->u.value_car->price - (val->u.value_car->price*25)/100;

					}else if (annee == 2 && annee == 3){

						prix = val->u.value_car->price - (val->u.value_car->price*15)/100;

					}else if (annee >= 3 && annee < 11){

						prix = val->u.value_car->price - (val->u.value_car->price*(12-annee))/100;
					}
					else if (annee >= 11){

						prix = val->u.value_car->price - (val->u.value_car->price*(2))/100;

					}
			break;

			case 'C':
				if (annee == 1){
						prix = val->u.value_car->price - (val->u.value_car->price*20)/100;

					}else if (annee == 2 && annee == 3){

						prix = val->u.value_car->price - (val->u.value_car->price*15)/100;

					}else if (annee >= 3 && annee < 11){

						prix = val->u.value_car->price - (val->u.value_car->price*(12-annee))/100;
					}
					else if (annee >= 11){

						prix = val->u.value_car->price - (val->u.value_car->price*(2))/100;

					}
			break;

		}

		return prix;

	}else{
		printf("It's not a car!\n");
		return 0;
	}

}
