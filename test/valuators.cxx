// generated by Fast Light User Interface Designer (fluid) version 2.1000

#include "valuators.h"

static void callback(gnui::Widget* o, void*) {
  printf("%g     \r", ((gnui::Valuator*)o)->value());
  fflush(stdout);
}

#include <fltk/run.h>

int main (int argc, char **argv) {

  gnui::Window* w;
   {gnui::Window* o = new gnui::Window(565, 490, "Valuator classes, showing values for the type()");
    w = o;
    o->labelsize(10);
    o->shortcut(0xff1b);
    o->begin();
     {gnui::Widget* o = new gnui::Widget(10, 10, 280, 235, "GNUI_Slider");
      o->box(gnui::ENGRAVED_BOX);
      o->labelfont(gnui::HELVETICA_BOLD);
      o->color((gnui::Color)49);
      o->align(gnui::ALIGN_TOP|gnui::ALIGN_CENTER);
    }
     {gnui::Slider* o = new gnui::Slider(25, 49, 20, 157, "VERTICAL");
      o->set_vertical();
      o->color((gnui::Color)10);
      o->selection_color((gnui::Color)1);
      o->labelsize(8);
      o->callback((gnui::Callback*)callback);
      o->align(gnui::ALIGN_TOP);
    }
     {gnui::Slider* o = new gnui::Slider(60, 70, 20, 158, "VERTICAL|TICK_LEFT");
      o->type(gnui::Slider::TICK_ABOVE);
      o->set_vertical();
      o->color((gnui::Color)10);
      o->selection_color((gnui::Color)1);
      o->labelsize(8);
      o->callback((gnui::Callback*)callback);
    }
     {gnui::Slider* o = new gnui::Slider(100, 49, 20, 157, "VERTICAL|TICK_RIGHT");
      o->type(gnui::Slider::TICK_BELOW);
      o->set_vertical();
      o->color((gnui::Color)10);
      o->selection_color((gnui::Color)1);
      o->labelsize(8);
      o->callback((gnui::Callback*)callback);
      o->align(gnui::ALIGN_TOP);
    }
     {gnui::Slider* o = new gnui::Slider(140, 54, 130, 16, "HORIZONTAL");
      o->color((gnui::Color)10);
      o->selection_color((gnui::Color)1);
      o->labelsize(8);
      o->callback((gnui::Callback*)callback);
    }
     {gnui::Slider* o = new gnui::Slider(140, 81, 130, 22, "HORIZONTAL|TICK_ABOVE");
      o->type(gnui::Slider::TICK_ABOVE);
      o->color((gnui::Color)10);
      o->selection_color((gnui::Color)1);
      o->labelsize(8);
      o->callback((gnui::Callback*)callback);
    }
     {gnui::Slider* o = new gnui::Slider(140, 119, 130, 22, "HORIZONTAL|TICK_ABOVE,box");
      o->type(gnui::Slider::TICK_ABOVE);
      o->box(gnui::DOWN_BOX);
      o->color((gnui::Color)10);
      o->selection_color((gnui::Color)1);
      o->labelsize(8);
      o->callback((gnui::Callback*)callback);
    }
     {gnui::Slider* o = new gnui::Slider(140, 157, 130, 22, "HORIZONTAL|TICK_BELOW");
      o->type(gnui::Slider::TICK_BELOW);
      o->color((gnui::Color)10);
      o->selection_color((gnui::Color)1);
      o->labelsize(8);
      o->callback((gnui::Callback*)callback);
    }
     {gnui::Slider* o = new gnui::Slider(140, 201, 130, 22, "HORIZONTAL|TICK_BOTH");
      o->type(gnui::Slider::TICK_BOTH);
      o->color((gnui::Color)10);
      o->selection_color((gnui::Color)1);
      o->labelsize(8);
      o->callback((gnui::Callback*)callback);
    }
     {gnui::Widget* o = new gnui::Widget(295, 10, 260, 126, "GNUI_Value_Input");
      o->box(gnui::ENGRAVED_BOX);
      o->labelfont(gnui::HELVETICA_BOLD);
      o->color((gnui::Color)49);
      o->align(gnui::ALIGN_TOP|gnui::ALIGN_CENTER);
    }
     {gnui::ValueInput* o = new gnui::ValueInput(360, 35, 180, 22, "outside label");
      o->color((gnui::Color)10);
      o->selection_color((gnui::Color)1);
      o->labelsize(8);
      o->callback((gnui::Callback*)callback);
    }
     {gnui::ValueInput* o = new gnui::ValueInput(310, 63, 100, 22, "inside");
      o->color((gnui::Color)10);
      o->selection_color((gnui::Color)1);
      o->labelsize(8);
      o->callback((gnui::Callback*)callback);
      o->align(gnui::ALIGN_LEFT|gnui::ALIGN_CENTER);
    }
     {gnui::ValueInput* o = new gnui::ValueInput(410, 63, 65, 22, "x");
      o->color((gnui::Color)10);
      o->selection_color((gnui::Color)1);
      o->maximum(100);
      o->step(0.1);
      o->callback((gnui::Callback*)callback);
      o->align(gnui::ALIGN_LEFT|gnui::ALIGN_CENTER);
    }
     {gnui::ValueInput* o = new gnui::ValueInput(475, 63, 65, 22, "y");
      o->color((gnui::Color)10);
      o->selection_color((gnui::Color)1);
      o->maximum(100);
      o->step(0.1);
      o->callback((gnui::Callback*)callback);
      o->align(gnui::ALIGN_LEFT|gnui::ALIGN_CENTER);
    }
     {gnui::ValueInput* o = new gnui::ValueInput(360, 93, 180, 32, "larger");
      o->color((gnui::Color)10);
      o->selection_color((gnui::Color)1);
      o->callback((gnui::Callback*)callback);
    }
     {gnui::Widget* o = new gnui::Widget(10, 250, 280, 229, "GNUI_Value_Slider");
      o->box(gnui::ENGRAVED_BOX);
      o->labelfont(gnui::HELVETICA_BOLD);
      o->color((gnui::Color)49);
      o->align(gnui::ALIGN_TOP|gnui::ALIGN_CENTER);
    }
     {gnui::Widget* o = new gnui::Widget(295, 141, 145, 131, "   GNUI_Scrollbar");
      o->box(gnui::ENGRAVED_BOX);
      o->labelfont(gnui::HELVETICA_BOLD);
      o->color((gnui::Color)49);
      o->align(gnui::ALIGN_TOP|gnui::ALIGN_LEFT|gnui::ALIGN_CENTER);
    }
     {gnui::Scrollbar* o = new gnui::Scrollbar(300, 240, 105, 20, "HORIZONTAL");
      o->color((gnui::Color)10);
      o->selection_color((gnui::Color)1);
      o->labelsize(8);
      o->maximum(100);
      o->callback((gnui::Callback*)callback);
    }
     {gnui::Scrollbar* o = new gnui::Scrollbar(405, 145, 20, 115, "VERTICAL");
      o->set_vertical();
      o->color((gnui::Color)10);
      o->selection_color((gnui::Color)1);
      o->labelsize(8);
      o->minimum(100);
      o->maximum(0);
      o->callback((gnui::Callback*)callback);
    }
     {gnui::ValueSlider* o = new gnui::ValueSlider(25, 277, 30, 158, "VERTICAL");
      o->set_vertical();
      o->color((gnui::Color)10);
      o->selection_color((gnui::Color)1);
      o->labelsize(8);
      o->textsize(10);
      o->callback((gnui::Callback*)callback);
      o->align(gnui::ALIGN_TOP);
    }
     {gnui::ValueSlider* o = new gnui::ValueSlider(65, 310, 30, 152, "VERTICAL|TICK_LEFT");
      o->type(gnui::ValueSlider::TICK_ABOVE);
      o->set_vertical();
      o->color((gnui::Color)10);
      o->selection_color((gnui::Color)1);
      o->labelsize(8);
      o->textsize(10);
      o->callback((gnui::Callback*)callback);
    }
     {gnui::ValueSlider* o = new gnui::ValueSlider(105, 283, 35, 158, "VERTICAL|TICK_LEFT,box");
      o->type(gnui::ValueSlider::TICK_ABOVE);
      o->set_vertical();
      o->box(gnui::DOWN_BOX);
      o->color((gnui::Color)10);
      o->selection_color((gnui::Color)1);
      o->labelsize(8);
      o->textsize(10);
      o->callback((gnui::Callback*)callback);
      o->align(gnui::ALIGN_TOP);
    }
     {gnui::ValueSlider* o = new gnui::ValueSlider(145, 294, 130, 21, "HORIZONTAL");
      o->color((gnui::Color)10);
      o->selection_color((gnui::Color)1);
      o->labelsize(8);
      o->callback((gnui::Callback*)callback);
    }
     {gnui::ValueSlider* o = new gnui::ValueSlider(145, 337, 130, 22, "HORIZONTAL|TICK_BELOW");
      o->type(gnui::ValueSlider::TICK_BELOW);
      o->color((gnui::Color)10);
      o->selection_color((gnui::Color)1);
      o->labelsize(8);
      o->callback((gnui::Callback*)callback);
    }
     {gnui::ValueSlider* o = new gnui::ValueSlider(145, 381, 130, 21, "HORIZONTAL|TICK_BELOW,box");
      o->type(gnui::ValueSlider::TICK_BELOW);
      o->box(gnui::DOWN_BOX);
      o->color((gnui::Color)10);
      o->selection_color((gnui::Color)1);
      o->labelsize(8);
      o->callback((gnui::Callback*)callback);
    }
     {gnui::ValueSlider* o = new gnui::ValueSlider(145, 424, 130, 33, "HORIZONTAL|TICK_BOTH");
      o->type(gnui::ValueSlider::TICK_BOTH);
      o->color((gnui::Color)10);
      o->selection_color((gnui::Color)1);
      o->labelsize(8);
      o->callback((gnui::Callback*)callback);
    }
     {gnui::Widget* o = new gnui::Widget(295, 277, 145, 136, "GNUI_Roller");
      o->box(gnui::ENGRAVED_BOX);
      o->labelfont(gnui::HELVETICA_BOLD);
      o->color((gnui::Color)49);
      o->align(gnui::ALIGN_TOP|gnui::ALIGN_CENTER);
    }
     {gnui::ThumbWheel* o = new gnui::ThumbWheel(305, 340, 90, 20, "HORIZONTAL");
      o->color((gnui::Color)0xe6e7e600);
      o->selection_color((gnui::Color)1);
      o->labelsize(8);
      o->callback((gnui::Callback*)callback);
    }
     {gnui::ThumbWheel* o = new gnui::ThumbWheel(405, 299, 20, 103, "VERTICAL");
      o->set_vertical();
      o->color((gnui::Color)0xe6e7e600);
      o->selection_color((gnui::Color)1);
      o->labelsize(8);
      o->callback((gnui::Callback*)callback);
    }
     {gnui::Group* o = new gnui::Group(445, 141, 110, 272, "GNUI_Dial");
      o->set_vertical();
      o->box(gnui::ENGRAVED_BOX);
      o->labelfont(gnui::HELVETICA_BOLD);
      o->align(gnui::ALIGN_TOP|gnui::ALIGN_CENTER);
      o->begin();
       {gnui::Dial* o = new gnui::Dial(23, 24, 63, 65, "NORMAL");
        o->set_vertical();
        o->color((gnui::Color)10);
        o->selection_color((gnui::Color)1);
        o->labelsize(8);
        o->value(0.5);
        o->callback((gnui::Callback*)callback);
        o->angles(0,315);
      }
       {gnui::Dial* o = new gnui::Dial(23, 104, 63, 65, "LINE");
        o->type(gnui::Dial::LINE);
        o->set_vertical();
        o->color((gnui::Color)10);
        o->selection_color((gnui::Color)1);
        o->labelsize(8);
        o->value(0.5);
        o->callback((gnui::Callback*)callback);
      }
       {gnui::Dial* o = new gnui::Dial(23, 184, 63, 65, "FILL");
        o->type(gnui::Dial::FILL);
        o->set_vertical();
        o->color((gnui::Color)10);
        o->selection_color((gnui::Color)1);
        o->labelsize(8);
        o->value(0.75);
        o->callback((gnui::Callback*)callback);
        o->angles(0,360);
      }
      o->end();
    }
     {gnui::Widget* o = new gnui::Widget(295, 419, 260, 60, "All widgets have color(green) and selection_color(red) to show the areas thes\
e colors affect.");
      o->box(gnui::ENGRAVED_BOX);
      o->labelsize(10);
      o->align(gnui::ALIGN_WRAP);
    }
    o->end();
    o->resizable(o);
  }
  w->show(argc, argv);
  return  gnui::run();
}
