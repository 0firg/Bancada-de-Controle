#include <OneWire.h>
#include <DallasTemperature.h>


#define DS18B20_OneWire 4
#define amostras 100
OneWire oneWire(DS18B20_OneWire);
DallasTemperature sensortemp(&oneWire);


int i=0,j=0;
float T0,T1,T2,T3,TF,media_T1,media_T2;
float amostras_T1[amostras];
float amostras_T2[amostras];
 
void setup()  {
  Serial.begin(9600);
  sensortemp.begin(); 
  inicializa_m_m();
}
 
void loop() { 
  temperatura();
  delay(50);
}
void inicializa_m_m(){
  sensortemp.requestTemperatures(); 
  T0=(sensortemp.getTempCByIndex(0)+sensortemp.getTempCByIndex(1))/2;  
  for(i=0;i<amostras;i++)
  {
    amostras_T1[i]=T0;
    amostras_T2[i]=T0;   
  }
}
void temperatura(){
  sensortemp.requestTemperatures(); 
  T1 = sensortemp.getTempCByIndex(0);
  T2 = sensortemp.getTempCByIndex(1);
  T3 = (T1+T2)/2;
  media_m();
  TF=(media_T1+media_T2)/2;
  Serial.print("Sensor 1:");
  Serial.println(T1);
  Serial.print("Sensor 2:");
  Serial.println(T2); 
  Serial.print("Sensor 3:");
  Serial.println(T3);
  Serial.print("Sensor F:");
  Serial.println(TF);
  Serial.println("");
}

void media_m(){
  if(j>(amostras-1)){j=0;}
  amostras_T1[j]=T1;
  amostras_T2[j]=T2; 
  media_T1=0;
  media_T2=0; 
  for(i=0;i<amostras;i++)
  {
    media_T1=amostras_T1[i]+media_T1;
    media_T2=amostras_T2[i]+media_T2;  
  }
  media_T1=media_T1/amostras;
  media_T2=media_T2/amostras;  
}
