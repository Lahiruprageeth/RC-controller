//Include Libraries
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#define POT1 A6
#define POT2 A4
#define L_BTN 2
#define R_BTN 3
#define UP_BTN 4
#define DOWN_BTN 5
#define LEFT_BTN 7
#define RIGHT_BTN 6
#define INDICATER A5
#define L_Y_AXIS A1
#define L_X_AXIS A0
#define R_Y_AXIS A3
#define R_X_AXIS A2

//create an RF24 object
RF24 radio(9, 8);  // CE, CSN

//address through which two modules communicate.
const byte address[6] = "00001";

//store sensor data
struct myda {
  uint8_t pot1Value ;
  uint8_t pot2Value ;
  uint8_t lBtnValue ;
  uint8_t rBtnValue;
  uint8_t upBtnValue;
  uint8_t downBtnValue;
  uint8_t leftBtnValue;
  uint8_t rightBtnValue;
  uint8_t lXAxisValue;
  uint8_t lYAxisValue;
  uint8_t rXAxisValue;
  uint8_t rYAxisValue;
} myData;

void setup()
{
  radio.begin();

  //set the address
  radio.openWritingPipe(address);

  //Set module as transmitter
  radio.stopListening();

  pinMode(POT1, INPUT);
  pinMode(POT2, INPUT);
  pinMode(L_BTN, INPUT_PULLUP);
  pinMode(R_BTN, INPUT_PULLUP);
  pinMode(UP_BTN, INPUT_PULLUP);
  pinMode(DOWN_BTN, INPUT_PULLUP);
  pinMode(LEFT_BTN, INPUT_PULLUP);
  pinMode(RIGHT_BTN, INPUT_PULLUP);
  pinMode(INDICATER, OUTPUT);
  pinMode(L_X_AXIS, INPUT);
  pinMode(L_Y_AXIS, INPUT);
  pinMode(R_X_AXIS, INPUT);
  pinMode(R_Y_AXIS, INPUT);

}
void loop()
{

  // Read values from pins
  myData.pot1Value = analogRead(POT1);
  myData.pot2Value = analogRead(POT2);
  myData.lBtnValue = digitalRead(L_BTN);
  myData.rBtnValue = digitalRead(R_BTN);
  myData.upBtnValue = digitalRead(UP_BTN);
  myData.downBtnValue = digitalRead(DOWN_BTN);
  myData.leftBtnValue = digitalRead(LEFT_BTN);
  myData.rightBtnValue = digitalRead(RIGHT_BTN);
  myData.lXAxisValue = analogRead(L_X_AXIS);
  myData.lYAxisValue = map(analogRead(L_Y_AXIS),0,1024,0,255);
  myData.rXAxisValue = map(analogRead(R_X_AXIS),0,1024,0,255);
  myData.rYAxisValue = analogRead(R_Y_AXIS);
  delay(10);

  radio.write(&myData, sizeof(myData));
  
      digitalWrite(INDICATER, HIGH);
      delay(10);
      digitalWrite(INDICATER, LOW);
      delay(140);
    
}
