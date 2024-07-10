#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET    -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

int ballX = 20;
int ballY = 30;
int ballSize = 3;
int ballSpeedX = 2;
int ballSpeedY = 2;

void drawGoalpost() {
  display.drawRect(0, 20, 5, 24, SSD1306_WHITE);  
  display.drawRect(SCREEN_WIDTH - 5, 20, 5, 24, SSD1306_WHITE);  
}

void drawPlayer(int x, int y) {
  display.fillRect(x, y, 5, 10, SSD1306_WHITE);  
  display.fillCircle(x + 2, y - 2, 3, SSD1306_WHITE);  
}

void setup() {
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;);
  }
  display.clearDisplay();
  display.display();
}

void loop() {
  display.clearDisplay();
  drawGoalpost();
  int playerX = 50;
  int playerY = 40;
  drawPlayer(playerX, playerY);
  
  display.fillCircle(ballX, ballY, ballSize, SSD1306_WHITE);

  ballX += ballSpeedX;
  ballY += ballSpeedY;

  if (ballX <= 0 || ballX >= (SCREEN_WIDTH - ballSize)) {
    ballSpeedX = -ballSpeedX;
  }
  if (ballY <= 0 || ballY >= (SCREEN_HEIGHT - ballSize)) {
    ballSpeedY = -ballSpeedY;
  }

  if (ballX >= playerX && ballX <= playerX + 5 && ballY >= playerY - 2 && ballY <= playerY + 10) {
    ballSpeedX = -ballSpeedX;
    ballSpeedY = -ballSpeedY;
  }

  if (ballX <= 5 && ballY >= 20 && ballY <= 44) {
    ballSpeedX = -ballSpeedX;
  }
  if (ballX >= SCREEN_WIDTH - 5 - ballSize && ballY >= 20 && ballY <= 44) {
    ballSpeedX = -ballSpeedX;
  }

  display.display();
  delay(50);
}

