#include <Adafruit_NeoPixel.h>
#include <DFRobot_DS1307.h>

#define LED_PIN    2 // Modifier le numéro de pin si nécessaire
#define LED_COUNT  60

Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);
DFRobot_DS1307 DS1307;
int multi;
void setup() {
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
  Serial.begin(115200);

  // Initialize sensor
  while( !(DS1307.begin()) ){
    Serial.println("Communication with device failed, please check connection");
    delay(3000);
  }
  Serial.println("Begin ok!");
  DS1307.start();
  DS1307.setSqwPinMode(DS1307.eSquareWave_1Hz);
}

void loop() {
  // Obtenir l'heure actuelle
 
  // Effacer la bande de LED
  strip.clear();

  uint16_t getTimeBuff[7] = {0};
  DS1307.getTime(getTimeBuff);
  char outputarr[128];
  sprintf(outputarr, "time: %d/%d/%d-%d %d:%d:%d\r\n",
            getTimeBuff[6],
            getTimeBuff[5],
            getTimeBuff[4],
            getTimeBuff[3],
            getTimeBuff[2],
            getTimeBuff[1],
            getTimeBuff[0]
            );
  Serial.print(outputarr);
  int heures0 = getTimeBuff[2];
  int heures = getTimeBuff[2] % 12; // Convertir en format 12 heures

  int minutes = getTimeBuff[1]; //  minute();
  int secondes = getTimeBuff[0]; //second();
  for(int i = 0; i <= 60; i += 5) 
  {
    //Serial.println(multi);
     if (heures0 > 12)
    {
      strip.setPixelColor(i, 8, 8, 8);  
    }
    else
    {
      strip.setPixelColor(i, 8, 0, 8); 
    }
    if(i==0 or i==15 or i==30 or i==45)  {strip.setPixelColor(i, 16, 16, 0);}
   
  }

  int ledIndex0 = heures * (LED_COUNT / 12) + minutes/12;
  int ledIndex1 = minutes * (LED_COUNT / 60) ;
  int ledIndex2 = secondes * (LED_COUNT / 60);

  // Afficher la LED en rouge, bleu et vert
  strip.setPixelColor(ledIndex0, 8, 0, 0); // Rouge, bleu, vert
  strip.setPixelColor(ledIndex1, 0, 8, 0); // Rouge, bleu, vert
  strip.setPixelColor(ledIndex2, 0, 0, 8); // Rouge, bleu, vert
  // Actualiser les LEDs
  strip.show();

  // Délai d'une seconde
  delay(1000);
}
