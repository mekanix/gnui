// generated by Fast Light User Interface Designer (fluid) version 2.0002

#include "inactive.h"

gnui::Group* the_group;

static void cb_active(gnui::Button*, void*) {
  the_group->activate();
}

static void cb_inactive(gnui::Button*, void*) {
  the_group->deactivate();
}

#include <fltk/run.h>

int main (int argc, char **argv) {

  gnui::Window* w;
   {gnui::Window* o = new gnui::Window(395, 274);
    w = o;
    o->begin();
     {gnui::Group* o = the_group = new gnui::Group(5, 6, 384, 233, "activate()/deactivate() called on this Fl_Group");
      o->box(gnui::ENGRAVED_BOX);
      o->align(gnui::ALIGN_TOP|gnui::ALIGN_INSIDE);
      o->begin();
      new gnui::Button(25, 27, 105, 21, "button");
       {gnui::Group* o = new gnui::Group(25, 74, 105, 102, "Child group");
        o->begin();
         {gnui::CheckButton* o = new gnui::CheckButton(0, 0, 105, 25, "red");
          o->type(gnui::CheckButton::RADIO);
          o->selection_color((gnui::Color)1);
          o->selection_textcolor((gnui::Color)1);
          o->labelcolor((gnui::Color)1);
          o->highlight_textcolor((gnui::Color)1);
        }
         {gnui::CheckButton* o = new gnui::CheckButton(0, 25, 105, 25, "green");
          o->type(gnui::CheckButton::RADIO);
          o->selection_color((gnui::Color)2);
          o->selection_textcolor((gnui::Color)2);
          o->labelcolor((gnui::Color)2);
          o->highlight_textcolor((gnui::Color)2);
        }
         {gnui::CheckButton* o = new gnui::CheckButton(0, 50, 105, 25, "blue");
          o->type(gnui::CheckButton::RADIO);
          o->selection_color((gnui::Color)4);
          o->selection_textcolor((gnui::Color)4);
          o->labelcolor((gnui::Color)4);
          o->highlight_textcolor((gnui::Color)4);
        }
         {gnui::CheckButton* o = new gnui::CheckButton(0, 75, 105, 25, "white");
          o->type(gnui::CheckButton::RADIO);
          o->selection_color((gnui::Color)7);
          o->selection_textcolor((gnui::Color)55);
          o->labelcolor((gnui::Color)7);
          o->highlight_textcolor((gnui::Color)55);
        }
        o->end();
      }
       {gnui::Slider* o = new gnui::Slider(140, 25, 24, 146, "Fl_Slider");
        o->set_vertical();
        o->value(0.5);
      }
       {gnui::Input* o = new gnui::Input(170, 27, 195, 21);
        o->static_value("Fl_Input");
      }
       {gnui::InputBrowser* o = new gnui::InputBrowser(255, 59, 110, 21, "input browser");
        o->begin();
         {gnui::Item* o = new gnui::Item("Moe");
          o->set_vertical();
        }
         {gnui::Item* o = new gnui::Item("Larry");
          o->set_vertical();
        }
         {gnui::Item* o = new gnui::Item("Curly");
          o->set_vertical();
        }
        o->end();
        o->text("Shemp");
      }
       {gnui::Widget* o = new gnui::Widget(215, 134, 145, 86, "Fl_Box");
        o->box(gnui::ENGRAVED_BOX);
        o->labelfont(gnui::HELVETICA_BOLD_ITALIC);
        o->labeltype(gnui::SHADOW_LABEL);
        o->labelsize(38);
      }
       {gnui::ValueInput* o = new gnui::ValueInput(230, 91, 135, 32, "value:");
        o->textfont(gnui::COURIER_BOLD);
        o->textcolor((gnui::Color)4);
        o->textsize(24);
        o->maximum(10000);
        o->step(1);
        o->tooltip("This Fl_Value_Output widget has a tooltip.");
      }
       {gnui::Scrollbar* o = new gnui::Scrollbar(15, 191, 180, 19, "scrollbar");
        o->maximum(100);
      }
      o->end();
      gnui::Group::current()->resizable(o);
    }
     {gnui::Button* o = new gnui::Button(5, 244, 190, 25, "active");
      o->type(gnui::Button::RADIO);
      o->set();
      o->callback((gnui::Callback*)cb_active);
    }
     {gnui::Button* o = new gnui::Button(205, 244, 184, 25, "inactive");
      o->type(gnui::Button::RADIO);
      o->callback((gnui::Callback*)cb_inactive);
    }
    o->end();
  }
  w->show(argc, argv);
  return  gnui::run();
}
