/*
 * LED light sensing
 * Hunter Carlson
 * June 9 2009
 *
 */

int sense01 = A0;        // sensing LDR (light dependent resistor) connected to analog5       
int LED01 = 4;          // LED on dig3                       
int val01 = 0;          // variable to store the value read from sense01
int light = 217;        // set light threshold

int avgvect[32];
int avgind=0;
int latest=0;

void setup()
{
  Serial.begin(9600);          //  setup serial
  pinMode(LED01, OUTPUT);
  digitalWrite(LED01,HIGH);
}


void loop()
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
  

//  Serial.println(abs(val01-latest));            //debug print
  if(abs(val01-latest)>3)
  {
    Serial.print(abs(val01-latest));            //debug print
  Serial.println("\tBABY KICKING!");            //debug print    
  }
  else
  {
    Serial.println("z");            //debug print      
  }
  
  
  delay(10);
}
