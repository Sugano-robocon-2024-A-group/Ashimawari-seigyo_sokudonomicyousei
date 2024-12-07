#include <Arduino.h>
#include <CAN.h>
#include "tuushin.h"

// setupReceiver関数: 受信の初期設定
void setupReceiver() {
  // 受信側の初期化が行われる際にメッセージをシリアルに表示
  Serial.println("CAN Receiver Initialized");
}

// setupSender関数: 送信の初期設定
void setupSender() {
  // 送信側の初期化が行われる際にメッセージをシリアルに表示
  Serial.println("CAN Sender Initialized");
}

// sendPacket関数: CANメッセージを送信する
void sendPacket(int PS4_Circle, int PS4_Triangle, int PS4_R1, int PS4_L1) {
  // 通常パケットの送信
  Serial.print("Sending packet ... ");

  // CANパケットを送信。ID: 0x12
  CAN.beginPacket(0x12);
  Serial.print("Sending");

  //Serial.printf("%d\n",PS4_Circle);

  // 各引数をint16_t型として2バイトに分割して送信
  CAN.write(static_cast<uint8_t>((PS4_Circle >> 8) & 0xFF));  // 上位バイト
  CAN.write(static_cast<uint8_t>(PS4_Circle & 0xFF));         // 下位バイト
  CAN.write(static_cast<uint8_t>((PS4_Triangle >> 8) & 0xFF)); // 上位バイト
  CAN.write(static_cast<uint8_t>(PS4_Triangle & 0xFF));        // 下位バイト
  CAN.write(static_cast<uint8_t>((PS4_R1 >> 8) & 0xFF));       // 上位バイト
  CAN.write(static_cast<uint8_t>(PS4_R1 & 0xFF));              // 下位バイト
  CAN.write(static_cast<uint8_t>((PS4_L1 >> 8) & 0xFF));       // 上位バイト
  CAN.write(static_cast<uint8_t>(PS4_L1 & 0xFF));              // 下位バイト
  
  CAN.endPacket();  // 送信終了

  Serial.println("done");
}

/*void sendPacket(int PS4_Circle, int PS4_Triangle, int PS4_R1, int PS4_L1) {
  // 通常パケットの送信
  Serial.print("Sending packet ... ");
  // CANパケットを送信。ID: 0x12
  CAN.beginPacket(0x12);
  Serial.print("Sending");
int a=1; int b=1; int c=1; int d=1;

if(PS4_Circle<0){
     a=3; 
     PS4_Circle=-PS4_Circle;
}
if(PS4_Triangle<0){
     b=3; 
    PS4_Triangle=-PS4_Triangle;
}
if(PS4_Circle<0){
     c=3; 
     PS4_R1=-PS4_R1;
}
if(PS4_Circle<0){
     d=3; 
     PS4_L1=-PS4_L1;
}

  // 各引数をint16_t型として2バイトに分割して送信
  CAN.write(a);
  CAN.write(static_cast<uint8_t>((PS4_Circle >> 8) & 0xFF));  // 上位バイト
  CAN.write(static_cast<uint8_t>(PS4_Circle & 0xFF));         // 下位バイト
 CAN.write(b);
  CAN.write(static_cast<uint8_t>((PS4_Triangle >> 8) & 0xFF)); // 上位バイト
  CAN.write(static_cast<uint8_t>(PS4_Triangle & 0xFF));        // 下位バイト
 CAN.write(c);
  CAN.write(static_cast<uint8_t>((PS4_R1 >> 8) & 0xFF));       // 上位バイト
  CAN.write(static_cast<uint8_t>(PS4_R1 & 0xFF));              // 下位バイト
 CAN.write(d);
  CAN.write(static_cast<uint8_t>((PS4_L1 >> 8) & 0xFF));       // 上位バイト
  CAN.write(static_cast<uint8_t>(PS4_L1 & 0xFF));              // 下位バイト
  
  CAN.endPacket();  // 送信終了

  Serial.println("done");
}*/

/*
// sendPacket関数: CANメッセージを送信する
void sendPacket(int PS4_Circle, int PS4_Triangle, int PS4_R1, int PS4_L1) {
  // 通常パケットの送信
  Serial.print("Sending packet ... ");
  
  // CANパケットを送信。ID: 0x12
  CAN.beginPacket(0x12);
  Serial.print("Sending");
  CAN.write(static_cast<uint8_t>(PS4_Circle));
  Serial.print("Sending 2");
  CAN.write(static_cast<uint8_t>(PS4_Triangle));
  Serial.print("Sending 3 ");
  CAN.write(static_cast<uint8_t>(PS4_R1));
  Serial.print("Sending 4 ");
  CAN.write(static_cast<uint8_t>(PS4_L1));
  CAN.endPacket();  // 送信終了

  //Serial.print(PS4_Circle);
  
  Serial.println("done");
}*/

/*

// receivePacket関数: CANメッセージを受信し、内容を表示する
void receivePacket() {
  int packetSize = CAN.parsePacket();  // 受信したパケットのサイズを取得

  if (packetSize) {  // パケットが受信された場合
  
    Serial.print("Received ");

    // 拡張パケットの場合
    if (CAN.packetExtended()) {
      Serial.print("extended ");
    }

    // RTRパケットの場合
    if (CAN.packetRtr()) {
      Serial.print("RTR ");
    }

    // パケットIDを表示
    Serial.print("packet with id 0x");
    Serial.print(CAN.packetId(), HEX);

    // RTRパケットの場合、要求された長さを表示
    if (CAN.packetRtr()) {
      Serial.print(" and requested length ");
      Serial.println(CAN.packetDlc());
    } else {
      // 通常パケットの場合、受信データの長さを表示
      Serial.print(" and length ");
      Serial.println(packetSize);

      // データをシリアルに表示
      while (CAN.available()) {
        Serial.print((char)CAN.read());
      }
      Serial.println();
    }
    Serial.println();
  }
}*/
