int outputpin= 0;
void setup()
{
  Serial.begin(9600);
}
void loop()
{
 int rawvoltage= analogRead(outputpin);
 float volts= rawvoltage/205.0;
 float celsiustemp= 100.0 * volts - 50;
 Serial.print(celsiustemp);
 Serial.println("Celsius");
 delay(500);
}

