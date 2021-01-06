#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include "RafaelTrevisan.h"
#include <windows.h>


void main(){
  int res;
  UINT CPAGE_UTF8 = 65001;
  UINT CPAGE_DEFAULT = GetConsoleOutputCP();
  SetConsoleOutputCP(CPAGE_UTF8); //setando portugues no windows | talvez não funcione no linux

  double gasoPrice;
  Trip trip;

  res = selectMenu();
  if(res == 1){
    gasoPrice = getGasoPrice();
    getData(&trip, gasoPrice);
    testeProg(trip);
    createTripReport(trip);
  }
  if(res == 2){
    readReport(); 
  }else{
    exit(0);
  }

}
