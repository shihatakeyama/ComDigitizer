/*
  Digitizer.h

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

#ifndef DIGITIZER_H
#define DIGITIZER_H

#include "HID.h"

#if !defined(_USING_HID)

#warning "Using legacy HID core (non pluggable)"

#else

//================================================================================
//================================================================================
//  Digitizer

#define MOUSE_LEFT 1
#define MOUSE_RIGHT 2
#define MOUSE_MIDDLE 4
#define MOUSE_ALL (MOUSE_LEFT | MOUSE_RIGHT | MOUSE_MIDDLE)

class Digitizer_
{

private:
  uint8_t _buttons;			// ������Ă�{�^���̎��
  int screenX0,screenY0,screenX1,screenY1;
  float m_ax,m_ay;
  int logicalMinX,logicalMinY,logicalMaxX,logicalMaxY;
  int logicalX, logicalY;
//---  uint8_t _switch;
  void sendReport() const;
  void sendDirectReport(uint8_t ReportId, const uint8_t *Data ,uint8_t Len) const;
  void buttons(uint8_t b);

public:
  Digitizer_(void);
  void begin(void);
  void end(void);
  void setDisplayResolution(int resolution_x,int resolution_y);
//--  void setLogicalResolution(int param_x0,int param_y0,int param_x1,int param_y1);
  void click();
  void click(int x ,int y);

  void move(int x, int y);
//--  void set(int Pos_x ,int Pos_y);
  void press();     // press LEFT by default
  void press(int x ,int y);    
  void release();   // release LEFT by default
  bool isPressed(); // check LEFT by default

private:
  void putPoint(int Point_x ,int Point_y);  // 工学的な値をセット  
};
extern Digitizer_ Digitizer;

#endif
#endif
