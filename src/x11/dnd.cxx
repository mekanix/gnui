//
// "$Id$"
//
// Drag & Drop code for the Fast Light Tool Kit (FLTK).
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
//    http://www.gnui.org/str.php
//

// If this is set true, try to emulate drop on old programs by doing
// middle-mouse click. Unfortunatly lots of old programs do not work
// with this, so the cursor is misleading.
#define FAKE_DROP 0

#include <gnui/Window.h>
#include <gnui/run.h>
#include <gnui/events.h>
#include <gnui/Cursor.h>
#include <gnui/x.h>
using namespace gnui;

extern Atom XdndAware;
extern Atom XdndSelection;
extern Atom XdndEnter;
extern Atom XdndTypeList;
extern Atom XdndPosition;
extern Atom XdndLeave;
extern Atom XdndDrop;
extern Atom XdndStatus;
extern Atom XdndActionCopy;
extern Atom XdndFinished;
extern Atom textplainutf;
extern Atom textplain;
extern Atom UTF8_STRING;
//extern Atom XdndProxy;
extern Atom *gnui_incoming_dnd_source_types;

extern bool gnui_i_own_selection[2];

extern void gnui_sendClientMessage(XWindow xwindow, Atom message,
				 unsigned long d0,
				 unsigned long d1=0,
				 unsigned long d2=0,
				 unsigned long d3=0,
				 unsigned long d4=0);

// return version # of Xdnd this window supports.  Also change the
// window to the proxy if it uses a proxy:
static int dnd_aware(XWindow xwindow) {
  Atom actual; int format; unsigned long count, remaining;
  unsigned char *data = 0;
  XGetWindowProperty(xdisplay, xwindow, XdndAware,
		     0, 4, false, XA_ATOM,
		     &actual, &format,
		     &count, &remaining, &data);
  if (actual == XA_ATOM && format==32 && count && data)
    return int(*(Atom*)data);
  return 0;
}

static bool drop_ok;
static bool moved;

static bool grabfunc(int event) {
  if (event == RELEASE) pushed(0);
  else if (event == MOVE) moved = true;
  else if (!event && xevent.type == ClientMessage
	   && xevent.xclient.message_type == XdndStatus) {
    drop_ok = xevent.xclient.data.l[1] != 0;
    if (drop_ok) dnd_action = xevent.xclient.data.l[3];
  }
  return false;
}

extern bool (*gnui_local_grab)(int); // in Fl.cxx

// send an event to an gnui window belonging to this program:
static bool local_handle(int event, Window* window) {
  gnui_local_grab = 0;
  e_x = e_x_root-window->x();
  e_y = e_y_root-window->y();
  int ret = handle(event,window);
  gnui_local_grab = grabfunc;
  return ret;
}

extern gnui::Cursor gnui_drop_ok_cursor;

/*!
  Drag and drop the data set by the most recent gnui::copy() (with the
  clipboard argument false). Returns true if the data was dropped on
  something that accepted it.

  By default only blocks of text are dragged. You can use
  system-specific variables to change the type of data.
*/
bool gnui::dnd() {
  // Remember any user presets for the action and types:
  Atom* types;
  Atom action;
  Atom local_source_types[3] = {textplainutf, textplain, UTF8_STRING};
  if (dnd_source_types == gnui_incoming_dnd_source_types) {
    types = local_source_types;
    action = XdndActionCopy;
  } else {
    types = dnd_source_types;
    action = dnd_source_action;
  }

  Window* source_window = Window::first();
  XWindow source_xwindow = xid(source_window);

  gnui_local_grab = grabfunc;
  XWindow target_window = 0;
  Window* local_window = 0;
  int version = 4; int dest_x, dest_y;
  XSetSelectionOwner(xdisplay, XdndSelection, message_window, event_time);
  //  Cursor oldcursor = CURSOR_DEFAULT;
  drop_ok = true;
  moved = true;

  while (event_state(ANY_BUTTON)) {

    // figure out what window we are pointing at:
    XWindow new_window = 0; int new_version = 0;
    Window* new_local_window = 0;
    for (XWindow child = RootWindow(xdisplay, xscreen);;) {
      XWindow root; unsigned int junk3;
      XQueryPointer(xdisplay, child, &root, &child,
		    &e_x_root, &e_y_root, &dest_x, &dest_y, &junk3);
      if (!child) {
	if (!new_window && (new_version = dnd_aware(root))) new_window = root;
	break;
      }
      new_window = child;
      if ((new_local_window = find(child))) break;
      if ((new_version = dnd_aware(new_window))) break;
    }

    if (new_window != target_window) {
      if (local_window) {
	dnd_source_window = 0;
	local_handle(DND_LEAVE, local_window);
      } else if (version) {
	gnui_sendClientMessage(target_window, XdndLeave, source_xwindow);
      }
      version = new_version;
      target_window = new_window;
      local_window = new_local_window;
      if (local_window) {
	dnd_source_window = source_xwindow;
	dnd_source_types = types;
	dnd_type = UTF8_STRING;
	local_handle(DND_ENTER, local_window);
      } else if (version) {
	gnui_sendClientMessage(target_window, XdndEnter, source_xwindow,
			     version<<24,
			     types[0], types[1], types[1] ? types[2] : 0);
      }
    }
    if (local_window) {
      dnd_source_window = source_xwindow;
      dnd_source_types = types;// ?? is this needed?
      dnd_action = action;
      drop_ok = local_handle(DND_DRAG, local_window);
    } else if (version) {
      if (moved)
	gnui_sendClientMessage(target_window, XdndPosition, source_xwindow,
			     0, (e_x_root<<16)|e_y_root, event_time,
			     action);
    } else {
#if FAKE_DROP
      drop_ok = (types == local_source_types);
#else
      drop_ok = false;
#endif
    }
    source_window->cursor(drop_ok ? &gnui_drop_ok_cursor : CURSOR_NO);
    moved = false;
    wait();
  }

  if (!drop_ok) ;
  else if (local_window) {
    gnui_i_own_selection[0] = true;
    if (local_handle(DND_RELEASE, local_window)) {
      gnui_local_grab = 0;
      source_window->cursor(0);
      paste(*belowmouse(),false);
    }
  } else if (version) {
    gnui_sendClientMessage(target_window, XdndDrop, source_xwindow,
			 0, event_time);
#if FAKE_DROP
  } else if (target_window) {
    // fake a drop by clicking the middle mouse button:
    XButtonEvent msg;
    msg.type = ButtonPress;
    msg.window = target_window;
    msg.root = RootWindow(xdisplay, xscreen);
    msg.subwindow = 0;
    msg.time = event_time+1;
    msg.x = dest_x;
    msg.y = dest_y;
    msg.x_root = e_x_root;
    msg.y_root = e_y_root;
    msg.state = 0x0;
    msg.button = Button2;
    XSendEvent(xdisplay, target_window, false, 0L, (XEvent*)&msg);
    msg.time++;
    msg.state = 0x200;
    msg.type = ButtonRelease;
    XSendEvent(xdisplay, target_window, false, 0L, (XEvent*)&msg);
#endif
  }

  gnui_local_grab = 0;
  source_window->cursor(0);

  // reset the action and type:
  dnd_source_types = gnui_incoming_dnd_source_types;

  return drop_ok;
}


//
// End of "$Id$".
//
