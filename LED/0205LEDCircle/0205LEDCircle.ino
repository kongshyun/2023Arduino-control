#include <Adafruit_NeoPixel.h>

#define LED_PIN    6
#define LED_COUNT  256

Adafruit_NeoPixel matrix(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  matrix.begin();
  matrix.setBrightness(80); // 50% brightness (0-255 scale)
  matrix.show();
}

void loop() {
  // Clear the matrix
  matrix.clear();

  // Draw a circle in the center
  drawCircle(matrix.Color(255, 255, 255), 50);

  // Show the updated matrix
  matrix.show();
  delay(1000);  // You can adjust the delay according to your preference
}

// Function to draw a circle in the center of the LED matrix
void drawCircle(uint32_t color, int wait) {
  int centerX = 8;  // X-coordinate of the center
  int centerY = 8;  // Y-coordinate of the center
  int radius = 6;   // Radius of the circle

  for (int x = 0; x < 16; x++) {
    for (int y = 0; y < 16; y++) {
      // Check if the pixel is within the circle
      if (pow(x - centerX, 2) + pow(y - centerY, 2) <= pow(radius, 2)) {
        matrix.setPixelColor(x + y * 16, color);
      }
    }
  }
}
