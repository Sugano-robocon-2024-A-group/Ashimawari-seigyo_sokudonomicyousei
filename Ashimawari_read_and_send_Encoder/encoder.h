//void handleEncoder(int index);

#ifndef ENCODER_H
#define ENCODER_H

#include <Arduino.h>

// 外部で使用される変数を宣言
extern volatile int encoderCount[4]; // カウント値（main.cppで定義される）

extern const int encoderA[4]; // エンコーダA相ピン
extern const int encoderB[4];

// 関数のプロトタイプ宣言
void handleEncoder(int index);

#endif
