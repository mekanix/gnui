//
// "$Id: fl_dnd_win32.cxx,v 1.1 2001/02/25 01:41:19 clip Exp $"
//
// Drag & Drop code for the Fast Light Tool Kit (FLTK).
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


// Dummy version of dnd for now, it waits until the FL_RELEASE and
// then does nothing.  The real version should drag the ascii text stored
// in selection_buffer (length = selection_length) and drop it on the
// target. It should either not return until the mouse is released
// or it should cause the DRAG+RELEASE events to not be passed to the
// program somehow. I'm pretty sure this is a simple call in WIN32:

#include <FL/Fl.H>
#include <FL/Fl_Window.H>

static int grabfunc(int event, void*) {
  if (event == FL_RELEASE) Fl::pushed(0);
  return 0;
}

int Fl::dnd() {
  Fl::first_window()->cursor(FL_CURSOR_HAND);
  Fl::local_grab(grabfunc);
  while (Fl::pushed()) Fl::wait();
  Fl::first_window()->cursor(FL_CURSOR_DEFAULT);
  Fl::release();
  return 1;
}


//
// End of "$Id: fl_dnd_win32.cxx,v 1.1 2001/02/25 01:41:19 clip Exp $".
//