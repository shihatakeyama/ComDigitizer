// *********************************************************************************
//  �R�}���h����
// *********************************************************************************

#include <stdio.h>
#include "numerical.h"
#include "AM_Global.h"

#include "AM_Define.h"

#include "USBAPI.h"
//--#include "Serial"

#include "Digitizer.h"


// *********************************************************************************
// コマンドを送信します。
// *********************************************************************************
Sint32 sendCommand(Uint8 Comand1 ,Uint8 Comand2 ,const Uint8 *Data ,Uint8 Len)
{
  Sint32 len;

//  len = intArrowToDump16((Sint8*)gTxBuf ,(Uint8*)Paran ,Paran->Len+2);

  intArrowToDump16((Sint8*)&gTxBuf[0] ,&Comand1 ,sizeof(Comand1));
  intArrowToDump16((Sint8*)&gTxBuf[2] ,&Comand2 ,sizeof(Comand2));
  len = 4;

  intArrowToDump16((Sint8*)&gTxBuf[4] ,Data ,Len);
  len += Len * 2;
  
  gTxBuf[len] = CR;
  len++;

  gTxBuf[len] = 0x00;
  len++;

  Serial.print(gTxBuf);
  
  return 0;
}

// -----------------------------------------------------------------------------
// デバグ用モニタ
// -----------------------------------------------------------------------------
Sint32 sendDebugLogFormat(const Sint8 *Text ,Uint16 Arg1 ,Uint16 Arg2)
{
  Sint8 buf[64];
  Uint8 cc;
  Sint32 len;
  
  cc = 0xD0;
  intArrowToDump16((Sint8*)&gTxBuf[0] ,&cc ,sizeof(cc));
  cc = 0x01;
  intArrowToDump16((Sint8*)&gTxBuf[2] ,&cc ,sizeof(cc));
  len = 4;

  strcpy(&gTxBuf[len] ,Text);
  Serial.write(gTxBuf);

  sprintf(gTxBuf ,",%d,%d\0d",Arg1 ,Arg2);

  Serial.write(gTxBuf);
}


#ifdef USE_DIGITIZER

// -----------------------------------------------------------------------------
// �f�W�^�C�U�}���h�󂯂�
// Cmd[0] : 0x03(�f�W�^�C�U) �Œ�
// Cmd[1] : 0x01 
// -----------------------------------------------------------------------------
void cmdDigitizer(const Uint8 *Cmd ,Sint16 len)
{
	Uint16 x0,y0,x,y;

	switch(Cmd[1]){
		case 0x00:  // リリース
      Digitizer.release();      
	  	break;
		case 0x02:	// 押下 座標なし
			Digitizer.press();
  		break;
		case 0x03:	// 押下 座標あり
			x = Uint8ArrowToUint16(&Cmd[2]);
			y = Uint8ArrowToUint16(&Cmd[4]);
			Digitizer.press(x ,y);	// click()
  		break;
    case 0x06:  // クリック 座標なし
      Digitizer.click();
      break;    
    case 0x07:  // クリック 座標あり
      x = Uint8ArrowToUint16(&Cmd[2]);
      y = Uint8ArrowToUint16(&Cmd[4]);
      Digitizer.click(x ,y);
/*      Digitizer.click(200,300);
      Serial.print("click");
      Serial.print(x ,DEC);
      Serial.println(y ,DEC);
      */
      break;
    case 0x04:  // 移動
      x = Uint8ArrowToUint16(&Cmd[2]);
      y = Uint8ArrowToUint16(&Cmd[4]);
      Digitizer.move(x ,y);
      break;
		case 0x90:	// �ݒ�
			x = Uint8ArrowToUint16(&Cmd[2]);
			y = Uint8ArrowToUint16(&Cmd[4]);
//			Digitizer.setDisplayResolution(x ,y);	// 1920,1080
      Digitizer.setDisplayResolution(1920,1080);
//--      Serial.print("setDisplayResolution");
//--      Serial.print(x ,DEC);
//--      Serial.println(y ,DEC);

      sendDebugLogFormat("setDisplayResolution" ,x ,y);
		break;
		default:
		break;
	}
}
#endif //#define USE_DIGITIZER

#ifdef USE_MOUSE
// -----------------------------------------------------------------------------
// �}�E�X�R�}���h�󂯂�
// Cmd[0] : 0x01(Mouse) �Œ�
// Cmd[1] : 0x01
// -----------------------------------------------------------------------------
void cmdMouse(const Uint8 *Cmd ,Sint16 len)
{
	
}
#endif //#define USE_MOUSE

void cmdMainte(const Uint8 *Cmd ,Sint16 len)
{
  switch(Cmd[1]){
    case 0x01:
      cmdRandomSeed(Cmd ,len);
      break;
    case 0x99:
      cmdVersion(Cmd ,len);
      break;
  }
}

void cmdRandomSeed(const Uint8 *Cmd ,Sint16 len)
{
  long seedval = ((long)Cmd[2]<<24) | ((long)Cmd[3]<<16) | ((long)Cmd[4]<<8) | ((long)Cmd[5]<<0);  

  randomSeed(seedval);
}

// -----------------------------------------------------------------------------
// �o�[�W�����擾�R�}���h�󂯂�
// -----------------------------------------------------------------------------
void cmdVersion(const Uint8 *Cmd ,Sint16 len)
{
  Uint8 buf[8];
  memset(buf ,0 ,sizeof(buf));
  
  Uint32ToUint8Arrow(&buf[0] ,(Uint32)CPU_VERSION);
/*  
buf[0] = CPU_VERSION>>24;
buf[1] = CPU_VERSION>>16;
buf[2] = CPU_VERSION>>8;
buf[3] = CPU_VERSION>>0;
buf[4] = 0x05;
buf[5] = 0x06;
buf[6] = 0x07;
buf[7] = 0x08;
  */
  sendCommand(0x99 ,0x99 ,&buf[0] ,4);
  }
