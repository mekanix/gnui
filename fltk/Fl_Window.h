//
// "$Id: Fl_Window.h,v 1.1 2001/07/23 09:50:04 spitzak Exp $"
//
// Window header file for the Fast Light Tool Kit (FLTK).
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

#ifndef Fl_Window_H
#define Fl_Window_H

#include "Fl_Group.h"

// value for x,y to indicate window system places window
#define  FL_USEDEFAULT ((int)0x80000000) // same as Win32 value

class FL_API Fl_Window : public Fl_Group {
public:

  Fl_Window(int,int,int,int, const char* = 0);
  Fl_Window(int,int, const char* = 0);
  static Fl_Named_Style* default_style;
  virtual ~Fl_Window();

  virtual int handle(int);

  void clear_border()	{set_flag(FL_NOBORDER);}
  int border() const	{return !(flags() & FL_NOBORDER);}
  void set_override()	{set_flag(FL_NOBORDER|FL_OVERRIDE);}
  int override() const  { return flags()&FL_OVERRIDE; }
  void set_modal()	{set_flag(FL_MODAL);}
  int modal() const	{return flags() & FL_MODAL;}
  void set_non_modal()	{set_flag(FL_NON_MODAL);} // back compatability only!

  void move(int x, int y);
  void hotspot(int x, int y, int offscreen = 0);
  void hotspot(const Fl_Widget*, int offscreen = 0);
  void hotspot(const Fl_Widget& p, int offscreen = 0) {hotspot(&p,offscreen);}
  void size_range(int a, int b, int c=0, int d=0, int e=0, int f=0)
    { minw=a; minh=b; maxw=c; maxh=d; dw=e; dh=f; size_range_(); }

  const char* label() const	{return Fl_Widget::label();}
  const char* iconlabel() const	{return iconlabel_;}
  void label(const char*);
  void iconlabel(const char*);
  void label(const char* label, const char* iconlabel);
  const void* icon() const	{return icon_;}
  void icon(const void * ic)	{icon_ = ic;}
  static const char* xclass()	{return xclass_;}
  static void xclass(const char* v) {xclass_ = v;}

  int shown() const {return i != 0;}
  void show();
  void show(int, char**);
  void show(const Fl_Window* parent);
  int exec(const Fl_Window* parent = 0);
  void show_inside(const Fl_Window* parent);
  void iconize();
  int iconic() const;
  virtual void destroy();

  void fullscreen();
  void fullscreen_off(int,int,int,int);

  int x_root() const ;
  int y_root() const ;

  static const Fl_Window *current() {return current_;}
  void make_current() const;

  void cursor(Fl_Cursor, Fl_Color=FL_BLACK, Fl_Color=FL_WHITE);
  static void default_callback(Fl_Window*, void* v);

  const Fl_Window* modal_for() const {return modal_for_;}
  void modal_for(const Fl_Window* w);

  virtual void layout();
  virtual void flush();
  virtual void draw();
  virtual void draw_n_clip();

protected:
  virtual void create();
  static const Fl_Window *current_;

private:

  friend class Fl_X; Fl_X *i; // points at the system-specific stuff
  const Fl_Window* modal_for_;
  const char* iconlabel_;
  const void* icon_;
  // size_range stuff:
  short minw, minh, maxw, maxh;
  unsigned char dw, dh, size_range_set;
  void size_range_();
  // values for flags():
  enum {
    FL_MODAL		= 0x80000000,
    FL_NOBORDER 	= 0x40000000,
    FL_OVERRIDE         = 0x20000000,
    FL_NON_MODAL 	= 0x10000000
  };
  static const char* xclass_;
  void _Fl_Window(); // constructor innards
};

#endif

//
// End of "$Id: Fl_Window.h,v 1.1 2001/07/23 09:50:04 spitzak Exp $".
//