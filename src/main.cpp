#include "WS_QMI8658.h"
#include "WS_Matrix.h"
// #include <Preferences.h>
// #include <nvs_flash.h>

#include <Preferences.h>
#include <nvs_flash.h>


#define BOOT_BUTTON_PIN 0

volatile int gameSelection = 0;

void IRAM_ATTR buttonISR()
{
  // 버튼이 눌렸을 때 실행할 코드
  Serial.println("BOOT 버튼이 눌렸습니다. 특정 코드 실행 중...");
  gameSelection++;
}

extern IMUdata Accel;
extern IMUdata Gyro;
IMUdata game;



void setup()
{
  Serial.begin(115200);

  pinMode(BOOT_BUTTON_PIN, INPUT_PULLUP); // 버튼을 입력 모드로 설정
  // 인터럽트 설정 (하강 엣지에서 트리거)
  attachInterrupt(digitalPinToInterrupt(BOOT_BUTTON_PIN), buttonISR, FALLING);

  QMI8658_Init();
  Matrix_Init();

}

int i = 0;
uint8_t X_EN = 0, Y_EN = 0, Time_X_A = 0, Time_X_B = 0, Time_Y_A = 0, Time_Y_B = 0;


void loop()
{
 

switch (gameSelection)
  {
  case 0:

  if (pcnt >= 100)
  {
    shiftUp();
    generateLine();
    pcnt = 0;
  }
  drawFrame(pcnt);
  matrix.show();
  pcnt += 30;

case 1:
    RGB_Matrix1(i);
    delay(30);
    i++;
    if (i == 24)
      i = 0;
    break;
  case 2:
    RGB_Matrix2(i);
    delay(60);
    i++;
    if (i == 16)
      i = 0;
    break;
  case 3:
    QMI8658_Loop();
    if (Accel.x > 0.15 || Accel.x < 0 || Accel.y > 0.15 || Accel.y < 0 || Accel.z > -0.9 || Accel.z < -1.1)
    {
      if (Accel.x > 0.15)
      {
        Time_X_A = Time_X_A + Accel.x * 10;
        Time_X_B = 0;
      }
      else if (Accel.x < 0)
      {
        Time_X_B = Time_X_B + std::abs(Accel.x) * 10;
        Time_X_A = 0;
      }
      else
      {
        Time_X_A = 0;
        Time_X_B = 0;
      }
      if (Accel.y > 0.15)
      {
        Time_Y_A = Time_Y_A + Accel.y * 10;
        Time_Y_B = 0;
      }
      else if (Accel.y < 0)
      {
        Time_Y_B = Time_Y_B + std::abs(Accel.y) * 10;
        Time_Y_A = 0;
      }
      else
      {
        Time_Y_A = 0;
        Time_Y_B = 0;
      }
      if (Time_X_A >= 10)
      {
        X_EN = 1;
        Time_X_A = 0;
        Time_X_B = 0;
      }
      if (Time_X_B >= 10)
      {
        X_EN = 2;
        Time_X_A = 0;
        Time_X_B = 0;
      }
      if (Time_Y_A >= 10)
      {
        Y_EN = 2;
        Time_Y_A = 0;
        Time_Y_B = 0;
      }
      if (Time_Y_B >= 10)
      {
        Y_EN = 1;
        Time_Y_A = 0;
        Time_Y_B = 0;
      }
      Game(X_EN, Y_EN);
      X_EN = 0;
      Y_EN = 0;
    }
    delay(10);
    break;
  case 4:
    Serial.println("BOOT 버튼이 눌렸습니다. 특정 코드 실행 중...");
    gameSelection = 0;
    break;
  default:
    break;
  }


}

/* void setup()
{
  Matrix_Init();
}
int x=0;

void loop()
{
  RGB_Matrix1(x);
  delay(30);
  x++;
  if(x==24)
    x=0;
}
 */