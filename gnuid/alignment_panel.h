// generated by Fast Light User Interface Designer (gnuid) version 2.1000

#ifndef alignment_panel_h
#define alignment_panel_h
#include <gnui/Preferences.h>
#include <gnui/TextBuffer.h>
#include <gnui/TextDisplay.h>
extern void load_history();
extern gnui::TextBuffer *shell_run_buffer;
#include <gnui/Window.h>
extern gnui::Window* preferences_window;
#include <gnui/TabGroup.h>
extern gnui::TabGroup* pref_tabs;
#include <gnui/Group.h>
#include <gnui/CheckButton.h>
extern gnui::CheckButton* openlast_button;
extern gnui::CheckButton* prevpos_button;
extern gnui::CheckButton* completion_button;
#include <gnui/ValueInput.h>
extern gnui::ValueInput* recent_spinner;
extern gnui::CheckButton* tabcolor_button;
extern gnui::CheckButton* splash_button;
#include <gnui/Widget.h>
#include <gnui/Input.h>
extern void header_input_cb(gnui::Input*, void*);
extern gnui::Input* header_file_input;
extern void code_input_cb(gnui::Input*, void*);
extern gnui::Input* code_file_input;
extern void include_H_from_C_button_cb(gnui::CheckButton*, void*);
extern gnui::CheckButton* include_H_from_C_button;
extern void alignment_cb(gnui::Input*, long);
extern gnui::Input* horizontal_input;
extern gnui::Input* vertical_input;
extern gnui::Input* snap_input;
#include <gnui/RadioButton.h>
extern void default_widget_size_cb(gnui::RadioButton*, long);
extern gnui::RadioButton* def_widget_size[6];
#include <gnui/Button.h>
gnui::Window* make_preferences_window();
#include <gnui/DoubleBufferWindow.h>
extern gnui::DoubleBufferWindow* shell_window;
extern gnui::Input* shell_command_input;
extern gnui::CheckButton* shell_writecode_button;
extern gnui::CheckButton* shell_writemsgs_button;
extern gnui::CheckButton* shell_savegnui_button;
#include <gnui/ReturnButton.h>
extern void do_shell_command(gnui::ReturnButton*, void*);
extern gnui::DoubleBufferWindow* shell_run_window;
#include <gnui/TextDisplay.h>
extern gnui::TextDisplay* shell_run_display;
extern gnui::ReturnButton* shell_run_button;
gnui::DoubleBufferWindow* make_shell_window();
#endif
