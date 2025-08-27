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
  // Firebase 관련 부분 임시 주석처리 (에러 방지용)
  /*
  app.loop();
  database.loop();
  storage.loop();
  */
  
  if (pcnt >= 100)
  {
    shiftUp();
    // Y축으로 좌우 기울기 적용 + 더 강한 증폭
    generateLineWithTilt(Accel.y * 1.5); // Y축 값이 작으니 1.5배 증폭
    
    // 기울기 효과 확인용 출력
    static unsigned long lastDebug = 0;
    if (millis() - lastDebug > 1000)
    {
      float amplifiedY = Accel.y * 1.5;
      float centerShift = -amplifiedY * 4.5;
      int tiltedCenter = (Matrix_Col / 2) + (int)round(centerShift);
      if (tiltedCenter < 0) tiltedCenter = 0;
      if (tiltedCenter >= Matrix_Col) tiltedCenter = Matrix_Col - 1;
      
      Serial.printf("Accel.y: %.3f -> Amplified: %.3f -> Center: %d\n", Accel.y, amplifiedY, tiltedCenter);
      lastDebug = millis();
    }
    
    pcnt = 0;
  }
  drawFrame(pcnt);
  matrix.show();
  pcnt += 30;
  
  // Firebase 관련 부분 임시 주석처리 (에러 방지용)
  /*
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
  */
  if (millis() - timeout > 10)
  {
    timeout = millis();
    QMI8658_Loop();
    
    // 모든 축 출력해서 어느 축이 좌우 기울기인지 확인
    static unsigned long lastPrint = 0;
    if (millis() - lastPrint > 500) // 0.5초마다 출력
    {
      Serial.printf("Accel X: %.2f, Y: %.2f, Z: %.2f\n", Accel.x, Accel.y, Accel.z);
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