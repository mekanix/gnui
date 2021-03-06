//
// "$Id$"
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

#include <config.h>
#include <gnui/damage.h>
#include <gnui/MenuWindow.h>
#include <gnui/x.h>
#include <gnui/draw.h>

using namespace gnui;

/*! \class gnui::MenuWindow

  This is the window type used by Menu to make the pop-ups, and for
  tooltip popups. It will send special information to the window server
  to indicate that the windows are temporary, won't move, and should
  not have any decorations.

  On X this turns on override_redirect and save-under and thus avoids
  the window manager.
*/

static void revert(Style* s) {
  s->box_ = UP_BOX;
}
static NamedStyle style("MenuWindow", revert, &MenuWindow::default_style);
/*! The default style sets box() to UP_BOX. This box is used around all
  popup menus. */
NamedStyle* MenuWindow::default_style = &::style;

MenuWindow::MenuWindow(int W, int H, const char *l) : Window(W,H,l) {
  style(default_style);
  set_override();
}

MenuWindow::MenuWindow(int X, int Y, int W, int H, const char *l) : Window(X,Y,W,H,l) {
  style(default_style);
  set_override();
}

/*! \fn void MenuWindow::clear_overlay()
  Tells FLTK to not try to use the overlay hardware planes. This is
  disabled except on Irix. On Irix you will have to call this if you
  want to draw colored images in the popup.
*/

/*! \fn void MenuWindow::set_overlay()
  Undoes clear_overlay().
*/

#if USE_OVERLAY && !defined(__sgi)
#undef USE_OVERLAY
#define USE_OVERLAY 0
#endif

// _WIN32 note: USE_OVERLAY is false
#if USE_OVERLAY
extern XVisualInfo *gnui_find_overlay_visual();
extern XVisualInfo *gnui_overlay_visual;
extern Colormap gnui_overlay_colormap;
extern unsigned long gnui_transparent_pixel;
static GC menugc; // the GC used by all X windows
extern bool gnui_overlay; // changes how color(x) works
#endif

void MenuWindow::create() {
  set_override();
  clear_double_buffer();
#if USE_OVERLAY
  if (overlay() && gnui_find_overlay_visual()) {
    XInstallColormap(xdisplay, gnui_overlay_colormap);
    CreatedWindow::create(this, gnui_overlay_visual, gnui_overlay_colormap,
			  int(gnui_transparent_pixel));
  } else
#endif
    Window::create();
}

void MenuWindow::flush() {
#if USE_OVERLAY
  if (!gnui_overlay_visual || !overlay()) {Window::flush(); return;}
  CreatedWindow *i = CreatedWindow::find(this);
  xwindow = i->xid;
  if (!menugc) menugc = XCreateGC(xdisplay, i->xid, 0, 0);
  gnui::gc = menugc;
  gnui_overlay = true;
  current_ = this;
  bool expose =
    (damage() & DAMAGE_EXPOSE) && !(damage() & DAMAGE_ALL);
  if (expose) set_damage(damage() & ~DAMAGE_EXPOSE);
  if (damage()) draw();
  if (expose) {
    clip_region(i->region); i->region = 0;
    set_damage(DAMAGE_EXPOSE); draw();
    clip_region(0);
  }
  gnui_overlay = false;
#else
  Window::flush();
#endif
}

void MenuWindow::destroy() {
#if USE_OVERLAY
  // Fix the colormap flashing on Maximum Impact Graphics by erasing the
  // menu before unmapping it:
  if (gc && shown()) XClearWindow(xdisplay, xid(this));
#endif
  Window::destroy();
}

MenuWindow::~MenuWindow() {
  destroy();
}

//
// End of "$Id$".
//
