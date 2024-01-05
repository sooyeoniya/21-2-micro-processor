#include <LiquidCrystal.h>
#include <core_build_options.h>
#include <swRTC.h>

LiquidCrystal lcd(12,10,5,4,3,2);        //RS 핀, E핀, 데이터 핀 4개
String lcdString = "";                   //객체 선언 : 출력 할 글자 저장

swRTC rtc;

int num = 0;
int count = 1;
int piezo = 6;
int echoPin = 7;
int trigPin = 8;
int switchPin1 = A1;
int switchPin2 = A2;
int switchPin3 = A3;
int switchPin4 = A4;
int temp;
long duration, cm;

//AM PM을 구분해 주는 함수
void Set_AMPM(int hour) {
  if(hour >=12)
    lcd.print("PM");
  else
    lcd.print("AM");
  lcd.print(hour%12, DEC);     //시간 출력
}

//10보다 작은수를 출력할때 앞에 0을 출력하게 하는 함수
void Set_lowThanTen(int time) {
  if(time < 10) {
    lcd.print("0");
    lcd.print(time%10);
  }
  else
    lcd.print(time);
}

//유효한 알람시간인지 체크하는 함수
int checkTheAlarmClock(int time) {
  if(time/100 < 24 && time %100 < 60) {
    Serial.println("알람이 설정되었습니다.");
    return time;
  }
  else {
    Serial.println("유효한 알람시간이 아닙니다.");
    return 0;
  }
}

//알람이 울릴시간인지 체크하는 함수
void checkTheAlarmTime(int alarmHour, int alarmMinute) {
  if(alarmHour == rtc.getHours() && alarmMinute == rtc.getMinutes()) {
        analogWrite(piezo, 523);
    }
}

//setup문
void setup() {
  lcd.begin(16,2);         //LCD 크기 지정, 2줄 16칸
  lcd.clear();             //화면 초기화
  rtc.stopRTC();           //정지
  rtc.setTime(17,43,30);    //시간, 분, 초 초기화
  rtc.setDate(12, 12, 2021);  //일, 월, 년 초기화
  rtc.startRTC();          //시작

  pinMode(piezo, OUTPUT);
  pinMode(switchPin1, INPUT_PULLUP); //HIGH(OFF), LOW(ON) -> 풀업(PULL-UP)
  pinMode(switchPin2, INPUT_PULLUP);
  pinMode(switchPin3, INPUT_PULLUP);
  pinMode(switchPin4, INPUT_PULLUP);
  Serial.begin(9600);                    //시리얼 포트 초기화
  Serial.begin(9600);                    //시리얼 통신 초기화
}

//loop문
void loop() {
  int day;
  lcd.setCursor(0,0);                    //커서를 0,0에 지정
  //날짜를 LCD에 출력
  lcd.print("[");
  Set_lowThanTen(rtc.getMonth());
  lcd.print("/");
  Set_lowThanTen(rtc.getDay());
  lcd.print("]");
  //1초 단위로 갱신하며 현재시간을 LCD에 출력
  Set_AMPM(rtc.getHours());
  lcd.print(":");
  Set_lowThanTen(rtc.getMinutes());
  lcd.print(":");
  Set_lowThanTen(rtc.getSeconds());
  //세팅된 알람시간을 LCD에 출력
  lcd.setCursor(0,1);                    //커서를 0,1에 지정
  lcd.print("Alarm ");
  Set_AMPM(temp/100);
  lcd.print(":");
  Set_lowThanTen(temp%100);

  //1초마다 LCD갱신
  lcdString = "";                      //문자열 초기화
  lcd.print("               ");        //전 글씨 삭제
  delay(1000);

  //알람이 울릴 시간인지 체크
  checkTheAlarmTime(temp/100, temp%100);

  //초음파 감지
  digitalWrite(trigPin, LOW);
  delayMicroseconds(5);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  cm = (duration/2) * 0.0343;

  //스위치버튼이 눌렸을 경우 피에조센서의 소리를 0으로 하고 알람시간을 초기화
  if(num == 0 && !digitalRead(switchPin1)){
    num++;
    //Serial.println(num);
    Serial.print("*");
  }
  if(num == 1 && !digitalRead(switchPin3)){
    num++;
    //Serial.println(num);
    Serial.print("*");
  }
  if(num == 2 && !digitalRead(switchPin2)){
    num++;
    //Serial.println(num);
    Serial.print("*");
  }
  if(num == 3 && !digitalRead(switchPin4)){
    num++;
    //Serial.println(num);
    Serial.println("*");
  }
  if(num == 4){
    temp = 0;
    day = 0;
    analogWrite(piezo, 0);
    Serial.println("알람이 초기화되었습니다.");
    Serial.println("AM0:00");
    num = 0;
  }

  //시리얼 통신을 통해 알람시간을 입력받고 시리얼 모니터에 출력
  char theDay[4];
  int i = 0;
  if(Serial.available()) {
    count = 1;
    while(Serial.available()) {
      theDay[i] = Serial.read();
      i++;
    }
    day = atoi(theDay); // 문자열 → 정수
    if(day/100 >= 12) {
      Serial.print("PM");
      Serial.print((day/100)-12);
    }
    else {
      Serial.print("AM");
      Serial.print(day/100);
    }
    Serial.print(":");
    if(day%100 < 10)
      Serial.print("0");
    Serial.println(day%100);
    temp = checkTheAlarmClock(day);
  }

  //초음파에 20cm 이하로 물체가 감지되었을 때 알람시간을 1분 뒤로 재설정
  if(cm <= 20){
    Serial.print(cm);
    Serial.print("cm");
    Serial.println();
    analogWrite(piezo, 0);
    Serial.println("알람이 1분 뒤 다시 울립니다.");
    day = atoi(theDay);
    day += count;
    count++;
    if(day/100 >= 12) {
      Serial.print("PM");
      Serial.print((day/100)-12);
    }
    else {
      Serial.print("AM");
      Serial.print(day/100);
    }
    Serial.print(":");
    if(day%100 < 10)
      Serial.print("0");
    Serial.println(day%100);
    temp = checkTheAlarmClock(day);
  }
}