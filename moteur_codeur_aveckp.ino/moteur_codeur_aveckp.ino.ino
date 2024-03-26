
#include <Encoder.h>
Encoder myEnc(3, 2); // initialiser l'encodeur 


long teta, teta_old;     // definition des variables de position 

unsigned long t_old, t, t2 = 0;  // definition des variables de temps 

int commande_moteur = 0; // definition de la commande du moteur qui varie entre 0 et 255 

float vitesse_mesuree; // definition de la vitesse mesurée par l'encodeur 

float vitesse_desiree = 170; // --> remplacer le 0 par 170 !

float kp = 0.5; // coefficient de régulation 

float ki = 0.007;

float dt = 0.016;

float erreur_cumulee ; 

float erreur_vitesse; 



void setup() {  

   Serial.begin(9600);   // communication série 

   pinMode(5, OUTPUT);  // pin du codeur et mateur en 5 car carte puissance
   erreur_cumulee = 0.0;
   analogWrite(5,0);
}



void loop() {  

   t = millis();  // initialisation du delai depuis la mise en route du programme en millisecondes 

   teta = myEnc.read();  // teta = valeur lue l'encodeur 

   if (t != t_old) { // Vérification pour éviter la division par zéro
       vitesse_mesuree = ((teta - teta_old) / 360.0) / ((t - t_old) / 60000.0);  
   } else {
       vitesse_mesuree = 0; // Assigner une valeur par défaut si la division par zéro est évitée
   }

   erreur_vitesse =  vitesse_desiree - vitesse_mesuree;

   erreur_cumulee = erreur_cumulee + erreur_vitesse ; //Pour calcul ki

   commande_moteur = commande_moteur + kp*erreur_vitesse ;

   commande_moteur=constrain(commande_moteur,0,255);

   analogWrite(5,commande_moteur);

   t2 = t; //Pour calcul ki

  //  Serial.print("La vitesse mesurée par l'encodeur est  : ");  
  //Serial.println(erreur_cumulee);
   //Serial.print(commande_moteur);
   Serial.print(',');
   Serial.println(vitesse_mesuree);  
 //  Serial.println(" tr/min");

   t_old = t;

   teta_old = teta;

//   delay(100); 

}


