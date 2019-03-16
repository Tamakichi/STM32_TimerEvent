#include "TimerEvent.h"

#define LED_PIN  PC13             // LEDピン

// タイマー割り込み管理
TimerEvent ticker(Timer2);      // Timer2を使った割り込み

// タイマー割り込み呼び出し関数
void handle_timer() {
  static uint8_t sw = LOW;
  sw = !sw;
  digitalWrite(LED_PIN, sw);      // LEDの制御
}
 
void setup() {
  pinMode(LED_PIN, OUTPUT);
  ticker.set(500, handle_timer);  // 0.5秒間隔で handle_timer()を呼び出す
  ticker.setPriority(14);         // 割り込み優先度の設定
  ticker.start();                 // タイマー割り込み実行開始   

}

void loop() {
  delay(10000);
  ticker.stop();                  // 10秒後に停止する
  delay(10000);
  ticker.resume();                // 10秒後に再開する
  
}
