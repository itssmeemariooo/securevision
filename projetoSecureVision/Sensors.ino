// C++ code
#define trigPin 3
#define echoPin 2
const int botaoSafe = 7;
const int botaoAlarm = 6;
int speakerPin=4;
int length=15; // numero maximo de notas
char notes[]="cdefgabCbagdedc";
int beats[]= {1,1,1,1,1,1,2,1,1,1,1,2,4,8,4};
int tempo=300;
int alarme=0;
int ldrAlarm=0;
int modoBOTAO=0;

#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7735.h> // Hardware-specific library for ST7735
#include <Adafruit_ST7789.h> // Hardware-specific library for ST7789
#include <SPI.h>


#if defined(ARDUINO_FEATHER_ESP32) // Feather Huzzah32
  #define TFT_CS         14
  #define TFT_RST        15
  #define TFT_DC         32

#elif defined(ESP8266)
  #define TFT_CS         4
  #define TFT_RST        16                                            
  #define TFT_DC         5

#else
  // For the breakout board, you can use any 2 or 3 pins.
  // These pins will also work for the 1.8" TFT shield.
  #define TFT_CS        10
  #define TFT_RST        9 // Or set to -1 and connect to Arduino RESET pin
  #define TFT_DC         8
#endif

Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);

long measureDistance() {
	long duration, distance;

  	//Send pulse
	digitalWrite(trigPin, LOW);
	delayMicroseconds(2);
	digitalWrite(trigPin, HIGH);
	delayMicroseconds(10);
	digitalWrite(trigPin, LOW);

  	//Wait for echo and measure time until it happens
	duration = pulseIn(echoPin, HIGH);

  	//Compute distance
	distance = duration/58;

  	return distance;
}
              

              
void playTone(int tone, int duration){              
  for(long i=0; i<duration*1000L; i+= tone*2) {
    digitalWrite(speakerPin, HIGH);
    delayMicroseconds(tone);
    digitalWrite(speakerPin, LOW);
    delayMicroseconds(tone);
  }
}

void playNote(char note, int duration){                
  char names[]={'c','d','e','f','g', 'a', 'b', 'C' };
  int tones[]={1915,1700,1519,1432,1275,1136,1014,956};
  for(int i=0; i<8; i++)
    if(names[i] == note)
    	playTone(tones[i],duration);
}
                     
void setup()
{
  Serial.begin(9600);
  pinMode(speakerPin, OUTPUT);
  pinMode(trigPin, OUTPUT);
	pinMode(echoPin, INPUT);
  pinMode(botaoAlarm,INPUT);
  pinMode(botaoSafe,INPUT);
  tft.initR(INITR_144GREENTAB);
}

void menu(int alarme){
  tft.fillScreen(ST77XX_GREEN);
  tft.setTextColor(ST77XX_BLACK);
  tft.setCursor(0,20);
  tft.setTextSize(2);
  if(alarme==0){
    tft.print("Alarme:OFF");
  }
  else tft.print("Alarme:ON");
}

void loop()
{
  
  int ldr = analogRead(A0);
  
  tft.fillScreen(ST77XX_GREEN);
  tft.setTextColor(ST77XX_BLACK);
  tft.setCursor(0,20);
  tft.setTextSize(2);
  if(alarme==0){
    tft.print("Alarme:OFF");
  }
  else tft.print("Alarme:ON");

  tft.setCursor(0,70);
  ldr = analogRead(A0);
  if(ldr < 20){
    ldrAlarm=1;
    tft.print("Noite");
  }else tft.print("Dia");
 
  if(digitalRead(botaoAlarm)){
      modoBOTAO=1;
      Serial.println(modoBOTAO);
      Serial.println("Aqui");
}
  ldr = analogRead(A0);
  if(ldr<20){
    
  alarme=1;
  tft.fillScreen(ST77XX_GREEN);
  tft.setTextColor(ST77XX_BLACK);
  tft.setCursor(0,20);
  tft.setTextSize(2);
  if(alarme==0){
    tft.print("Alarme:OFF");
  }
  else tft.print("Alarme:ON");
  tft.setCursor(0,70);
  ldr = analogRead(A0);
  if(ldr < 20){
    ldrAlarm=1;
    tft.print("Noite");
  }else tft.print("Dia");
  
  
  
  ldr=analogRead(A0);
 
  Serial.println(measureDistance());
  if(digitalRead(botaoSafe) ){
    tft.setTextColor(ST77XX_BLACK);
    tft.setCursor(0,20);
    tft.setTextSize(2);
    tft.print("ALarme : OFF");
    alarme=0;
    return;
  }
  Serial.println(modoBOTAO);
  Serial.println("Aquiiii");
  if(ldr>20 && alarme == 1 ){
    tft.setTextColor(ST77XX_BLACK);
    tft.setCursor(0,20);
    tft.setTextSize(2);
    tft.print("ALarme : OFF");
    alarme=0;
    return;
  }
  while(measureDistance()<30){
    Serial.println(measureDistance());
    for( int i=0; i < 1; i++){
      if(notes[i] == ' ')
        delay(beats[i] * tempo);
      else
        playNote(notes[i], beats[i] * tempo);
    
      delay(tempo/2);
  }
}
}


if(digitalRead(botaoAlarm) || alarme==1 ){    
  alarme=1;
  tft.fillScreen(ST77XX_GREEN);
  tft.setTextColor(ST77XX_BLACK);
  tft.setCursor(0,20);
  tft.setTextSize(2);
  if(alarme==0){
      tft.print("Alarme:OFF");
    }
    else tft.print("Alarme:ON");
  tft.setCursor(0,70);
  ldr = analogRead(A0);
  if(ldr < 20){
    ldrAlarm=1;
    tft.print("Noite");
    }else tft.print("Dia");
  ldr=analogRead(A0);
  Serial.println(measureDistance());
  if(digitalRead(botaoSafe) ){
    tft.setTextColor(ST77XX_BLACK);
    tft.setCursor(0,20);
    tft.setTextSize(2);
    tft.print("ALarme : OFF");
    alarme=0;
    return;
  }
  Serial.println(modoBOTAO);
  Serial.println("Aquiiii");
  if(ldr>20 && alarme == 1 && modoBOTAO == 0){
    tft.setTextColor(ST77XX_BLACK);
    tft.setCursor(0,20);
    tft.setTextSize(2);
    tft.print("ALarme : OFF");
    alarme=0;
    return;
  }
  while(measureDistance()<30){
    Serial.println(measureDistance());
    for( int i=0; i < 1; i++){
      if(notes[i] == ' ')
        delay(beats[i] * tempo);
      else
        playNote(notes[i], beats[i] * tempo);
    
      delay(tempo/2);
  }
}
}
}

  
