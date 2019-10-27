// *********************************************************************************
// AM_Global.h
//
// AutoMouse独自のグローバルを定義します。
// *********************************************************************************

#include "numerical.h"
#include "AM_Define.h"
#include "AM_Global.h"

// コマンド送受信
Sint8 gTxBuf[TRX_BUF_SIZE*2];    // ASCII
Uint8 gRxBuf[TRX_BUF_SIZE];
Sint16 gRxCo = 0;
Sint16 gRxTimer = 0;
