//
// "$Id: fl_motif.cxx,v 1.5 1999/11/10 15:11:28 carl Exp $"
//
// Theme plugin file for FLTK
//
// Copyright 1999 Bill Spitzak and others.
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

// fl_motif.cxx

// Motif L&F

#include <FL/Fl.H>
#include <FL/Fl_Widget.H>
#include <FL/Fl_Menu_Item.H>
#include <FL/Fl_Check_Button.H>
#include <FL/Fl_Scrollbar.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Output.H>
#include <FL/Fl_Style.H>
#include <FL/fl_draw.H>
#include <stdio.h>
#include <string.h>

// a boxtype drawing function in fl_boxtype.cxx
extern void fl_frame(Fl_Boxtype b, int x, int y, int w, int h,
                     Fl_Color c, Fl_Flags f);

// a boxtype drawing function in fl_boxtype.cxx
extern void fl_flatx(Fl_Boxtype b, int x, int y, int w, int h,
                     Fl_Color c, Fl_Flags f);

// some new boxtypes (look familiar?)
static const Fl_Boxtype_ thick_motif_down_box = {
  fl_frame, "HHVVHHVVHHVV", &thick_motif_down_box, &thick_motif_down_box, 3,3,6,6, true
};

static const Fl_Boxtype_ thick_motif_up_box = {
  fl_frame, "VVHHVVHHVVHH", &thick_motif_up_box, &thick_motif_up_box, 3,3,6,6, true
};

static const Fl_Boxtype_ thick_motif_box = {
  fl_frame, "VVHHVVHHVVHH", &thick_motif_down_box, &thick_motif_box, 3,3,6,6, true
};

static const Fl_Boxtype_ thin_motif_down_box = {
  fl_frame, "HHVVHHVV", &thin_motif_down_box, &thin_motif_down_box, 2,2,4,4, true
};

static const Fl_Boxtype_ thin_motif_up_box = {
  fl_frame, "VVHHVVHH", &thin_motif_up_box, &thin_motif_up_box, 2,2,4,4, true
};

static const Fl_Boxtype_ thin_motif_box = {
  fl_frame, "VVHHVVHH", &thin_motif_down_box, &thin_motif_box, 2,2,4,4, true
};

static const Fl_Boxtype_ thick_motif_highlight_box = {
  fl_flatx, 0, &thick_motif_down_box, &thick_motif_up_box, 3,3,6,6, true
};

static const Fl_Boxtype_ thin_motif_highlight_box = {
  fl_flatx, 0, &thin_motif_down_box, &thin_motif_up_box, 2,2,4,4, true
};

static const Fl_Boxtype_ thick_motif_title_box = {
  fl_flatx, 0, &thick_motif_up_box, &thick_motif_up_box, 3,3,6,6, true
};

static const Fl_Boxtype_ thin_motif_title_box = {
  fl_flatx, 0, &thin_motif_up_box, &thin_motif_up_box, 2,2,4,4, true
};

static void motif_glyph(int t, int x, int y, int w, int h, Fl_Color bc, Fl_Color fc,
                Fl_Flags f, Fl_Boxtype box)
{
  switch (t) {
    case FL_GLYPH_LIGHT:
      thin_motif_down_box.draw(x, y, w, h, fc, f);
      break;
    case FL_GLYPH_RADIO: {
      w = (w-1)|1; h = (h-1)|1;
      int x1 = x+w/2;
      int y1 = y+h/2;
      Fl_Color light = FL_LIGHT2, dark = FL_DARK3;
      if (f&FL_VALUE) { light = FL_DARK3; dark = FL_LIGHT2; }

      if (f&FL_INACTIVE)
        { fc = fl_inactive(fc); light = fl_inactive(light); dark = fl_inactive(dark); }
      fl_color( box == FL_NO_BOX ? bc : fc); // hack! for color
      fl_polygon(x+3,y1, x1,y+3, x+w-4,y1, x1,y+h-4);

      fl_color(light); fl_line(x, y1, x1, y, x+w-1, y1);
      fl_color(light); fl_line(x+1, y1, x1, y+1, x+w-2, y1);
      fl_color(light); fl_line(x+2, y1, x1, y+2, x+w-3, y1);

      fl_color(dark); fl_line(x, y1, x1, y+h-1, x+w-1, y1);
      fl_color(dark); fl_line(x+1, y1, x1, y+h-2, x+w-2, y1);
      fl_color(dark); fl_line(x+2, y1, x1, y+h-3, x+w-3, y1);
      break;
    }
    case FL_GLYPH_CHECK:
      x += 2; y += 2; w -= 4; h -= 4; // fudge factor
      thin_motif_box.draw(x, y, w, h, box == FL_NO_BOX ? bc : fc, f); // hack! for color
      break;
    case FL_GLYPH_RIGHT:
    case FL_GLYPH_LEFT:
    case FL_GLYPH_UP:
    case FL_GLYPH_DOWN: {
      if (box == FL_NO_BOX) { x += 3; y += 3; w -= 6; h -= 6; } // menu fudge factor
      Fl_Color d1, d2, l1, l2;
      if (f&FL_VALUE) {
        d1 = FL_LIGHT2; d2 = FL_LIGHT2; l1 = FL_DARK3; l2 = FL_DARK3;
      } else{
        l1 = FL_LIGHT2; l2 = FL_LIGHT2; d1 = FL_DARK3; d2 = FL_DARK3;
      }

      if (f&FL_INACTIVE) {
        l1 = fl_inactive(l1); l2 = fl_inactive(l2);
        d1 = fl_inactive(d1); d2 = fl_inactive(d2);
      }

      if (t == FL_GLYPH_RIGHT) {
        fl_color(bc); fl_polygon(x,y, x+w-1,y+h/2, x,y+h-1);
        fl_color(l2); fl_line(x+2,y+2, x+w-3,y+h/2);
        fl_color(d2); fl_line(x+2,y+h-3, x+w-3,y+h/2);
        fl_color(l2); fl_line(x+1,y+h-2, x+1,y+1, x+w-2,y+h/2);
        fl_color(d2); fl_line(x+1,y+h-2, x+w-2,y+h/2);
        fl_color(l1); fl_line(x,y+h-1, x,y, x+w-1,y+h/2);
        fl_color(d1); fl_line(x,y+h-1, x+w-1,y+h/2);
      } else if (t == FL_GLYPH_LEFT) {
        fl_color(bc); fl_polygon(x+w-1,y, x+w-1,y+h-1, x,y+h/2);
        fl_color(d2); fl_line(x+w-3,y+h-3, x+2,y+h/2);
        fl_color(l2); fl_line(x+w-3,y+2, x+2,y+h/2);
        fl_color(d2); fl_line(x+w-2,y+1, x+w-2,y+h-2, x+1,y+h/2);
        fl_color(l2); fl_line(x+w-2,y+1, x+1,y+h/2);
        fl_color(d1); fl_line(x+w-1,y, x+w-1,y+h-1, x,y+h/2);
        fl_color(l1); fl_line(x+w-1,y, x,y+h/2);
      } else if (t == FL_GLYPH_DOWN) {
        fl_color(bc); fl_polygon(x,y, x+w/2,y+h-1, x+w-1,y);
        fl_color(l2); fl_line(x+2,y+2, x+w/2,y+h-3);
        fl_color(d2); fl_line(x+w-3,y+2, x+w/2,y+h-3);
        fl_color(l2); fl_line(x+w-2,y+1, x+1,y+1, x+w/2,y+h-2);
        fl_color(d2); fl_line(x+w-2,y+1, x+w/2,y+h-2);
        fl_color(l1); fl_line(x+w-1,y, x,y, x+w/2,y+h-1);
        fl_color(d1); fl_line(x+w-1,y, x+w/2,y+h-1);
      } else { // UP
        fl_color(bc); fl_polygon(x,y+h-1, x+w-1,y+h-1, x+w/2,y);
        fl_color(d2); fl_line(x+w-3,y+h-3, x+w/2,y+2);
        fl_color(l2); fl_line(x+2,y+h-3, x+w/2,y+2);
        fl_color(d2); fl_line(x+1,y+h-2, x+w-2,y+h-2, x+w/2,y+1);
        fl_color(l2); fl_line(x+1,y+h-2, x+w/2,y+1);
        fl_color(d1); fl_line(x,y+h-1, x+w-1,y+h-1, x+w/2,y);
        fl_color(l1); fl_line(x,y+h-1, x+w/2,y);
      }
      break;
    }
    default:
      fl_glyph(t, x, y, w, h, bc, fc, f, box);
  }
}

int fl_motif() {
  Fl_Style::revert(); // revert to FLTK default styles

  fl_up_box.data = "VVHHVVHH";
  fl_up_box.dx_ = 2;
  fl_up_box.dy_ = 2;
  fl_up_box.dw_ = 4;
  fl_up_box.dh_ = 4;
  fl_down_box.data = "HHVVHHVV";
  fl_down_box.dx_ = 2;
  fl_down_box.dy_ = 2;
  fl_down_box.dw_ = 4;
  fl_down_box.dh_ = 4;

  Fl_Widget::default_style.set_box(&thin_motif_box);
  Fl_Widget::default_style.set_selection_color(FL_DARK1);
  Fl_Widget::default_style.set_glyph_box(&thin_motif_box);
  Fl_Widget::default_style.set_highlight_color(0);
  Fl_Widget::default_style.set_glyph(motif_glyph);

  Fl_Style* s;

  if ((s = Fl_Style::find("menu item"))) {
    s->set_box(&thin_motif_highlight_box);
    s->set_glyph_box(FL_NO_BOX);
    s->set_highlight_color(FL_GRAY);
    s->set_highlight_label_color(FL_BLACK);
    s->set_on_color(FL_DARK1);
    s->set_off_color(FL_GRAY);
  }

  if ((s = Fl_Style::find("menu title"))) {
    s->set_glyph_box(FL_NO_BOX);
    s->set_box(&thin_motif_title_box);
    s->set_selection_color(FL_GRAY);
    s->set_selection_text_color(FL_BLACK);
    s->set_off_color(FL_GRAY);
  }

  if ((s = Fl_Style::find("check button"))) {
    s->set_on_color(FL_DARK1);
    s->set_off_color(FL_GRAY);
  }

  if ((s = Fl_Style::find("scrollbar"))) {
    s->set_box(&thin_motif_down_box);
    s->set_color(FL_DARK1);
    s->set_selection_color(FL_DARK1);
  }

  if ((s = Fl_Style::find("slider"))) {
    s->set_box(&thin_motif_down_box);
    s->set_color(FL_DARK1);
    s->set_selection_color(FL_DARK1);
  }

  if ((s = Fl_Style::find("value slider"))) {
    s->set_box(&thin_motif_down_box);
    s->set_color(FL_DARK1);
    s->set_selection_color(FL_DARK1);
  }

  if ((s = Fl_Style::find("input"))) {
    s->set_color(FL_GRAY);
    s->set_selection_color(FL_BLACK);
    s->set_selection_text_color(FL_GRAY);
    s->set_box(&thin_motif_down_box);
  }

  if ((s = Fl_Style::find("output"))) {
    s->set_color(FL_GRAY);
    s->set_selection_color(FL_BLACK);
    s->set_selection_text_color(FL_GRAY);
    s->set_box(&thin_motif_down_box);
  }

  if ((s = Fl_Style::find("counter"))) {
    s->set_box(&thin_motif_down_box);
  }

  if ((s = Fl_Style::find("highlight button"))) {
    s->set_highlight_color(FL_GRAY);
  }

  if ((s = Fl_Style::find("browser"))) {
    s->set_color(FL_GRAY);
    s->set_selection_color(FL_BLACK);
    s->set_selection_text_color(FL_GRAY);
    s->set_box(&thin_motif_down_box);
  }

  static Fl_Boxtype_Definer motif("motif", thin_motif_box);
  static Fl_Boxtype_Definer motif_up("motif up", thin_motif_up_box);
  static Fl_Boxtype_Definer motif_down("motif down", thin_motif_down_box);
  static Fl_Boxtype_Definer motif_highlight("motif highlight", thin_motif_highlight_box);
  static Fl_Boxtype_Definer motif_title("motif title", thin_motif_title_box);
  static Fl_Boxtype_Definer motif_thick("motif thick", thick_motif_box);
  static Fl_Boxtype_Definer motif_thick_up("motif thick up", thick_motif_up_box);
  static Fl_Boxtype_Definer motif_thick_down("motif thick down", thick_motif_down_box);
  static Fl_Boxtype_Definer motif_thick_highlight("motif thick highlight", thick_motif_highlight_box);
  static Fl_Boxtype_Definer motif_thick_title("motif thick title", thick_motif_title_box);

  Fl::redraw();
  return 0;
}

//
// End of "$Id: fl_motif.cxx,v 1.5 1999/11/10 15:11:28 carl Exp $".
//