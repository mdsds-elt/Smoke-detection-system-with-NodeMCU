/********************************
  Autora : Márcia de Sá 
 | SENSOR MQ2 | OLED | ESP8266 | 
*********************************/

#include <Wire.h>
#include <SPI.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

/*******************
#include <SPI.h>
#define BME_SCK 18
#define BME_MISO 19
#define BME_MOSI 23
#define BME_CS 5
********************/

int buzzer = 0;/*buzzer!!*/
int smokeA0 = A0; /*Sensor MQ2*/
int pin_led_verm = 14;/* D5 | Led vermelho*/
int pin_led_verde = 12;/* D6 | Led verde*/

int nivel_sensor  = 250; /* Nivel do Sensor MQ2 */

//Adafruit_BME280 bme; //comunicação I2C
//Adafruit_BME280 bme(BME_CS); // hardware SPI

Adafruit_SSD1306 display = Adafruit_SSD1306(128, 32, &Wire);
unsigned long delayTime;

void setup() {
  
  pinMode(buzzer, OUTPUT); /* Pino Buzzer */
  pinMode(smokeA0, INPUT); /* Pino MQ2 */
  pinMode(pin_led_verm, OUTPUT);
  pinMode(pin_led_verde, OUTPUT);
  
  Serial.begin(115200);
    
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3C 
   // init done
  display.display();
  delay(100);
  display.clearDisplay();
  display.display();
  display.setTextSize(1.5);// era 1.2
  display.setTextColor(WHITE);
  
  Serial.println();
}

void loop() { 
  
  int analogSensor = analogRead(smokeA0);
  
  /*Diplay*/
  display.clearDisplay();
  display.setCursor(0,0);
  display.setTextSize(2.0);
  
  
  /* Sensor MQ2 */  
  Serial.print("Smoke: ");  
  Serial.println(analogRead(smokeA0));
  //Serial.println(" ppm");
  display.println("Smoke: "); 
  display.print(analogRead(smokeA0)); 
  display.println(" ppm");
  
  if (analogSensor > nivel_sensor)
  {
   digitalWrite(pin_led_verm, HIGH);
   digitalWrite(pin_led_verde, LOW);
   tone(buzzer, 1000, 200);
   }
   else
   {
    digitalWrite(pin_led_verm, LOW);/*Desliga O led Vermelho*/
    digitalWrite(pin_led_verde, HIGH);/*Liga O led Verde*/
    noTone(buzzer);
    }
    delay(100);

    Serial.println();
    display.display();
    delay(1000);
  }

  
