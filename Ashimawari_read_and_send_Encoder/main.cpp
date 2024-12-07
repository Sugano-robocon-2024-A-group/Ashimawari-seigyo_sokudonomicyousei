#include <Arduino.h>
#include <CAN.h>
#include "encoder.h"
#include "tuushin.h"

// エンコーダ関連のピン設定 CPPにあり。
/*const int encoderA[4] = {19, 14, 23, 33}; // エンコーダA相ピンconst int encoderB[4] = {18, 25, 22, 32}; // エンコーダB相ピン*/
/*const int encoderA[4] = {22, 18, 34, 35};const int encoderB[4] = {23, 19, 36, 39};*/
// カウント値をグローバルに定義済み（CPP) volatile int encoderCount[4] = {0, 0, 0, 0};

void setup()
{
  Serial.begin(115200);  // シリアル通信開始
  Serial.println("Ready.");
  while (!Serial);  // シリアル接続待機


//CAN通信設定　ここから
const int CAN_TX_PIN = 27;  // 送信ピン（GPIO27）
const int CAN_RX_PIN = 26;  // 受信ピン（GPIO26）
Serial.println("CAN Communication");
CAN.setPins(CAN_RX_PIN, CAN_TX_PIN);
 // CANバスの初期化（通信速度500kbps）
  CAN.begin(500E3);
  //CAN.begin(500E3);
  // CANバスの初期化。500kbpsで動作を設定
  if (!CAN.begin(500E3)) {
    // CAN初期化に失敗した場合、エラーメッセージを表示して停止
    Serial.println("CANの初期化に失敗しました！");
    while (1);  // 永久ループで停止
  }
  // 受信と送信の初期化関数を呼び出し
  setupReceiver();
  setupSender();
  Serial.println("Start");
//CAN通信設定　ここまで

  // エンコーダピンの設定
  for (int i = 0; i < 4; i++)
  {
    pinMode(encoderA[i], INPUT_PULLUP);
    pinMode(encoderB[i], INPUT_PULLUP);
  }

  // 割り込みの設定
  attachInterrupt(digitalPinToInterrupt(encoderA[0]), []() { handleEncoder(0); }, CHANGE);
  attachInterrupt(digitalPinToInterrupt(encoderA[1]), []() { handleEncoder(1); }, CHANGE);
  attachInterrupt(digitalPinToInterrupt(encoderA[2]), []() { handleEncoder(2); }, CHANGE);
  attachInterrupt(digitalPinToInterrupt(encoderA[3]), []() { handleEncoder(3); }, CHANGE);
}

void loop()
{
  // デバッグ用：エンコーダカウントを出力
  for (int i = 0; i < 4; i++)
  {
    Serial.print("Encoder ");
    Serial.print(i);
    Serial.print(": ");
    Serial.println(encoderCount[i]);
  }

  Serial.print("Counted\n");

  //ここでCAN通信を実装,encoderCount[i]を送る。


  // 送信処理を実行
  sendPacket(encoderCount[0], encoderCount[1], encoderCount[2], encoderCount[3]);
  
  delay(50);
  //delay(10);これだと、干渉することあり　行けたときは500でやっていた
}


/*#include "Encoder_read.h"
#include <Arduino.h>
// 割り込みの設定
void setup()
{
  attachInterrupt(digitalPinToInterrupt(encoderA[0]), []() { handleEncoder(0); }, CHANGE);
  attachInterrupt(digitalPinToInterrupt(encoderA[1]), []() { handleEncoder(1); }, CHANGE);
  attachInterrupt(digitalPinToInterrupt(encoderA[2]), []() { handleEncoder(2); }, CHANGE);
  attachInterrupt(digitalPinToInterrupt(encoderA[3]), []() { handleEncoder(3); }, CHANGE);
}

void loop()
{
  //ここでCANで送るコードをつくる。
  //EncoderCountを送る形
  
}*/
