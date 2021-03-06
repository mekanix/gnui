#
# "$Id$"
#
# Top-level makefile for the Fast Light Tool Kit (gnui).
#
# Copyright 1998-2003 by Bill Spitzak and others.
#
# This library is free software; you can redistribute it and/or
# modify it under the terms of the GNU Library General Public
# License as published by the Free Software Foundation; either
# version 2 of the License, or (at your option) any later version.
#
# This library is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
# Library General Public License for more details.
#
# You should have received a copy of the GNU Library General Public
# License along with this library; if not, write to the Free Software
# Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307
# USA.
#
# Please report all bugs and problems to the following page:
#
#    http://www.gnui.org/str.php
#

include makeinclude

# DIRS = src $(LOCALIMAGES) images OpenGL gnuid glut test
DIRS = src $(LOCALIMAGES) images OpenGL gnuid

all: makeinclude
	for dir in $(DIRS); do\
		echo "=== making $$dir ===";\
		(cd $$dir; $(MAKE) $(MFLAGS)) || exit $$?;\
	done

install: makeinclude
	for dir in $(DIRS) documentation; do\
		echo "=== installing $$dir ===";\
		(cd $$dir; $(MAKE) $(MFLAGS) DESTDIR=$(DESTDIR) install) || exit $$?;\
	done

uninstall: makeinclude
	for dir in $(DIRS) documentation; do\
		echo "=== uninstalling $$dir ===";\
		(cd $$dir; $(MAKE) $(MFLAGS) uninstall) || exit $$?;\
	done

depend: makeinclude
	for dir in $(DIRS); do\
		echo "=== making dependencies in $$dir ===";\
		(cd $$dir; $(MAKE) $(MFLAGS) depend) || exit $$?;\
	done

clean:
	$(RM) core
	$(RM) core.* *.o
	for dir in $(DIRS); do\
		echo "=== cleaning $$dir ===";\
		(cd $$dir; $(MAKE) $(MFLAGS) clean) || break;\
	done

distclean: clean
	$(RM) config.*
	$(RM) gnui-config gnui.list makeinclude
	$(RM) FL/Makefile
	$(RM) documentation/*.$(CAT1EXT)
	$(RM) documentation/*.$(CAT3EXT)
	$(RM) documentation/gnui.pdf
	$(RM) documentation/gnui.ps
	$(RM) -r documentation/gnui.d
	$(RM) lib/*.*
	for file in test/*.fl; do\
		$(RM) test/`basename $file .fl`.cxx; \
		$(RM) test/`basename $file .fl`.h; \
	done

makeinclude: configure configh.in makeinclude.in gnui/string.h.in
	if test -f config.status; then \
		./config.status --recheck; \
		./config.status; \
	else \
		./configure; \
	fi

configure: configure.in
	autoconf

portable-dist:
	epm -v gnui

native-dist:
	epm -v -f native gnui

etags:
	etags gnui/*.h src/*.cxx src/win32/*.cxx src/osx/*.cxx src/*.c \
	images/*.cxx gnuid/*.cxx gnuid/*.h test/*.cxx test/*.h Makefile */Makefile
dos2unix:
	dos2unix gnui/*.h src/*.cxx src/win32/*.cxx src/*.c images/*.cxx \
		gnuid/*.cxx gnuid/*.h gnuid/*.fl test/*.cxx test/*.h gnui/compat/FL/*.H README*
	chmod -x gnui/*.h src/*.cxx src/win32/*.cxx src/*.c images/*.cxx \
		gnuid/*.cxx gnuid/*.h gnuid/*.fl test/*.cxx test/*.h
#
# End of "$Id$".
#
# DO NOT DELETE
