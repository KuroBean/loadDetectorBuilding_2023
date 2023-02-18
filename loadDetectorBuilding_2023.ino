#include <math.h>
#define blue 7
#define red 4
#define green 2
#define lowerThreshold 41//mass lower than this flashes low color, equal or higher (and less than upperthresh) is mid color
#define upperThreshold 201//equal or higher cocnetnartion is high color
#define voltReader A0
#define fixedRes 2220 //at 500g, fsr was abt 2000 ohms
#define Vin 5
#define voltThresholdForTimeCount 0.3 
float val=0;
float volts=0;
float varResistance=0;
float mass=0;
int secCount=0;
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
  val=analogRead(voltReader);
  volts=val*5.0/1023.0;

  //put on weight RIGHT AS UPDATE HAPPENS
  if(volts>voltThresholdForTimeCount){
    secCount++;
    Serial.print("seconds since nonzero reading: ");
    Serial.println(secCount);
  }else{
    secCount=0;
  }
  
  // put your main code here, to run repeatedly:
  Serial.print("voltage: ");
  //Serial.println((analogRead(voltReader))*0.342/1023.0);
  
  Serial.println(volts);
  
  /**
  //code for calculating resistance of solution, to make sure fixed resistor is about equal to it
  varResistance=fixedRes*(Vin-volts)/volts;
  Serial.print("resistance of fsr: ");
  Serial.println(varResistance);
  */

  //weight conversion
  mass=239.982*pow(1.62165,volts)-239.982;

  Serial.print("mass (g): ");
  Serial.println(mass);
  lightUp(lowerThreshold,upperThreshold,red,green,blue );

  Serial.println();
  delay(1000);
  
}

void lightUp(int lowThresh,int highThresh,int colorRed, int colorGreen,int colorBlue){
 if(mass==0){
   digitalWrite(colorRed,LOW);
   digitalWrite(colorGreen,LOW);
   digitalWrite(colorBlue,LOW);
 }
 else if(mass<lowThresh){
      digitalWrite(colorRed,LOW);
      digitalWrite(colorGreen,HIGH);
      digitalWrite(colorBlue,LOW);
  }else if(mass>=lowThresh&&mass<highThresh){
      digitalWrite(colorRed,HIGH);
      digitalWrite(colorGreen,HIGH);
      digitalWrite(colorBlue,HIGH);
  }else{
      digitalWrite(colorRed,LOW);
      digitalWrite(colorGreen,LOW);
      digitalWrite(colorBlue,HIGH);
   }
 }

