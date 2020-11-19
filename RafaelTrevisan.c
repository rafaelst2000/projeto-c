#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include "RafaelTrevisan.h"

/* utils */

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
  fprintf(arq,"\n----- Vestuário ------\n");
  fprintf(arq,"Superior: %s\n", trip.upperClothes);
  fprintf(arq,"Inferior: %s\n", trip.lowerClothes);
  fprintf(arq,"Mãos: %s\n", trip.handClothes);
  fprintf(arq,"Pés: %s\n", trip.footClothes);
  fclose (arq);
}

/* functions */

void getData(Trip *trip){
  int i;
  double sum;
  printf("Monte sua viagem!\n");
  printf("Digite o nome do destino: ");
  fgets(trip->name, 255, stdin);

  printf("Digite a distância total: ");
  scanf("%lf", &trip->distance);

  printf("Digite a quantidade de dias: ");
  scanf("%d", &trip->numDays);

  trip->distancePerDay = (double *) malloc(trip->numDays * sizeof(double));

  printf("Digite a distância de cada dia: \n\n");
  for(i=0; i<trip->numDays-1; i++){
    trip->distancePerDay[i] = distancePerDayDynamically(i);
    sum += trip->distancePerDay[i];
  }
  trip->distancePerDay[trip->numDays - 1] = trip->distance - sum;

  printf("Vai chover? 1- Sim | 0 - Não");
  scanf("%d", &trip->willRain);

  printf("Digite a menor temperatura dentre os dias: ");
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

void testeProg(Trip *trip){
  int i;
  printf("\n\n");
  printf("Nome: %s\n", trip->name);
  printf("Distancia: %.2f\n", trip->distance);
  printf("Quant dias: %d\n", trip->numDays);
  printf("Km de cada dia: ");
  for(i=0;i<trip->numDays; i++){
    printf("%.2f - ", trip->distancePerDay[i]);
  }
  printf("\n------- Roupas --------\n");
  printf("Superior: %s\n",trip->upperClothes);
  printf("Inferior: %s\n",trip->lowerClothes);
  printf("Luvas: %s\n",trip->handClothes);
  printf("Calçados: %s\n",trip->footClothes);
  printf("\n");
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