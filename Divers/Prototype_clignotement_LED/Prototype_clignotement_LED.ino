

#define LED 2             // notre LED
int Vtm = 340;              // Vitesse d'entrée moteur en tour/min
float Vts = Vtm / 60000.0;  //Vitesse d'entrée moteur en tour/ms
float T;                    // Temps d'un tour complet en ms
float Td;                   // Temps led allumée en ms
int Tde;                    // Temps led éteinte en ms
int n = 5;                  // nombre de degré LED allumée

void setup() {
  Serial.begin(9600);
  pinMode(LED, OUTPUT);
  T = 1 / Vts;
  Td = 1000.0 * n * T / 360.0;
  // Tde = (1000.0 * (360 - n) * T) / (360.0); 
}

void loop() {
  Serial.println(Td);
  digitalWrite(LED, HIGH);
  delayMicroseconds(Td);
  digitalWrite(LED, LOW);
  delayMicroseconds(100*Td);
}
