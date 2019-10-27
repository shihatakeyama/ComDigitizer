

#include "numerical.h"
#include "AM_Define.h"
#include "AM_Global.h"

//#include "Serial"

//++#ifdef USE_DIGITIZER
#include "Digitizer.h"
//++#endif

#ifdef USE_MOUSE
#include <Mouse.h>
#include "USBAPI.h"
#endif

#ifdef USE_KEYBOARD
#include "Keyboard.h"
#endif

/*
  JoystickMouseControl

  Controls the mouse from a joystick on an Arduino Leonardo, Micro or Due.
  Uses a pushbutton to turn on and off mouse control, and a second pushbutton
  to click the left mouse button.

  Hardware:
  - 2-axis joystick connected to pins A0 and A1
  - pushbuttons connected to pin D2 and D3

  The mouse movement is always relative. This sketch reads two analog inputs
  that range from 0 to 1023 (or less on either end) and translates them into
  ranges of -6 to 6.
  The sketch assumes that the joystick resting values are around the middle of
  the range, but that they vary within a threshold.

  WARNING: When you use the Mouse.move() command, the Arduino takes over your
  mouse! Make sure you have control before you use the command. This sketch
  includes a pushbutton to toggle the mouse control state, so you can turn on
  and off mouse control.

  created 15 Sep 2011
  updated 28 Mar 2012
  by Tom Igoe

  This example code is in the public domain.

  http://www.arduino.cc/en/Tutorial/JoystickMouseControl
*/

const int ledPin = 5;         // Mouse control LED

int LoopDelay = 1000;


void setup() {

  Serial.begin(115200);
  
  randomSeed(16);
 
//--  pinMode(switchPin, INPUT);       // the switch pin
//--  pinMode(ledPin, OUTPUT);         // the LED pin
  // take control of the mouse:

  // 最初1発効かない。?
//--  Digitizer.press(1000+random(20) ,720+random(20));
  Digitizer.click(1,1);

  delay(3000);
}

void loop() {
  int rxco_h,recvdata,i;

	if(Serial.available() > 0){
      recvdata = Serial.read(); // 受信データを読み込む
      rxco_h = gRxCo >> 1;
//      Serial.print("I received: "); // 受信データを送りかえす


		if(recvdata != CR){
      // 0.5バイトづつバッファにいれる。
      if((gRxCo & 0x01) == 0){
        gRxBuf[rxco_h] = asciiToInt(recvdata) << 4;
      }else{
        gRxBuf[rxco_h] |= asciiToInt(recvdata);
// Serial.write(gRxBuf[rxco_h]);
    }
      gRxCo++;
      if(gRxCo > TRX_BUF_SIZE){
        gRxCo = 0;
      }
		}else{
      
#if 1   // デバグ用
      {
        char dbuf[4];
        // 1フレーム受信完了
        Serial.print("frame");
//        Serial.print(rxco_h ,DEC);
//        Serial.write(" ");
        sprintf(dbuf ,"%2d",rxco_h);
        Serial.write(dbuf);
        for(i=0;i<rxco_h;i++){
//          Serial.print(gRxBuf[i] ,HEX); // gRxBuf[i]
          sprintf(dbuf ,"%02X",gRxBuf[i]);
          Serial.write(dbuf);
        }
        Serial.write("\x0D");
      }
#endif 
      if((gRxCo & 0x01) == 0){
        switch(gRxBuf[0]){
          case EN_mouse:      // マウス
            cmdMouse(&gRxBuf[0] ,rxco_h);
            break;
          case EN_keyboard:
            cmdKeyboard(&gRxBuf[0] ,rxco_h);// キーボード
            break;
          case EN_digitizer:  // デジタイザ
            cmdDigitizer(&gRxBuf[0] ,rxco_h);
            break;
          case EN_system:     // システム、メンテナンス
            cmdMainte(&gRxBuf[0] ,rxco_h);
            break;
          default:
            break;
        }
     }
     gRxCo = 0;
		}
		gRxTimer = RX_TIMEOUT;
	}else{
#if 1
		if(gRxTimer>0){
			gRxTimer--;
		}else{
			gRxCo = 0;
		}
#endif
		delay(1);
	}
    
}

// ランダム
int randScatter(int CenterVal ,int Width)
{
  Sint32 ret = random(Width);
  return CenterVal + ret - (Width>>1);
}
