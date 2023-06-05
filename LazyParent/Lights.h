
int HSVtoRGB(float h, float s, float v) {
  int r, g, b;
  int i = int(h / 60) % 6;
  float f = h / 60 - i;
  float p = v * (1 - s);
  float q = v * (1 - f * s);
  float t = v * (1 - (1 - f) * s);

  switch (i) {
    case 0:
      r = int(v * 255);
      g = int(t * 255);
      b = int(p * 255);
      break;
    case 1:
      r = int(q * 255);
      g = int(v * 255);
      b = int(p * 255);
      break;
    case 2:
      r = int(p * 255);
      g = int(v * 255);
      b = int(t * 255);
      break;
    case 3:
      r = int(p * 255);
      g = int(q * 255);
      b = int(v * 255);
      break;
    case 4:
      r = int(t * 255);
      g = int(p * 255);
      b = int(v * 255);
      break;
    case 5:
      r = int(v * 255);
      g = int(p * 255);
      b = int(q * 255);
      break;
  }

  return (r << 16) | (g << 8) | b;
}

void rainbow() {
  int pixelCount = CircuitPlayground.strip.numPixels();

  // Set the hue increment for each pixel
  float hueIncrement = 360.0 / pixelCount;

  // Iterate through each pixel and set its color
  for (int i = 0; i < pixelCount; i++) {
    float hue = i * hueIncrement;
    int color = HSVtoRGB(hue, 1.0, 1.0);
    CircuitPlayground.strip.setPixelColor(i, color);
  }

  CircuitPlayground.strip.show();
  delay(100); // Adjust the delay time to change the speed of the rainbow effect
}