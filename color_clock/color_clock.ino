#include <M5Stack.h>
#include <WiFi.h>

#define JST 3600*9

//ここを変える
const char* ssid = "your wifi ssid";
const char* password = "your wifi password";

//M5stackでは2byteカラー
int color = 0xfffe;

int color_h[12] = {}; //時間の色
int color_m[60] = {}; //分の色

//初期値の色を宣言
int R = B11111;
int G = B000000;
int B = B00000;

int setColor(int color, int Red, int Green, int Blue){
  //RGBの値を設定する関数
  
  color = color | Red << 11;
  color = color | Green << 5;
  color = color | Blue;

  return color;
}

void setup(){
  M5.begin();
  delay(100);
  
  //Wifiの接続
  M5.Lcd.print("\n\nStart\n");
 
  WiFi.begin(ssid, password);
  while(WiFi.status() != WL_CONNECTED) {
    M5.Lcd.print('.');
    delay(500);
  }
  M5.Lcd.println();
  M5.Lcd.printf("Connected, IP address: ");
  M5.Lcd.println(WiFi.localIP());
  delay(500);
  M5.Lcd.fillScreen(BLACK); //表示している文字の削除
 
  configTime( JST, 0, "ntp.nict.jp", "ntp.jst.mfeed.ad.jp");

  float pi = 3.14;
  
  for(int i = 0; i <= 360; i++){ //色相環の作成
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
    
    if(i % 30 == 0){
      //時の色配列を作成
      color_h[i/30] = color;
    }
    if(i % 6 == 0){
      //分の色配列を作成
      color_m[i/6] = color;
    }
    color = 0;
  }
}

void loop(){
  time_t t;
  struct tm *tm;

  t = time(NULL);
  tm = localtime(&t);
  
  //時間によって色を変える
  M5.Lcd.fillCircle(60,60,40,color_h[tm->tm_hour % 12]);
  M5.Lcd.fillCircle(160,60,40,color_m[tm->tm_min]);
  M5.Lcd.fillCircle(260,60,40,color_m[tm->tm_sec]);
  
  delay(1000);
}
