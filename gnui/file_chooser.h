// "$Id$"
//
// Copyright 1998-2006 by Bill Spitzak and others.
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
// Please report all bugs and problems on the following page:
//
//    http://www.gnui.org/str.php

#ifndef gnui_file_chooser_h
#define gnui_file_chooser_h

#include "GNUI_API.h"

namespace gnui {

/// \name gnui/file_chooser.h
//@{

GNUI_API void file_chooser_ok_label(const char*l);
GNUI_API void use_system_file_chooser(bool = true);
GNUI_API const char *dir_chooser(const char *message, const char *fname, int relative = 0);
GNUI_API void file_chooser_callback(void (*cb)(const char *));
GNUI_API const char *file_chooser(const char *message, const char *pattern, const char *filename, bool save = false, int relative = 1);


//@}

}

#endif

//
// End of "$Id$".
//
