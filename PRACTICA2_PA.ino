#include <Controllino.h>
const int ledPins[] = { //declaracion de leds
  CONTROLLINO_D0,
  CONTROLLINO_D6,
  CONTROLLINO_D12,
  CONTROLLINO_D13,
  CONTROLLINO_D14,
  CONTROLLINO_D8,
  CONTROLLINO_D2,
  CONTROLLINO_D1,
  CONTROLLINO_D7
};

const int* ptrLed = ledPins;     //variable puntero               
const int numLeds = 9;//numero de leds
int aux = 0;  //variable auxiliar

// Pines de botones
const int botonNormal = CONTROLLINO_I16;
const int botonInverso = CONTROLLINO_I17;
const int botonReinicio = CONTROLLINO_I18;

// Estados posibles
enum BOTON {NORMAL, INVERSO, REINICIO};
BOTON estado = NORMAL;//ESTADO INICIAL

unsigned long t_previo = 0;
const unsigned long intervalo = 500; // ms
int Led = 0;

//definir los leds como salida y botones como entradas
void setup() {
  for (int i = 0; i < numLeds; i++) {
    pinMode(*(ptrLed + i), OUTPUT); //puntero de cada led
    digitalWrite(*(ptrLed + i), LOW);//leds inician apagados
  }

  pinMode(botonNormal, INPUT);
  pinMode(botonInverso, INPUT);
  pinMode(botonReinicio, INPUT);
}

void loop() {
  // Leer botones
  if (digitalRead(botonNormal) == HIGH) {
    estado = NORMAL; //variable de estado actual
    Led = 0; //inicia en modo normal
    apagarTodos(); //llama a la funcion
     aux = 0;
  } else if (digitalRead(botonInverso) == HIGH) {
    estado = INVERSO;  //variable de estado actual
    Led = numLeds - 1; //inicia desde el ultimo
    apagarTodos(); //llama a la funcion
    aux = 1;
  } else if (digitalRead(botonReinicio) == HIGH) {
    estado = REINICIO;  //variable de estado actual
  }

  // Máquina de estados
  switch (estado) {
    case NORMAL:
      if (millis() - t_previo > intervalo) {
        apagarTodos();
        digitalWrite(*(ptrLed + Led), HIGH); //enciende el led
        Led = (Led + 1) % numLeds; //aumenta el contador de led
        t_previo = millis();
      }
      break;

    case INVERSO:
      if (millis() - t_previo > intervalo) {
        apagarTodos();
        digitalWrite(*(ptrLed + Led), HIGH);
        Led = (Led - 1 + numLeds) % numLeds; //decrementa desde el ultmo 
        t_previo = millis();
      }
      break;

    case REINICIO:
    //enciende y apaga asemejando un reinicio
      encenderTodos();
      apagarTodos();
      if (aux == 0){
      estado = NORMAL;
      Led = 0;
      } else {
        estado = INVERSO;
         Led = numLeds - 1;
        };
    
      break;
    
  }
}

//encender todos los leds por un tiempo
void encenderTodos() {
  for (int i = 0; i < numLeds; i++) {
    digitalWrite(*(ptrLed + i), HIGH);
  }
}

//apagar todos los leds por un tiempo
void apagarTodos() {
  for (int i = 0; i < numLeds; i++) {
    digitalWrite(*(ptrLed + i), LOW);
  }
}