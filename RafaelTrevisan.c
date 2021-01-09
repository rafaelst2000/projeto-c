#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include "RafaelTrevisan.h"

/* utils */

int selectMenu(){
  int i;
  printMotorcycle();
  printf("Seja bem vindo! Em que posso ajudar?\n");
  printf("1 - Nova Simulação\n");
  printf("2 - Ver dados anteriores\n");
  printf("0 - Sair\n");
  printf("R: ");
  scanf("%d", &i);
  while(i < 0 || i > 2){
    printf("Comando inválido, digite novamente!\n");
    printf("R: ");
    scanf("%d", &i);
  }
  return i;
}

double getGasoPrice(){
  double gas;
  printf("\n----------Monte sua viagem!---------\n\n");
  printf("Qual o preço da gasolina no momento?\n");
  printf("R: ");
  scanf("%lf", &gas);
  while(gas <= 0 ){
    printf("Digite novamente o preço.\nR: R$");
    scanf("%lf",&gas);
  }
  return gas;
}

void createTripReport(Trip trip){
  FILE *arq;
  int i;

  if ((arq = fopen("trip.txt","a+")) == NULL) {
    printf("Erro na criação do arquivo\n"); 
  }
  fprintf(arq,"-------Dados da viagem -------\n");
  fprintf(arq,"Nome: %s", trip.name);
  fprintf(arq,"Distância: %.2lf\n Kms", trip.distance);
  fprintf(arq,"Número de paradas: %d\n", trip.restSum);
  fprintf(arq,"Número de dias: %d\n", trip.numDays);
  fprintf(arq, "Kms de cada dia:\n");
  for(i=0;i<trip.numDays;i++){
    fprintf(arq, "Dia %d: %.2lf Kms\n",i+1, trip.distancePerDay[i]);
  }
  fprintf(arq,"Saída: %s\n", trip.leavingDate);
  fprintf(arq,"Chegada: %s\n", trip.arrivingDate);
  fprintf(arq,"Temperatura mais fria: %.1lfºC\n", trip.minTemp);
  fprintf(arq, "Vai chover? %s\n", getRain(trip.willRain));
  fprintf(arq, "Consumo da moto: %.2lfKm/l\n", trip.gasolineAvg);
  fprintf(arq,"Alimentação: %s\n", trip.food);
  fprintf(arq, "Total de gastos: R$%.2lf\n", trip.totalMoney);
  fprintf(arq,"\n----- Vestuário ------\n");
  fprintf(arq,"Superior: %s\n", trip.upperClothes);
  fprintf(arq,"Inferior: %s\n", trip.lowerClothes);
  fprintf(arq,"Mãos: %s\n", trip.handClothes);
  fprintf(arq,"Pés: %s\n", trip.footClothes);
  fprintf(arq,"----------------------------\n");
  fclose (arq);
}

void readReport(){
  FILE *arq;
  char info[255];

  if ((arq = fopen("trip.txt","r")) == NULL) {
    printf("Erro na criação do arquivo\n"); 
  }
  while( (fgets(info, sizeof(info), arq))!=NULL ){
   printf("%s", info);
  }
  fclose(arq);
}

/* functions */

void getData(Trip *trip, double gasoPrice){
  int i;
  double sum;
  printf("\nQual o destino?\n");
  printf("R: ");
  while ((getchar()) != '\n'); //gambiarra da net pro fgets nao bugar após o scanf
  fgets(trip->name, 255, stdin); 

  printf("\nQual a distância total?\n");
  printf("R: ");
  scanf("%lf", &trip->distance);
  while(trip->distance <= 0 ){
    printf("Digite novamente a distância total: ");
    scanf("%lf",&trip->distance);
  }

  printf("\nQual a quantidade de dias?\n");
  printf("R: ");
  scanf("%d", &trip->numDays);
  while(trip->numDays <= 0 ){
    printf("Digite novamente a quantidade de dias: ");
    scanf("%d",&trip->numDays);
  }
  
  trip->distancePerDay = (double *) malloc(trip->numDays * sizeof(double));

  getDate(trip);

  if(trip->numDays > 1){
    printf("\nQual a distância entre cada dia?\n");
    recursiveDistancePerDayDynamically(0, trip->numDays, trip);
  }else{
    trip->distancePerDay[0] = trip->distance;
  }
  averageGasoline(trip, gasoPrice);

  strcpy(trip->food, getFood(trip));

  printf("\nVai chover? \n1 - Sim \n0 - Não\n");
  printf("R: ");
  scanf("%d", &trip->willRain);
  while(trip->willRain != 1 && trip->willRain != 0){
    printf("%d\n\n",trip->willRain);
    printf("Digite novamente.\n");
    printf("R: ");
    scanf("%d", &trip->willRain);
  }

  printf("\nDigite a menor temperatura dentre os dias.\n");
  printf("R: ");
  scanf("%lf", &trip->minTemp);

  printf("\nVocê tem roupa adequada para motociclismo?\n");
  printf("1 - Sim\n");
  printf("0 - Não\n");
  printf("R: ");
  scanf("%d", &trip->userHasMotorcycleClothes);
  while(trip->userHasMotorcycleClothes != 1 && trip->userHasMotorcycleClothes != 0){
    printf("Digite novamente.\n");
    printf("R: ");
    scanf("%d", &trip->willRain);
  }

  strcpy(trip->upperClothes, getUpperClothes(trip->minTemp, trip->willRain, trip->userHasMotorcycleClothes));
  strcpy(trip->lowerClothes, getLowerClothes(trip->minTemp, trip->userHasMotorcycleClothes));
  strcpy(trip->handClothes, getHandClothes(trip->minTemp, trip->willRain));
  strcpy(trip->footClothes, getFootClothes(trip->minTemp, trip->willRain, trip->userHasMotorcycleClothes)); 

  getRestSum(trip);
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
  printf("\nQual o consumo da sua moto em Km/l ?\n");
  printf("R: ");
  scanf("%lf",&cons);
  while(cons <= 0){
    printf("Digite novamente o consumo da moto: ");
    scanf("%lf", &cons);
  }
  trip->totalMoney = trip->distance/cons*gasoPrice;
  trip->gasolineAvg = cons;
}

void getDate(Trip *trip){
  int d,m,a,dC,mC,aC;
  char date[15];
  printf("------- Data -------\n");
  printf("Dia: ");
  scanf("%d", &d);
  while(d<0 || d>31){
    printf("Digite novamente o dia: ");
    scanf("%d", &d);
  }
  printf("Mes: ");
  scanf("%d", &m);
  while(m<0 || m>12){
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
  dC--;
  if(dC == 0){
    dC = 31;
    mC--;
    if(mC == 0){
      mC = 12;
      aC--;
    }
  }
  sprintf(date, "%d/%d/%d", dC,mC,aC);
  strcpy(trip->arrivingDate, date);
}

char *getFood(Trip *trip){
  int i;
  printf("\n*Lembre-se de levar o mínimo o possível para economizar espaço, \n");
  printf("além de fazer paradas regularmente para se hidratar e alongar.\n");
  printf("É recomendável comer algo a cada 2 ou 3 horas. ");
  printf("Se você fizer refeições em restaurantes,\nopte por alimentos leves como legumes e carne de frango,\n");
  printf("já que estes podem evitar o sono por necessitarem de menos energia na digestão*\n\n");
  if(trip->distance < 150){
    return "Não é necessário levar comida";
  }else if(trip->distance >= 150 && trip->distance <250){
    for(i=0;i<trip->numDays;i++){
      trip->totalMoney += 1.5; //cerca de uma ou duas barras ou frutas por dia
    }
    return "Barras de Cereal ou Frutas Secas";
  }else{
    for(i=0;i<trip->numDays;i++){
      trip->totalMoney += 51.5; //duas refeições de R$25 + 2 frutas ou barras;
    }
    return "Barras de Cereal ou Frutas Secas + Refeições em restaurantes";
  }
}

void getRestSum(Trip *trip){
  trip->restSum = 0;
  int i,aux;
  double tes;

  if((int) trip->distance % 90 == 0){
    trip->restSum = ((int) trip->distance/90) - 1; 
  }else{
    for(i=0;i<trip->numDays;i++){
      aux = (int) trip->distance/90;
      trip->restSum += aux; //uma parada a cada cerca de 90km
    }
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
  printf("Nome: %s", trip.name);
  printf("Distância: %.2lf\n Kms", trip.distance);
  printf("Número de paradas: %d\n", trip.restSum);
  printf("Número de dias: %d\n", trip.numDays);
  printf( "Kms de cada dia:\n");
  for(i=0;i<trip.numDays;i++){
     printf( "Dia %d: %.2lf Kms\n",i+1, trip.distancePerDay[i]);
  }
  printf("Alimentação: %s\n", trip.food);
  printf("Vai chover? %s\n", getRain(trip.willRain));
  printf("Consumo da moto: %.2lfKm/l\n", trip.gasolineAvg);
  printf("Temperatura mais fria: %.1lfºC\n", trip.minTemp);
  printf("Saída: %s\n", trip.leavingDate);
  printf("Chegada: %s\n", trip.arrivingDate);
  printf( "Total de gastos: R$%.2lf\n", trip.totalMoney);
  printf("\n----- Vestuário ------\n");
  printf("Superior: %s\n", trip.upperClothes);
  printf("Inferior: %s\n", trip.lowerClothes);
  printf("Mãos: %s\n", trip.handClothes);
  printf("Pés: %s\n", trip.footClothes);
  printf("----------------------------\n");
}

char *getRain(int willRain){
  if(willRain == true){
    return "Sim";
  }else{
    return "Não";
  }
}

/* Vestuário */

char *getUpperClothes(double minTemp, int willRain, int userHasMotorcycleClothes){
  if(userHasMotorcycleClothes == true){
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
  }else{
    if(willRain == true){
      if(minTemp < 15){
        return "Camiseta manga longa + blusão de lã + Jaqueta de Couro + Capa de chuva";
      }
      else if(minTemp > 15 && minTemp < 23){
        return "Camiseta manga longa + Jaqueta de Couro + Capa de chuva";
      }else{
        return "Camiseta manga curta + Jaqueta de Couro + Capa de chuva";
      }
    }
    else{
      if(minTemp < 15){
        return "Camiseta manga longa + blusão de lã + Jaqueta de Couro + Capa de chuva";
      }
      else if(minTemp > 15 && minTemp < 23){
        return "Camiseta manga longa + Jaqueta de Couro";
      }else{
        return "Camiseta manga curta + Jaqueta de Couro + Capa de chuva";
      }
    }
  }
    
}

char *getLowerClothes(double minTemp, int userHasMotorcycleClothes){
  if(userHasMotorcycleClothes == true){
    if(minTemp < 15){
      return "Segunda pele de inverno + Calça de Cordura c/forro";
    }
    else if(minTemp > 15 && minTemp < 23){
      return "Calça de Cordura c/forro";
    }else{
      return "Calça de Cordura s/forro";
    }  
  }else{
    if(minTemp < 15){
      return "Pijama + Calça Jeans";
    }else{
      return "Calça Jeans";
    } 
  }
}

char *getFootClothes(double minTemp, int willRain, int userHasMotorcycleClothes){
  if(userHasMotorcycleClothes == true){
    if(willRain == true){
      return "Botas para chuva";
    }else{
      if(minTemp < 23){
        return "Botas para Motociclista";
      }else{
        return "Coturno para Motociclista";
      }
    }
  }else{
    if(willRain == true){
      return "Botas para chuva";
    }else{
      return "Calçado fechado";
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