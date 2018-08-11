#include <M5Stack.h>

int color = 0xfffe;

int R = B111111;
int G = B000000;
int B = B000000;

int setColor(int color, int Red, int Green, int Blue){
  color = color | Red << 11;
  color = color | Green << 5;
  color = color | Blue;

  return color;
}

void setup(){
  M5.begin();
  
  float pi = 3.14;
  
  for(int i = 0; i < 360; i++){ 
    int angle = i-90;
    float rad = float(angle) * (pi/ 180);
    
    int x1 = 160 + 40 * cos(rad);
    int y1 = 180 + 40 * sin(rad);

    if(0 <= i && i < 60){
      G++;
    }
    if(60 <= i && i < 120){
      R--;
    }
    if(120 <= i && i < 180){
      B++;
    }
    if(180 <= i && i < 240){
      G--;
    }
    if(240 <= i && i < 300){
      R++;
    }
    if(300 <= i && i < 360){
      B--;
    }
    color = setColor(color, R/2, G, B/2);
    M5.Lcd.drawLine(x1, y1, 160, 180, color);
    color = 0;
  }
}

void loop(){
  
}

