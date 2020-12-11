typedef struct{
  char name[255];         //nome do destino
  double distance;        //distancia total da viagem (em KM)
  double gasolineAvg;     //consumo da moto
  double hydration;       //quantidade de agua (em litros)
  int restAvg;            //numero de paradas que deverão ser feitas
  double restDistance;    //kilometragem de cada parada
  int numPeople;          //numero de pessoas que vao na viagem
  int willRain;           //boolean para saber se deve levar roupa de chuva
  int numDays;            //numero de dias de viagem
  double *distancePerDay; //distancia a ser percorrida por dia
  double minTemp;         //temperatura mais fria dentre os dias
  double totalMoney;      //Total de gastos

  char upperClothes[255]; //roupas
  char lowerClothes[255];
  char footClothes[255];
  char handClothes[255];

  char leavingDate[255];
  char arrivingDate[255];

} Trip;

#define true 1
#define false 0

void getData(Trip *trip, double gasoPrice);
void createTripReport(Trip trip);
double distancePerDayDynamically(int pos);
char *getUpperClothes(double minTemp, int willRain);
char *getLowerClothes(double minTemp);
char *getFootClothes(double minTemp, int willRain);
char *getHandClothes(double minTemp, int willRain);
char *getRain(int willRain);
void averageGasoline(Trip *trip, double gasoPrice);
double getGasoPrice();
void recursiveDistancePerDayDynamically(int pos, int tamanho, Trip *trip);
void getDate(Trip *trip);

void printMotorcycle();
void testeProg(Trip trip);