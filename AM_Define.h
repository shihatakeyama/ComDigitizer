// *********************************************************************************
// AutoMouseDefine.h
// *********************************************************************************


#define CPU_VERSION		0x0118B130

//--#define _USING_HID

#define USE_DIGITIZER	// �f�W�^�C�U���g�p����ꍇ�������B
#define USE_MOUSE
#define USE_KEYBOARD

// コマンド送信、受信用
#define TRX_BUF_SIZE     32
#define RX_TIMEOUT      400
#define CR              0x0D  // コマンド終端
#define RX_TIMEOUT      400


enum E_Notification{
  EN_mouse      = 1,
  EN_keyboard   = 2,
  EN_digitizer  = 3,
  EN_system     = 0x99
};

struct AM_Point{
  Sint32 x, y;
  Sint32 randx, randy;
  Sint32 wait;
};

// operation_Thread.cpp
struct AM_CommandFrame{
  Uint8 Command1;
  Uint8 Command2;
  Uint8 Len;          // Data長
  Uint8 Data[TRX_BUF_SIZE-3];
};
// -----------------------------------------------------------------------------
// command.cpp
// -----------------------------------------------------------------------------

void cmdMainte(const Uint8 *Cmd ,Sint16 len);
void cmdKeyboard(const Uint8 *Cmd ,Sint16 len);
void cmdDigitizer(const Uint8 *Cmd ,Sint16 len);
void cmdMouse(const Uint8 *Cmd ,Sint16 len);
void cmdVersion(const Uint8 *Cmd ,Sint16 len);
void cmdRandomSeed(const Uint8 *Cmd ,Sint16 len);
