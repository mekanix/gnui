//
// "$Id: filename.h,v 1.2 2001/07/29 21:52:43 spitzak Exp $"
//
// Filename header file for the Fast Light Tool Kit (FLTK).
//
// Copyright 1998-1999 by Bill Spitzak and others.
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

#ifndef FL_FILENAME_H
#define FL_FILENAME_H

//
// The following is only used when building DLLs under _WIN32
//

#include <fltk/Enumerations.h>

#define FL_PATH_MAX 256 // all buffers are this length

FL_API const char *filename_name(const char *); // return pointer to name
FL_API const char *filename_ext(const char *); // return pointer to .ext
FL_API char *filename_setext(char *,const char *ext); // clobber .ext
FL_API int filename_expand(char *, const char *from); // do $x and ~x
FL_API int filename_absolute(char *, const char *from); // prepend getcwd()
FL_API int filename_match(const char *, const char *pattern); // glob match
FL_API int filename_isdir(const char*);

// Portable "scandir" function.  Ugly but apparently necessary...

#if defined(_WIN32) && !defined(__CYGWIN__)

struct FL_API dirent {char d_name[1];};

#else

#include <sys/types.h>
#include <dirent.h>
// warning: on some systems (very few nowadays?) <dirent.h> may not exist.
// The correct information is in one of these files:
//#include <sys/ndir.h>
//#include <sys/dir.h>
//#include <ndir.h>
// plus you must do the following #define:
//#define dirent direct
// It would be best to create a <dirent.h> file that does this...

#endif

FL_API int filename_list(const char *d, struct dirent ***);

#endif

//
// End of "$Id: filename.h,v 1.2 2001/07/29 21:52:43 spitzak Exp $".
//