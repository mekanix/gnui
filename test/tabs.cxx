// generated by Fast Light User Interface Designer (fluid) version 2.0000

#include "tabs.h"

Fl_Window *foo_window=(Fl_Window *)0;

static void cb_cancel(Fl_Button*, void*) {
  exit(1);
}

static void cb_OK(Fl_Return_Button*, void*) {
  exit(0);
}

int main(int argc, char **argv) {
  Fl_Window* w;
  { Fl_Window* o = foo_window = new Fl_Window(321, 324);
    w = o;
    { Fl_Tabs* o = new Fl_Tabs(10, 10, 300, 200);
      o->color((Fl_Color)47);
      o->selection_color((Fl_Color)15);
      { Fl_Group* o = new Fl_Group(10, 30, 300, 180, "Label1");
        o->hide();
        new Fl_Input(60, 50, 240, 40, "input:");
        new Fl_Input(60, 90, 240, 30, "input2:");
        new Fl_Input(60, 120, 240, 80, "input3:");
        o->end();
        Fl_Group::current()->resizable(o);
      }
      { Fl_Group* o = new Fl_Group(10, 30, 300, 180, "tab2");
        o->hide();
        new Fl_Button(20, 60, 100, 30, "button1");
        new Fl_Input(140, 100, 100, 30, "input in box2");
        new Fl_Button(30, 140, 260, 30, "This is stuff inside the Fl_Group \"tab2\"");
        o->end();
      }
      { Fl_Group* o = new Fl_Group(10, 30, 300, 180, "tab3");
        o->hide();
        new Fl_Button(20, 60, 60, 80, "button2");
        new Fl_Button(80, 60, 60, 80, "button");
        new Fl_Button(140, 60, 60, 80, "button");
        o->end();
      }
      { Fl_Group* o = new Fl_Group(10, 30, 300, 180, "tab4");
        o->label_font(fl_fonts+2);
        o->hide();
        new Fl_Button(20, 50, 60, 110, "button2");
        new Fl_Button(80, 50, 60, 110, "button");
        new Fl_Button(140, 50, 60, 110, "button");
        o->end();
      }
      { Fl_Group* o = new Fl_Group(10, 30, 300, 180, "     tab5      ");
        o->label_type(FL_ENGRAVED_LABEL);
        o->hide();
        new Fl_Button(20, 80, 60, 80, "button2");
        new Fl_Button(90, 90, 60, 80, "button");
        { Fl_Clock* o = new Fl_Clock(160, 50, 100, 100, "Make sure this clock does not use processor time when this tab is hidden or w\
indow is iconized");
          o->box(FL_OSHADOW_BOX);
          o->label_font(fl_fonts+8);
          o->color((Fl_Color)238);
          o->label_size(10);
          o->align(130);
        }
        o->end();
      }
      o->end();
      Fl_Group::current()->resizable(o);
    }
    new Fl_Input(60, 220, 130, 30, "inputA:");
    new Fl_Input(60, 250, 250, 30, "inputB:");
    { Fl_Button* o = new Fl_Button(180, 290, 60, 30, "cancel");
      o->callback((Fl_Callback*)cb_cancel);
    }
    { Fl_Return_Button* o = new Fl_Return_Button(250, 290, 60, 30, "OK");
      o->shortcut(0xff0d);
      o->callback((Fl_Callback*)cb_OK);
    }
    o->end();
  }
  w->show(argc, argv);
  return Fl::run();
}