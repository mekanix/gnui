//
// "$Id$"
//
// Forms pixmap drawing routines for the Fast Light Tool Kit (FLTK).
//
// Copyright 1998-2006 by Bill Spitzak and others.
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
// Please report all bugs and problems on the following page:
//
//    http://www.fltk.org/str.php
//

#include <fltk/forms.h>

GNUI_FormsPixmap::GNUI_FormsPixmap(
  GNUI_Boxtype t, int x, int y, int w, int h, const char* l)
: GNUI_Widget(x, y, w, h, l) {
  box(t);
  b = 0;
  clear_flag(GNUI_ALIGN_MASK);
  set_flag(GNUI_ALIGN_BOTTOM);
}

void GNUI_FormsPixmap::set(const char* const* bits) {
  delete b;
  b = new GNUI_Pixmap(bits);
}

void GNUI_FormsPixmap::draw() {
  box()->draw(0, 0, w(), h(), selection_color());
  if (b) {
    int W,H; b->measure(W,H);
    b->draw((w()-W)/2, (h()-H)/2);
  }
  draw_inside_label();
}

//
// End of "$Id$".
//
