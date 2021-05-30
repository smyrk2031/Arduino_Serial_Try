// 複数のアナログセンサを同時計測する感じのやつ

// アナログピン(0～7)を設定
const int VOL_PIN_0 = 0;
const int VOL_PIN_1 = 1;
const int VOL_PIN_2 = 2;
const int VOL_PIN_3 = 3;
const int VOL_PIN_4 = 4;
const int VOL_PIN_5 = 5;
const int VOL_PIN_6 = 6;
const int VOL_PIN_7 = 7;

// BlinkWithoutDelayの為の、変数
int LEDState = LOW;
long previosMillis = 0;
long interval_LED = 1;

// millisとmicrosで、閾値の単位が1000倍変わるので注意する
// millis：10ms、micros：5000usより下は誤差大きいので注意
// アナログデータ取得、2chと8chでは時刻計測誤差は変わらなかったので。。
long interval_MEAS = 100;


// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);
  // pinMode(VOL_PIN, INPUT);
  // initialize_Serial_(9600, 19200, 38400, 57600, 74880, 115200)
  Serial.begin(115200);
}

// the loop function runs over and over again forever
void loop() {
  
  // delay()中は何も操作できなくなるので、回避する為に BlinkWithoutDelay を使う
  // 時間取得にmillis()を使う場合：ミリ単位で最大約50日までカウントする→10ms以下は誤差に飲まれるので注意
  // 時間取得にmicros()を使う場合：マイクロ単位で、最大約70分→5000usが限界ぽいので注意する(コードを簡略化すれば違うかも)
  // 仮に5000usは2kHzだから余裕だけど、50kHzとか高速にするとADCの挙動限界が来るので注意する
  unsigned long currentMillis = millis();
  if(currentMillis - previosMillis > interval_MEAS) {
    previosMillis = currentMillis;

    //LEDチカチカの部分
    //if (LEDState == LOW){
    //  LEDState = HIGH;
    //}
    //else {
    //  LEDState = LOW;
    //}
    //LED点灯させた方が分かりやすいと思うけど、計測の遅延原因になるのでいったん除去
    //並列で実行できるようにしたい
    //digitalWrite(LED_BUILTIN, LEDState);
    
    // アナログピンの値を取得する(順番に取得しているので、同時刻ではない)
    int v0 = analogRead( VOL_PIN_0 );         /*A0のアナログピンより数値を読み取り変数v0に代入*/
    int v1 = analogRead( VOL_PIN_1 );         /*A1のアナログピンより数値を読み取り変数v1に代入*/
    int v2 = analogRead( VOL_PIN_2 );         /*A2のアナログピンより数値を読み取り変数v2に代入*/
    int v3 = analogRead( VOL_PIN_3 );         /*A3のアナログピンより数値を読み取り変数v3に代入*/
    int v4 = analogRead( VOL_PIN_4 );         /*A4のアナログピンより数値を読み取り変数v4に代入*/
    int v5 = analogRead( VOL_PIN_5 );         /*A5のアナログピンより数値を読み取り変数v5に代入*/  
    int v6 = analogRead( VOL_PIN_6 );         /*A6のアナログピンより数値を読み取り変数v6に代入*/
    int v7 = analogRead( VOL_PIN_7 );         /*A7のアナログピンより数値を読み取り変数v7に代入*/

    //ここで電圧値に変換している。
    float v0_ = v0 * 5.0 / 1024.0;    /*上の行で読み取った、A0への入力電圧の数値を補正し電圧表示に*/
    float v1_ = v1 * 5.0 / 1024.0;    /*上の行で読み取った、A1への入力電圧の数値を補正し電圧表示に*/
    float v2_ = v2 * 5.0 / 1024.0;    /*上の行で読み取った、A2への入力電圧の数値を補正し電圧表示に*/
    float v3_ = v3 * 5.0 / 1024.0;    /*上の行で読み取った、A3への入力電圧の数値を補正し電圧表示に*/
    float v4_ = v4 * 5.0 / 1024.0;    /*上の行で読み取った、A4への入力電圧の数値を補正し電圧表示に*/
    float v5_ = v5 * 5.0 / 1024.0;    /*上の行で読み取った、A5への入力電圧の数値を補正し電圧表示に*/
    float v6_ = v6 * 5.0 / 1024.0;    /*上の行で読み取った、A6への入力電圧の数値を補正し電圧表示に*/
    float v7_ = v7 * 5.0 / 1024.0;    /*上の行で読み取った、A7への入力電圧の数値を補正し電圧表示に*/


    // 同期通信の為のプロトコル(STX)を作ってみる
    Serial.print(1111);
    Serial.print( ", " );
    // 時刻情報
    Serial.print(currentMillis);
    Serial.print( ", " );

    // データの出力(カンマ区切りのバイト型で出力する)
    Serial.print(v0_);              /*v0_cal(小数点第5位まで)をシリアルモニタに出力して改行*/
    Serial.print( ", " );
    Serial.print(v1_);              /*v0_cal(小数点第5位まで)をシリアルモニタに出力して改行*/
    Serial.print( ", " );
    Serial.print(v2_);              /*v0_cal(小数点第5位まで)をシリアルモニタに出力して改行*/
    Serial.print( ", " );
    Serial.print(v3_);              /*v0_cal(小数点第5位まで)をシリアルモニタに出力して改行*/
    Serial.print( ", " );
    Serial.print(v4_);              /*v0_cal(小数点第5位まで)をシリアルモニタに出力して改行*/
    Serial.print( ", " );
    Serial.print(v5_);              /*v0_cal(小数点第5位まで)をシリアルモニタに出力して改行*/
    Serial.print( ", " );
    Serial.print(v6_);              /*v0_cal(小数点第5位まで)をシリアルモニタに出力して改行*/
    Serial.print( ", " );
    Serial.println(v7_);              /*v0_cal(小数点第5位まで)をシリアルモニタに出力して改行*/

    //同期通信の為のプロトコル(ETX)を作ってみる
    //Serial.print( ", " );
    //Serial.println(1111);
    
  }
}
