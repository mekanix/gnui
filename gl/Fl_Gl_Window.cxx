//
// "$Id: Fl_Gl_Window.cxx,v 1.1 1999/11/21 04:22:54 vincent Exp $"
//
// OpenGL window code for the Fast Light Tool Kit (FLTK).
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

#include <config.h>
#if HAVE_GL

#include <FL/Fl.H>
#include <FL/x.H>
#include <FL/Fl_Gl_Window.H>
#include "Fl_Gl_Choice.H"

////////////////////////////////////////////////////////////////

// The symbol SWAP_TYPE defines what is in the back buffer after doing
// a glXSwapBuffers().

// The OpenGl documentation says that the contents of the backbuffer
// are "undefined" after glXSwapBuffers().  However, if we know what
// is in the backbuffers then we can save a good deal of time.  For
// this reason you can define some symbols to describe what is left in
// the back buffer.

// The default of SWAP_SWAP works on an SGI, and will also work (but
// is sub-optimal) on machines that should be SWAP_COPY or SWAP_NODAMAGE.
// The win32 emulation of OpenGL can use COPY, but some (all?) OpenGL
// cards use SWAP.

// contents of back buffer after glXSwapBuffers():
#define UNDEFINED 0 	// unknown
#define SWAP 1		// former front buffer
#define COPY 2		// unchanged
#define NODAMAGE 3	// unchanged even by X expose() events

#ifdef MESA
#define SWAP_TYPE NODAMAGE
#else
#define SWAP_TYPE SWAP
#endif

////////////////////////////////////////////////////////////////

int Fl_Gl_Window::can_do(int a, const int *b) {
  return Fl_Gl_Choice::find(a,b) != 0;
}

void Fl_Gl_Window::create() {
  if (!g) {
    g = Fl_Gl_Choice::find(mode_, alist);
    if (!g) {Fl::error("Insufficient OpenGL"); return;}
  }
#ifndef WIN32
  Fl_X::create(this, g->vis, g->colormap, -1);
  //if (overlay && overlay != this) ((Fl_Gl_Window*)overlay)->show();
#else
  Fl_Window::create();
#endif
}

void Fl_Gl_Window::invalidate() {
  valid(0);
#ifndef WIN32
  if (overlay) ((Fl_Gl_Window*)overlay)->valid(0);
#endif
}

int Fl_Gl_Window::mode(int m, const int *a) {
  if (m == mode_ && a == alist) return 0;
  mode_ = m; alist = a;
  // destroy context and g:
  if (shown()) {destroy(); g = 0; create();}
  return 1;
}

void Fl_Gl_Window::make_current() {
  if (!context) {
#ifdef WIN32
    context = wglCreateContext(fl_private_dc(this, g));
    if (fl_first_context) wglShareLists(fl_first_context, (GLXContext)context);
    else fl_first_context = (GLXContext)context;
#else
    context = glXCreateContext(fl_display, g->vis, fl_first_context, 1);
    if (!fl_first_context) fl_first_context = (GLXContext)context;
#endif
    valid(0);
  }
  fl_set_gl_context(this, (GLXContext)context);
#if defined(WIN32) && USE_COLORMAP
  if (fl_palette) {
    fl_GetDC(fl_xid(this));
    SelectPalette(fl_gc, fl_palette, FALSE);
    RealizePalette(fl_gc);
  }
#endif // USE_COLORMAP
  glDrawBuffer(GL_BACK);
}

void Fl_Gl_Window::ortho() {
  GLint p[2];
  glGetIntegerv(GL_MAX_VIEWPORT_DIMS, p);
  glLoadIdentity();
  glViewport(w()-p[0], h()-p[1], p[0], p[1]);
  glOrtho(w()-p[0], w(), h()-p[1], h(), -1, 1);
}

void Fl_Gl_Window::swap_buffers() {
#ifdef WIN32
  SwapBuffers(Fl_X::i(this)->private_dc);
#else
  glXSwapBuffers(fl_display, fl_xid(this));
#endif
}

#if HAVE_GL_OVERLAY
#ifdef WIN32
uchar fl_overlay; // changes how fl_color() works
#endif
#endif

void Fl_Gl_Window::flush() {
  make_current();

#if HAVE_GL_OVERLAY
#ifdef WIN32
  uchar save_valid = valid_;
  if (overlay && overlay!= this && damage() == FL_DAMAGE_OVERLAY) goto DRAW_OVERLAY_ONLY;
#endif
#endif

  if (mode_ & FL_DOUBLE) {

#if SWAP_TYPE == NODAMAGE

    // don't draw if only overlay damage or expose events:
    if ((damage()&~(FL_DAMAGE_OVERLAY|FL_DAMAGE_EXPOSE)) || !valid()) draw();
    swap_buffers();

#elif SWAP_TYPE == COPY

    // don't draw if only the overlay is damaged:
    if (damage() != FL_DAMAGE_OVERLAY || !valid()) draw();
    swap_buffers();

#else // SWAP_TYPE == SWAP || SWAP_TYPE == UNDEFINED

    if (overlay == this) { // Use CopyPixels to act like SWAP_TYPE == COPY

      // don't draw if only the overlay is damaged:
      if (damage1_ || damage() != FL_DAMAGE_OVERLAY || !valid()) draw();
      // we use a seperate context for the copy because rasterpos must be 0
      // and depth test needs to be off:
      static GLXContext ortho_context;
      if (!ortho_context) {
#ifdef WIN32
	ortho_context = wglCreateContext(Fl_X::i(this)->private_dc);
#else
	ortho_context = glXCreateContext(fl_display,g->vis,fl_first_context,1);
#endif
	fl_set_gl_context(this, ortho_context);
	glDisable(GL_DEPTH_TEST);
	glReadBuffer(GL_BACK);
	glDrawBuffer(GL_FRONT);
      } else {
	fl_set_gl_context(this, ortho_context);
      }
      glCopyPixels(0,0,w(),h(),GL_COLOR);
      make_current(); // set current context back to draw overlay
      damage1_ = 0;

    } else {

#if SWAP_TYPE == SWAP
      uchar old_damage = damage();
      clear_damage(damage1_|old_damage); draw();
      swap_buffers();
      damage1_ = old_damage;
#else // SWAP_TYPE == UNDEFINED
      clear_damage(~0); draw();
      swap_buffers();
      damage1_ = ~0;
#endif

    }
#endif

    if (overlay==this) { // fake overlay in front buffer
      glDrawBuffer(GL_FRONT);
      draw_overlay();
      glDrawBuffer(GL_BACK);
      glFlush();
    }

  } else {	// single-buffered context is simpler:

    draw();
    if (overlay == this) draw_overlay();
    glFlush();

  }

#if HAVE_GL_OVERLAY
#ifdef WIN32
  if (overlay && overlay != this) {
  DRAW_OVERLAY_ONLY:
    valid_ = save_valid;
    fl_set_gl_context(this, (GLXContext)overlay);
    glDisable(GL_SCISSOR_TEST);
    fl_overlay = 1;
    glClear(GL_COLOR_BUFFER_BIT);
    draw_overlay();
    wglSwapLayerBuffers(Fl_X::i(this)->private_dc,WGL_SWAP_OVERLAY1);
    fl_overlay = 0;
  }
#endif
#endif

  valid(1);
}

void Fl_Gl_Window::layout() {
  if (ow() != w() || oh() != h()) valid(0);
  Fl_Window::layout();
}

void Fl_Gl_Window::destroy() {
  if (context) {
    fl_no_gl_context();
#ifdef WIN32
    if (context && context != fl_first_context)
      wglDeleteContext((GLXContext)context);
#else
    if (context != fl_first_context)
      glXDestroyContext(fl_display, (GLXContext)context);
#if GLX_MESA_release_buffers
    glXReleaseBuffersMESA(fl_display, fl_xid(this));
#endif
#endif
    context = 0;
  }
  Fl_Window::destroy();
}

Fl_Gl_Window::~Fl_Gl_Window() {
  destroy();
}

void Fl_Gl_Window::init() {
  end(); // we probably don't want any children
  mode_ = FL_RGB | FL_DEPTH | FL_DOUBLE;
  alist = 0;
  context = 0;
  g = 0;
  overlay = 0;
  damage1_ = 0;
}

void Fl_Gl_Window::draw_overlay() {}

#endif

//
// End of "$Id: Fl_Gl_Window.cxx,v 1.1 1999/11/21 04:22:54 vincent Exp $".
//