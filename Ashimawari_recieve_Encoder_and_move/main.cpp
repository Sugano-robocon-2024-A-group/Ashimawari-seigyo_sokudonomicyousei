#include <Arduino.h>
#include <CAN.h>
#include <PS4Controller.h>
#include "tuushin.h"
#include "functions.h"

// カウント値をグローバルに定義
volatile int encoderCount[4] = {0, 0, 0, 0};

uint32_t id;          // CAN IDを格納する変数
int16_t data[8]={0,0,0,0,0,0,0,0};      // 受信データを格納する配列（最大8バイト）
uint16_t length=0;       // 受信データの長さを格納する変数

// PID制御のゲイン
/*
float kp[4] = {100.0, 0.0, 0.0, 0.0};//(0,1,2,3)
float ki[4] = {0, 0.1, 0.1, 0.1};
float kd[4] = {0, 0.1, 0.1, 0.3};*/

//1はえらい
/*float kp[4] = {100.0, 2.0, 2.0, 1.0};//(0,1,2,3)
float ki[4] = {0, 0.1, 0.1, 0.1};
float kd[4] = {0, 0.1, 0.1, 0.3};*/

// 許容誤差と移動距離目標
const int allowableError = 5;
float targetDistance[4]={0.0,0.0,0.0,0.0}; // 各ホイールの移動距離目標

// エンコーダ関連の設定
const float wheelDiameter = 80.0;
const float encoderPulsesPerRevolution = 750;
const float distancePerCount = (PI * wheelDiameter) / encoderPulsesPerRevolution;

// PID制御の変数
float integral[4] = {0, 0, 0, 0};
float previous_error[4] = {0, 0, 0, 0};


void setup()
{
  Serial.begin(115200);  // シリアル通信開始
  PS4.begin("1c:69:20:e6:20:d2");
  Serial.println("Ready.");
  while (!Serial);  // シリアル接続待機


//CAN通信設定　ここから
const int CAN_TX_PIN = 27;  // 送信ピン（GPIO27）
const int CAN_RX_PIN = 26;  // 受信ピン（GPIO26）
Serial.println("CAN Communication");
CAN.setPins(CAN_RX_PIN, CAN_TX_PIN);
 // CANバスの初期化（通信速度500kbps）//速度を落とす
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

    init_pwm_setup();
    //init_encoder_setup();
    stopMotors();
/*
  attachInterrupt(digitalPinToInterrupt(encoderA[0]), []() { handleEncoder(0); }, CHANGE);
  attachInterrupt(digitalPinToInterrupt(encoderA[1]), []() { handleEncoder(1); }, CHANGE);
  attachInterrupt(digitalPinToInterrupt(encoderA[2]), []() { handleEncoder(2); }, CHANGE);
  attachInterrupt(digitalPinToInterrupt(encoderA[3]), []() { handleEncoder(3); }, CHANGE);*/
}

void loop()
{
 //ここでCAN通信を実装,encoderCount[i]を受け取る　ここであの統合のコードを参照
  receivePacket(id, data, length);
  //receivePacket(id, data, length, *encoderCount);

  int packetSize = CAN.parsePacket();
  Serial.print(packetSize);
  //Serial.printf("\n");
  //Serial.print(encoderCount[1]);//デバッグ用
  Serial.printf(" A \n");
  //Serial.print(data[3]);
//if (receivePacket)
//if (packetSize > 0) 
if(receivePacket){ 
  // CANメッセージを受信
    Serial.print("Data and Encoder Check\n");
    encoderCount[0]=data[0];
    Serial.print(encoderCount[0]);
    //Serial.print(" ");Serial.print(data[1]);
    encoderCount[1]=data[1];
    Serial.print(encoderCount[1]);
    //Serial.print(" ");Serial.print(data[2]); 
    encoderCount[2]=data[2];
    Serial.print(encoderCount[2]);
    //Serial.print(" ");Serial.print(data[3]);
    encoderCount[3]=data[3];
    Serial.println(encoderCount[3]);
   // 
  // 
  //これでHIGHにする   
  /*  for (int i = 0; i < 8; i++) {
      data[i] = 0;
    }//これはリセット用*/


  //ここに「EncoderCount」を利用した動きの関数を入れる。

  bool reachedTarget = true;

    for (int i = 0; i < 4; i++) {
        float currentDistance = encoderCount[i] * distancePerCount;
        //float controlSignal = pidCompute(i, targetDistance[i], currentDistance);
        float controlSignal = pidCompute(i, targetDistance[i], currentDistance);

        if(abs(targetDistance[i]-currentDistance)<30){
        //float controlSignal=30.0;
        }

        Serial.printf("%f ",currentDistance);
        Serial.printf("%f ",targetDistance[i]);
        Serial.printf("%f \n",controlSignal);

        driveMotor(i, controlSignal);

   /*   Serial.print("Wheel ");
        Serial.print(i);
        Serial.print(" Target Distance: ");
        Serial.print(targetDistance[i]);
        Serial.print(" Current Distance: ");
        Serial.print(currentDistance);
        Serial.print(" Control Signal: ");
        Serial.println(controlSignal);*/

        if (abs(currentDistance - targetDistance[i]) > allowableError) {
            reachedTarget = false;
        }
    }

    if (reachedTarget) {
        stopMotors();
        resetControlVariables();
        //ここでTargetも0にする
         for (int j = 0; j < 4; j++) {
        targetDistance[j]=0.0;
         }
        Serial.print("reachedTarget\n");

        if (PS4.isConnected()) {
           // handlePS4Input();//動きを説明する関数（もし入力が入ったら？）
            handlePS4Input(targetDistance);//動きを説明する関数（もし入力が入ったら？）
        }
    }

  Serial.print("Done all movements");
  delay(50);//delay(1)⇒delay(10)
}
}
