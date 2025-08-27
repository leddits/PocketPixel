#include "WS_Matrix.h"

float tiltOffset = 0.0; // 불꽃 기울기 오프셋
uint8_t RGB_Data[3] = {100, 100, 30};
uint8_t RGB_Data1[64][3] = {};
uint8_t RGB_Data2[192][3] = {
    {64, 1, 0}, {63, 2, 0}, {62, 3, 0}, {61, 4, 0}, {60, 5, 0}, {59, 6, 0}, {58, 7, 0}, {57, 8, 0}, {56, 9, 0}, {55, 10, 0}, {54, 11, 0}, {53, 12, 0}, {52, 13, 0}, {51, 14, 0}, {50, 15, 0}, {49, 16, 0}, {48, 17, 0}, {47, 18, 0}, {46, 19, 0}, {45, 20, 0}, {44, 21, 0}, {43, 22, 0}, {42, 23, 0}, {41, 24, 0}, {40, 25, 0}, {39, 26, 0}, {38, 27, 0}, {37, 28, 0}, {36, 29, 0}, {35, 30, 0}, {34, 31, 0}, {33, 32, 0}, {32, 33, 0}, {31, 34, 0}, {30, 35, 0}, {29, 36, 0}, {28, 37, 0}, {27, 38, 0}, {26, 39, 0}, {25, 40, 0}, {24, 41, 0}, {23, 42, 0}, {22, 43, 0}, {21, 44, 0}, {20, 45, 0}, {19, 46, 0}, {18, 47, 0}, {17, 48, 0}, {16, 49, 0}, {15, 50, 0}, {14, 51, 0}, {13, 52, 0}, {12, 53, 0}, {11, 54, 0}, {10, 55, 0}, {9, 56, 0}, {8, 57, 0}, {7, 58, 0}, {6, 59, 0}, {5, 60, 0}, {4, 61, 0}, {3, 62, 0}, {2, 63, 0}, {1, 64, 0}, {0, 64, 1}, {0, 63, 2}, {0, 62, 3}, {0, 61, 4}, {0, 60, 5}, {0, 59, 6}, {0, 58, 7}, {0, 57, 8}, {0, 56, 9}, {0, 55, 10}, {0, 54, 11}, {0, 53, 12}, {0, 52, 13}, {0, 51, 14}, {0, 50, 15}, {0, 49, 16}, {0, 48, 17}, {0, 47, 18}, {0, 46, 19}, {0, 45, 20}, {0, 44, 21}, {0, 43, 22}, {0, 42, 23}, {0, 41, 24}, {0, 40, 25}, {0, 39, 26}, {0, 38, 27}, {0, 37, 28}, {0, 36, 29}, {0, 35, 30}, {0, 34, 31}, {0, 33, 32}, {0, 32, 33}, {0, 31, 34}, {0, 30, 35}, {0, 29, 36}, {0, 28, 37}, {0, 27, 38}, {0, 26, 39}, {0, 25, 40}, {0, 24, 41}, {0, 23, 42}, {0, 22, 43}, {0, 21, 44}, {0, 20, 45}, {0, 19, 46}, {0, 18, 47}, {0, 17, 48}, {0, 16, 49}, {0, 15, 50}, {0, 14, 51}, {0, 13, 52}, {0, 12, 53}, {0, 11, 54}, {0, 10, 55}, {0, 9, 56}, {0, 8, 57}, {0, 7, 58}, {0, 6, 59}, {0, 5, 60}, {0, 4, 61}, {0, 3, 62}, {0, 2, 63}, {0, 1, 64},

    {1, 0, 64},
    {2, 0, 63},
    {3, 0, 62},
    {4, 0, 61},
    {5, 0, 60},
    {6, 0, 59},
    {7, 0, 58},
    {8, 0, 57},
    {9, 0, 56},
    {10, 0, 55},
    {11, 0, 54},
    {12, 0, 53},
    {13, 0, 52},
    {14, 0, 51},
    {15, 0, 50},
    {16, 0, 49},
    {17, 0, 48},
    {18, 0, 47},
    {19, 0, 46},
    {20, 0, 45},
    {21, 0, 44},
    {22, 0, 43},
    {23, 0, 42},
    {24, 0, 41},
    {25, 0, 40},
    {26, 0, 39},
    {27, 0, 38},
    {28, 0, 37},
    {29, 0, 36},
    {30, 0, 35},
    {31, 0, 34},
    {32, 0, 33},
    {33, 0, 32},
    {34, 0, 31},
    {35, 0, 30},
    {36, 0, 29},
    {37, 0, 28},
    {38, 0, 27},
    {39, 0, 26},
    {40, 0, 25},
    {41, 0, 24},
    {42, 0, 23},
    {43, 0, 22},
    {44, 0, 21},
    {45, 0, 20},
    {46, 0, 19},
    {47, 0, 18},
    {48, 0, 17},
    {49, 0, 16},
    {50, 0, 15},
    {51, 0, 14},
    {52, 0, 13},
    {53, 0, 12},
    {54, 0, 11},
    {55, 0, 10},
    {56, 0, 9},
    {57, 0, 8},
    {58, 0, 7},
    {59, 0, 6},
    {60, 0, 5},
    {61, 0, 4},
    {62, 0, 3},
    {63, 0, 2},
    {64, 0, 1}};
uint8_t RGB_Data3[128][3] = {
    {64, 1, 1}, {63, 2, 2}, {62, 3, 3}, {61, 4, 4}, {60, 5, 5}, {59, 6, 6}, {58, 7, 7}, {57, 8, 8}, {56, 9, 9}, {55, 10, 10}, {54, 11, 11}, {53, 12, 12}, {52, 13, 13}, {51, 14, 14}, {50, 15, 15}, {49, 16, 16}, {48, 17, 17}, {47, 18, 18}, {46, 19, 19}, {45, 20, 20}, {44, 21, 21}, {43, 22, 22}, {42, 23, 23}, {41, 24, 24}, {40, 25, 25}, {39, 26, 26}, {38, 27, 27}, {37, 28, 28}, {36, 29, 29}, {35, 30, 30}, {34, 31, 31}, {33, 32, 32}, {32, 32, 33}, {31, 31, 34}, {30, 30, 35}, {29, 29, 36}, {28, 28, 37}, {27, 27, 38}, {26, 26, 39}, {25, 25, 40}, {24, 24, 41}, {23, 23, 42}, {22, 22, 43}, {21, 21, 44}, {20, 20, 45}, {19, 19, 46}, {18, 18, 47}, {17, 17, 48}, {16, 16, 49}, {15, 15, 50}, {14, 14, 51}, {13, 13, 52}, {12, 12, 53}, {11, 11, 54}, {10, 10, 55}, {9, 9, 56}, {8, 8, 57}, {7, 7, 58}, {6, 6, 59}, {5, 5, 60}, {4, 4, 61}, {3, 3, 62}, {2, 2, 63}, {1, 1, 64},

    {1, 1, 64},
    {2, 2, 63},
    {3, 3, 62},
    {4, 4, 61},
    {5, 5, 60},
    {6, 6, 59},
    {7, 7, 58},
    {8, 8, 57},
    {9, 9, 56},
    {10, 10, 55},
    {11, 11, 54},
    {12, 12, 53},
    {13, 13, 52},
    {14, 14, 51},
    {15, 15, 50},
    {16, 16, 49},
    {17, 17, 48},
    {18, 18, 47},
    {19, 19, 46},
    {20, 20, 45},
    {21, 21, 44},
    {22, 22, 43},
    {23, 23, 42},
    {24, 24, 41},
    {25, 25, 40},
    {26, 26, 39},
    {27, 27, 38},
    {28, 28, 37},
    {29, 29, 36},
    {30, 30, 35},
    {31, 31, 34},
    {32, 32, 33},
    {33, 32, 32},
    {34, 31, 31},
    {35, 30, 30},
    {36, 29, 29},
    {37, 28, 28},
    {38, 27, 27},
    {39, 26, 26},
    {40, 25, 25},
    {41, 24, 24},
    {42, 23, 23},
    {43, 22, 22},
    {44, 21, 21},
    {45, 20, 20},
    {46, 19, 19},
    {47, 18, 18},
    {48, 17, 17},
    {49, 16, 16},
    {50, 15, 15},
    {51, 14, 14},
    {52, 13, 13},
    {53, 12, 12},
    {54, 11, 11},
    {55, 10, 10},
    {56, 9, 9},
    {57, 8, 8},
    {58, 7, 7},
    {59, 6, 6},
    {60, 5, 5},
    {61, 4, 4},
    {62, 3, 3},
    {63, 2, 2},
    {64, 1, 1}

};

uint8_t Matrix_Data[8][8];
uint8_t x=4,y=4;

Adafruit_NeoPixel pixels(RGB_COUNT, RGB_Control_PIN, NEO_RGB + NEO_KHZ800);

void RGB_Matrix() {
  for (int row = 0; row < Matrix_Row; row++) {
    for (int col = 0; col < Matrix_Col; col++) {
    // int hue = ((i * 256 / RGB_COUNT) % 256)*2;
    // pixels.setPixelColor(i, pixels.ColorHSV(hue, 255, 10)); 
      if(Matrix_Data[row][col] == 1)      
      {
        pixels.setPixelColor(row*8+col, pixels.Color(RGB_Data[0], RGB_Data[1], RGB_Data[2]));   
      }
      else
      {
        pixels.setPixelColor(row*8+col, pixels.Color(0, 0, 0)); 
      }
    }
  }
  pixels.show();
}


void Game(uint8_t X_EN,uint8_t Y_EN) 
{
  Matrix_Data[x][y] = 0;
  if(X_EN && Y_EN){
    if(X_EN == 1)
      x=x+1;
    else
      x=x-1;
    if(Y_EN == 1)
      y=y+1;
    else
      y=y-1;
  }
  else if(X_EN){
    if(X_EN == 1)
      x=x+1;
    else
      x=x-1;
  }
  else if(Y_EN){
    if(Y_EN == 1)
      y=y+1;
    else
      y=y-1;
  }
  if(x < 0) x = 0;
  if(x == 8) x = 7;
  if(x > 8) x = 0;
  if(y < 0) y = 0;
  if(y == 8) y = 7;
  if(y > 8) y = 0;
  // printf("%d\r\n",y); y값을 표시
  Matrix_Data[x][y]=1;
  RGB_Matrix();
}

void RGB_Matrix1(int x)
{
  for (int row = 0; row < Matrix_Row; row++)
  {
    for (int col = 0; col < Matrix_Col; col++)
    {
      if (x < 16)
      {
        RGB_Data1[row * 8 + col][0] = RGB_Data2[row * 8 + col + x * 8][0];
        RGB_Data1[row * 8 + col][1] = RGB_Data2[row * 8 + col + x * 8][1];
        RGB_Data1[row * 8 + col][2] = RGB_Data2[row * 8 + col + x * 8][2];
      }
      else
      {
        if (x + row < 24)
        {
          RGB_Data1[row * 8 + col][0] = RGB_Data2[row * 8 + col + x * 8][0];
          RGB_Data1[row * 8 + col][1] = RGB_Data2[row * 8 + col + x * 8][1];
          RGB_Data1[row * 8 + col][2] = RGB_Data2[row * 8 + col + x * 8][2];
        }
        else
        {
          RGB_Data1[row * 8 + col][0] = RGB_Data2[(x + row - 24) * 8 + col][0];
          RGB_Data1[row * 8 + col][1] = RGB_Data2[(x + row - 24) * 8 + col][1];
          RGB_Data1[row * 8 + col][2] = RGB_Data2[(x + row - 24) * 8 + col][2];
        }
      }
    }
  }
  for (int row = 0; row < Matrix_Row; row++)
  {
    for (int col = 0; col < Matrix_Col; col++)
    {
      // int hue = ((i * 256 / RGB_COUNT) % 256)*2;
      // pixels.setPixelColor(i, pixels.ColorHSV(hue, 255, 10));
      if (Matrix_Data[row][col] == 1)
      {
        pixels.setPixelColor(row * 8 + col, pixels.Color(RGB_Data1[row * 8 + col][0], RGB_Data1[row * 8 + col][1], RGB_Data1[row * 8 + col][2]));
      }
      else
      {
        pixels.setPixelColor(row * 8 + col, pixels.Color(0, 0, 0));
      }
    }
  }
  pixels.show();
}

void RGB_Matrix2(int x)
{
  for (int row = 0; row < Matrix_Row; row++)
  {
    for (int col = 0; col < Matrix_Col; col++)
    {
      RGB_Data1[row * 8 + col][0] = RGB_Data3[row * 8 + col + x * 8][0];
      RGB_Data1[row * 8 + col][1] = RGB_Data3[row * 8 + col + x * 8][1];
      RGB_Data1[row * 8 + col][2] = RGB_Data3[row * 8 + col + x * 8][2];
    }
  }
  for (int row = 0; row < Matrix_Row; row++)
  {
    for (int col = 0; col < Matrix_Col; col++)
    {
      // int hue = ((i * 256 / RGB_COUNT) % 256)*2;
      // pixels.setPixelColor(i, pixels.ColorHSV(hue, 255, 10));
      if (Matrix_Data[row][col] == 1)
      {
        pixels.setPixelColor(row * 8 + col, pixels.Color(RGB_Data1[row * 8 + col][0], RGB_Data1[row * 8 + col][1], RGB_Data1[row * 8 + col][2]));
      }
      else
      {
        pixels.setPixelColor(row * 8 + col, pixels.Color(0, 0, 0));
      }
    }
  }
  pixels.show();
}






// these values are substracetd from the generated values to give a shape to the animation
const unsigned char valueMask[Matrix_Row][Matrix_Col] = {
    {32, 0, 0, 0, 0, 0, 0, 32},
    {64, 0, 0, 0, 0, 0, 0, 64},
    {96, 32, 0, 0, 0, 0, 32, 96},
    {128, 64, 32, 0, 0, 32, 64, 128},
    {160, 96, 64, 32, 32, 64, 96, 160},
    {192, 128, 96, 64, 64, 96, 128, 192},
    {255, 160, 128, 96, 96, 128, 160, 255},
    {255, 192, 160, 128, 128, 160, 192, 255}};

// these are the hues for the fire,
// should be between 0 (red) to about 25 (yellow)
const unsigned char hueMask[Matrix_Row][Matrix_Col] = {
    {1, 11, 19, 25, 25, 22, 11, 1},
    {1, 8, 13, 19, 25, 19, 8, 1},
    {1, 8, 13, 16, 19, 16, 8, 1},
    {1, 5, 11, 13, 13, 13, 5, 1},
    {1, 5, 11, 11, 11, 11, 5, 1},
    {0, 1, 5, 8, 8, 5, 1, 0},
    {0, 0, 1, 5, 5, 1, 0, 0},
    {0, 0, 0, 1, 1, 0, 0, 0}};

unsigned char matrixValue[Matrix_Row][Matrix_Col];
unsigned char line[Matrix_Col];
int pcnt = 0;

Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(
    Matrix_Col, Matrix_Row,
    RGB_Control_PIN,
    NEO_MATRIX_TOP + NEO_MATRIX_LEFT + NEO_MATRIX_COLUMNS + NEO_MATRIX_PROGRESSIVE,
    NEO_GRB + NEO_KHZ800);

// IMPORTANT: To reduce NeoPixel burnout risk, add 1000 uF capacitor across
// pixel power leads, add 300 - 500 Ohm resistor on first pixel's data input
// and minimize distance between Arduino and first pixel.  Avoid connecting
// on a live circuit...if you must, connect GND first.

// 아래쪽-왼쪽 방향 기준으로 픽셀 설정
void setPixelBottomLeft(uint16_t x, uint16_t y, uint16_t color)
{
    uint16_t newX = y;
    uint16_t newY = matrix.width() - 1 - x;
    matrix.drawPixel(newX, newY, color);
}

// 아래쪽-오른쪽 방향 기준으로 픽셀 설정
void setPixelBottomRight(uint16_t x, uint16_t y, uint16_t color)
{
    uint16_t newX = matrix.height() - 1 - y;
    uint16_t newY = matrix.width() - 1 - x;
    matrix.drawPixel(newX, newY, color);
}

// 위쪽-오른쪽 방향 기준으로 픽셀 설정
void setPixelTopRight(uint16_t x, uint16_t y, uint16_t color)
{
    uint16_t newX = matrix.height() - 1 - y;
    uint16_t newY = x;
    matrix.drawPixel(newX, newY, color);
}

// 위쪽-왼쪽 방향 기준으로 픽셀 설정
void setPixelTopLeft(uint16_t x, uint16_t y, uint16_t color)
{
    matrix.drawPixel(x, y, color); // 기본 좌표 그대로 사용
}

// Converts an HSV color to RGB color
uint16_t HSVtoRGB(uint8_t ih, uint8_t is, uint8_t iv)
{
    float r, g, b, h, s, v; // this function works with floats between 0 and 1
    float f, p, q, t;
    int i;

    h = (float)(ih / 256.0);
    s = (float)(is / 256.0);
    v = (float)(iv / 256.0);

    // if saturation is 0, the color is a shade of grey
    if (s == 0.0)
    {
        b = v;
        g = b;
        r = g;
    }
    // if saturation > 0, more complex calculations are needed
    else
    {
        h *= 6.0;            // to bring hue to a number between 0 and 6, better for the calculations
        i = (int)(floor(h)); // e.g. 2.7 becomes 2 and 3.01 becomes 3 or 4.9999 becomes 4
        f = h - i;           // the fractional part of h

        p = (float)(v * (1.0 - s));
        q = (float)(v * (1.0 - (s * f)));
        t = (float)(v * (1.0 - (s * (1.0 - f))));

        switch (i)
        {
        case 0:
            r = v;
            g = t;
            b = p;
            break;
        case 1:
            r = q;
            g = v;
            b = p;
            break;
        case 2:
            r = p;
            g = v;
            b = t;
            break;
        case 3:
            r = p;
            g = q;
            b = v;
            break;
        case 4:
            r = t;
            g = p;
            b = v;
            break;
        case 5:
            r = v;
            g = p;
            b = q;
            break;
        default:
            r = g = b = 0;
            break;
        }
    }
    return matrix.Color(g * 255.0, r * 255.0, b * 255.0);
}

/**
 * Randomly generate the next line (matrix row)
 */
void generateLine()
{
    // 기본 불꽃 생성 (중심 기반)
    int baseCenter = Matrix_Col / 2; // 4 (0-7 중 중앙)
    
    for (uint8_t x = 0; x < Matrix_Col; x++)
    {
        // 중심에서 멀어질수록 불꽃 강도 약간 감소
        int distance = abs((int)x - baseCenter);
        int maxIntensity = (distance == 0) ? 100 : (distance == 1) ? 80 : 60;
        
        line[x] = random(10, maxIntensity);
    }
}

/**
 * Generate line with tilt effect based on accelerometer
 * @param accelX X-axis acceleration value (-1.0 to 1.0)
 */
void generateLineWithTilt(float accelX)
{
    // 기울기 효과를 더 강하게 - 좌우 끝까지 이동 (3.5 -> 4.5로 증가)
    float centerShift = -accelX * 4.5;
    int tiltedCenter = (Matrix_Col / 2) + (int)round(centerShift);
    
    // 범위 제한 (0~7까지 모든 위치 사용)
    if (tiltedCenter < 0) tiltedCenter = 0;
    if (tiltedCenter >= Matrix_Col) tiltedCenter = Matrix_Col - 1;
    
    for (uint8_t x = 0; x < Matrix_Col; x++)
    {
        // 중심 근처와 가장자리 차이를 더 크게
        int distance = abs((int)x - tiltedCenter);
        int maxIntensity;
        
        if (distance == 0) maxIntensity = 100;      // 중심: 최대
        else if (distance == 1) maxIntensity = 60;  // 1칸: 중간
        else if (distance == 2) maxIntensity = 35;  // 2칸: 약간
        else maxIntensity = 15;                     // 3칸 이상: 최소
        
        line[x] = random(3, maxIntensity);
    }
}

/**
 * shift all values in the matrix up one row
 */
void shiftUp()
{
    for (uint8_t y = Matrix_Row - 1; y > 0; y--)
    {
        for (uint8_t x = 0; x < Matrix_Col; x++)
        {
            matrixValue[y][x] = matrixValue[y - 1][x];
        }
    }

    for (uint8_t x = 0; x < Matrix_Col; x++)
    {
        matrixValue[0][x] = line[x];
    }
}

/**
 * draw a frame, interpolating between 2 "key frames"
 * @param pcnt percentage of interpolation
 */
void drawFrame(int pcnt)
{
    int nextv;

    // each row interpolates with the one before it
    for (unsigned char y = Matrix_Row - 1; y > 0; y--)
    {
        for (unsigned char x = 0; x < Matrix_Col; x++)
        {
            nextv =
                (((100.0 - pcnt) * matrixValue[y][x] + pcnt * matrixValue[y - 1][x]) / 100.0) - valueMask[y][x];
            uint16_t color = HSVtoRGB(
                hueMask[y][x],         // H
                255,                   // S
                (uint8_t)max(0, nextv) // V
            );
            // matrix.drawPixel(x, y, color);
            setPixelBottomLeft(x, y, color);
        }
    }

    // first row interpolates with the "next" line
    for (unsigned char x = 0; x < Matrix_Col; x++)
    {
        uint16_t color = HSVtoRGB(
            hueMask[0][x],                                                           // H
            255,                                                                     // S
            (uint8_t)(((100.0 - pcnt) * matrixValue[0][x] + pcnt * line[x]) / 100.0) // V
        );
        // matrix.drawPixel(x, 0, color);
        setPixelBottomLeft(x, 0, color);
    }
}

void Matrix_Init()
{
    matrix.begin();
    randomSeed(analogRead(0));
    generateLine();
    // init all pixels to zero
    memset(matrixValue, 0, sizeof(matrixValue));
    matrix.fillScreen(matrix.Color(255, 255, 255)); 
}