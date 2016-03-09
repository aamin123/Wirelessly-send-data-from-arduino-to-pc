// DATA FROM HUMIDITY SENSOR
#include <Sensirion.h>   

#include <SendOnlySoftwareSerial.h>
SendOnlySoftwareSerial bluetooth (7);  // Tx pin is 7


const uint8_t wi_power = 2;    // controlling the wireless power unit on/off

const uint8_t dataPin =  9;              // SHT serial data
const uint8_t sclkPin =  8;              // SHT serial clock
const uint8_t ledPin  = 13;              // Arduino built-in LED
const uint32_t TRHSTEP   = 5000UL;       // Sensor query period
const uint32_t BLINKSTEP =  250UL;       // LED blink period



Sensirion sht = Sensirion(dataPin, sclkPin);

uint16_t rawData;
float temperature;
float humidity;
float dewpoint;

byte ledState = 0;
byte measActive = false;
byte measType = TEMP;

unsigned long trhMillis = 0;             // Time interval tracking
unsigned long blinkMillis = 0;

// DATA FROM TEMPERATURE SENSOR
int temppin= 2; 


long runningAverage=0;          //the running average of calculated values
const int averagedOver= 16;     //how quickly new values affect running average
//bigger numbers mean slower


// DATA FROM ACCELEROMETER
int sense01 = A0;        // sensing LDR (light dependent resistor) connected to analog5       
int redPin = 4;// LED on dig3 
int greenPin = 5;
int bluePin = 6;

int val01 = 0;          // variable to store the value read from sense01
int light = 217;        // set light threshold
int avgvect[32];
int avgind=0;
int latest=0;

int sense01a = A1;        // accelerometer A1      
int val01a = 0;          // variable to store the value read from sense01
int avgvecta[32];
int avginda=0;
int latesta=0;

void setup() {
  Serial.begin(57600);
  bluetooth.begin(9600);

  pinMode(ledPin, OUTPUT);
  pinMode(redPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  pinMode(greenPin, OUTPUT);

  //digitalWrite(LED01,HIGH);
  //delay(15);   

}



void TempSensor()
{
  //we have to change this code because the sensor is different, but the RGB led code is working
  int rawvoltage= analogRead(temppin);
  float volts= rawvoltage/205.0;
  float celsiustemp= 100.0 * volts - 50;


  if (celsiustemp <= 36) {
    //led shold be blue
    digitalWrite(bluePin, HIGH);
    digitalWrite(redPin,LOW);
    digitalWrite(greenPin,LOW);
    delay(15);
  }
  else if ((celsiustemp >36) && (celsiustemp<=37.5)) {
    // led should be green
    digitalWrite(bluePin, LOW);
    digitalWrite(redPin,LOW);
    digitalWrite(greenPin,HIGH);
    delay(15);
  }
  else
  {
    digitalWrite(bluePin, LOW);
    digitalWrite(redPin,HIGH);
    digitalWrite(greenPin,LOW);
    delay(15);
  }

  // determine the threshold here
  Serial.print(celsiustemp);
  Serial.println("Celsius");

}

void accel()
{
  latesta=avgvecta[avginda] = analogRead(sense01a);      // read sense01 led
  avginda++;
  if(avginda>31)
  {
    avginda=0;
  }

  val01a=0;
  for(int foo=0;foo<32;foo++)
  {
    val01a+=avgvecta[foo];
  }
  val01a=val01a/32;


  if(abs(val01a-latesta)>30)
  {
    //    Serial.print(abs(val01-latest));            //debug print
    Serial.println("A");            //debug print    
    bluetooth.print("A");
  }
  else
  {
    Serial.println("x");            //debug print      
    bluetooth.print("x");
  }

}


void fiber_sensor()
{
  latest=avgvect[avgind] = analogRead(sense01);      // read sense01 led
  avgind++;
  if(avgind>31)
  {
    avgind=0;
  }

  val01=0;
  for(int foo=0;foo<32;foo++)
  {
    val01+=avgvect[foo];
  }
  val01=val01/32;


  if(abs(val01-latest)>3)
  {
    //    Serial.print(abs(val01-latest));            //debug print
    Serial.println("B");            //debug print    
    bluetooth.print("B");
  }
  else
  {
    Serial.println("z");            //debug print      
    bluetooth.print("z");
  }

}

void loop()
{
  // HumiditySensor();  // Each of these is a function defined below
  //    Serial.println("o");            //debug print      
  TempSensor();
  fiber_sensor();
  accel();

  delay(100);     
}





