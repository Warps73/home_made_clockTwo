#include <Wire.h>
#include <RTClib.h>
#include <Adafruit_NeoPixel.h> // Charge la librairie Neo Pixel d'Adafruit utilisé pour piloter le ruban de LED

#define PIXEL_PIN 6 // On définit le pin où est connecté la patte DATA du bandeau
#define PIXEL_COUNT 198 // On définit le nombre de LED compris sur le Ruban de LED soit 150 pour le ruban de 5m50

Adafruit_NeoPixel strip = Adafruit_NeoPixel(PIXEL_COUNT, PIXEL_PIN, NEO_GRB +  NEO_KHZ800); // Paramètre l'objet strip qui correspond à toute les LED du ruban

RTC_DS3231 rtc;
//RTC_DS1307 rtc;



/* Définition des couleurs */
//int RED[3] = {255, 0, 0}; // Couleur Rouge
//int GREEN[3] = {0, 255, 0}; // Couleur Verte
//int CYAN[3] = {0, 255, 255}; // Couleur Cyan
//int YELLOW[3] = {255, 125, 0}; // Couleur Jaune
//int ORANGE[3] = {255, 40, 0}; // Couleur Orange
//int PURPLE[3] = {255, 0, 255}; // Couleur Violette
//int PINK[3] = {255, 0, 100}; // Couleur Rose
//int BLUE[3] = {0, 0, 255}; // Couleur Bleu
//int WHITE[3] = {255, 255, 255}; // Couleur Blanche
int MAINCOLOR[3] = {30, 30, 30};
//int HALFON[3] = {127, 127, 127};
//int TIEREON[3] = {63, 63, 63};
//int QUARETERON[3] = {30, 30, 30};
//int OFF[3] = {0, 0, 0}; // Éteint





// Definition des mots
// the words
int arrIlEst[] = {111, 110, 108, 107, 106};
int IL_EST_COUNT = 5;
int arrDeux[] = {104, 103, 102, 101};
int DEUX_COUNT = 4;
int arrQuatre[] = {90, 91, 92, 93, 94, 95};
int QUATRE_COUNT = 6;
int arrTrois[] = {96, 97, 98, 99, 100};
int TROIS_COUNT = 5;
int arrNeuf[] = {89, 88, 87, 86};
int NEUF_COUNT = 4;
int arrUne[] = {85, 84, 83};
int UNE_COUNT = 3;
int arrSept[] = {82, 81, 80, 79};
int SEPT_COUNT = 4;
int arrHuit[] = {68, 69, 70, 71};
int HUIT_COUNT = 4;
int arrSix[] = {72, 73, 74};
int SIX_COUNT = 3;
int arrCinq[] = {75, 76, 77, 78};
int CINQ_COUNT = 4;
int arrMidi[] = {67, 66, 65, 64};
int MIDI_COUNT = 4;
int arrDix[] = {65, 64, 63};
int DIX_COUNT = 3;
int arrMinuit[] = {62, 61, 60, 59, 58, 57};
int MINUIT_COUNT = 6;
int arrOnze[] = {46, 47, 48, 49};
int ONZE_COUNT = 4;
int arrHeure[] = {51, 52, 53, 54, 55};
int HEURE_COUNT = 5;
int arrHeures[] = {51, 52, 53, 54, 55, 56};
int HEURES_COUNT = 6;
int arrMoins[] = {45, 44, 43, 42, 41};
int MOINS_COUNT = 5;
int arrLe[] = {38, 39};
int LE_COUNT = 2;
int arrDixMinute[] = {37, 36, 35};
int DIX_MIN_COUNT = 3;
int arrEtQuart[] = {24, 25, 27, 28, 29, 30, 31};
int ET_QUART_COUNT = 7;
int arrQuart[] = {27, 28, 29, 30, 31};
int QUART_COUNT = 5;
int arrVingt[] = {23, 22, 21, 20, 19};
int VINGT_COUNT = 5;
int arrVingtCinq[] = {23, 22, 21, 20, 19, 18, 17, 16, 15, 14};
int VINGT_CINQ_COUNT = 10;
int arrCinqMinute[] = {17, 16, 15, 14};
int CINQ_MIN_COUNT = 4;
int arrEtMinute[] = {1, 2};
int ET_MIN_COUNT = 2;
int arrDemie[] = {4, 5, 6, 7, 8};
int DEMIE_COUNT = 5;

int arrUneMintute[] = {112};
int UNE_MINUTE_COUNT = 1;
int arrDeuxMintute[] = {113};
int DEUX_MINUTE_COUNT = 1;
int arrTroisMintute[] = {12};
int TROIS_MINUTE_COUNT = 1;
int arrQuatreMintute[] = {0};
int QUATRE_MINUTE_COUNT = 1;

bool heureHiver = false;


void setup() {
  strip.begin(); // Lance la connection
  Serial.begin(9600);
  strip.show();
  warmUp(10, MAINCOLOR);

  if (!rtc.begin()) {
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
    rtc.adjust(DateTime(2020, 16, 02, 17, 27, 20));
  }
  //  rtc.adjust(DateTime(2019, 22, 12, 12, 12, 15));
  // Use this line to set the current date time
  //    rtc.adjust(DateTime(2020, 31, 05, 10,01, 50));
}

void loop() {
  DateTime now = rtc.now();
  int hours = now.hour();
  int minutes = now.minute();

  //  Serial.print(now.hour(), DEC);
  //  Serial.print(now.minute(), DEC);

  if (!heureHiver) {
    hours++;
  }

  // IF Midnight SET hours to 24
  // to not get negative hours
  if (hours > 20 || hours < 7 ) {
    strip.setBrightness(100);
  } else {
    strip.setBrightness(255);
  }
  Serial.print(strip.getBrightness());

  // Set hours if more than half an hour
  // ex :"Trois heures moins cinq"
  if (minutes > 34) {
    hours++;
  }

  // if midnight set hours to 0
  if (hours == 24) {
    hours = 0;
  }

  // SET hours to 0-12
  if (hours > 12) {
    hours = hours - 12;
  }



  displayTime(hours, minutes);
  strip.show();

  // Reloading all ten seconds
  //    delay(1500);

}


// WARM UP LED
void warmUp(int temps, int color[3]) {

  for (int i = PIXEL_COUNT; i > 0; i--) {
    strip.setPixelColor(i, color[0], color[1], color[2]);
    delay(temps);
    strip.show();
  }
}

void displayTime(int hours, int minutes) {

  // ON SUPPRIME LE RESIDU DE LEDS ALLUMEES
  for (int i = 0; i < PIXEL_COUNT; i++) {
    strip.setPixelColor(i, 0, 0, 0);
  }

  if (hours != 12 && hours != 0 ) {
    int plural = false;

    if (hours > 1) {
      plural = true;
    }
    paintHourText(plural);
  }

  paintWord(arrIlEst, MAINCOLOR, IL_EST_COUNT);
  paintHours(hours);
  paintMinutes(minutes);
  paintTinyMinutes(minutes);


}


void progressiveLightOff() {
  for (int j = 255; j > 0; j--) {
    for (int i = 0; i < PIXEL_COUNT; i++) {
      strip.setPixelColor(i, j, j, j);
    }
    strip.show();
  }
}


void progressiveLightOn() {
  for (int j = 0; j > 255; j++) {
    for (int i = 0; i < PIXEL_COUNT; i++) {
      strip.setPixelColor(i, j, j, j);
    }
    strip.show();
  }
}

void paintWord(int arrWord[], int color[3], int COUNT) {

  // ON SET LES LEDS QU'ON DOIT ALLUMER
  for (int i = 0; i < COUNT; i++) {
    strip.setPixelColor(arrWord[i], color[0], color[1], color[2]);
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
    paintWord(arrLe, MAINCOLOR, LE_COUNT);

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
void paintTinyMinutes(int minutes) {

  if (minutes == 1 || minutes == 11 || minutes == 21 || minutes == 31 || minutes == 41 || minutes == 51) {
    paintWord(arrUneMintute, MAINCOLOR, UNE_MINUTE_COUNT);
  }
  if (minutes == 2 || minutes == 12 || minutes == 22 || minutes == 32 || minutes == 42 || minutes == 52) {
    paintWord(arrUneMintute, MAINCOLOR, UNE_MINUTE_COUNT);
    paintWord(arrDeuxMintute, MAINCOLOR, DEUX_MINUTE_COUNT);
  }
  if (minutes == 3 || minutes == 13 || minutes == 23 || minutes == 33 || minutes == 43 || minutes == 53) {
    paintWord(arrUneMintute, MAINCOLOR, UNE_MINUTE_COUNT);
    paintWord(arrDeuxMintute, MAINCOLOR, DEUX_MINUTE_COUNT);
    paintWord(arrTroisMintute, MAINCOLOR, TROIS_MINUTE_COUNT);
  }
  if (minutes == 4 || minutes == 14 || minutes == 24 || minutes == 34 || minutes == 44 || minutes == 54) {
    paintWord(arrUneMintute, MAINCOLOR, UNE_MINUTE_COUNT);
    paintWord(arrDeuxMintute, MAINCOLOR, DEUX_MINUTE_COUNT);
    paintWord(arrTroisMintute, MAINCOLOR, TROIS_MINUTE_COUNT);
    paintWord(arrQuatreMintute, MAINCOLOR, QUATRE_MINUTE_COUNT);
  }

  if (minutes == 6 || minutes == 16 || minutes == 26 || minutes == 36 || minutes == 46 || minutes == 56) {
    paintWord(arrUneMintute, MAINCOLOR, UNE_MINUTE_COUNT);
  }
  if (minutes == 7 || minutes == 17 || minutes == 27 || minutes == 37 || minutes == 47 || minutes == 57) {
    paintWord(arrUneMintute, MAINCOLOR, UNE_MINUTE_COUNT);
    paintWord(arrDeuxMintute, MAINCOLOR, DEUX_MINUTE_COUNT);
  }
  if (minutes == 8 || minutes == 18 || minutes == 28 || minutes == 38 || minutes == 48 || minutes == 58) {
    paintWord(arrUneMintute, MAINCOLOR, UNE_MINUTE_COUNT);
    paintWord(arrDeuxMintute, MAINCOLOR, DEUX_MINUTE_COUNT);
    paintWord(arrTroisMintute, MAINCOLOR, TROIS_MINUTE_COUNT);
  }
  if (minutes == 9 || minutes == 19 || minutes == 29 || minutes == 39 || minutes == 49 || minutes == 59) {
    paintWord(arrUneMintute, MAINCOLOR, UNE_MINUTE_COUNT);
    paintWord(arrDeuxMintute, MAINCOLOR, DEUX_MINUTE_COUNT);
    paintWord(arrTroisMintute, MAINCOLOR, TROIS_MINUTE_COUNT);
    paintWord(arrQuatreMintute, MAINCOLOR, QUATRE_MINUTE_COUNT);
  }
}
