#include "Dimmer.h"
#include <OneWire.h>
#include <DallasTemperature.h>

#define DS18B20_OneWire 4
#define amostras 10

OneWire oneWire(DS18B20_OneWire);
DallasTemperature sensortemp(&oneWire);
Dimmer dimmer(9, DIMMER_NORMAL);

int i=0,j=0,lampada = 0,lampada_aux=0;;
float T0,T1,T2,TF,media_T1,media_T2;
float amostras_T1[amostras];
float amostras_T2[amostras];
unsigned long tempo_leitura=0;
double erro=0,erro_ant=0,P=0,Integral=0,D=0,setpoint=0,kp=2.6155,ki=0.0027,kd=0,PID=0;

void setup() {
  //inicializa porta serial
  Serial.begin(115200);
  sensortemp.begin(); 
  inicializa_m_m();
  dimmer.begin();
  tempo_leitura=millis();
}

void loop() {

  
  if (millis() - tempo_leitura >= 1000) {
    leSerial();
    temperatura();
    Controlador_PID();

    tempo_leitura=millis(); 

    if (lampada != lampada_aux){
      dimmer.set(lampada); 
      lampada_aux=lampada;
    }
    Serial.print(TF);
    Serial.print(",");
    Serial.print(setpoint);
    Serial.print(",");
    Serial.print(erro);
    Serial.print(",");
    Serial.print(tempo_leitura/1000.00);
    Serial.print(",");
    Serial.println(lampada);

  }

}

long int lenumero(char caracter){
  /*
    Função resonsável por interpredar o que é dígito enviado pela comunicação serial ao arduino e concatená-los
    maneira a formar um número inteiro.
  */
  long int valor = 0;
  int sinal = 1;
  while (caracter != 10)                   // verifica se eh um digito entre 0 e 9
  {
   caracter = Serial.read();
   if (caracter >= '0' && caracter <= '9')  // verifica se eh um digito entre 0 e 9
   valor = (valor * 10) + (caracter - '0'); // se sim, acumula valor
  else if ( caracter == '-')
    sinal = -1;
  else                                     // em caso de nao ser um numero ou simbolo de menos termina o valor
    {
      valor = valor * sinal ;                  // seta a variavel valor com o valor acumulado
      return (valor);
      // valor = 0;                        // reseta valor para 0 para a provima sequencia de digitos
      sinal = 1;
    }
  }
}
void leSerial(){
  // LEITURA DOS DADOS SERIAIS
  if ( Serial.available() > 0)
  {
    char ch = Serial.read();
    switch (ch) 
    {
      case 'r':
      lampada = lenumero(ch); // le o valor de referencia recebido
      break;
      case 'v':
      setpoint = lenumero(ch);
      break;
    } // Fim do switch
  } // Fim da leitura serial
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
  media_m();
  TF=(media_T1+media_T2)/2;
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
  j=j+1;  
}

void Controlador_PID(){
  erro=setpoint-TF;
  P=kp*erro;

  Integral=Integral+(ki*erro);
  if (Integral > (100)) {Integral = (100);}
  if (Integral < (0)) {Integral = 0;}

  D=kd*(erro_ant-erro);


  PID=P+Integral+D;
  erro_ant=erro;
  if (PID > (100)) {PID = (100);}
  if (PID < (0)) {PID = 0;}

  lampada=PID;

}