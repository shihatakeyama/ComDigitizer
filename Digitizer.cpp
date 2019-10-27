/*
  Digitizer.cpp

  Copyright (c) 2015, Arduino LLC
  Original code (pre-library): Copyright (c) 2011, Peter Barrett

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/


#include "numerical.h"
#include "AM_Define.h"

#include "Digitizer.h"

#if defined(_USING_HID)

#define LSB(_x) ((_x) & 0xFF)
#define MSB(_x) ((_x) >> 8)

static const uint8_t _hidReportDescriptor[] PROGMEM = {
  
  // Digitizer
  0x05, 0x0d,                         // USAGE_PAGE (Digitizers) 
  0x09, 0x02,                         // USAGE (Pen) 
  0xa1, 0x01,                         // COLLECTION (Application) 
  0x85, 0x03,                         //   REPORT_ID (3) 
  0x09, 0x20,                         //   USAGE (Stylus) 
  0xa1, 0x00,                         //   COLLECTION (Physical)
  0x09, 0x42,                         //     USAGE (Tip Switch)
  0x09, 0x44,                         //     USAGE (Barrel Switch)
  0x09, 0x45,                         //     USAGE (Eraser Switch) 
  0x09, 0x3c,                         //     USAGE (Invert) 
  0x09, 0x32,                         //     USAGE (In Range) 
  0x15, 0x00,                         //     LOGICAL_MINIMUM (0)
  0x25, 0x01,                         //     LOGICAL_MAXIMUM (1) 
  0x75, 0x01,                         //     REPORT_SIZE (1) 
  0x95, 0x05,                         //     REPORT_COUNT (5)
  0x81, 0x02,                         //     INPUT (Data,Var,Abs) 
  0x95, 0x0b,                         //     REPORT_COUNT (11)
  0x81, 0x03,                         //     INPUT (Cnst,Var,Abs)
  0x05, 0x01,                         //     USAGE_PAGE (Generic Desktop)
  0x75, 0x10,                         //     REPORT_SIZE (16) 
  0x95, 0x01,                         //     REPORT_COUNT (1) 
  0x55, 0x0d,                         //     UNIT_EXPONENT (-3)
  0x65, 0x33,                         //     UNIT (Inch,EngLinear)
  0x15, 0x00,                         //     LOGICAL_MINIMUM (0)
  0x26, 0xff, 0x7f,                   //     LOGICAL_MAXIMUM (32767)
  0x09, 0x30,                         //     USAGE (X)
  0x81, 0x02,                         //     INPUT (Data,Var,Abs) 
  0x09, 0x31,                         //     USAGE (Y) 
  0x81, 0x02,                         //     INPUT (Data,Var,Abs) 
  0xc0,                               //   END_COLLECTION
  0xc0,                               // END_COLLECTION 
};

//================================================================================
//================================================================================
//	Digitizer

Digitizer_::Digitizer_(void)
: _buttons(0)
{
  setDisplayResolution(1280 ,1024);
  
  static HIDSubDescriptor node(_hidReportDescriptor, sizeof(_hidReportDescriptor));
  HID().AppendDescriptor(&node);
}

void Digitizer_::begin(void) 
{
}

void Digitizer_::end(void) 
{
}
void Digitizer_::setDisplayResolution(int resolution_x,int resolution_y)
{
  m_ax    = (float)0x8000 / (float)resolution_x;
  m_ay    = (float)0x8000 / (float)resolution_y;
}

/*
void Digitizer_::setLogicalResolution(int param_x0,int param_y0,int param_x1,int param_y1)
{
  logicalMinX = param_x0;
  logicalMinY = param_y0;
  logicalMaxX = param_x1;
  logicalMaxY = param_y1;
}
*/
void Digitizer_::click(int x ,int y)
{
//  logicalX = x;
//  logicalY = y;
  putPoint(x,y);
  click();
}
void Digitizer_::click()
{
#if 0
  _buttons = 0x01;
  sendReport();
  _buttons = 0;
  sendReport();  
#else
  buttons(0x01);
  buttons(0x00);
#endif
}
  
void Digitizer_::move(int x, int y)
{
  putPoint(x ,y);
}
/*
// �����͉�ʍ��W�Ŏw��
void Digitizer_::set(int Pos_x ,int Pos_y)
{
  double x,y;
  
  logicalX = map(Pos_x,screenX0,screenX1,logicalMinX,logicalMaxX);
  logicalY = map(Pos_y,screenY0,screenY1,logicalMinY,logicalMaxY);

  logicalX = (int)((double)Pos_x * (double)0x8000 / (double)1920);
  logicalY = (int)((double)Pos_y * (double)0x8000 / (double)1080);
  
  sendReport();
}
*/
void Digitizer_::sendReport() const
{
 #if 0
  uint8_t m[6];
  m[0] = 0x11; //0x10 | _buttons;
  m[1] = 0;
  m[2] = 0;  //LSB(logicalX);
  m[3] = 0x40;   //MSB(logicalX);
  m[4] = 0;  //LSB(logicalY);
  m[5] = 0x40;   //MSB(logicalY);
  HID().SendReport(3,m,6);
#else
  uint8_t m[6];
  m[0] = 0x10 | _buttons;
  m[1] = 0;
  m[2] = LSB(logicalX);
  m[3] = MSB(logicalX);
  m[4] = LSB(logicalY);
  m[5] = MSB(logicalY);
  HID().SendReport(3,m,6);
#endif
}
//================================================================================
// HIDに直接SendReport()します。
//================================================================================
void Digitizer_::sendDirectReport(uint8_t ReportId, const uint8_t *Data ,uint8_t Len) const
{
  HID().SendReport(ReportId, Data, Len);  
}
 
void Digitizer_::buttons(uint8_t b)
{
	if (b != _buttons)
	{
		_buttons = b;
		sendReport();
	}
}

void Digitizer_::press() 
{
  buttons(0x01);
}
void Digitizer_::press(int x ,int y)
{
  putPoint(x,y);
  press();  
}
  
void Digitizer_::release()
{
	buttons(0x00);
}

bool Digitizer_::isPressed()
{
	if ((0x01 & _buttons) > 0) 
		return true;
	return false;
}

// *********************************************************************************
// USBで送信する工学的な値をセット
// *********************************************************************************
void Digitizer_::putPoint(int Point_x ,int Point_y)
{
  logicalX = (int)(m_ax * Point_x);
  logicalY = (int)(m_ay * Point_y);

  if(logicalX < 0){
    logicalX = 0;
  }else if(logicalX > 0xFFFF){
    logicalX = 0xFFFF;
  }else{
  }

  if(logicalY < 0){
    logicalY = 0;
  }else if(logicalY > 0xFFFF){
    logicalY = 0xFFFF;
  }else{
  }
  
}

Digitizer_ Digitizer;

#endif
