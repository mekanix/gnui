//
// "$Id: Fl_FileBrowser.cxx,v 1.2 1999/10/24 14:30:41 mike Exp $"
//
// Fl_FileBrowser routines for the Fast Light Tool Kit (FLTK).
//
// Copyright 1997-1999 by Easy Software Products.
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
// Contents:
//
//   Fl_Fl_FileBrowser::item_width()  - Return the width of a list item.
//   Fl_Fl_FileBrowser::item_draw()   - Draw a list item.
//   Fl_Fl_FileBrowser::FileBrowser() - Create a FileBrowser widget.
//   Fl_Fl_FileBrowser::load()        - Load a directory into the browser.
//   Fl_Fl_FileBrowser::filter()      - Set the filename filter.
//

//
// Include necessary header files...
//

#include <FL/Fl_FileBrowser.h>
#include <FL/fl_draw.H>
#include <FL/filename.H>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#if defined(WIN32) || defined(__EMX__)
#  include <windows.h>
#  include <direct.h>
#endif /* WIN32 || __EMX__ */


//
// FL_BLINE definition from "Fl_Browser.cxx"...
//

#define SELECTED 1
#define NOTDISPLAYED 2

struct FL_BLINE			// data is in a linked list of these
{
  FL_BLINE	*prev;		// Previous item in list
  FL_BLINE	*next;		// Next item in list
  void		*data;		// Pointer to data (function)
  short		length;		// sizeof(txt)-1, may be longer than string
  char		flags;		// selected, displayed
  char		txt[1];		// start of allocated array
};


//
// 'Fl_FileBrowser::item_height()' - Return the height of a list item.
//

int					// O - Height in pixels
Fl_FileBrowser::item_height(void *p) const	// I - List item data
{
  FL_BLINE	*line;			// Pointer to line
  char		*text;			// Pointer into text
  int		height;			// Width of line
  int		textheight;		// Height of text


  // Figure out the standard text height...
  fl_font(textfont(), textsize());
  textheight = fl_height();

  // We always have at least 1 line...
  height = textheight;

  // Scan for newlines...
  line = (FL_BLINE *)p;

  if (line != NULL)
    for (text = line->txt; *text != '\0'; text ++)
      if (*text == '\n')
	height += textheight;

  // If we have enabled icons then add space for them...
  if (Fl_FileIcon::first() != NULL && height < iconsize_)
    height = iconsize_;

  // Add space for the selection border..
  height += 2;

  // Return the height
  return (height);
}


//
// 'Fl_FileBrowser::item_width()' - Return the width of a list item.
//

int					// O - Width in pixels
Fl_FileBrowser::item_width(void *p) const	// I - List item data
{
  FL_BLINE	*line;			// Pointer to line
  char		*text,			// Pointer into text
		*ptr,			// Pointer into fragment
		fragment[10240];	// Fragment of text
  int		width,			// Width of line
		tempwidth;		// Width of fragment
  int		column;			// Current column


  // Set the font and size...
  fl_font(textfont(), textsize());

  // Scan for newlines...
  line = (FL_BLINE *)p;

  if (strchr(line->txt, '\n') == NULL &&
      strchr(line->txt, '\t') == NULL)
  {
    // Do a fast width calculation...
    width = (int)fl_width(line->txt);
  }
  else
  {
    // More than 1 line or have columns; find the maximum width...
    width     = 0;
    tempwidth = 0;
    column    = 0;

    for (text = line->txt, ptr = fragment; *text != '\0'; text ++)
      if (*text == '\n')
      {
        // Newline - nul terminate this fragment and get the width...
        *ptr = '\0';

	tempwidth += (int)fl_width(fragment);

        // Update the max width as needed...
	if (tempwidth > width)
	  width = tempwidth;

        // Point back to the start of the fragment...
	ptr       = fragment;
	tempwidth = 0;
      }
      else if (*text == '\t')
      {
        // Advance to the next column...
        column ++;
        tempwidth = column * (int)fl_width("        ");

        if (tempwidth > width)
	  width = tempwidth;

	ptr = fragment;
      }
      else
        *ptr++ = *text;

    if (ptr > fragment)
    {
      // Nul terminate this fragment and get the width...
      *ptr = '\0';

      tempwidth += (int)fl_width(fragment);

      // Update the max width as needed...
      if (tempwidth > width)
	width = tempwidth;
    }
  }

  // If we have enabled icons then add space for them...
  if (Fl_FileIcon::first() != NULL)
    width += iconsize_ + 8;

  // Add space for the selection border..
  width += 2;

  // Return the width
  return (width);
}


//
// 'Fl_FileBrowser::item_draw()' - Draw a list item.
//

void
Fl_FileBrowser::item_draw(void *p,	// I - List item data
                          int  x,	// I - Upper-lefthand X coordinate
	 	          int  y,	// I - Upper-lefthand Y coordinate
		          int  w,	// I - Width of item
		          int  h) const	// I - Height of item
{
  FL_BLINE	*line;			// Pointer to line


  // Draw the list item text...
  line = (FL_BLINE *)p;

  fl_font(textfont(), textsize());

  if (line->flags & SELECTED)
    fl_color(fl_contrast(textcolor(), selection_color()));
  else
    fl_color(textcolor());

  if (Fl_FileIcon::first() == NULL)
  {
    // No icons, just draw the text...
    fl_draw(line->txt, x + 1, y, w - 2, h, FL_ALIGN_LEFT);
  }
  else
  {
    // Icons; draw the text offset to the right...
    fl_draw(line->txt, x + iconsize_ + 9, y, w - iconsize_ - 10, h,
            FL_ALIGN_LEFT);

    // And then draw the icon if it is set...
    if (line->data)
      ((Fl_FileIcon *)line->data)->draw(x, y, iconsize_, iconsize_,
                                        (line->flags & SELECTED) ? FL_YELLOW :
				                                   FL_LIGHT2);
  }
}


//
// 'Fl_FileBrowser::Fl_FileBrowser()' - Create a Fl_FileBrowser widget.
//

Fl_FileBrowser::Fl_FileBrowser(int        x,	// I - Upper-lefthand X coordinate
                               int        y,	// I - Upper-lefthand Y coordinate
			       int        w,	// I - Width in pixels
			       int        h,	// I - Height in pixels
			       const char *l)	// I - Label text
    : Fl_Browser(x, y, w, h, l)
{
  // Initialize the filter pattern, current directory, and icon size...
  pattern_   = "*";
  directory_ = "";
  iconsize_  = 3 * textsize() / 2;
}


//
// 'Fl_FileBrowser::load()' - Load a directory into the browser.
//

int					// O - Number of files loaded
Fl_FileBrowser::load(const char *directory)// I - Directory to load
{
  int		i;		// Looping var
  int		num_files;	// Number of files in directory
  char		filename[4096];	// Current file
  Fl_FileIcon	*icon;		// Icon to use


  clear();
  directory_ = directory;

  if (directory_[0] == '\0')
  {
    //
    // No directory specified; for UNIX list all mount points.  For DOS
    // list all valid drive letters...
    //

    num_files = 0;
    icon      = Fl_FileIcon::find("any", Fl_FileIcon::DIRECTORY);

#if defined(WIN32) || defined(__EMX__)
    DWORD	drives;		// Drive available bits


    drives = GetLogicalDrives();
    for (i = 'A'; i <= 'Z'; i ++, drives >>= 1)
      if (drives & 1)
      {
        sprintf(filename, "%c:", i);

	if (i < 'C')
	  add(filename, icon);
	else
	  add(filename, icon);

	num_files ++;
      }
#else
    FILE	*mtab;		// /etc/mtab or /etc/mnttab file
    char	line[1024];	// Input line


    //
    // Open the file that contains a list of mounted filesystems...
    //
#  if defined(hpux) || defined(__sun)
    mtab = fopen("/etc/mnttab", "r");	// Fairly standard
#  elif defined(__sgi) || defined(linux)
    mtab = fopen("/etc/mtab", "r");	// More standard
#  else
    mtab = fopen("/etc/fstab", "r");	// Otherwise fallback to full list
    if (mtab == NULL)
      mtab = fopen("/etc/vfstab", "r");
#  endif

    if (mtab != NULL)
    {
      while (fgets(line, sizeof(line), mtab) != NULL)
      {
        if (line[0] == '#' || line[0] == '\n')
	  continue;
        if (sscanf(line, "%*s%4095s", filename) != 1)
	  continue;

        add(filename, icon);
	num_files ++;
      }

      fclose(mtab);
    }
#endif // WIN32 || __EMX__
  }
  else
  {
    dirent	**files;	// Files in in directory


    //
    // Build the file list...
    //

#if defined(WIN32) || defined(__EMX__)
    strcpy(filename, directory_);
    i = strlen(filename) - 1;

    if (i == 2 && filename[1] == ':' &&
        (filename[2] == '/' || filename[2] == '\\'))
      filename[2] = '/';
    else if (filename[i] != '/' && filename[i] != '\\')
      strcat(filename, "/");

    num_files = filename_list(filename, &files);
#else
    num_files = filename_list(directory_, &files);
#endif /* WIN32 || __EMX__ */

    for (i = 0; i < num_files; i ++)
    {
      if (strcmp(files[i]->d_name, ".") == 0 ||
          strcmp(files[i]->d_name, "..") == 0)
	continue;

      sprintf(filename, "%s/%s", directory_, files[i]->d_name);

      if (filename_isdir(filename) ||
          filename_match(files[i]->d_name, pattern_))
        add(files[i]->d_name, Fl_FileIcon::find(filename));

      free(files[i]);
    }

    free(files);
  }

  return (num_files);
}


//
// 'Fl_FileBrowser::filter()' - Set the filename filter.
//

void
Fl_FileBrowser::filter(const char *pattern)	// I - Pattern string
{
  // If pattern is NULL set the pattern to "*"...
  if (pattern)
    pattern_ = pattern;
  else
    pattern_ = "*";

  // Reload the current directory...
  load(directory_);
}


//
// End of "$Id: Fl_FileBrowser.cxx,v 1.2 1999/10/24 14:30:41 mike Exp $".
//