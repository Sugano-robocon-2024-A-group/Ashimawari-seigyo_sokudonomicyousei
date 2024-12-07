/*void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:


エンコーダカウントは、共通にして、値を読み込んだ方がいいのか。（でないとまったく何やってるのかわからん）
// エンコーダ関連の変数
volatile long encoderCount[4] = {0, 0, 0, 0}; // 各ホイールのエンコーダカウント


}*/
//STEP1　エンコーダカウント　とれる　OK

//STEP2 CAN通信で送る。　OK

//STEP3 実際のモータのエンコーダを読む　いけるはず

//STEP3.5 実際のプログラムを作る　OK

//STEP4 PS4コントローラの入力を入れる OK

//STEP5 (Final) PIDを実践する。 値調整終了のはず
