#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include "RafaelTrevisan.h"

/* utils */

double getGasoPrice(){
  double gas;
  printf("Qual o preço da gasolina no momento?\n");
  printf("R: ");
  scanf("%lf", &gas);
  return gas;
}

void createTripReport(Trip trip){
  FILE *arq;
  int i;

  if ((arq = fopen("trip.txt","a+")) == NULL) {
    printf("Erro na criação do arquivo\n"); 
  }
  fprintf(arq,"-------Dados da viagem-------\n");
  fprintf(arq,"Nome: %s\n", trip.name);
  fprintf(arq,"Distância: %.2lf\n", trip.distance);
  fprintf(arq,"Número de dias: %d\n", trip.numDays);
  fprintf(arq, "Kms de cada dia:\n");
  for(i=0;i<trip.numDays;i++){
     fprintf(arq, "Dia %d: %.2lf Kms\n",i+1, trip.distancePerDay[i]);
  }
  fprintf(arq, "Vai chover? %s\n", getRain(trip.willRain));
  fprintf(arq, "Consumo da moto: %.2lfKm/l\n", trip.gasolineAvg);
  fprintf(arq, "Total de gastos: R$%.2lf\n", trip.totalMoney);
  fprintf(arq,"\n----- Vestuário ------\n");
  fprintf(arq,"Superior: %s\n", trip.upperClothes);
  fprintf(arq,"Inferior: %s\n", trip.lowerClothes);
  fprintf(arq,"Mãos: %s\n", trip.handClothes);
  fprintf(arq,"Pés: %s\n", trip.footClothes);
  fclose (arq);
}

/* functions */

void getData(Trip *trip, double gasoPrice){
  int i;
  double sum;
  printf("\n----------Monte sua viagem!---------\n\n");
  printf("Qual o destino?\n");
  printf("R: ");
  scanf("%s", trip->name);
  fflush(stdin);
  /* fgets(trip->name, 255, stdin); */

   printf("Qual a distância total?\n");
  printf("R: ");
  scanf("%lf", &trip->distance);

  printf("Qual a quantidade de dias?\n");
  printf("R: ");
  scanf("%d", &trip->numDays);

  trip->distancePerDay = (double *) malloc(trip->numDays * sizeof(double));

  printf("Qual a distância entre cada dia?\n");
  for(i=0; i<trip->numDays-1; i++){
    trip->distancePerDay[i] = distancePerDayDynamically(i);
    sum += trip->distancePerDay[i];
  }
  trip->distancePerDay[trip->numDays - 1] = trip->distance - sum;

  averageGasoline(trip, gasoPrice);

  printf("Vai chover? 1- Sim | 0 - Não\n");
  printf("R: ");
  scanf("%d", &trip->willRain);

  printf("Digite a menor temperatura dentre os dias.\n");
  printf("R: ");
  scanf("%lf", &trip->minTemp);

  strcpy(trip->upperClothes, getUpperClothes(trip->minTemp, trip->willRain));
  strcpy(trip->lowerClothes, getLowerClothes(trip->minTemp));
  strcpy(trip->handClothes, getHandClothes(trip->minTemp, trip->willRain));
  strcpy(trip->footClothes, getFootClothes(trip->minTemp, trip->willRain)); 
}

double distancePerDayDynamically(int pos){
  double value;
  printf("Dia %d: ",pos+1);
  scanf("%lf", &value); 
  return value;
}

void averageGasoline(Trip *trip, double gasoPrice){
  double cons;
  printf("Qual o consumo da sua moto em Km/l ?\n");
  printf("R: ");
  scanf("%lf",&cons);
  trip->totalMoney = trip->distance/cons*gasoPrice;
  trip->gasolineAvg = cons;
  
}

/* miscellaneous */
void printMotorcycle(){
  printf("\n\n");
  printf("                  . ---- .~%c%c<|     \n",92,92);
  printf(" /~ ~ ~ ~%c-------/        |~%c%c          \n", 92,92,92);
  printf("|_.------.______/_%c______/ / %c%c _ _\n", 92,92,92);
  printf("/   - -// %c    /[_]={==}=%c/  /%c%c- -      \n",92, 92,92,92);
  printf(" /   _// %c %c__/  O  |==| /  // %c%c-   %c  \n", 92,92,92,92,92);
  printf(" |  | *-|--|-%c ( )*__(  )/   |  | * | |\n",92);
  printf(" %c   -  ~/~ ~ ~      ~~      %c   -   /  \n",92,92);
  printf("    - -                         - -     \n");
  printf("\n\n");
}

void testeProg(Trip trip){
  int i;
  printf("-------Dados da viagem-------\n");
  printf("Nome: %s\n", trip.name);
  printf("Distância: %.2lf\n", trip.distance);
  printf("Número de dias: %d\n", trip.numDays);
  printf( "Kms de cada dia:\n");
  for(i=0;i<trip.numDays;i++){
     printf( "Dia %d: %.2lf Kms\n",i+1, trip.distancePerDay[i]);
  }
  printf( "Vai chover? %s\n", getRain(trip.willRain));
  printf( "Consumo da moto: %.2lfKm/l\n", trip.gasolineAvg);
  printf( "Total de gastos: R$%.2lf\n", trip.totalMoney);
  printf("\n----- Vestuário ------\n");
  printf("Superior: %s\n", trip.upperClothes);
  printf("Inferior: %s\n", trip.lowerClothes);
  printf("Mãos: %s\n", trip.handClothes);
  printf("Pés: %s\n", trip.footClothes);
}

char *getRain(int willRain){
  if(willRain == true){
    return "Sim";
  }else{
    return "Não";
  }
}

/* Montando a roupa */

char *getUpperClothes(double minTemp, int willRain){
    if(willRain == true){
      if(minTemp < 15){
        return "Segunda pele de inverno + Jaqueta de Cordura c/forro + Capa de chuva";
      }
      else if(minTemp > 15 && minTemp < 23){
        return "Segunda pele de inverno + Jaqueta de Cordura s/forro + Capa de chuva";
      }else{
        return "Segunda pele de verao + Jaqueta de Cordura s/forro + Capa de chuva";
      }
    }
    else{
      if(minTemp < 15){
        return "Segunda pele de inverno + Jaqueta de Cordura c/forro";
      }
      else if(minTemp > 15 && minTemp < 23){
        return "Segunda pele de inverno + Jaqueta de Cordura s/forro";
      }else{
        return "Segunda pele de verao + Jaqueta de Cordura s/forro";
      }
    }
}

char *getLowerClothes(double minTemp){
  if(minTemp < 15){
    return "Segunda pele de inverno + Calça de Cordura c/forro";
  }
  else if(minTemp > 15 && minTemp < 23){
    return "Calça de Cordura c/forro";
  }else{
    return "Calça de Cordura s/forro";
  }  
}

char *getFootClothes(double minTemp, int willRain){
  if(willRain == true){
    return "Botas para chuva";
  }else{
    if(minTemp < 23){
      return "Botas para Motociclista";
    }else{
      return "Coturno para Motociclista";
    }
  }
}

char *getHandClothes(double minTemp, int willRain){
  if(willRain == true){
    if(minTemp < 23){
      return "Luvas para frio impermeáveis";
    }else{
      return "Luvas de verão impermeáveis";
    }
  }else{
    if(minTemp < 23){
      return "Luvas para frio";
    }else{
      return "Luvas de verão";
    }
  }
}