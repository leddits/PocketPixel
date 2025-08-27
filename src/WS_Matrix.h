#ifndef _WS_Matrix_H_
#define _WS_Matrix_H_
#include <Adafruit_GFX.h>
#include <Adafruit_NeoPixel.h>
#include <Adafruit_NeoMatrix.h>

#define RGB_Control_PIN 14
#define Matrix_Row 8
#define Matrix_Col 8
#define RGB_COUNT         64     
#define COLOR_X           20     


extern int pcnt;
extern Adafruit_NeoMatrix matrix;
extern float tiltOffset; // 불꽃 기울기 오프셋

void shiftUp();                         
void generateLine();
void generateLineWithTilt(float accelX); // 기울기 적용된 라인 생성                         
void drawFrame(int pcnt);

void RGB_Matrix();                         
void RGB_Matrix1(int x);                         
void RGB_Matrix2(int x);                         
void Game(uint8_t X_EN,uint8_t Y_EN);

void Matrix_Init();                                     
#endif