// essai.cxx

// Demonstration of a plugin that replaces the boxes such that a pixmap
// is used to draw everything.

#include <FL/Fl.H>
#include <FL/Fl_Widget.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Menu_Item.H>
#include <FL/Fl_Check_Button.H>
#include <FL/Fl_Scrollbar.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Output.H>
#include <FL/fl_draw.H>
#include <FL/Fl_Style.H>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include <FL/Fl_Boxtype.H>
#include <FL/Fl_Shared_Image.H>

struct Fl_Image_Box : Fl_Boxtype_ {
  Fl_Shared_Image* normal_img;
  Fl_Shared_Image* down_img;
  Fl_Shared_Image* highlight_img;

  Fl_Image_Box(char*, char*, char*);
};

static void image_box_draw(const Fl_Boxtype_* bt, int x, int y, int w, int h,
		      Fl_Color fill, Fl_Flags flags)
{
  Fl_Shared_Image* img;

  if (flags&FL_VALUE) img = ((Fl_Image_Box*)bt)->down_img;
  else if (flags&FL_HIGHLIGHT) img = ((Fl_Image_Box*)bt)->highlight_img;
  else img = ((Fl_Image_Box*)bt)->normal_img;

  if (!(flags&FL_FRAME_ONLY))
    img->draw_tiled(x+bt->dx_, y+bt->dy_, w-bt->dw_, h-bt->dh_, -w/2, -h/2);
  FL_NORMAL_BOX->draw(x,y,w,h,fill,flags|FL_FRAME_ONLY);
}

Fl_Image_Box::Fl_Image_Box(char* normal_b, char* down_b, char* highlight_b) {
  draw_ = image_box_draw;
  down = this;
  highlight = this;
  normal_img = Fl_JPEG_Image::get(fl_find_config_file(normal_b));
  down_img = Fl_JPEG_Image::get(fl_find_config_file(down_b));
  highlight_img = Fl_JPEG_Image::get(fl_find_config_file(highlight_b));
  dx_=dy_=2; dw_=dh_=4;
  rectangular = 1;
}

struct Fl_Image_NoBorderBox : Fl_Image_Box {
  Fl_Image_NoBorderBox(char*, char*, char*);
};

static void image_noborderbox_draw(const Fl_Boxtype_* bt, int x, int y, int w, int h,
		      Fl_Color fill, Fl_Flags flags)
{
  Fl_Shared_Image* img;

  if (flags&FL_VALUE) img = ((Fl_Image_Box*)bt)->down_img;
  else if (flags&FL_HIGHLIGHT) img = ((Fl_Image_Box*)bt)->highlight_img;
  else img = ((Fl_Image_Box*)bt)->normal_img;

  if (!(flags&FL_FRAME_ONLY))
    img->draw_tiled(x, y, w, h, -w/2, -h/2);
  if (flags&(FL_HIGHLIGHT|FL_VALUE))
    FL_NORMAL_BOX->draw(x,y,w,h,fill,(flags|FL_FRAME_ONLY)&(~FL_VALUE));
  else
    FL_FLAT_BOX->draw(x,y,w,h,fill,flags|FL_FRAME_ONLY);
}

Fl_Image_NoBorderBox::Fl_Image_NoBorderBox(char* normal_b, char* down_b,
  char* highlight_b) : Fl_Image_Box(normal_b, down_b, highlight_b)
{
  draw_ = image_noborderbox_draw;
  dx_=dy_=0; dw_=dh_=0;
}

extern "C" fltk_theme(int, char**);
int fltk_theme(int, char** argv) {
  fl_background(0xD0D0E000); // it would be nice to figure out color from image
  Fl_Boxtype flat1 = new Fl_Image_NoBorderBox("themes/bg.jpeg", "themes/bg2.jpeg", "themes/bg3.jpeg");
  Fl_Boxtype flat2 = new Fl_Image_NoBorderBox("themes/bg2.jpeg", "themes/bg3.jpeg", "themes/bg3.jpeg");
  Fl_Boxtype box1 = new Fl_Image_Box("themes/bg2.jpeg", "themes/bg3.jpeg", "themes/bg3.jpeg");
  Fl_Boxtype box2 = new Fl_Image_Box("themes/bg.jpeg", "themes/bg.jpeg", "themes/bg.jpeg");
  Fl_Widget::default_style.set_box(box1);
  Fl_Widget::default_style.set_glyph_box(box1);
  Fl_Window::default_style.set_box(flat1);
  Fl_Style* s;
  if ((s = Fl_Style::find("menu item"))) {
    s->set_highlight_label_color(FL_BLACK);
    s->set_box(flat2);
  }
  if ((s = Fl_Style::find("menu title"))) {
    s->set_highlight_label_color(FL_BLACK);
    s->set_selection_text_color(FL_BLACK);
    s->set_box(flat2);
  }
  if ((s = Fl_Style::find("box"))) {
    s->set_box(flat1);
  }
  if ((s = Fl_Style::find("highlight button"))) {
    s->set_box(flat1);
  }
  if ((s = Fl_Style::find("button"))) {
    s->set_selection_text_color(FL_BLACK);
  }
  if ((s = Fl_Style::find("tabs"))) {
    s->set_box(box2);
  }
  return 0;
}