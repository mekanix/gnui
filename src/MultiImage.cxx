/*! \class fltk::MultiImage

  A Symbol containing a set of different Symbols.  The flags passed to
  draw() are used to select which one to draw.  This is most useful
  for making an image for a button that is different depending on
  whether it is pushed in, the current value is on, or when the mouse
  is over it.

*/

#include <fltk/MultiImage.h>

using namespace fltk;

/*! \fn MultiImage::MultiImage(Symbol& image0, Flags flags1, Symbol& image1);

  The set of images must be provided to the constructor. Only pointers
  to them are stored, you must not destroy them until after the MultiImage
  is destroyed (usually all of these are static variables).

  The flags select when the image is drawn. Useful flags are:
  - INACTIVE
  - VALUE True for button that is turned on
  - HIGHLIGHT True when the mouse is over widget or pushing it (you
  must also set highlight_color() to non-zero or most widgets will
  not redraw because they don't think they changed appearance).
  - PUSHED True if user is pushing button (it also
  inverts the VALUE setting, so you may want to swap your images)
  - FOCUSED True if button has the keyboard focus

  Typical example:

\code
  MultiImage buttonImage(OffImage,
		HIGHLIGHT, BrightOffImage,
		VALUE, OnImage,
		HIGHLIGHT|VALUE, BrightOnImage,
		INACTIVE, DimOffImage,
		INACTIVE|VALUE, DimOnImage);
\endcode
*/

/*! It probably is useless for the images to be different sizes.
  However if they are, Image0 (the first
  one passed to the constructor) is used to figure out the size. */
void MultiImage::_measure(int& w, int& h) const {
  images[0]->measure(w,h);
}

/*! Returns the info from the first image given to the constructor. */
const BoxInfo* MultiImage::boxinfo() const {return images[0]->boxinfo();}

/*! Select one of the images and draw it. The last image with all the
  flags specified for it turned on will be drawn. If none of them match
  then Image0 is drawn.
*/
void MultiImage::_draw(const Rectangle& r, const Style* style, Flags f) const
{
  int which = 0;
  //Flags passed_flags = f;
  for (int i = 1; i < MAXIMAGES && images[i]; i++) {
    if ((f & flags[i]) == flags[i]) {which = i; /*passed_flags = f&~flags[i];*/}
  }
  images[which]->draw(r, style, f);
}