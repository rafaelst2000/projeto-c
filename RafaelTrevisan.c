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
  while ((getchar()) != '\n'); //gambiarra da net pro fgets nao bugar após o scanf
  fgets(trip->name, 255, stdin); 

  printf("Qual a distância total?\n");
  printf("R: ");
  scanf("%lf", &trip->distance);

  printf("Qual a quantidade de dias?\n");
  printf("R: ");
  scanf("%d", &trip->numDays);

  trip->distancePerDay = (double *) malloc(trip->numDays * sizeof(double));
  getDate(trip);
  if(trip->numDays > 1){
    printf("Qual a distância entre cada dia?\n");
  }

  recursiveDistancePerDayDynamically(0, trip->numDays, trip);
  averageGasoline(trip, gasoPrice);

  strcpy(trip->food, getFood(trip));

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

/* double distancePerDayDynamically(int pos){
  double value;
  printf("Dia %d: ",pos+1);
  scanf("%lf", &value); 
  return value;
} */

void recursiveDistancePerDayDynamically(int pos, int tamanho, Trip *trip){
  if(pos != tamanho){
    printf("Dia %d: ", pos+1);
    scanf("%lf", &trip->distancePerDay[pos]);
    pos++;
    recursiveDistancePerDayDynamically(pos, tamanho, trip);
  }
}

void averageGasoline(Trip *trip, double gasoPrice){
  double cons;
  printf("Qual o consumo da sua moto em Km/l ?\n");
  printf("R: ");
  scanf("%lf",&cons);
  trip->totalMoney = trip->distance/cons*gasoPrice;
  trip->gasolineAvg = cons;
}

void getDate(Trip *trip){
  int d,m,a,dC,mC,aC;
  char date[15];
  printf("------- Data -------\n");
  printf("---- DD/MM/AAAA ----\n");
  printf("Dia: ");
  scanf("%d", &d);
    while(d<0 && d>31){
      printf("Digite novamente o dia: ");
      scanf("%d", &d);
    }
  printf("Mes: ");
  scanf("%d", &m);
    while(d<0 && d>12){
      printf("Digite novamente o mes: ");
      scanf("%d", &m);
    }
  printf("Ano: ");
  scanf("%d", &a);
    while(a<2020){
      printf("Digite novamente o ano: ");
      scanf("%d", &a);
    }
  sprintf(date, "%d/%d/%d", d,m,a);
  strcpy(trip->leavingDate, date);
  strcpy(date, "");
  dC = d + trip->numDays;
  mC = m;
  aC = a;
  while(dC > 31){  
    dC = dC - 31;
    mC++;
  }
  while(mC > 12){  
    mC = mC - 12;
    aC++;
  }
  sprintf(date, "%d/%d/%d", dC,mC,aC);
  strcpy(trip->arrivingDate, date);
}

char *getFood(Trip *trip){
  int i;
  printf("\n*Lembre-se de levar o mínimo o possível para economizar espaço, \n");
  printf("além de fazer paradas regularmente para se hidratar e alongar.\n");
  printf("É recomendável comer algo a cada 2 ou 3 horas.");
  printf("Se você fizer refeições em restaurantes, opte por alimentos leves como legumes e carne de frango,\n");
  printf("Já que estes podem evitar o sono por necessitarem de menos energia na digestão\n");
  if(trip->distance < 150){
    return "Não é necessário levar comida";
  }else if(trip->distance >= 150 && trip->distance <250){
    for(i=0;i<trip->numDays;i++){
      trip->totalMoney += 1;
    }
    return "Barras de Cereal ou Frutas Secas";
  }else{
    for(i=0;i<trip->numDays;i++){
      trip->totalMoney += 61;
    }
    return "Barras de Cereal ou Frutas Secas + Refeições em restaurantes";
  }
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

/* Vestuário */

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