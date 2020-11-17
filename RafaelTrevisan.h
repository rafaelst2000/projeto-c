typedef struct
{
  char name[255];         //nome do destino
  double distance;        //distancia total da viagem (em KM)
  double gasolineAvg;     //media de gasolina calculado dinamicamente (em litros)
  double hydration;       //quantidade de agua e/ou gatorade (em litros)
  double energy;          //quantidade de energetico (em litros)
  int restAvg;            //numero de paradas que deverão ser feitas
  double restDistance;    //kilometragem de cada parada
  int numMotos;           //numero de motos
  int numPeople;          //numero de pessoas que vao na viagem
  int willRain;           //para saber se deve levar roupa de chuva
  int numDays;            //numero de dias de viagem
  double *distancePerDay; //distancia a ser percorrida por dia

} Trip;

#define true 1
#define false 0

void getData(Trip *trip);
void printMotorcycle();
void createTripReport(Trip trip);
double distancePerDayDynamically(int pos);

void testeProg(Trip *trip);