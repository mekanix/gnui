// generated by Fast Light User Interface Designer (fluid) version 2.0000

#include "mandelbrot_ui.h"
#include <stdlib.h>

inline void Drawing_Window::cb_x_input_i(Fl_Input* o, void*) {
  d->X = atof(o->value());;
d->new_display();
}
void Drawing_Window::cb_x_input(Fl_Input* o, void* v) {
  ((Drawing_Window*)(o->parent()->user_data()))->cb_x_input_i(o,v);
}

inline void Drawing_Window::cb_y_input_i(Fl_Input* o, void*) {
  d->Y = atof(o->value());
d->new_display();
}
void Drawing_Window::cb_y_input(Fl_Input* o, void* v) {
  ((Drawing_Window*)(o->parent()->user_data()))->cb_y_input_i(o,v);
}

inline void Drawing_Window::cb_w_input_i(Fl_Input* o, void*) {
  d->scale = atof(o->value());
d->new_display();
}
void Drawing_Window::cb_w_input(Fl_Input* o, void* v) {
  ((Drawing_Window*)(o->parent()->user_data()))->cb_w_input_i(o,v);
}

inline void Drawing_Window::cb_brightness_i(Fl_Slider* o, void*) {
  d->brightness = int(o->value());
d->new_display();
}
void Drawing_Window::cb_brightness(Fl_Slider* o, void* v) {
  ((Drawing_Window*)(o->parent()->user_data()))->cb_brightness_i(o,v);
}

inline void Drawing_Window::cb_iterations_i(Fl_Slider* o, void*) {
  d->iterations = 1<<int(o->value());
d->new_display();
}
void Drawing_Window::cb_iterations(Fl_Slider* o, void* v) {
  ((Drawing_Window*)(o->parent()->user_data()))->cb_iterations_i(o,v);
}

void Drawing_Window::make_window() {
  void* w;
  { Fl_Window* o = window = new Fl_Window(450, 520);
    w = o;
    o->user_data((void*)(this));
    { Drawing_Area* o = d = new Drawing_Area(20, 80, 410, 430);
      o->box(FL_DOWN_BOX);
      o->user_data((void*)(this));
      Fl_Group::current()->resizable(o);
    }
    { Fl_Input* o = x_input = new Fl_Input(30, 15, 125, 30, "x:");
      o->type(1);
      o->callback((Fl_Callback*)cb_x_input);
      o->when(FL_WHEN_ENTER_KEY|FL_WHEN_RELEASE);
    }
    { Fl_Input* o = y_input = new Fl_Input(175, 15, 125, 30, "y:");
      o->type(1);
      o->callback((Fl_Callback*)cb_y_input);
      o->when(FL_WHEN_ENTER_KEY|FL_WHEN_RELEASE);
    }
    { Fl_Input* o = w_input = new Fl_Input(325, 15, 105, 30, "w:");
      o->type(1);
      o->callback((Fl_Callback*)cb_w_input);
      o->when(FL_WHEN_ENTER_KEY|FL_WHEN_RELEASE);
    }
    { Fl_Slider* o = new Fl_Slider(80, 50, 160, 15, "brightness:");
      o->type(1);
      o->step(1);
      o->slider_size(2560);
      o->callback((Fl_Callback*)cb_brightness);
      o->align(FL_ALIGN_LEFT);
      o->range(0,d->MAX_BRIGHTNESS);
      o->value(d->DEFAULT_BRIGHTNESS);
    }
    { Fl_Box* o = new Fl_Box(240, 50, 190, 30, "left: click = zoom out, drag = zoom in\nright click: Julia set");
      o->label_size(10);
      o->align(FL_ALIGN_RIGHT|FL_ALIGN_INSIDE);
      o->deactivate();
    }
    { Fl_Slider* o = new Fl_Slider(80, 65, 160, 15, "iterations:");
      o->type(1);
      o->step(1);
      o->slider_size(2560);
      o->callback((Fl_Callback*)cb_iterations);
      o->align(FL_ALIGN_LEFT);
      o->range(1,d->MAX_ITERATIONS);
      o->value(d->DEFAULT_ITERATIONS);
    }
    o->size_range(220,220);
    o->end();
  }
}