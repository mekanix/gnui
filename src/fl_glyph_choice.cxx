//
// "$Id: fl_glyph_choice.cxx,v 1.1 1999/11/21 06:23:29 carl Exp $"
//
// Glyph drawing code for the Fast Light Tool Kit (FLTK).
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

#include <FL/Fl.H>

void fl_glyph_choice(int t, int x,int y,int w,int h, Fl_Color bc, Fl_Color fc,
                     Fl_Flags f, Fl_Boxtype box)
{
  int H = h/3;
  int Y = y + (h-H)/2;
  FL_FLAT_BOX->draw(x,Y,w,H, fc, f);
}

//
// End of "$Id: fl_glyph_choice.cxx,v 1.1 1999/11/21 06:23:29 carl Exp $".
//