#include <Wire.h>
#include "RTClib.h"
#include <Adafruit_NeoPixel.h> // Charge la librairie Neo Pixel d'Adafruit utilisé pour piloter le ruban de LED

#define PIXEL_PIN 6 // On définit le pin où est connecté la patte DATA du bandeau
#define PIXEL_COUNT 198 // On définit le nombre de LED compris sur le Ruban de LED soit 150 pour le ruban de 5m50

Adafruit_NeoPixel strip = Adafruit_NeoPixel(PIXEL_COUNT, PIXEL_PIN, NEO_GRB + NEO_KHZ800); // Paramètre l'objet strip qui correspond à toute les LED du ruban

RTC_DS3231 rtc;



/* Définition des couleurs */
int RED[3] = {255, 0, 0}; // Couleur Rouge
int GREEN[3] = {0, 255, 0}; // Couleur Verte
int CYAN[3] = {0, 255, 255}; // Couleur Cyan
int YELLOW[3] = {255, 125, 0}; // Couleur Jaune
int ORANGE[3] = {255, 40, 0}; // Couleur Orange
int PURPLE[3] = {255, 0 , 255}; // Couleur Violette
int PINK[3] = {255, 0, 100}; // Couleur Rose
int BLUE[3] = {0, 0, 255}; // Couleur Bleu
int WHITE[3] = {255, 255, 255}; // Couleur Blanche
int OFF[3] = {0, 0, 0}; // Éteint
int MAINCOLOR[3] = {255, 255, 255};

// Definition des mots
// the words
int arrIlEst [5] =   {0, 2, 6, 8, 10};
int IL_EST_COUNT = 5;
int arrDeux [4] =   {14, 16, 17, 18};
int DEUX_COUNT = 4;
int arrQuatre [6] =   {38, 36, 34, 32, 30, 28};
int QUATRE_COUNT = 6;
int arrTrois [5] =   {26, 24, 22, 20, 19};
int TROIS_COUNT = 5;
int arrNeuf [4] =   {39, 41, 43, 45};
int NEUF_COUNT = 4;
int arrUne [3] =   {47, 49, 51};
int UNE_COUNT = 3;
int arrSept [4] =   {53, 55, 57, 58};
int SEPT_COUNT = 4;
int arrHuit [4] =   {78, 76, 74, 72};
int HUIT_COUNT = 4;
int arrSix [3] =   {70, 68, 66};
int SIX_COUNT = 3;
int arrCinq [4] =   {64, 62, 60, 59};
int CINQ_COUNT = 4;
int arrMidi [4] =   {79, 81, 83, 85};
int MIDI_COUNT = 4;
int arrDix [3] =   {83, 85, 87};
int DIX_COUNT = 3;
int arrMinuit [6] =   {89, 91, 93, 95, 97, 98};
int MINUIT_COUNT = 6;
int arrOnze [4] =   {118, 116, 114, 112};
int ONZE_COUNT = 4;
int arrHeure [5] =   {108, 106, 104, 102, 100};
int HEURE_COUNT = 5;
int arrHeures [6] =   {108, 106, 104, 102, 100, 99};
int HEURES_COUNT = 6;
int arrMoins [5] = {119, 121, 123, 125, 127};
int MOINS_COUNT = 5;
int arrLe [2] = {131, 133};
int LE_COUNT = 2;
int arrDixMinute [3] = {135, 137, 138};
int DIX_MIN_COUNT = 3;
int arrEtQuart [7] = {158, 156, 152, 150, 148, 146, 144};
int ET_QUART_COUNT = 7;
int arrQuart [5] = {152, 150, 148, 146, 144};
int QUART_COUNT = 5;
int arrVingt [5] = {159, 161, 163, 165, 167};
int VINGT_COUNT = 5;
int arrVingtCinq [10] = {159, 161, 163, 165, 167, 169, 171, 173, 175, 177};
int VINGT_CINQ_COUNT = 10;
int arrCinqMinute [4] = {171, 173, 175, 177};
int CINQ_MIN_COUNT = 4;
int arrEtMinute [2] = {197, 195};
int ET_MIN_COUNT = 2;
int arrDemie [5] = {191, 189, 187, 185, 183};
int DEMIE_COUNT = 5;
 

void setup ()
{
  strip.begin(); // Lance la connection
  Serial.begin(9600);
  strip.show();
  warmUp(20, MAINCOLOR);

  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    while (1);
  }

  if (rtc.lostPower()) {
    Serial.println("RTC lost power, lets set the time!");

    // Comment out below lines once you set the date & time.
    // Following line sets the RTC to the date & time this sketch was compiled
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));

    // Following line sets the RTC with an explicit date & time
    // for example to set January 27 2017 at 12:56 you would call:
    // rtc.adjust(DateTime(2017, 1, 27, 12, 56, 0));
  }
}

void loop ()
{
  DateTime now = rtc.now();
  int hours = now.hour();
  int minutes = now.minute();

  // IF Midnight SET hours to 24
  // to not get negative hours
  if (hours == 0) {
    hours += 24;
  }
  // SET hours to UTC+1 PARIS
  hours = hours - 1;
  // SET hours to 0-12
  if (hours > 12) {
    hours = hours - 12;
  }
  // Set hours to get ex :"Trois heures moins cinq"
  if (minutes >= 35) {
    hours++;
  }

  displayTime(hours, minutes);
  strip.show();
  
  // Reload all ten seconds
  delay(10000);
}


// WARM UP LED
void warmUp(int temps, int color[3])
{

  for (int i = 0 ; i < PIXEL_COUNT ; i++)
  {
    strip.setPixelColor(i, color[0] , color[1] , color[2] );
    delay(temps);
    strip.show();
  }
}

void displayTime(int hours, int minutes) {

  // ON SUPPRIME LE RESIDU DE LEDS ALLUMEES
  for (int i = 0; i < PIXEL_COUNT; i++) {
    strip.setPixelColor(i, 0 , 0, 0);
  }
  int plural = false;
  paintWord(arrIlEst, MAINCOLOR, IL_EST_COUNT);
  if (hours > 1) {
    plural = true;
  }
  paintHours(hours);
  paintHourText(false);
  paintMinutes(minutes);



}

void progessiveBrightness(){
  for(int lumi = 0 ; lumi < 100 ; lumi++)
  {
    strip.setBrightness(lumi); 
  }
}

void paintWord(int arrWord[], int color[3], int COUNT) {
  
  // ON SET LES LEDS QU'ON DOIT ALLUMER
  for (int i = 0; i < COUNT; i++) {
    strip.setPixelColor(arrWord[i], color[0] , color[1], color[2]);
  }
}

void paintHourText(bool plural) {
  if (plural) {
    paintWord(arrHeures, MAINCOLOR, HEURES_COUNT);
  } else {
    paintWord(arrHeure, MAINCOLOR, HEURE_COUNT);
  }

}

void paintHours(int hours) {
  switch (hours) {
    case (0):
      paintWord(arrMinuit, MAINCOLOR, MINUIT_COUNT);
      break;
    case (1):
      paintWord(arrUne, MAINCOLOR, UNE_COUNT);
      break;
    case (2):
      paintWord(arrDeux, MAINCOLOR, DEUX_COUNT);
      break;
    case (3):
      paintWord(arrTrois, MAINCOLOR, TROIS_COUNT);
      break;
    case (4):
      paintWord(arrQuatre, MAINCOLOR, QUATRE_COUNT);
      break;
    case (5):
      paintWord(arrCinq, MAINCOLOR, CINQ_COUNT);
      break;
    case (6):
      paintWord(arrSix, MAINCOLOR, SIX_COUNT);
      break;
    case (7):
      paintWord(arrSept, MAINCOLOR, SEPT_COUNT);
      break;
    case (8):
      paintWord(arrHuit, MAINCOLOR, HUIT_COUNT);
      break;
    case (9):
      paintWord(arrNeuf, MAINCOLOR, NEUF_COUNT);
      break;
    case (10):
      paintWord(arrDix, MAINCOLOR, DIX_COUNT);
      break;
    case (11):
      paintWord(arrOnze, MAINCOLOR, ONZE_COUNT);
      break;
    case (12):
      paintWord(arrMidi, MAINCOLOR, MIDI_COUNT);
      break;
  }
}

void paintMinutes(int minutes) {
  // Colorisation des minutes 5 par 5 //
  if (minutes >= 5 && minutes < 10) {
    paintWord(arrCinqMinute, MAINCOLOR, CINQ_MIN_COUNT);


  }
  if (minutes >= 10 && minutes < 15) {
    paintWord(arrDixMinute, MAINCOLOR, DIX_MIN_COUNT);


  }
  if (minutes >= 15 && minutes < 20) {
    paintWord(arrEtQuart, MAINCOLOR, ET_QUART_COUNT);


  }
  if (minutes >= 20 && minutes < 25) {
    paintWord(arrVingt, MAINCOLOR, VINGT_COUNT);


  }
  if (minutes >= 25 && minutes < 30) {
    paintWord(arrVingtCinq, MAINCOLOR, VINGT_CINQ_COUNT);


  }
  if (minutes >= 30 && minutes < 35) {
    paintWord(arrDemie, MAINCOLOR, DEMIE_COUNT);
    paintWord(arrEtMinute, MAINCOLOR, ET_MIN_COUNT);

  }
  if (minutes >= 35 && minutes < 40) {
    paintWord(arrMoins, MAINCOLOR, MOINS_COUNT);
    paintWord(arrVingtCinq, MAINCOLOR, VINGT_CINQ_COUNT);

  }
  if (minutes >= 40 && minutes < 45) {
    paintWord(arrMoins, MAINCOLOR, MOINS_COUNT);
    paintWord(arrVingt, MAINCOLOR, VINGT_COUNT);

  }
  if (minutes >= 45 && minutes < 50) {
    paintWord(arrMoins, MAINCOLOR, MOINS_COUNT);
    paintWord(arrQuart, MAINCOLOR, QUART_COUNT);
  }
  if (minutes >= 50 && minutes < 55) {
    paintWord(arrMoins, MAINCOLOR, MOINS_COUNT);
    paintWord(arrDixMinute, MAINCOLOR, DIX_MIN_COUNT);

  }
  if (minutes >= 55 && minutes < 60) {
    paintWord(arrMoins, MAINCOLOR, MOINS_COUNT);
    paintWord(arrCinqMinute, MAINCOLOR, CINQ_MIN_COUNT);
  }
}
