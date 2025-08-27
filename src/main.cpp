#include <Arduino.h>
#include <SPI.h>
#include <WiFi.h>
#include <WiFiManager.h>
#include <FirebaseClient.h>
#include <WiFiClientSecure.h>
#include <FS.h>
#include <LittleFS.h>

#include "system.h"
#include "credential.h"
#include "definitions.h"
#include "externalFunc.h"
#include "WS_QMI8658.h"
#include "WS_Matrix.h"

#define FILESYSTEM LittleFS
#define FORMAT_LITTLEFS_IF_FAILED true

extern IMUdata Accel;
extern IMUdata Gyro;
IMUdata game;

int i = 0;
uint8_t X_EN = 0, Y_EN = 0, Time_X_A = 0, Time_X_B = 0, Time_Y_A = 0, Time_Y_B = 0;

// 부드러운 기울기 효과를 위한 변수들
float smoothAccelX = 0.0;
const float smoothingFactor = 0.1; // 0.1 = 매우 부드럽게, 0.9 = 빠르게 반응

void setup()
{
  Serial.begin(115200);
  QMI8658_Init();
  Matrix_Init();

  // wifi매니저 세팅
  wifiSetup();
  // 외부 ip 세팅
  getExternalIP();
  // firebase 세팅
  firebaseSetup();
}

void loop()
{
  app.loop();
  database.loop();
  storage.loop();
  if (pcnt >= 100)
  {
    shiftUp();
    
    // 테스트 모드 ON/OFF (true = 테스트, false = 실제 센서)
    bool testMode = false; // 실제 센서 사용으로 변경
    
    float finalTilt = 0.0;
    
    if (testMode)
    {
      // 테스트용: 부드럽게 좌우로 흔들리는 효과
      static unsigned long lastTime = 0;
      if (millis() - lastTime > 50) // 50ms마다 업데이트
      {
        float timeInSeconds = millis() / 1000.0;
        finalTilt = 0.6 * sin(timeInSeconds * 0.3); // 약 3.3초 주기로 왕복, 진폭 줄임
        lastTime = millis();
      }
      Serial.printf("Test mode - Tilt: %.3f\n", finalTilt);
    }
    else
    {
      // 실제 가속도센서 값 사용 (스무딩 적용)
      finalTilt = smoothAccelX;
    }
    
    generateLineWithTilt(finalTilt);
    
    // 기울기 효과 디버깅 출력
    static unsigned long lastTiltPrint = 0;
    if (millis() - lastTiltPrint > 500) // 0.5초마다 출력
    {
      Serial.printf("Final tilt: %.3f (mode: %s)\n", finalTilt, testMode ? "TEST" : "SENSOR");
      lastTiltPrint = millis();
    }
    
    pcnt = 0;
  }
  drawFrame(pcnt);
  matrix.show();
  pcnt += 30;
  if (app.ready() && millis() - timeout > 100)
  {
    timeout = millis();
    if (taskComplete != 0)
    {
      Serial.println("start get latest version data");
      database.get(aClient1, "/Firmware/version", asyncCB, false, "getFirmwareVersionTask");

      Serial.println("start set data");
      localIp = WiFi.localIP().toString();
      database.set<float>(aClient3, "/Controller/" + macID + "/version", version, asyncCB, "setVersionTask");
      database.set<String>(aClient3, "/Controller/" + macID + "/ID", macID, asyncCB, "setIDTask");
      database.set<String>(aClient3, "/Controller/" + macID + "/IP", localIp, asyncCB, "setIPTask");
      database.set<String>(aClient3, "/Controller/" + macID + "/physicalIP", physicalIP, asyncCB, "setphysicalIPTask");

      
      taskComplete = 0;
    }
  }
  if (millis() - timeout > 10)
  {
    timeout = millis();
    QMI8658_Loop();
    
    // 가속도센서 값 스무딩 (부드러운 움직임을 위해)
    smoothAccelX = smoothAccelX * (1.0 - smoothingFactor) + Accel.x * smoothingFactor;
    
    // 가속도센서 값 디버깅 출력
    static unsigned long lastPrint = 0;
    if (millis() - lastPrint > 500) // 0.5초마다 출력
    {
      Serial.printf("Accel X: %.3f -> Smooth: %.3f, Y: %.3f, Z: %.3f\n", Accel.x, smoothAccelX, Accel.y, Accel.z);
      lastPrint = millis();
    }
    
    /* 움직이는 닷 게임 주석처리
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
    */
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