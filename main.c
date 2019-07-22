#include <stdlib.h>
#include <stdio.h>
#include "calculus.h"
#include "chained_list.h"
#include "initialize.h"
#include "smartFunctions.h"

int mainList(int argc, char const *argv[])
{
    maillon *car, *customers, *reservation, *resultcar;
    customers = initializeClients("files/clients.csv");
    reservation = initializeReservation("files/booking.csv", customers);
    car = initializeCar("files/vehicules.csv", reservation);

/*
    float price;
    price = rentalPrice(car->rent, car->rent->u.value_car->history_rent->reserv);
    printf("Rental Price: %f $\n",price);

    int days;
    days = delayTime(car->rent->u.value_car->history_rent->reserv);
    printf("Delayed Days: %d\n", days );

    int upgraded;
    resultcar = searchCar(car, car->rent->u.value_car->history_rent->reserv, &upgraded);
    printf("The car is: %d\n",upgraded );
    printf("Model: %s\n", resultcar->rent->u.value_car->brand_name );

*/
    int prediction;
    date d,e;
    d.day = 3;
    d.year = 2019;
    d.month = 10;
    d.hour = 9;

    e.day = 23;
    e.year = 2019;
    e.month = 10;
    e.hour = 9;
    prediction = milePrediction(&reservation , d, e);
    int h;
    h = calculusDate(d,e);
    printf("Prediction %d pour %d jours \n", prediction ,h);

    //saveData(customers);
    //saveData(car);
	return 0;
}
