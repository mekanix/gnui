// generated by Fast Light User Interface Designer (fluid) version 2.00

#include <FL/Fl_FileChooser.h>

inline void Fl_FileChooser::cb_window_i(Fl_Window*, void*) {
  fileList->deselect();
fileName->value("");
window->hide();
}
void Fl_FileChooser::cb_window(Fl_Window* o, void* v) {
  ((Fl_FileChooser*)(o->user_data()))->cb_window_i(o,v);
}

inline void Fl_FileChooser::cb_fileList_i(Fl_FileBrowser*, void*) {
  fileListCB();
}
void Fl_FileChooser::cb_fileList(Fl_FileBrowser* o, void* v) {
  ((Fl_FileChooser*)(o->parent()->user_data()))->cb_fileList_i(o,v);
}

inline void Fl_FileChooser::cb_Cancel_i(Fl_Button*, void*) {
  fileList->deselect();
fileName->value("");
window->hide();
}
void Fl_FileChooser::cb_Cancel(Fl_Button* o, void* v) {
  ((Fl_FileChooser*)(o->parent()->user_data()))->cb_Cancel_i(o,v);
}

inline void Fl_FileChooser::cb_okButton_i(Fl_Return_Button*, void*) {
  window->hide();
}
void Fl_FileChooser::cb_okButton(Fl_Return_Button* o, void* v) {
  ((Fl_FileChooser*)(o->parent()->user_data()))->cb_okButton_i(o,v);
}

inline void Fl_FileChooser::cb_fileName_i(Fl_FileInput*, void*) {
  fileNameCB();
}
void Fl_FileChooser::cb_fileName(Fl_FileInput* o, void* v) {
  ((Fl_FileChooser*)(o->parent()->user_data()))->cb_fileName_i(o,v);
}

inline void Fl_FileChooser::cb_upButton_i(Fl_Button*, void*) {
  up();
}
void Fl_FileChooser::cb_upButton(Fl_Button* o, void* v) {
  ((Fl_FileChooser*)(o->parent()->user_data()))->cb_upButton_i(o,v);
}

#include <FL/Fl_Bitmap.H>
static unsigned char bits_up[] =
"\0\0x\0\204\0\2\1""1\376y\200\375\200""1\200""1\200""1\200""1\200""1\200\1\
\200\1\200\377\377\0\0";
static Fl_Bitmap bitmap_up(bits_up, 16, 16);

inline void Fl_FileChooser::cb_newButton_i(Fl_Button*, void*) {
  newdir();
}
void Fl_FileChooser::cb_newButton(Fl_Button* o, void* v) {
  ((Fl_FileChooser*)(o->parent()->user_data()))->cb_newButton_i(o,v);
}

static unsigned char bits_new[] =
"\0\0x\0\204\0\2\1\1\376\1\200""1\200""1\200\375\200\375\200""1\200""1\200\1\
\200\1\200\377\377\0\0";
static Fl_Bitmap bitmap_new(bits_new, 16, 16);

inline void Fl_FileChooser::cb_dirMenu_i(Fl_Choice*, void*) {
  char pathname[1024];
int i;

pathname[0] = '\0';
for (i = 1; i <= dirMenu->value(); i ++)
  strcat(pathname, dirMenu->text(i));
directory(pathname);
}
void Fl_FileChooser::cb_dirMenu(Fl_Choice* o, void* v) {
  ((Fl_FileChooser*)(o->parent()->user_data()))->cb_dirMenu_i(o,v);
}

inline void Fl_FileChooser::cb__i(Fl_Button*, void*) {
  fileList->filter("*");;
rescan();
}
void Fl_FileChooser::cb_(Fl_Button* o, void* v) {
  ((Fl_FileChooser*)(o->parent()->user_data()))->cb__i(o,v);
}

static unsigned char bits_allfiles[] =
"\374?\4 \4 \4 \204!\244%\304#\364/\364/\304#\244%\204!\4 \4 \4 \374?";
static Fl_Bitmap bitmap_allfiles(bits_allfiles, 16, 16);

Fl_FileChooser::Fl_FileChooser(const char *d, const char *p, int t, const char *title) {
  Fl_Window* w;
  { Fl_Window* o = window = new Fl_Window(375, 315, "Pick a File");
    w = o;
    o->callback((Fl_Callback*)cb_window, (void*)(this));
    w->hotspot(o);
    { Fl_FileBrowser* o = fileList = new Fl_FileBrowser(10, 45, 355, 180);
      o->type(2);
      o->callback((Fl_Callback*)cb_fileList);
      Fl_Group::current()->resizable(o);
    }
    { Fl_Button* o = new Fl_Button(300, 280, 65, 25, "Cancel");
      o->callback((Fl_Callback*)cb_Cancel);
    }
    { Fl_Return_Button* o = okButton = new Fl_Return_Button(240, 280, 55, 25, "OK");
      o->callback((Fl_Callback*)cb_okButton);
    }
    { Fl_FileInput* o = fileName = new Fl_FileInput(10, 245, 355, 25, "Filename:");
      o->callback((Fl_Callback*)cb_fileName);
      o->align(FL_ALIGN_TOP_LEFT);
      o->when(FL_WHEN_ENTER_KEY);
      fileName->when(FL_WHEN_CHANGED | FL_WHEN_ENTER_KEY_ALWAYS);
    }
    { Fl_Button* o = upButton = new Fl_Button(280, 10, 25, 25);
      o->image(bitmap_up);
      o->label_size(8);
      o->callback((Fl_Callback*)cb_upButton);
    }
    { Fl_Button* o = newButton = new Fl_Button(310, 10, 25, 25);
      o->image(bitmap_new);
      o->label_size(8);
      o->callback((Fl_Callback*)cb_newButton);
    }
    { Fl_Choice* o = dirMenu = new Fl_Choice(75, 10, 200, 25, "Directory:");
      o->callback((Fl_Callback*)cb_dirMenu);
    }
    { Fl_Button* o = new Fl_Button(340, 10, 25, 25);
      o->image(bitmap_allfiles);
      o->label_color((Fl_Color)4);
      o->label_size(28);
      o->callback((Fl_Callback*)cb_);
      o->align(FL_ALIGN_CENTER|FL_ALIGN_INSIDE);
    }
    if (title) window->label(title);
    o->set_modal();
    o->end();
  }
  window->size_range(345, 270, 345);
fileList->filter(p);
type(t);
value(d);
}

void Fl_FileChooser::color(Fl_Color c) {
  fileList->color(c);
}

Fl_Color Fl_FileChooser::color() {
  return (fileList->color());
}

char * Fl_FileChooser::directory() {
  return directory_;
}

void Fl_FileChooser::filter(const char *p) {
  fileList->filter(p);
rescan();
}

const char * Fl_FileChooser::filter() {
  return (fileList->filter());
}

void Fl_FileChooser::hide() {
  window->hide();
}

void Fl_FileChooser::iconsize(uchar s) {
  fileList->iconsize(s);
}

uchar Fl_FileChooser::iconsize() {
  return (fileList->iconsize());
}

void Fl_FileChooser::label(const char *l) {
  window->label(l);
}

const char * Fl_FileChooser::label() {
  return (window->label());
}

void Fl_FileChooser::show() {
  window->show();
fileList->deselect();
}

void Fl_FileChooser::textcolor(Fl_Color c) {
  fileList->textcolor(c);
}

Fl_Color Fl_FileChooser::textcolor() {
  return (fileList->textcolor());
}

void Fl_FileChooser::textfont(Fl_Font f) {
  fileList->text_font(f);
}

Fl_Font Fl_FileChooser::textfont() {
  return (fileList->textfont());
}

void Fl_FileChooser::textsize(uchar s) {
  fileList->text_size(s);
}

uchar Fl_FileChooser::textsize() {
  return (fileList->textsize());
}

void Fl_FileChooser::type(int t) {
  type_ = t;
if (t == MULTI)
  fileList->type(FL_MULTI_BROWSER);
else
  fileList->type(FL_HOLD_BROWSER);
if (t != CREATE)
  newButton->deactivate();
else
  newButton->activate();
}

int Fl_FileChooser::type() {
  return (type_);
}

int Fl_FileChooser::visible() {
  return window->visible();
}