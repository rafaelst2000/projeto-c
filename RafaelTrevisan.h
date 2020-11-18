typedef struct
{
  char name[255];         //nome do destino
  double distance;        //distancia total da viagem (em KM)
  double gasolineAvg;     //media de gasolina calculado dinamicamente (em litros)
  double hydration;       //quantidade de agua e/ou gatorade (em litros)
  double energy;          //quantidade de energetico (em litros)
  int restAvg;            //numero de paradas que deverão ser feitas
  double restDistance;    //kilometragem de cada parada
  int numPeople;          //numero de pessoas que vao na viagem
  int willRain;           //boolean para saber se deve levar roupa de chuva
  int numDays;            //numero de dias de viagem
  double *distancePerDay; //distancia a ser percorrida por dia
  double minTemp;         //temperatura mais fria dentre os dias
  char upperDress[255];
  char lowerDress[255];
  char footDress[255];
  char handDress[255];

} Trip;

#define true 1
#define false 0

void getData(Trip *trip);
void printMotorcycle();
void createTripReport(Trip trip);
double distancePerDayDynamically(int pos);
char *getUpperClothes(double minTemp, int willRain);
char *getLowerClothes(double minTemp);
char *getFootClothes(double minTemp, int willRain);
char *getHandClothes(double minTemp, int willRain);

void testeProg(Trip *trip);