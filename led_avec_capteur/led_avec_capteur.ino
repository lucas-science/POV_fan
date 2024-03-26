#define LED 2             // notre LED
#define HALL_CAPTEUR 3
#include "Adafruit_NeoPixel.h"

int nbr_pix = 8;
Adafruit_NeoPixel strip (nbr_pix, 6, NEO_GRB + NEO_KHZ800);

int Vtm = 340;              // Vitesse d'entrée moteur en tour/min
float Vts = Vtm / 60000.0;  //Vitesse d'entrée moteur en tour/ms
unsigned long T;                    // Temps d'un tour complet en ms
unsigned long previous_T;
unsigned long current_T;
unsigned long Td;                   // Temps led allumée en ms
unsigned long Tde;                    // Temps led éteinte en ms
int n = 1;                  // nombre de degré LED allumée

// Generally, you should use "unsigned long" for variables that hold time
// The value will quickly become too large for an int to store
unsigned long previousMicros = 0; // will store last time LED was updated
unsigned long currentMicros;

// Variables will change:
int ledState = 0;  // ledState used to set the LED


void setup() {
  Serial.begin(9600);
  pinMode(LED, OUTPUT);
  pinMode(HALL_CAPTEUR, INPUT_PULLUP);
  T = 1000 / Vts;
  Td =  n * T / 360;
  Tde = ((360 - n) * T) / (360); 
  Serial.println(Tde);
  attachInterrupt(digitalPinToInterrupt(HALL_CAPTEUR), change_period, RISING); // Permet d'effectuer la fonction change_period quand le capteur se déclanche (c'est-à-dire quand la LED a fait un tour) : to trigger when the pin goes from low to high
    
   strip.begin();
   strip.show();
   strip.setBrightness(200); // maximum 255
}

void loop() {
   // check to see if it's time to blink the LED; that is, if the difference
  // between the current time and last time you blinked the LED is bigger than
  // the interval at which you want to blink the LED.
  currentMicros = micros();
  // Serial.print("curent : " );
  // Serial.println(currentMicros);
  // Serial.print("previouMicross : " );
  // Serial.println(previousMicros);

    
  if (ledState == LOW) {
    // Si la LED est éteinte depuis Tde Microsecondes, on l'allume
    if ((currentMicros - previousMicros) >= Tde) {
      ledState = 255;
      previousMicros = currentMicros;
    }
  } else {
    // Si la LED est allumée depuis Td Microsecondes, on l'éteint
    if ((currentMicros - previousMicros) >= Td) {
      ledState = 0;
      previousMicros = currentMicros;
    }
  }
  
  // Met à jour l'état de la LED
  strip.setPixelColor(1, 0, 0, ledState);
  strip.setPixelColor(7, 0, 0, ledState);
  strip.show();
}

void change_period(){   // Fonction qui permet de changer la durée d'une d'une rotation dans le calcul du temps de clignotement de la led afin de contrer l'irrégularité de la vitesse de rotation du moteur
  current_T = micros();
  T = current_T - previous_T;
  
  Td =  n * T / 360;
  Tde = ((360 - n) * T) / (360);

  previous_T = current_T;
}
































  /*
  if (ledState == LOW){
    Serial.print((currentMicros - previousMicros) >= Tde);
    
    if (currentMicros - previousMicros >= Tde) {
      previousMicros = currentMicros;
      ledState = HIGH;
      }
    else{
      ledState = LOW;
      }
    digitalWrite(LED, ledState);
  }

  else{
      if (currentMicros - previousMicros >= Td) {
        previousMicros = currentMicros;
        ledState = LOW;
      }
    else{
      ledState = HIGH;
      }
    digitalWrite(LED, ledState);
  }
  */
  
