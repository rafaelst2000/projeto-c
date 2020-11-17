#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include "RafaelTrevisan.h"

/* utils */

void createTripReport(Trip trip){
  FILE *arqS;

  if ((arqS = fopen("trip.txt","a+")) == NULL) {
    printf("Erro na criação do arquivo\n"); 
  }
  fprintf(arqS,"------ Relatório do passeio------\nNome: %s\nMédia de Gasolina: %.2f\nDistância total: %.2f\n---------------------------------\n\n",trip.name, trip.gasolineAvg, trip.distance);
  fclose (arqS);
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
  printf("\n");
}