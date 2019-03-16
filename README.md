# Arduino STM32用 簡易タイマー割り込みライブラリ
## 概要
Arduino STM32環境にてインターバルタイマー割り込みを実装する利用するためライブラリです。  
1～65535msecの間隔のインターバルタイマー割り込みを実装することが出来ます。  
デフォルトでは、ハードウェアタイマー Timer1を利用しています。

動作確認は、下記の環境にて行っています。    
- Arduino IDE 1.8.8 + Arduino STM32 1.0.0Beta
- Blue Pillボード (STM32F103C8T6 72MHz)

## ライブラリ名称
TimerEvent (ヘッダーファイル TimerEvent.h)  

## インストール  
本パッケージをダウンロードし、解凍したフォルダ **TimerEvent** を各自のArduino環境の  
ライブラリ配置フォルダ **libraries** に配置して下さい。  
( **環境設定** - **スケッチの保存場所** に設定のフォルダ の  **libraries** に配置）

## サンプルスケッチ
TimerBlink  : 0.5秒間隔でボート上のLEDを点滅させる

````
#include "TimerEvent.h"

#define LED_PIN  PC13 // LEDピン

// タイマー割り込み管理
TimerEvent ticker;     

// タイマー割り込み呼び出し関数
void handle_timer() {
  static uint8_t sw = LOW;
  sw = !sw;
  digitalWrite(LED_PIN, sw);      // LEDの制御
}
 
void setup() {
  pinMode(LED_PIN, OUTPUT);
  ticker.set(500, handle_timer);  // 0.5秒間隔で handle_timer()を呼び出す
  ticker.start();                 // タイマー割り込み実行開始
}

void loop() {

}
````

## ライブラリリファレンス
ライブラリはクラスライブラリとして実装しています。  


### ヘッダーファイル
`#include "TimerEvent.h"`  

### パブリックメンバー関数

#### コンストラクタ

- 書式  
`TimerEvent`  
`TimerEvent(HardwareTimer& pt)`  

- 引数  
  `pt`  ： ハードウェア・タイマー（省略可能）  
  `Timer1`、`Timer2`、`Timer3`、`Timer4`のいずれかの指定または、引数なし  

- 戻り値  
 なし

- 説明  
 **TimerEvent** クラスのインスタンスを作成します。  
 デフォルトではハードウェア・タイマー **Timer1** を利用します。  
 引数の指定により、利用するハードウェア・タイマーの指定が可能です。  

- 記述例  
`TimerEvent myTimer;`  
`TimerEvent(Timer2) myTimer;`

#### 初期化

- 書式  
`void init()` 

- 引数  
なし

- 戻り値  
 なし

- 説明 
タイマーを初期状態にします。  
本関数は、インスタンス生成時にコンストラクタおよび **set()** 関数内で実行されます。  
通常は、本関数を利用しての初期化を行う必要はありません。  

- 記述例  
`myTimer.init();`

#### タイマー割り込みの設定

- 書式  
`void set(uint32_t tm, void (*func)(void) )`  

- 引数  
`tm`    ：タイマー割り込み間隔（ミリ秒） 1 ～ 65535  
`func`  ：呼び出す関数  

- 戻り値  
 なし

- 説明 
タイマー割り込みの間隔（ミリ秒）と呼び出す関数の設定を行います。  
設定後は、**start()** 関数にて割り込みを開始することが出来ます。  

- 記述例  
`myTimer.set(500,myfunc);`  

#### タイマー割り込みの開始

- 書式  
`void start()`  

- 引数  
なし  

- 戻り値  
 なし  

- 説明 
**set()** 関数で設定した条件で、タイマー割り込みを開始します。  


- 記述例  
`myTimer.start();`  

#### タイマー割り込みの中断

- 書式  
`void stop()`  

- 引数  
なし  

- 戻り値  
 なし  

- 説明 
実行中のタイマー割り込みを中断します。  
**resume()** 関数で途中からの再開が可能です。  
**start()** 関数では、経過時間を初期化の上、再スタートとなります。  

- 記述例  
`myTimer.stop();`  

#### タイマー割り込みの再開

- 書式  
`void resume()`  

- 引数  
なし  

- 戻り値  
 なし  

- 説明 
**stop()** 関数で中断したタイマー割り込みを再開します。  

- 記述例  
`myTimer.resume();`  

####  実行状態の取得

- 書式  
`uint8_t isRun()`  

- 引数  
なし  

- 戻り値  
 実行状態 0:停止 1:実行中  

- 説明 
タイマー割り込みの実行状態を取得します。  

- 記述例  
`s = myTimer.isRun();`  

####  割り込み優先レベルの設定

- 書式  
`void setPriority(uint8_t priority)`  

- 引数  
priority ：割り込み優先度 0 ～ 15 （デフォルト 15）  

- 戻り値  
 なし  

- 説明 
割り込み優先度の設定を行います。  
デフォルトでは、全ての割り込み優先度は15が設定されています。  
数値が小さいほど、優先度が高くなります。  

- 記述例  
`myTimer.setPriority(14);`  

#### ハードウェアタイマーの設定

- 書式  
`void setTimer(HardwareTimer& pt)`  

- 引数  
pt ：ハードウェアタイマー  
`Timer1`、`Timer2`、`Timer3`、`Timer4`のいずれかの指定  

- 戻り値  
 なし  

- 説明 
利用するハードウェアタイマーを指定します。  
タイマー割り込み実行中は、本関数による変更は行わないで下さい。  

- 記述例  
`myTimer.setTimer(Tmer2);`  

#### 利用ハードウェアタイマーの参照

- 書式  
`HardwareTimer*  getTimer()`  

- 引数  
 なし  

- 戻り値  
ハードウェアタイマーへの参照（ポインタ）    
`Timer1`、`Timer2`、`Timer3`、`Timer4`のいずれかのポインタ    

- 説明 
利用しているハードウェアタイマーのポインタを取得します。  

- 記述例  
`pt = myTimer.getTimer();`  

