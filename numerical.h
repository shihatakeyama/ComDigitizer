// *********************************************************************************
// numerical.h
// *********************************************************************************

// -----------------------------------------------------------------------------
//  CPU依存
// �^���v���g�^�C�v
// -----------------------------------------------------------------------------
typedef  char         Sint8;
typedef unsigned char Uint8;
typedef bool          Bool;
typedef int           Bool32;
typedef void*         pVoid;    // ���@�ɔp�~�\��
typedef void*         Pvoid;    // 32bit-64bit �|�C���^�݊��̈�
typedef short         Sint16;
typedef unsigned short  Uint16;
typedef long          Sint32;   // CPU依存
typedef unsigned long Uint32;
typedef float         Float32;
typedef double        Float64;


// *********************************************************************************
//  配列/整数 変換
// *********************************************************************************
Uint16 Uint8ArrowToUint16(const Uint8 * data);
void Uint16ToUint8Arrow(Uint8 * Result ,Uint16 Src);
void Uint32ToUint8Arrow(Uint8 * Result ,Uint32 Numerial);

Sint32 intArrowToDump16(Sint8 *OutAscii ,const Uint8 *Src ,Sint32 Len);
Uint8 asciiToInt(Sint8 c);
