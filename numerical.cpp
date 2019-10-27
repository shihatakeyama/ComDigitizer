// *********************************************************************************
// numerical.cpp
// *********************************************************************************

#include "numerical.h"


// *********************************************************************************
// �^�ϊ�
// *********************************************************************************
Uint16 Uint8ArrowToUint16(const Uint8 * data)
{
	return  ((Uint16)data[0] << 8) | (Uint16)data[1];
}

void Uint16ToUint8Arrow(Uint8 * Result ,Uint16 Src)
{
	Result[0] = (Uint8)(Src >> 8);
	Result[1] = (Uint8)(Src & 0xff);
}

void Uint32ToUint8Arrow(Uint8 * Result ,Uint32 Numerial)
{
    Result[0] = (Uint8)(Numerial >> 24);
    Result[1] = (Uint8)(Numerial >> 16);
    Result[2] = (Uint8)(Numerial >> 8);
    Result[3] = (Uint8)(Numerial);
}

// *********************************************************************************
// 数値を16進ダンプ変換します。
// 戻り値：OutAscii出力した長さ
// *********************************************************************************
Sint32 intArrowToDump16(Sint8 *OutAscii ,const Uint8 *Src ,Sint32 Len)
{
  const static Sint8 ictbl[] = {'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};
  Sint32 i,ii=0;

  for(i=0;i<Len;i++){
    OutAscii[ii] = ictbl[Src[i] >> 4];
    ii++;
    OutAscii[ii] = ictbl[Src[i] & 0x0F];  
    ii++;
  }

  return ii;
}

// *********************************************************************************
// AsciiをIntに変換します。
// *********************************************************************************
Uint8 asciiToInt(Sint8 c)
{
  if('0' <= c && c <= '9') return (c-'0');
  if('A' <= c && c <= 'F') return (c-'A'+10);
  if('a' <= c && c <= 'f') return (c-'a'+10);
  return 0;
}
