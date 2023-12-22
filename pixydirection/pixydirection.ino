//Libraries
#include <Pixy2.h>

//Variables
Pixy2 pixy;
int buzzer=11;

// MOTEUR A
int ENA=9; // 9 pour sortie PWM
int IN1=4;
int IN2=5;

// MOTEUR B
int ENB=10; // 10 pour sortie PWM
int IN3=6;
int IN4=7;


void setup() {
 	Serial.begin(19200);
 	pixy.init();
  pinMode(buzzer,OUTPUT);
  pinMode(ENA,OUTPUT);
  pinMode(ENB,OUTPUT);
  pinMode(IN1,OUTPUT);
  pinMode(IN2,OUTPUT);  
  pinMode(IN3,OUTPUT);
  pinMode(IN4,OUTPUT);

// Direction du Moteur droit
  digitalWrite(IN1,HIGH);  
  digitalWrite(IN2,LOW);

// Direction du Moteur gauche
  digitalWrite(IN3,HIGH);
  digitalWrite(IN4,LOW);

// Met les 2 moteurs à l'arrêt
  digitalWrite(ENA,0);
  digitalWrite(ENB,0);
  noTone(buzzer);
}

void loop() {
  noTone(buzzer);
 	testPixy();
  //tryTaser();
}

void testPixy() { 
 	//// Get blocks from Pixy2
 	pixy.ccc.getBlocks(true, 1);
 	if (pixy.ccc.numBlocks) {
    pixy.setLamp(1,0); //Allume les 2 leds Pixy
 		if (pixy.ccc.blocks[0].m_x<150){
      // Tourne le véhicule à gauche pour centrer l'objet
      turnLeft();
    }
    else if (pixy.ccc.blocks[0].m_x>165){
      // Tourne le véhicule à droite pour centrer l'objet
      turnRight();
    } 
    else {
      //Le véhicule avance
      forward();
    }
 	}
  else {
    stop();
    pixy.setLamp(0,0);}
}

void stop(){
  digitalWrite(IN1,HIGH);  
  digitalWrite(IN2,LOW);
  digitalWrite(IN3,HIGH);
  digitalWrite(IN4,LOW);
  digitalWrite(ENA,0);
  digitalWrite(ENB,0);
}

void forward(){
  digitalWrite(IN1,HIGH);  
  digitalWrite(IN2,LOW);
  digitalWrite(IN3,HIGH);
  digitalWrite(IN4,LOW);
  digitalWrite(ENA,90);
  digitalWrite(ENB,90);
}

void turnRight(){
  digitalWrite(IN1,LOW);  
  digitalWrite(IN2,HIGH);
  digitalWrite(IN3,HIGH);
  digitalWrite(IN4,LOW);
  digitalWrite(ENA,0);
  digitalWrite(ENB,90);
}

void turnLeft(){
  digitalWrite(IN1,HIGH);  
  digitalWrite(IN2,LOW);
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,HIGH);
  digitalWrite(ENA,90);
  digitalWrite(ENB,0);
}

//void tryTaser(){
//  if(sonar.ping_cm()<5){
    //tase()
//  }
//}


//void tase(){//warning buzzer + light}
