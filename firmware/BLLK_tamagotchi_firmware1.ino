#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>

#include "kaiser_sprites.h"

// Buttons are active-low: INPUT_PULLUP reads LOW when pressed.
#define BTN_LEFT   2   // SW1 -> GPIO2 / D0
#define BTN_MIDDLE 3   // SW2 -> GPIO3 / D1
#define BTN_RIGHT  4   // SW3 -> GPIO4 / D2

// Digital light detector input. Replace -1 with the GPIO you add in KiCad.
// If your detector outputs HIGH in darkness, change LIGHT_DARK_STATE to HIGH.
#define LIGHT_PIN -1
#define LIGHT_DARK_STATE LOW

// TODO: assign a real buzzer GPIO after fixing the schematic.
// In the screenshot, the buzzer appears tied to RES/GPIO20, which is also TFT_RST.
#define BUZZER_PIN -1

// ST7735 SPI display, 160 x 128 landscape.
#define TFT_CS   21 // LCD CS1
#define TFT_RST  20 // LCD RES
#define TFT_DC   10 // LCD DC
#define TFT_MOSI 9  // LCD SDA, per current schematic
#define TFT_SCLK 8  // LCD CLK
#define TFT_BLK  7

#define SCREEN_WIDTH  160
#define SCREEN_HEIGHT 128

Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_MOSI, TFT_SCLK, TFT_RST);

struct Pet {
  int hunger;        // 0 to 100 (0 = starving, 100 = full)
  int happiness;     // 0 to 100 (0 = miserable, 100 = delighted)
  int energy;        // 0 to 100 (0 = exhausted, 100 = fully rested)
  int health;        // 0 to 100 (0 = sick, 100 = healthy)
  unsigned long age; // total seconds the pet has been alive
};

Pet pet;

enum Screen {
  SCREEN_MAIN,
  SCREEN_FEED,
  SCREEN_PLAY,
  SCREEN_SLEEP
};

enum Pose {
  POSE_NORMAL,
  POSE_EATING,
  POSE_PLAYING,
  POSE_SLEEPING,
  POSE_RESTING
};

Screen currentScreen = SCREEN_MAIN;
Pose currentPose = POSE_NORMAL;

unsigned long lastUpdate = 0;
unsigned long lastButtonPress = 0;
unsigned long poseUntil = 0;
unsigned long lastDraw = 0;
bool roomIsDark = false;

const uint16_t COLOR_BG = ST77XX_WHITE;
const uint16_t COLOR_TEXT = ST77XX_BLACK;
const uint16_t COLOR_BAR_BG = 0xDEFB; // light gray
const uint16_t COLOR_HUNGER = 0xFD20; // orange
const uint16_t COLOR_ENERGY = ST77XX_BLUE;
const uint16_t COLOR_HAPPY = ST77XX_GREEN;
const uint16_t COLOR_HEALTH = ST77XX_RED;

const int SPRITE_X = 8;
const int SPRITE_Y = 24;

void setup() {
  pinMode(BTN_LEFT, INPUT_PULLUP);
  pinMode(BTN_MIDDLE, INPUT_PULLUP);
  pinMode(BTN_RIGHT, INPUT_PULLUP);
  if (LIGHT_PIN >= 0) {
    pinMode(LIGHT_PIN, INPUT);
  }
  if (BUZZER_PIN >= 0) {
    pinMode(BUZZER_PIN, OUTPUT);
  }
  pinMode(TFT_BLK, OUTPUT);
  digitalWrite(TFT_BLK, HIGH);

  tft.initR(INITR_BLACKTAB);
  tft.setRotation(1);
  tft.fillScreen(COLOR_BG);
  tft.setTextWrap(false);

  tft.setTextColor(COLOR_TEXT, COLOR_BG);
  tft.setTextSize(1);
  tft.setCursor(8, 8);
  tft.print("Kaiser Init...");
  delay(1000);

  pet.hunger = 80;
  pet.happiness = 80;
  pet.energy = 80;
  pet.health = 100;
  pet.age = 0;
}

void loop() {
  updateLightSensor();
  updatePet();
  checkButtons();
  handleScreenLogic();
  drawMainScreen();
}

void updateLightSensor() {
  if (LIGHT_PIN < 0) {
    roomIsDark = false;
    return;
  }

  roomIsDark = digitalRead(LIGHT_PIN) == LIGHT_DARK_STATE;
}

void updatePet() {
  if (millis() - lastUpdate > 5000) {
    pet.hunger--;
    pet.happiness--;
    pet.energy--;

    if (pet.hunger < 20 || pet.happiness < 20 || pet.energy < 20) {
      pet.health--;
    }

    pet.hunger = clampStat(pet.hunger);
    pet.happiness = clampStat(pet.happiness);
    pet.energy = clampStat(pet.energy);
    pet.health = clampStat(pet.health);

    pet.age += 5;
    lastUpdate = millis();
  }
}

void checkButtons() {
  if (millis() - lastButtonPress < 200) return;

  if (digitalRead(BTN_LEFT) == LOW) {
    currentScreen = SCREEN_FEED;
    beep(1000, 50);
    lastButtonPress = millis();
  } else if (digitalRead(BTN_MIDDLE) == LOW) {
    currentScreen = SCREEN_PLAY;
    beep(1200, 50);
    lastButtonPress = millis();
  } else if (digitalRead(BTN_RIGHT) == LOW) {
    currentScreen = SCREEN_SLEEP;
    beep(800, 50);
    lastButtonPress = millis();
  }
}

void handleScreenLogic() {
  switch (currentScreen) {
    case SCREEN_FEED:
      pet.hunger += 10;
      pet.health += 2;
      pet.hunger = clampStat(pet.hunger);
      pet.health = clampStat(pet.health);
      showPose(POSE_EATING, 900);
      currentScreen = SCREEN_MAIN;
      break;

    case SCREEN_PLAY:
      pet.happiness += 10;
      pet.energy -= 5;
      pet.happiness = clampStat(pet.happiness);
      pet.energy = clampStat(pet.energy);
      showPose(POSE_PLAYING, 900);
      currentScreen = SCREEN_MAIN;
      break;

    case SCREEN_SLEEP:
      pet.energy += 15;
      pet.health += 3;
      pet.energy = clampStat(pet.energy);
      pet.health = clampStat(pet.health);
      showPose(POSE_SLEEPING, 1200);
      currentScreen = SCREEN_MAIN;
      break;

    case SCREEN_MAIN:
      break;
  }
}

void drawMainScreen() {
  if (millis() - lastDraw < 100) return;
  lastDraw = millis();

  tft.fillScreen(COLOR_BG);
  drawStats();
  drawCurrentSprite();
}

void drawStats() {
  drawStatBar(86, 2, "HUNGRY", pet.hunger, COLOR_HUNGER);
  drawStatBar(86, 12, "ENERGY", pet.energy, COLOR_ENERGY);
  drawStatBar(86, 22, "HAPPY", pet.happiness, COLOR_HAPPY);
  drawStatBar(86, 32, "HEALTH", pet.health, COLOR_HEALTH);
}

void drawStatBar(int x, int y, const char *label, int value, uint16_t color) {
  const int barX = x + 42;
  const int barY = y + 1;
  const int barW = 22;
  const int barH = 6;
  const int fillW = map(value, 0, 100, 0, barW);

  tft.setTextColor(COLOR_TEXT, COLOR_BG);
  tft.setTextSize(1);
  tft.setCursor(x, y);
  tft.print(label);

  tft.drawRect(barX, barY, barW, barH, COLOR_TEXT);
  tft.fillRect(barX + 1, barY + 1, barW - 2, barH - 2, COLOR_BAR_BG);
  int innerFillW = fillW - 2;
  if (innerFillW < 0) innerFillW = 0;
  tft.fillRect(barX + 1, barY + 1, innerFillW, barH - 2, color);
}

void drawCurrentSprite() {
  const uint16_t *sprite = KAISER_NORMAL;

  if (roomIsDark) {
    sprite = KAISER_SLEEP;
  } else if (millis() < poseUntil) {
    switch (currentPose) {
      case POSE_EATING:
        sprite = KAISER_EAT;
        break;
      case POSE_PLAYING:
        sprite = KAISER_PLAY;
        break;
      case POSE_SLEEPING:
        sprite = KAISER_SLEEP;
        break;
      case POSE_RESTING:
        sprite = KAISER_REST;
        break;
      case POSE_NORMAL:
        sprite = KAISER_NORMAL;
        break;
    }
  } else if (pet.health < 40 || pet.energy < 30) {
    sprite = KAISER_REST;
  }

  tft.drawRGBBitmap(SPRITE_X, SPRITE_Y, sprite, KAISER_SPRITE_WIDTH, KAISER_SPRITE_HEIGHT);
}

void showPose(Pose pose, unsigned long durationMs) {
  currentPose = pose;
  poseUntil = millis() + durationMs;
}

int clampStat(int value) {
  if (value < 0) return 0;
  if (value > 100) return 100;
  return value;
}

void beep(unsigned int frequency, unsigned long durationMs) {
  if (BUZZER_PIN >= 0) {
    tone(BUZZER_PIN, frequency, durationMs);
  }
}
