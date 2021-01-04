#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include "RafaelTrevisan.h"
#include <windows.h>


void main(){
  UINT CPAGE_UTF8 = 65001;
  UINT CPAGE_DEFAULT = GetConsoleOutputCP();
  SetConsoleOutputCP(CPAGE_UTF8); //setando portugues no windows | talvez não funcione no linux

  double gasoPrice;
  Trip trip;

  printMotorcycle();
  gasoPrice = getGasoPrice();
  getData(&trip, gasoPrice);
  testeProg(trip);
  createTripReport(trip);
}
