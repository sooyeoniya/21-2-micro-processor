#include <LiquidCrystal.h>

LiquidCrystal lcd(7,8,9,10,11,12);

int button = 13;
int btn_now = 0, btn_last=0;
int count = 0;

void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2);
  lcd.clear();
  pinMode(button, INPUT);
}

void loop() {
  if(digitalRead(button)==LOW){
    count++;
    if(count == 4) count = 2;
  }
  if(count == 1){
    lcd.clear();
    Serial.println(digitalRead(button));
    lcd.setCursor(0,0);
    lcd.print("2020136129      2020136129      ");
    lcd.setCursor(0,1);
    lcd.print("CHOI SOO YEON   CHOI SOO YEON   ");
    delay(500);
  }
  if(count == 2){
    lcd.scrollDisplayLeft();
    delay(500);
  }
  if(count == 3){
    delay(1000);
  }
  if(count == 4){
    lcd.scrollDisplayLeft();
  }
}