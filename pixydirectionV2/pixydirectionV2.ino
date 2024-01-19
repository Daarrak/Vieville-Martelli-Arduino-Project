//Libraries
#include <Pixy2.h>

//Variables
Pixy2 pixy;
int buzzer=11;
int trig = 2;  // Arduino pin tied to trigger pin on the ultrasonic sensor.
int echo =  8; // Arduino pin tied to echo pin on the ultrasonic sensor.
int t;
float coord;

// MOTEUR A
int ENA=9; // 9 pour sortie PWM
int IN1=4;
int IN2=5;

// MOTEUR B
int ENB=10; // 10 pour sortie PWM
int IN3=6;
int IN4=7;

void setup() {
 	Serial.begin(9600);
 	pixy.init();
  pinMode(buzzer,OUTPUT);
  pinMode(trig,OUTPUT);
  pinMode(echo,INPUT);

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
  coord = turretPixy(); //la tourelle tourne et se déplace jusqu'à detecter un objet rouge
  stopTurret(coord);   //ajuste la caméra au centre et tourne la voiture en direction de l'objet
  if(TaseObject()){  //se dirige vers l'objet et tase
    moveAround(); // change de place pour trouver un autre objet
  }
}

float turretPixy() { //la tourelle tourne et se déplace jusqu'à detecter un objet rouge
  pixy.ccc.getBlocks(true, 1);
 	while(!pixy.ccc.numBlocks){
    //tourne le servomoteur
    //apres un tour entier la voiture se deplace et recommence
  }
  return pixy.ccc.blocks[0].m_x;
}

void stopTurret(coord){
  //ajuste la caméra au centre et tourne la voiture en direction de l'objet
}

bool tryTaser(){
  digitalWrite(trig,LOW);
  delayMicroseconds(5);
  digitalWrite(trig,HIGH);
  delayMicroseconds(10);
  digitalWrite(trig,LOW);
  t = pulseIn(echo,HIGH);
  if(t/58 < 6){
    Serial.println("tase");
    //tase();
    return true;
  }
  return false;
}

//void tase(){//warning buzzer + light}

bool TaseObject(){
  pixy.ccc.getBlocks(true, 1);
  while(pixy.ccc.numBlocks) {
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
    if(tryTaser()){
      return true;
    }
 	}
  return false;
}

void moveAround(){
  // change de place pour trouver un autre objet
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

