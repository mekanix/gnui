//
// "$Id: Fl_Roller.h,v 1.1 2001/07/23 09:50:04 spitzak Exp $"
//
// Roller header file for the Fast Light Tool Kit (FLTK).
//
// Copyright 1998-1999 by Bill Spitzak and others.
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Library General Public
// License as published by the Free Software Foundation; either
// version 2 of the License, or (at your option) any later version.
//
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// Library General Public License for more details.
//
// You should have received a copy of the GNU Library General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307
// USA.
//
// Please report all bugs and problems to "fltk-bugs@easysw.com".
//

#ifndef Fl_Roller_H
#define Fl_Roller_H

#ifndef Fl_Valuator_H
#include "Fl_Valuator.h"
#endif

class FL_API Fl_Roller : public Fl_Valuator {
public:
  int handle(int);
  Fl_Roller(int X,int Y,int W,int H,const char* L=0);

protected:
  void draw();
};

#endif

//
// End of "$Id: Fl_Roller.h,v 1.1 2001/07/23 09:50:04 spitzak Exp $".
//