//Libraries
#include <Pixy2.h>

//Variables
Pixy2 pixy;

void setup() {
 	//Init Serial USB
 	Serial.begin(19200);
 	Serial.println(F("Initialize System"));
 	//Init Pixy2
 	pixy.init();
}

void loop() {
 	testPixy();
}

void testPixy() { /* function testPixy */
 	//// Get blocks from Pixy2
 	// grab blocks!
 	pixy.ccc.getBlocks();

 	// If there are detect blocks, print them!
 	if (pixy.ccc.numBlocks) {
 			Serial.print("Detected ");
 			Serial.println(pixy.ccc.numBlocks);
 			for (int i = 0; i < pixy.ccc.numBlocks; i++) {
 					Serial.print(" 	block ");
 					Serial.print(i);
 					Serial.print(": ");
 					pixy.ccc.blocks[i].print();
 			}
 	}
}

