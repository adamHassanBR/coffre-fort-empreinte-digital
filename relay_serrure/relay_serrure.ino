/**************
 * /******* switch *******/
/*
 *  5V : 5V 
 *  GND : GND
 *  DATA : D4
 *
 * /******* switch *******/
   /******* serrure *******/
/*
 *  5V : switch : Millieu 
 *  GND : switch : Bas
 *
 * /******* serrure *******/
 /***************/


#define RELAY 4

void setup() {
  Serial.begin(115200);
  pinMode(RELAY, OUTPUT);
}

void loop() {
  Serial.println("fermer");
   digitalWrite(RELAY, LOW);
   delay(3000); // On attend 3s
   
   Serial.println("ouvert");
   digitalWrite(RELAY, HIGH);
   delay(3000); // On attend 3s



}
