const int redPin = 11;
const int greenPin = 12;
const int bluePin = 13;

int red_bs = 0;//яркость светодиода1 (0-255)
int green_bs = 0;//яркость светодиода2 (0-255)
int blue_bs = 0;//яркость светодиода3 (0-255)

const byte rainbow[8][3] = {
    {0,255,255}, // красный
    {0,0,255}, // жёлтый
    {255,0,255}, // зелёный
    {255,0,0}, // голубой
    {255,255,0}, // синий
    {0,255,0}, // фиолетовый
    {0,0,0} // белый
};

void setColorRgb(int red, int green, int blue) {
  analogWrite(redPin, red);
  analogWrite(greenPin, green);
  analogWrite(bluePin, blue);
}

void changeColor(int to_red, int to_green, int to_blue, int pause) {
  while(red_bs!=to_red||green_bs!=to_green||blue_bs!=to_blue){
    if(to_red!=red_bs)
      if(to_red>red_bs)red_bs++;
      else red_bs--;
    if(to_green!=green_bs)
      if(to_green>green_bs)green_bs++;
      else green_bs--;
    if(to_blue!=blue_bs)
      if(to_blue>blue_bs)blue_bs++;
      else blue_bs--;
    if(pause)delay(pause);
    setColorRgb(red_bs, green_bs, blue_bs);
  }
}

void setup() {
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
}

void loop() {
  randomSeed(analogRead(0));
  changeColor(rand(),rand(),rand(),20);
  changeColor(255,255,255,25);
  delay(2000);
/*
  unsigned int rgbColor[3] = {0,255,255};
  for (int i=0; i<7; i++) {
    int r = rainbow[i][0];
    int g = rainbow[i][1];
    int b = rainbow[i][2];
    setColorRgb(r,g,b);
    delay(500);
  }
  //R->Y
  for (int i=255; i>=0; i--) {
    rgbColor[0] = 255 - i;
    rgbColor[1] = i;
    setColorRgb(rgbColor[0], rgbColor[1], rgbColor[2]);
    delay(10);
  }
  //G->lB
  rgbColor[1] = 0;
  for (int i=255;i>=0;i--) {
    rgbColor[2] = i;
    setColorRgb(rgbColor[0], rgbColor[1], rgbColor[2]);
    delay(10);
  }
  //G->B
  for (int i=255;i>=0;i--) {
    rgbColor[1] = 255 - i;
    setColorRgb(rgbColor[0], rgbColor[1], rgbColor[2]);
    delay(10);
  }
  //B->P
  for (int i=255;i>=0;i--) {
    rgbColor[0] = i;
    rgbColor[2] = 255 - i;
    setColorRgb(rgbColor[0], rgbColor[1], rgbColor[2]);
    delay(30);
  }
  */
}
