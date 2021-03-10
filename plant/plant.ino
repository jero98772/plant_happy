#include "DHT.h"
#include <Adafruit_SSD1306.h>
// define variables
//dht vars

#define DHTPIN 2
#define DHTTYPE DHT11
//init dht funcition
DHT dht(DHTPIN, DHTTYPE);

//oled vars
#define HEIGHT 64
#define WIDTH 128
#define OLED_RESET -1
Adafruit_SSD1306 display(WIDTH, HEIGHT, &Wire, OLED_RESET);

void setup() {
  Serial.begin(9600);
  dht.begin();
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { 
    Serial.println(F("oled allocation failed"));
    
  }
}

void loop() {
  display.display();
  int soilhum = analogRead(A0);
  int meansoil = soilhum*100/1024;
  Serial.println("Humidity from soil(%)");
  Serial.println(meansoil);
  // declare vars for Humidity and Temperature  for get values
  float hum = dht.readHumidity();
  float temp = dht.readTemperature();
  //time for new measure
  delay(2000);
  //show data
  Serial.println("humidity (%)");
  Serial.println(hum);
  Serial.println("temperature (C°)");
  Serial.println(temp);
  // if have a error show the error
  if (isnan(temp) || isnan(hum)) {
    Serial.print("ERROR for read data");
  }
  display.clearDisplay();
  if (20<meansoil && meansoil<80){
    happy();
  }
  else {
    sad();  
  }
  display.display(); 

}
void happy(){
  display.clearDisplay();
  //display.drawCircle(82, 44, 60, WHITE);
  display.drawCircle(64, 32, 30, WHITE);
  display.fillCircle(45, 28, 7, WHITE);
  display.fillCircle(75, 28, 7, WHITE);
  display.setTextSize(3);
  display.setTextColor(WHITE);
  display.setCursor(56, 40);
  display.println("V");
  display.display(); 
}
void sad(){
  display.clearDisplay();
  display.drawCircle(64, 32, 30, WHITE);
  display.setTextSize(2);//size  
  display.setCursor(45, 25);//eye 1 position
  display.println("X");//eye 1
  display.setCursor(75, 25);//eye 2 position
  display.println("X");//eye 2
  display.setTextColor(WHITE);
  display.setCursor(64, 40);
  display.println("_");
  display.display(); 
}
