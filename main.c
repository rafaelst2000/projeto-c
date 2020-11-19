#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include "RafaelTrevisan.h"


void main(){
  Trip trip;
  setlocale(LC_ALL, "Portuguese");
  printMotorcycle();
  getData(&trip);
  testeProg(&trip);
  createTripReport(trip);

















/*   strcpy(trip.name, "Viagem 1");
  trip.distance = 300.50;
  trip.gasolineAvg = 10.5; 
  createTripReport(trip);*/
}
