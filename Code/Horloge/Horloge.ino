#include <Adafruit_NeoPixel.h> // Charge la librairie Neo Pixel d'Adafruit utilisé pour piloter le ruban de LED

#define PIXEL_PIN 6 // On définit le pin où est connecté la patte DATA du bandeau
#define PIXEL_COUNT 114 // On définit le nombre de LED compris sur le Ruban de LED soit 150 pour le ruban de 5m50 150 le new ruban

Adafruit_NeoPixel strip = Adafruit_NeoPixel(PIXEL_COUNT, PIXEL_PIN, NEO_GRB + NEO_KHZ800); // Paramètre l'objet strip qui correspond à toute les LED du ruban

void setup() {
  strip.begin(); // Lance la connection
  strip.show(); // Initialise toute les led à 'off'
}

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

void loop() {
//  allLeds(WHITE, WHITE);
  strip.setBrightness(85); // Règle la luminosité à 100 % de la luminosité maximale
//  chenillardUp(10, WHITE);
  //  randLed();
    int leds[2] = { 113, 112}; // initialize array a
    specifcLed(leds, WHITE);

}


void randLed() {
  int L = random(0, 150);
  int r = random(0, 255);
  int g = random(0, 255);
  int b = random(0, 255);
  strip.setPixelColor(L, r, g, b);
  strip.show();
  delay(1000);
  strip.setPixelColor(L, 0, 0, 0);
  strip.show();
}
void allLeds(int COLOR1[], int COLOR2[])
{
  for (int i = 0 ; i < PIXEL_COUNT ; i++)
  {
    if (i % 2 == 0 ) {
      strip.setPixelColor(i, COLOR1[0], COLOR1[1], COLOR1[2]);
    } else {
      strip.setPixelColor(i, COLOR2[0], COLOR2[1], COLOR2[2]);
    }

  }
  strip.show();
}

void chenillardUp(int temps, int color[3])
{
  int r = random(0, 255);
  int g = random(0, 255);
  int b = random(0, 255);
  for (int i = 0 ; i < PIXEL_COUNT ; i++)
  {
    strip.setPixelColor(i, r , g , b );
    strip.show();
    delay(temps);
  }
  r = random(0, 255);
  g = random(0, 255);
  b = random(0, 255);
  for (int i = PIXEL_COUNT ; i > 0 ; i--)
  {
    strip.setPixelColor(i, r, g, b);
    strip.show();
    delay(temps);
  }
}


void specifcLed(int leds[2], int COLOR[3])
{
  //  for (int i = 0 ; i > 2 ; i++)
  //  {
  strip.setPixelColor(leds[0], COLOR[0], COLOR[1], COLOR[2]);
  strip.setPixelColor(leds[1], COLOR[0], COLOR[1], COLOR[2]);

  strip.show();
  //  }
}
