#include "Dimmer.h"

Dimmer dimmer(3, DIMMER_NORMAL);

int lampada = 0; // 0 a 100

void setup() 
{
  //inicializa porta serial
  Serial.begin(115200);
  dimmer.begin();
}

void loop() 
{
  leSerial();
  dimmer.set(lampada);
  delay(150);
}

long int lenumero(char caracter)
{
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
void leSerial()
{
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
      lampada = lenumero(ch);
      break;
    } // Fim do switch
  } // Fim da leitura serial
}