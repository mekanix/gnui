/** \file Threads.h

  Inline classes to provide a "toy" interface for threads and mutexes.
  These are used by the gnui demo programs. They have been improved
  quite a bit and may be useful for non-toy programs, too.  <i>This
  file is optional</i>, you can use pthreads or any other
  multithreading library if you want more control over multithreading.

  Warning: on Windows including this will cause the <windows.h> header
  file to be included. This file often has undesirable effects and
  should be avoided if at all possible.

\section multithreading How to Multithread FLTK Applications

  If you have multiple threads accessing FLTK functions, you must
  surround any calls to FLTK with gnui::lock() and gnui::unlock()
  pairs. This is a recursive mutex so you can nest multiple calls to
  lock/unlock.

  Although it appears that whatever thread calls run() has the lock
  all the time, in fact FLTK releases the lock internally when it
  waits for events, and then grabs it again before handling the
  events.

\section mtbugs Known problems

  The "main" thread is the one that is calling gnui::wait().

  If non-main threads want the display to update, besides calling
  Widget::redraw(), they must call gnui::awake() before calling
  gnui::unlock(). Otherwise the redraw will not be noticed until
  the next event comes in, making your program look very sluggish
  or broken.

  Non-main threads cannot call all gnui functions. In particular any
  functions that wait for events (including gnui::Window::exec(),
  gnui::check(), and gnui::ask()) do not work. The function
  gnui::in_main_thread() can be used to check if your code is in the
  main thread or not (you have to hold the lock to call this). The
  only workaround is to store what you want to do in static variables,
  call gnui::awake(), and make the main thread call gnui::wait()
  repeatedly, checking and acting on the static values after each
  call.

  On Windows you cannot change which thread is the "main" one, and
  the Window::show() method can only be called by the main thread.

\section texample Example

  \code
  main() {
    gnui::lock(); // ALWAYS call before any gnui calls
    create_widgets();
    Thread t1; create_thread(t1, func, data1);
    Thread t2; create_thread(t2, func, data2);
    for (;;) {
      gnui::wait();
      check_what_threads_are_up_to();
    }
  }

  gnui::Mutex mutex;

  func1(void* data) {
    mutex.lock();
    do_something();
    mutex.unlock();
    gnui::lock();
    widget->value(foo);
    widget->redraw();
    gnui::awake(); // Without this it may not redraw until next event!
    gnui::unlock();
  }
  \endcode

*/

/*! \fn void gnui::lock()

  A multi-threaded gnui program must surround all calls to any gnui
  functions with lock() and unlock() pairs. This is a "recursive
  lock", a thread can call lock() n times, and it must call
  unlock() n times before it really is unlocked.

  If another thread calls lock() while it is locked, it will block
  (not return from lock()) until the first thread unlocks.

  The main thread must call lock() once before \e any call to gnui to
  initialize the thread system.

  The X11 version of gnui uses XInitThreads(), XLockDisplay(), and
  XUnlockDisplay(). This should allow an gnui program to cooperate
  with other packages updating the display using Xlib calls.
*/

/*! \fn void gnui::unlock()
  Releases the lock that was set using the gnui::lock() method. Child
  threads should call this method as soon as they are finished
  accessing FLTK. If some other thread is waiting for gnui::lock() to
  return, it will get control.
*/

/*! \fn void gnui::awake(void* message)

  A child thread can call this to cause the main thread's call to
  wait() to return (with the lock locked) even if there are no events
  ready. The main purpose of this is to get the main thread to redraw
  the screen, but it will also cause gnui::wait() to return so the
  program's code can do something.

  You should call this immediately before gnui::unlock() for best
  performance.

  The message argument can be retrieved by the other thread using
  gnui::thread_message().
*/

/*! \fn void* gnui::thread_message()

  Returns an argument sent to the most recent awake(), or returns null
  if none. Warning: this is almost useless for communication as the
  current implementation only has a one-entry queue and
  only returns the most recent awake() result.
*/

/*! \fn bool gnui::in_main_thread()

  Returns true if the current thread is the main thread, i.e. the one
  that called wait() first. Many gnui calls such as wait() will not

  work correctly if this is not true. This function must be surrounded
  by lock() and unlock() just like all other gnui functions, the
  return value is wrong if you don't hold the gnui lock!

  Warning: in_main_thread() is wrong if the main thread calls
  gnui::unlock() and another thread calls gnui::lock() (the
  assumption is that the main thread only calls wait()). Current
  fix is to do the following unsupported code:

\code
  gnui::in_main_thread_ = false;
  gnui::unlock();
  wait_for_something_without_calling_gnui_wait();
  gnui::lock();
  gnui::in_main_thread_ = true;
\endcode
*/

#include <gnui/run.h>
#include <config.h>

// Define the mutex-init value needed by gnui::RecursiveMutex:
#if HAVE_PTHREAD && (!defined(_WIN32) || defined(__CYGWIN__))
# ifndef __USE_GNU
#  define __USE_GNU // makes the RECURSIVE stuff appear on Linux
# endif
# include <gnui/Threads.h>

# if defined(PTHREAD_RECURSIVE_MUTEX_INITIALIZER_NP) && !defined(__CYGWIN__)
static pthread_mutexattr_t recursive_attrib = {{PTHREAD_MUTEX_RECURSIVE_NP}};
gnui::RecursiveMutex::RecursiveMutex() : Mutex(&recursive_attrib) {}
# elif defined(PTHREAD_MUTEX_RECURSIVE)
static pthread_mutexattr_t* recursive_attrib() {
  static pthread_mutexattr_t a;
  static bool beenhere = false;
  if (!beenhere) {
    pthread_mutexattr_init(&a);
    pthread_mutexattr_settype(&a,PTHREAD_MUTEX_RECURSIVE);
    beenhere=true;
  }
  return &a;
}
gnui::RecursiveMutex::RecursiveMutex() : Mutex(recursive_attrib()) {}
# endif
#endif

#if USE_X11 && USE_X11_MULTITHREADING

// This is NOT normally done, instead the HAVE_PTHREAD case is done
# include "x11/lock.cxx"

#elif defined(_WIN32) && !defined(__CYGWIN__)

# include "win32/lock.cxx"

#elif HAVE_PTHREAD

// Use our RecursiveLock for lock/unlock, and a pipe for awake():

#include <unistd.h>
#include <fcntl.h>

extern void (*gnui_lock_function)();
extern void (*gnui_unlock_function)();
static void init_function();
static void (*init_or_lock_function)() = init_function;

static gnui::RecursiveMutex gnuimutex;

static void lock_function() { gnuimutex.lock(); }
static void unlock_function() { gnuimutex.unlock(); }

static pthread_t main_thread_id;

static void* thread_message_;
static void thread_awake_cb(int fd, void*) {
  while (read(fd, &thread_message_, sizeof(void*)) > 0);
}
static int thread_filedes[2];

static void init_function() {
  // Init threads communication pipe to let threads awake FLTK from wait
  main_thread_id = pthread_self();
  if(pipe(thread_filedes)); //ignore the return value
  fcntl(thread_filedes[0], F_SETFL, O_NONBLOCK);
  gnui::add_fd(thread_filedes[0], gnui::READ, thread_awake_cb);
  gnui_lock_function = init_or_lock_function = lock_function;
  gnui_unlock_function = unlock_function;
  lock_function();
}

void gnui::lock() {init_or_lock_function();}

void gnui::unlock() {gnui_unlock_function();}

bool gnui::in_main_thread() {
  return init_or_lock_function == init_function || pthread_self() == main_thread_id;
}

void gnui::awake(void* msg) {
  if(write(thread_filedes[1], &msg, sizeof(void*))); //ignore the return value
}

// the following is already defined in CYGWIN
// for the common win32/run.cxx part
#if !defined(__CYGWIN__) 
void* gnui::thread_message() {
  void* r = thread_message_;
  thread_message_ = 0;
  return r;
}
#endif

#else

// If no lock is supported, the gnui::lock() and similar functions are
// missing.

#endif

// end of lock.cxx
