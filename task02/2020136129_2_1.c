int leds[] = {2, 3, 4, 5, 6, 7, 8, 9};
int led_num = 8;  //7세그먼트 led
int button = 13;  //택트 스위치 핀번호
int num = 0;      //현재 led에 표시되고 있는 숫자
int all[2][8] = {{1, 1, 1, 1, 1, 1, 1, 1}, {0, 0, 0, 0, 0, 0, 0, 0}};
int set_button[8][8] = {
{1, 0, 0, 0, 0, 0, 0, 0}, //a
{1, 1, 0, 0, 0, 0, 0, 0}, //a, b
{1, 1, 1, 0, 0, 0, 0, 0}, //a, b, c
{1, 1, 1, 1, 0, 0, 0, 0}, //a, b, c, d
{1, 1, 1, 1, 1, 0, 0, 0}, //a, b, c, d, e
{1, 1, 1, 1, 1, 1, 0, 0}, //a, b, c, d, e, f
{1, 1, 1, 1, 1, 1, 1, 0}, //a, b, c, d, e, f, g
{1, 1, 1, 1, 1, 1, 1, 1}  //a, b, c, d, e, f, g, .
};
int set_number[10][8] = {
{1, 1, 1, 1, 1, 1, 0, 0}, //0
{0, 1, 1, 0, 0, 0, 0, 0}, //1
{1, 1, 0, 1, 1, 0, 1, 0}, //2
{1, 1, 1, 1, 0, 0, 1, 0}, //3
{0, 1, 1, 0, 0, 1, 1, 0}, //4
{1, 0, 1, 1, 0, 1, 1, 0}, //5
{1, 0, 1, 1, 1, 1, 1, 0}, //6
{1, 1, 1, 0, 0, 0, 0, 0}, //7
{1, 1, 1, 1, 1, 1, 1, 0}, //8
{1, 1, 1, 1, 0, 1, 1, 0}  //9
};
int set_alpha[26][8] = {
  {1, 1, 1, 1, 1, 0, 1, 0}, //a
  {0, 0, 1, 1, 1, 1, 1, 0}, //b
  {0, 0, 0, 1, 1, 0, 1, 0}, //c
  {0, 1, 1, 1, 1, 0, 1, 0}, //d
  {1, 1, 0, 1, 1, 1, 1, 0}, //e
  {1, 0, 0, 0, 1, 1, 1, 0}, //f
  {1, 1, 1, 1, 0, 1, 1, 0}, //g
  {0, 0, 1, 0, 1, 1, 0, 0}, //h
  {0, 1, 1, 0, 0, 0, 0, 0}, //i
  {0, 1, 1, 1, 0, 0, 0, 0}, //j
  {0, 0, 0, 0, 0, 0, 1, 0}, //k
  {0, 1, 1, 0, 0, 0, 0, 0}, //l
  {0, 0, 0, 0, 0, 0, 1, 0}, //m
  {0, 0, 1, 0, 1, 0, 1, 0}, //n
  {0, 0, 1, 1, 1, 0, 1, 0}, //o
  {1, 1, 0, 0, 1, 1, 1, 0}, //p
  {1, 1, 1, 0, 0, 1, 1, 0}, //q
  {0, 0, 0, 0, 1, 0, 1, 0}, //r
  {1, 0, 1, 1, 0, 1, 1, 0}, //s
  {0, 0, 0, 1, 1, 1, 1, 0}, //t
  {0, 0, 1, 1, 1, 0, 0, 0}, //u
  {0, 0, 1, 1, 1, 0, 0, 0}, //v
  {0, 0, 0, 0, 0, 0, 1, 0}, //w
  {0, 0, 0, 0, 0, 0, 1, 0}, //x
  {0, 1, 1, 1, 0, 1, 1, 0}, //y
  {1, 1, 0, 1, 1, 0, 1, 0}  //z
};

void setup() {
  for (int i = 0 ; i < led_num ; i++){ // 7 세그먼트 led에 연결된 핀을 출력으로 설정
    pinMode(leds[i], OUTPUT);
  }
  pinMode(button, INPUT_PULLUP); // 택트 스위치를 input_pullup으로 설정
}

void loop() {
  while(1){
    if(digitalRead(button) == LOW){ // 버튼이 한 번 눌릴 때마다 LED 차례로 on
      if(num == 8) break;
      else{
        for(int j = 0; j < led_num; j++){
          digitalWrite(leds[j], set_button[num][j]);
        }
        num++;
      }
    }
    delay(300);
  }

  while(1){
    if(digitalRead(button) == LOW){
      if(num == 8){
        for(int i = 0; i < 10; i++){    // 버튼 클릭 시 숫자 출력
          for(int j = 0; j < led_num; j++){
            digitalWrite(leds[j], set_number[i][j]);
          }
          delay(1000);
        }
      }
      if(num == 9){
        for(int i = 0; i < 26; i++){    // 버튼 클릭 시 알파벳 출력
          for(int j = 0; j < led_num; j++){
            digitalWrite(leds[j], set_alpha[i][j]);
          }
          delay(500);
        }
        for(int i = 0; i < 3; i++){
          for(int j = 0; j < led_num; j++){ // 전부 켜기
            digitalWrite(leds[j], all[0][j]);
          }
          delay(1000);
          for(int j = 0; j < led_num; j++){ // 전부 끄기
            digitalWrite(leds[j], all[1][j]);
          }
          delay(1000);
        }
        break;
      }
      num++;
    }
  }
  num = 0;
}