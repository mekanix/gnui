//
// "$Id: Menu.h,v 1.2 2002/12/10 02:00:29 easysw Exp $"
//
// Base class for MenuBar, Choice, Browser. This manages a set
// of child Item widgets, and handles a "List" object that can
// generate the Item widgets on the fly (allowing the menu or
// browser to show program-defined data). It also provides a
// popup method for widgets to call so they can use this to
// implement their own popup menus.
//
// Copyright 1998-2002 by Bill Spitzak and others.
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
// Please report all bugs and problems to "fltk-bugs@fltk.org".
//

#ifndef fltk_Menu_h
#define fltk_Menu_h

#include "Group.h"

namespace fltk {

class FL_API Menu;

class FL_API List {
public:
  virtual int children(const Menu*, const int* indexes, int level);
  virtual Widget* child(const Menu*, const int* indexes, int level);
  virtual void flags_changed(const Menu*, Widget*);
};

enum { // Special flag values for add(), you can also use Flags.h values
  // These match values from Fl_Menu_Item in fltk 1.0:
  MENU_TOGGLE = 2,
  MENU_RADIO = 8,
  SUBMENU = 0x40,
  MENU_DIVIDER = 0x80
};

class FL_API Menu : public Group {

public:

  Menu(int,int,int,int, const char* l=0);
  List* list() const {return list_;}
  void list(List* l) {list_ = l;}

  int children(const int* indexes, int level) const ;
  int children() const ;
  Widget* child(const int* indexes, int level) const ;
  Widget* child(int index) const ;
  Widget* item() const {return item_;}
  Widget* item(Widget* v) {return item_ = v;}
  bool focus(const int* indexes, int level);
  Widget* get_focus();

  int value() const {return Group::focus();}
  void value(int v) {Group::focus(v);}
  int  size() const {return children();}

  int popup(int x,int y,int w=0,int h=0,Widget* title=0,bool menubar=false);
  int handle_shortcut();
  static void default_callback(Widget*, void*);
  void execute(Widget*);
  void global();

  Widget* find(const char* label) const;
  Widget* add(const char*, int shortcut, Callback*, void* = 0, int = 0);
  Widget* replace(const char*, int scut, Callback*, void* = 0, int = 0);
  Widget* add(const char*, void*);
  Widget* add(const char*);
  Widget* insert(int n, const char* s, void* data = 0);
  void remove(const char* l) { delete find(l); }

  // Undo the overrides of stuff from Group:
  void add(Widget& o) {Group::add(o);}
  void add(Widget* o) {add(*o);}
  void insert(Widget& o, int n) {Group::insert(o, n);}
  void replace(int index, Widget& o) {Group::replace(index, o);}
  void replace(Widget& old, Widget& o) {Group::replace(old,o);}
  void remove(int index) {Group::remove(index);}
  void remove(Widget& o) {Group::remove(o);}
  void remove(Widget* o) {Group::remove(o);}

#ifdef Fl_Menu_Item_h
  // Commented-out methods cannot be emulated.
//const Fl_Menu_Item* test_shortcut();
//Fl_Menu_Item* menu() const;
  void copy(const Fl_Menu_Item* m, void* data = 0) {clear(); m->add_to(this,data);}
  void menu(const Fl_Menu_Item* m) {copy(m,0);}
  void replace(int n, const char* s) { child(n)->label(s); }
  void replace(const char* l, const char* s) { find(l)->label(s); }
  void shortcut(const char* l, int s) { find(l)->shortcut(s); }
  void shortcut(int s) {Widget::shortcut(s);}
  int shortcut() const {return Widget::shortcut();}
  void shortcut(int i, int s) { child(i)->shortcut(s); }
//int index(Fl_Menu_Item* m) const { return m - menu_; }
//int index(const char* label) const;
//void replace(Fl_Menu_Item* m, const char* s) { replace(index(m), s); }
//void remove(Fl_Menu_Item* m) { remove(index(m)); }
//void shortcut(Fl_Menu_Item* m, int s) {shortcut(index(m), s);}
//void mode(int i,int x);
//void mode(Fl_Menu_Item* m, int x) {mode(index(m), x);}
//void mode(const char* l, int x) {mode(index(l), x);}
  unsigned mode(int i) const {return child(i)->flags() >> 8;}
//unsigned mode(Fl_Menu_Item* m) const {return mode(index(m));}
  unsigned mode(const char* l) const {return find(l)->flags() >> 8;}

  // in fltk 1.0 these returned/took an Fl_Menu_Item*:
  Widget* mvalue() {return item();}
//void value(Widget* o) {set_item(o);}

  const char *text(int i) const {return i >= 0 ? child(i)->label() : 0;}
  const char *text() const {Widget* w = item(); return w ? w->label() : 0;}
#endif

private:
  List* list_;
  Widget* item_;
};

}

#endif

//
// End of "$Id: Menu.h,v 1.2 2002/12/10 02:00:29 easysw Exp $".
//