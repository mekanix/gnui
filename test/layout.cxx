// Layout managers test program Fast Light Tool Kit (FLTK).
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

#include <stdio.h>
#include <FL/Fl.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Choice.H>
#include <FL/Fl_Light_Button.H>
#include <FL/Fl_Layout.H>
#include <FL/Fl_Window.H>

Fl_Align_Group* lower_half;

void align_cb(Fl_Choice* c,long w) {
  switch (w) {
    case 0: lower_half->vertical(!c->value()); break;
    case 1: 
    case 2: {
      Fl_Align new_align = lower_half->align();
      new_align &= (w == 1) ?
                   (FL_ALIGN_TOP | FL_ALIGN_BOTTOM) :
                   (FL_ALIGN_LEFT | FL_ALIGN_RIGHT);
      if (w == 1 && c->value() == 0) new_align |= FL_ALIGN_LEFT;
      if (w == 1 && c->value() == 1) new_align |= FL_ALIGN_RIGHT;
      if (w == 2 && c->value() == 0) new_align |= FL_ALIGN_TOP;
      if (w == 2 && c->value() == 1) new_align |= FL_ALIGN_BOTTOM;
      lower_half->align(new_align);
    }
    default: break;
  }
  lower_half->layout();
  lower_half->redraw();
}

int main(int argc, char ** argv) {
  Fl_Window *window = new Fl_Window(600,400);

  // I had to add this new group so that we can get the desired layout
  // type, since you no longer can change it on a window:
  Fl_Align_Group main_group(0,0,600,400,0,2,true,0,5,5);

  Fl_Align_Group* o = new Fl_Align_Group(0,0,0,0,0,2,false,FL_ALIGN_TOP_LEFT);
  {
    Fl_Align_Group* o = new Fl_Align_Group(0,0,0,0,"Tiled Buttons",
					   3,false,0,10,10);
    o->box(FL_DOWN_BOX);
    char *l,labels[18];
    l=labels;
    for (int i=1;i<=9;i++) {
      sprintf(l,"%1d",i);
      (void) new Fl_Button(0,0,0,0,l);
      l+=2;
    }
    o->end();
  }
  {
    Fl_Align_Group* o=new Fl_Align_Group(0,0,0,0,"Fl_Align_Group options",
					 3,true,0,10,10);
    o->box(FL_DOWN_BOX);
    static char* labels[3][3]={{"Vertical","Horizontal",""},
			       {"Left","Right","Center"},
			       {"Top","Bottom","Center"}};
    Fl_Choice* c;
    for (int i=0;i<3;i++) {
      c = new Fl_Choice(0,0,0,0);
      for (int j=0;j<3;j++) {c->add(labels[i][j]);if (i==0 && j==1) break;}
      c->callback((Fl_Callback*)align_cb);
      c->user_data((void*)i);
      c->value(i==2?2:0);
    }
    o->end();
  }
  o->end();
  o = lower_half = new Fl_Align_Group(0,0,0,0,0,4,true,FL_ALIGN_LEFT,10,10);
  o->box(FL_DOWN_BOX);
  static char* labels[24]={"Although","these","labels","have",
                           "different","lengths",",","the",
			   "widgets","they","belong","to",
			   "are","properly","aligned",".",
			   "Variable","lenghts\nare","respected\n,","as\nseen",
			   "h","e","r","e"};
  for (int i=0;i<24;i++) (void) new Fl_Button(0,0,0,0,labels[i]);
  o->end();

  main_group.end();
  main_group.layout(); // this is a bug, should not be necessary to call this
  window->resizable(main_group);
  window->end();
  window->show(argc,argv);
  return Fl::run();
}
