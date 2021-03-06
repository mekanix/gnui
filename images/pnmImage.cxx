//
// "$Id: pnmImage.cxx 4288 2005-04-16 00:13:17Z mike $"
//
// pnmImage routines.
//
// Copyright 1997-2005 by Easy Software Products.
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
//     http://www.gnui.org/str.php
//
// Contents:
//
//   pnmImage::pnmImage() - Load a PNM image...
//

//
// Include necessary header files...
//

#include <gnui/run.h>
#include <gnui/error.h>
#include <gnui/pnmImage.h>
#include <gnui/string.h>

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

using namespace gnui;
//
// 'pnmImage::pnmImage()' - Load a PNM image...
//
bool pnmImage::fetch() {
  FILE		*fp;		// File pointer
  int		x, y;		// Looping vars
  char		line[1024],	// Input line
		*lineptr;	// Pointer in line
  uchar		*ptr,		// Pointer to pixel values
		byte,		// Byte from file
		bit;		// Bit in pixel
  int		format,		// Format of PNM file
		val,		// Pixel value
		maxval;		// Maximum pixel value
  
  fp = fopen(name, "rb");
  if (!fp) return false;

  //
  // Read the file header in the format:
  //
  //   Pformat
  //   # comment1
  //   # comment2
  //   ...
  //   # commentN
  //   width
  //   height
  //   max sample
  //

  lineptr = fgets(line, sizeof(line), fp);
  if (!lineptr) {
    fclose(fp);
    gnui::error("Early end-of-file in PNM file \"%s\"!", name);
    return false;
  }

  lineptr ++;

  format = atoi(lineptr);
  while (isdigit(*lineptr)) lineptr ++;

  if (format == 7) lineptr = (char *)"";

  int w=0;
  while (lineptr != NULL && w == 0) {
    if (*lineptr == '\0' || *lineptr == '#') {
      lineptr = fgets(line, sizeof(line), fp);
    } else if (isdigit(*lineptr)) {
      w = strtol(lineptr, &lineptr, 10);
    } else lineptr ++;
  }

  int h=0;
  while (lineptr != NULL && h == 0) {
    if (*lineptr == '\0' || *lineptr == '#') {
      lineptr = fgets(line, sizeof(line), fp);
    } else if (isdigit(*lineptr)) {
      h = strtol(lineptr, &lineptr, 10);
    } else lineptr ++;
  }
  setsize(w,h);

  if (format != 1 && format != 4) {
    maxval = 0;
    while (lineptr != NULL && maxval == 0) {
      if (*lineptr == '\0' || *lineptr == '#') {
	lineptr = fgets(line, sizeof(line), fp);
      } else if (isdigit(*lineptr)) {
	maxval = strtol(lineptr, &lineptr, 10);
      } else lineptr ++;
    }
  } else maxval = 1;

  // Allocate memory ...
  if (format == 1 || format == 2 || format == 4 || format == 5)
    setpixeltype(MONO);
  else
    setpixeltype(RGB);

  // Read the image file ...
  for (y = 0; y < h; y ++) {
    uchar* linebuf = linebuffer(y);
    ptr = linebuf;

    switch (format) {
      case 1 :
      case 2 :
          for (x = w; x > 0; x --)
            if (fscanf(fp, "%d", &val) == 1) *ptr++ = (uchar)(255 * val / maxval);
          break;

      case 3 :
          for (x = w; x > 0; x --) {
            if (fscanf(fp, "%d", &val) == 1) *ptr++ = (uchar)(255 * val / maxval);
            if (fscanf(fp, "%d", &val) == 1) *ptr++ = (uchar)(255 * val / maxval);
            if (fscanf(fp, "%d", &val) == 1) *ptr++ = (uchar)(255 * val / maxval);
          }
          break;

      case 4 :
          for (x = w, byte = (uchar)getc(fp), bit = 128; x > 0; x --) {
	    if (byte & bit) *ptr++ = 255;
	    else *ptr++ = 0;

            if (bit > 1) bit >>= 1;
            else {
              bit  = 128;
              byte = (uchar)getc(fp);
            }
          }
          break;

      case 5 :
      case 6 :
        if (maxval < 256) {
          if(fread(ptr, w, depth(), fp)); //ignore the unused result
        } else {
          val = (uchar)getc(fp);
          val = (val<<8)|(uchar)getc(fp);
          *ptr++ = (255*val)/maxval;
        }
        break;

      case 7 : /* XV 3:3:2 thumbnail format */
          for (x = w; x > 0; x --) {
	    byte = (uchar)getc(fp);

	    *ptr++ = (uchar)(255 * ((byte >> 5) & 7) / 7);
	    *ptr++ = (uchar)(255 * ((byte >> 2) & 7) / 7);
	    *ptr++ = (uchar)(255 * (byte & 3) / 3);
	  }
          break;
    }
    setpixels(linebuf,y);
  }
  fclose(fp);
  return true;
}

pnmImage::pnmImage(const char *n) : SharedImage() {
  name = n;
}

//
// End of "$Id: pnmImage.cxx 4288 2005-04-16 00:13:17Z mike $".
//
