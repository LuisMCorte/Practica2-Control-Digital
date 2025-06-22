// Practica 2: Control básico de salidas digitales y aplicación vanzada con FSM.
// Parte B: Semaforo
#include <Controllino.h>  // Librería de Controllino

// Definición de pines para los semáforos
const int rojo_s1 = CONTROLLINO_D0;
const int amarillo_s1 = CONTROLLINO_D1;
const int verde_s1 = CONTROLLINO_D2;

const int rojo_s2 = CONTROLLINO_D12;
const int amarillo_s2 = CONTROLLINO_D13;
const int verde_s2 = CONTROLLINO_D14;

// Enum para los estados de la FSM
typedef enum {
  ESTADO_INICIAL,     // semaforos en rojo
  ESTADO_VERDE_A,     // semaforo A en verde, semaforo B en rojo
  ESTADO_AMARILLO_A,  // semaforo A en amarillo, semaforo B en rojo
  ESTADO_VERDE_B,     // semaforo A en rojo, semaforo B en verde
  ESTADO_AMARILLO_B   // semaforo A en rojo, semaforo B en amarillo
} estadoMEF_t;

// Estructura para gestionar el estado y tiempos
struct Semaforo {
  int rojo;
  int amarillo;
  int verde;
  unsigned long tiempoInicio;
  unsigned long tiempoDuracion;
};

estadoMEF_t estadoActual = ESTADO_INICIAL;  // inicia en el estado inicial

Semaforo semaforoA = { rojo_s1, amarillo_s1, verde_s1, 0, 0 };  //tiempo de inicio y duracion en 0
Semaforo semaforoB = { rojo_s2, amarillo_s2, verde_s2, 0, 0 };  //tiempo de inicio y duracion en 0

const unsigned long TIEMPO_VERDE = 15000;    // 15 segundos
const unsigned long TIEMPO_AMARILLO = 3000;  // 3 segundos

void setup() {
  // Configurar pines como salida
  pinMode(semaforoA.rojo, OUTPUT);
  pinMode(semaforoA.amarillo, OUTPUT);
  pinMode(semaforoA.verde, OUTPUT);
  pinMode(semaforoB.rojo, OUTPUT);
  pinMode(semaforoB.amarillo, OUTPUT);
  pinMode(semaforoB.verde, OUTPUT);

  // Estado inicial: Ambos rojos
  digitalWrite(semaforoA.rojo, HIGH);
  digitalWrite(semaforoB.rojo, HIGH);
}

void loop() {
  unsigned long tiempoActual = millis();

  switch (estadoActual) {
    case ESTADO_INICIAL:
      // Transición al primer estado después de 1 segundo
      if (tiempoActual < 1000) break;
      estadoActual = ESTADO_VERDE_A;
      semaforoA.tiempoInicio = tiempoActual;
      semaforoA.tiempoDuracion = TIEMPO_VERDE;
      apagarTodos();
      digitalWrite(semaforoA.verde, HIGH);
      digitalWrite(semaforoB.rojo, HIGH);
      break;

    case ESTADO_VERDE_A:
      if (tiempoActual - semaforoA.tiempoInicio >= TIEMPO_VERDE) {
        estadoActual = ESTADO_AMARILLO_A;
        semaforoA.tiempoInicio = tiempoActual;
        semaforoA.tiempoDuracion = TIEMPO_AMARILLO;
        apagarTodos();
        digitalWrite(semaforoA.amarillo, HIGH);
        digitalWrite(semaforoB.rojo, HIGH);
      }
      break;

    case ESTADO_AMARILLO_A:
      if (tiempoActual - semaforoA.tiempoInicio >= TIEMPO_AMARILLO) {
        estadoActual = ESTADO_VERDE_B;
        semaforoA.tiempoInicio = tiempoActual;
        semaforoA.tiempoDuracion = TIEMPO_VERDE;
        apagarTodos();
        digitalWrite(semaforoA.rojo, HIGH);
        digitalWrite(semaforoB.verde, HIGH);
      }
      break;

    case ESTADO_VERDE_B:
      if (tiempoActual - semaforoA.tiempoInicio >= TIEMPO_VERDE) {
        estadoActual = ESTADO_AMARILLO_B;
        semaforoA.tiempoInicio = tiempoActual;
        semaforoA.tiempoDuracion = TIEMPO_AMARILLO;
        apagarTodos();
        digitalWrite(semaforoA.rojo, HIGH);
        digitalWrite(semaforoB.amarillo, HIGH);
      }
      break;

    case ESTADO_AMARILLO_B:
      if (tiempoActual - semaforoA.tiempoInicio >= TIEMPO_AMARILLO) {
        estadoActual = ESTADO_VERDE_A;
        semaforoA.tiempoInicio = tiempoActual;
        semaforoA.tiempoDuracion = TIEMPO_VERDE;
        apagarTodos();
        digitalWrite(semaforoA.verde, HIGH);
        digitalWrite(semaforoB.rojo, HIGH);
      }
      break;
  }
}

void apagarTodos() {
  digitalWrite(semaforoA.rojo, LOW);
  digitalWrite(semaforoA.amarillo, LOW);
  digitalWrite(semaforoA.verde, LOW);
  digitalWrite(semaforoB.rojo, LOW);
  digitalWrite(semaforoB.amarillo, LOW);
  digitalWrite(semaforoB.verde, LOW);
}
