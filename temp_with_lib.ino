#include <Adafruit_MLX90614.h>
#include <Wire.h>


Adafruit_MLX90614 jd = Adafruit_MLX90614();

void setup() 
{
  Serial.begin(9600);

  Serial.println("gy-906 temperature");  

  jd.begin(); 
}

void loop() {
  float temp;
  Serial.print("Temp = ");
  temp = jd.readObjectTempC();
  Serial.print(temp);S
  Serial.println("*C");
  Serial.println();
  delay(500);
}
