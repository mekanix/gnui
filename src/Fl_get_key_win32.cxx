//
// "$Id: Fl_get_key_win32.cxx,v 1.15 2002/12/10 01:46:18 easysw Exp $"
//
// _WIN32 keyboard state routines for the Fast Light Tool Kit (FLTK).
//
// Copyright 1998-2003 by Bill Spitzak and others.
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

// Return the current state of a key.  Keys are named by fltk symbols,
// which are actually X keysyms.  So this has to translate to MSWindows
// VK_x symbols.

#include <fltk/events.h>
#include <fltk/x.h>
#include <ctype.h>
using namespace fltk;

// convert an Fltk (X) keysym to a MSWindows VK symbol:
// See also the inverse converter in win32.C
// This table is in numeric order by Fltk symbol order for binary search:

static const struct {unsigned short vk, fltk;} vktab[] = {
  {VK_SPACE,	' '},
  {'1',		'!'},
  {0xde,	'\"'},
  {'3',		'#'},
  {'4',		'$'},
  {'5',		'%'},
  {'7',		'&'},
  {0xde,	'\''},
  {'9',		'('},
  {'0',		')'},
  {'8',		'*'},
  {0xbb,	'+'},
  {0xbc,	','},
  {0xbd,	'-'},
  {0xbe,	'.'},
  {0xbf,	'/'},
  {0xba,	':'},
  {0xba,	';'},
  {0xbc,	'<'},
  {0xbb,	'='},
  {0xbe,	'>'},
  {0xbf,	'?'},
  {'2',		'@'},
  {0xdb,	'['},
  {0xdc,	'\\'},
  {0xdd,	']'},
  {'6',		'^'},
  {0xbd,	'_'},
  {0xc0,	'`'},
  {0xdb,	'{'},
  {0xdc,	'|'},
  {0xdd,	'}'},
  {0xc0,	'~'},
  {VK_BACK,	BackSpaceKey},
  {VK_TAB,	TabKey},
  {VK_CLEAR,	ClearKey},
  {VK_RETURN,	ReturnKey},
  {VK_PAUSE,	PauseKey},
  {VK_SCROLL,	ScrollLockKey},
  {VK_ESCAPE,	EscapeKey},
  {VK_HOME,	HomeKey},
  {VK_LEFT,	LeftKey},
  {VK_UP,	UpKey},
  {VK_RIGHT,	RightKey},
  {VK_DOWN,	DownKey},
  {VK_PRIOR,	PageUpKey},
  {VK_NEXT,	PageDownKey},
  {VK_END,	EndKey},
  {VK_SNAPSHOT,	PrintKey},
  {VK_INSERT,	InsertKey},
  {VK_APPS,	MenuKey},
  {VK_NUMLOCK,	NumLockKey},
//{VK_???,	KyepadEnter},
  {VK_MULTIPLY,	MultiplyKey},
  {VK_ADD,	AddKey},
  {VK_SUBTRACT,	SubtractKey},
  {VK_DECIMAL,	DecimalKey},
  {VK_DIVIDE,	DivideKey},
  {VK_LSHIFT,	LeftShiftKey},
  {VK_RSHIFT,	RightShiftKey},
  {VK_LCONTROL,	LeftControlKey},
  {VK_RCONTROL,	RightControlKey},
  {VK_CAPITAL,	CapsLockKey},
  {VK_LMENU,	LeftAltKey},
  {VK_RMENU,	RightAltKey},
  {VK_LWIN,	LeftCommandKey},
  {VK_RWIN,	RightCommandKey},
  {VK_DELETE,	DeleteKey}
};

static int fltk2ms(int fltk) {
  if (fltk >= '0' && fltk <= '9') return fltk;
  if (fltk >= 'A' && fltk <= 'Z') return fltk;
  if (fltk >= 'a' && fltk <= 'z') return fltk-('a'-'A');
  if (fltk >= F1Key && fltk <= LastFunctionKey) return fltk-F1Key+VK_F1;
  if (fltk >= Keypad0 && fltk<=Keypad9) return fltk-Keypad0+VK_NUMPAD0;
  int a = 0;
  int b = sizeof(vktab)/sizeof(*vktab);
  while (a < b) {
    int c = (a+b)/2;
    if (vktab[c].fltk == fltk) return vktab[c].vk;
    if (vktab[c].fltk < fltk) a = c+1; else b = c;
  }
  return 0;
}

bool fltk::event_key_state(int k) {
  return (GetKeyState(fltk2ms(k))&~1) != 0;
}

bool fltk::get_key_state(int k) {
  uchar foo[256];
  GetKeyboardState(foo);
  return (foo[fltk2ms(k)]&~1) != 0;
}

//
// End of "$Id: Fl_get_key_win32.cxx,v 1.15 2002/12/10 01:46:18 easysw Exp $".
//
