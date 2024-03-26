#define LED 2             // notre LED

int Vtm = 340;              // Vitesse d'entrée moteur en tour/min
float Vts = Vtm / 60000.0;  //Vitesse d'entrée moteur en tour/ms
float T;                    // Temps d'un tour complet en ms
float Td;                   // Temps led allumée en ms
int Tde;                    // Temps led éteinte en ms
int n = 5;                  // nombre de degré LED allumée

// Generally, you should use "unsigned long" for variables that hold time
// The value will quickly become too large for an int to store
unsigned long previousMicros = 0; // will store last time LED was updated


// Variables will change:
int ledState = LOW;  // ledState used to set the LED

void setup() {
  Serial.begin(9600);
  pinMode(LED, OUTPUT);
  T = 1 / Vts;
  Td =  1000* n * T / 360.0;
  Tde = (1000*(360 - n) * T) / (360.0); 
}

void loop() {
   // check to see if it's time to blink the LED; that is, if the difference
  // between the current time and last time you blinked the LED is bigger than
  // the interval at which you want to blink the LED.
  unsigned long currentMicros = micros();
  Serial.print("curent : " );
  Serial.println(currentMicros);
  Serial.print("previouMicross : " );
  Serial.println(previousMicros);
  Serial.println(Tde);
  Serial.println(Td);
  
  
  if (ledState == LOW) {
    // Si la LED est éteinte depuis Tde Microsecondes, on l'allume
    if (currentMicros - previousMicros >= Tde) {
      ledState = HIGH;
      previousMicros = currentMicros;
    }
  } else {
    // Si la LED est allumée depuis Td Microsecondes, on l'éteint
    if (currentMicros - previousMicros >= Td) {
      ledState = LOW;
      previousMicros = currentMicros;
    }
  }
  
  // Met à jour l'état de la LED
  digitalWrite(LED, ledState);
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
  



