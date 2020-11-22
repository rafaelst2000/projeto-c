#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include "RafaelTrevisan.h"


void main(){
  double gasoPrice;
  Trip trip;
  setlocale(LC_ALL, "Portuguese");
  printMotorcycle();
  gasoPrice = getGasoPrice();
  getData(&trip, gasoPrice);
  testeProg(trip);
  createTripReport(trip);
}
