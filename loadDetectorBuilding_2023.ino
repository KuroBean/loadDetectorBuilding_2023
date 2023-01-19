#include <math.h>
#define blue 7
#define red 4
#define green 2
#define lowerThreshold 1301//concentrationthan this flshes low color equal or higher (and less than upperthresh) is mid color
#define upperThreshold 4001//equal or higher cocnetnartion is high color
#define voltReader A0
#define fixedRes 1000 
#define Vin 5
float val=0;
float volts=0;
float varResistance=0;
float concentration=0;
void setup() {
  // put your setup code here, to run once:
  pinMode(red,OUTPUT);
  pinMode(green,OUTPUT);
  pinMode(blue,OUTPUT);
  Serial.begin(9600);
  Serial.println("starting");
}
//low: 900ppm, med: 2700,high: 4500 
void loop() {
  // put your main code here, to run repeatedly:
  Serial.print("voltage: ");
  //Serial.println((analogRead(voltReader))*0.342/1023.0);
  val=analogRead(voltReader);
  volts=val*5.0/1023.0;
  Serial.println(volts);
  
  //code for calculating resistance of solution, to make sure fixed resistor is about equal to it
  varResistance=fixedRes*(Vin-volts)/volts;
  Serial.print("resistance of fsr: ");
  Serial.println(varResistance);

  concentration=pow(volts,10)*(5.86*0.001);
  Serial.print("concentration (ppm): ");
  Serial.println(concentration);
  lightUp(lowerThreshold,upperThreshold,green,red,blue );
  delay(1000);
  
}

void lightUp(int lowThresh,int highThresh,int lowColor, int midColor,int highColor){
 if(concentration==0){
   digitalWrite(lowColor,LOW);
   digitalWrite(midColor,LOW);
   digitalWrite(highColor,LOW);
 }
 else if(concentration<lowThresh){
      digitalWrite(lowColor,HIGH);
      digitalWrite(midColor,LOW);
      digitalWrite(highColor,LOW);
  }else if(concentration>=lowThresh&&concentration<highThresh){
      digitalWrite(lowColor,LOW);
      digitalWrite(midColor,HIGH);
      digitalWrite(highColor,LOW);
  }else{
      digitalWrite(lowColor,LOW);
      digitalWrite(midColor,LOW);
      digitalWrite(highColor,HIGH);
   }
 }

