//
// "$Id: fl_engraved_label.cxx,v 1.14 2002/12/10 01:46:18 easysw Exp $"
//
// Engraved label drawing routines for the Fast Light Tool Kit (FLTK).
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

// Drawing code for XForms style engraved & embossed labels

#include <fltk/Widget.h>
#include <fltk/LabelType.h>
#include <fltk/draw.h>
using namespace fltk;

// data is dx, dy, color triples

void EngravedLabel::draw(const char* label,
			 int X, int Y, int W, int H,
			 Color fill, Flags flags) const
{
  for (const int *data = this->data; ; data += 3) {
    Color c = (Color)(data[2]);
    NORMAL_LABEL->draw(label,
		       X+data[0], Y+data[1], W, H,
		       c ? c : inactive(fill, flags),
		       flags&~INACTIVE);
    if (!c) break;
  }
}

static const int shadow_data[2][3] = {{2,2,GRAY33},{0,0,0}};
static EngravedLabel shadowLabel("shadow", shadow_data);
LabelType* const fltk::SHADOW_LABEL = &shadowLabel;

static const int engraved_data[7][3] = {
  {1,0,GRAY99},{1,1,GRAY99},{0,1,GRAY99},
  {-1,0,GRAY33},{-1,-1,GRAY33},{0,-1,GRAY33},
  {0,0,0}};
static EngravedLabel engravedLabel("engraved", engraved_data);
LabelType* const fltk::ENGRAVED_LABEL = &engravedLabel;

static const int embossed_data[7][3] = {
  {-1,0,GRAY99},{-1,-1,GRAY99},{0,-1,GRAY99},
  {1,0,GRAY33},{1,1,GRAY33},{0,1,GRAY33},
  {0,0,0}};
static EngravedLabel embossedLabel("embossed", embossed_data);
LabelType* const fltk::EMBOSSED_LABEL = &embossedLabel;

//
// End of "$Id: fl_engraved_label.cxx,v 1.14 2002/12/10 01:46:18 easysw Exp $".
//
