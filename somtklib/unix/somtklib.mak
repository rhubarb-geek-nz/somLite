#
#  Copyright 2008, Roger Brown
#
#  This file is part of Roger Brown's Toolkit.
#
#  This program is free software: you can redistribute it and/or modify it
#  under the terms of the GNU Lesser General Public License as published by the
#  Free Software Foundation, either version 3 of the License, or (at your
#  option) any later version.
# 
#  This program is distributed in the hope that it will be useful, but WITHOUT
#  ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
#  FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
#  more details.
#
#  You should have received a copy of the GNU Lesser General Public License
#  along with this program.  If not, see <http://www.gnu.org/licenses/>
#

include $(MAKEDEFS)

TARGET=$(OUTDIR_LIB)/libsomlite.a
TMPLIB=$(INTDIR)/libsomlite.a
STRIP=

SOMKPUB_INCLUDE= \
	$(OUTDIR)/include/som.h \
	$(OUTDIR)/include/som.xh \
	$(OUTDIR)/include/somapi.h \
	$(OUTDIR)/include/sombtype.h \
	$(OUTDIR)/include/somcdev.h \
	$(OUTDIR)/include/somcorba.h \
	$(OUTDIR)/include/somltype.h \
	$(OUTDIR)/include/somnames.h \
	$(OUTDIR)/include/somplatf.h \
	$(OUTDIR)/include/somtypes.h

SOMIDL_PLATFORM= \
	$(OUTDIR)/include/somcls.api \
	$(OUTDIR)/include/somcls.h \
	$(OUTDIR)/include/somcls.xh \
	$(OUTDIR)/include/somcm.h \
	$(OUTDIR)/include/somcm.xh \
	$(OUTDIR)/include/somobj.h \
	$(OUTDIR)/include/somobj.xh

SOMIDL_PUBLIC= \
	$(OUTDIR)/include/somcls.idl \
	$(OUTDIR)/include/somcm.idl \
	$(OUTDIR)/include/somobj.idl

HEADERS=$(SOMIDL_PUBLIC) $(SOMKPUB_INCLUDE) $(SOMIDL_PLATFORM)

all: $(TARGET) $(HEADERS)
	ls $(HEADERS) $(TARGET) >/dev/null

dist:
	if test -f ../$(PLATFORM_PROTO)/dist.mak; then $(MAKE) -f ../$(PLATFORM_PROTO)/dist.mak BUILDTYPE=$(BUILDTYPE) PLATFORM=$(PLATFORM); fi

install test:

clean:
	$(CLEAN) $(TARGET) $(TMPLIB) $(INTDIR)/lib*.so $(HEADERS)
	if test -f ../$(PLATFORM_PROTO)/dist.mak; then $(MAKE) -f ../$(PLATFORM_PROTO)/dist.mak clean BUILDTYPE=$(BUILDTYPE) PLATFORM=$(PLATFORM); fi

$(TARGET): $(TMPLIB)
	if test -f "$(TMPLIB)"; then mv "$(TMPLIB)" $@;	fi

$(TMPLIB):
	for d in som; \
	do \
		for e in so dylib; \
		do \
			if test -f "$(OUTDIR_LIB)/lib$$d.$$e"; \
			then \
				cp "$(OUTDIR_LIB)/lib$$d.$$e" "$(INTDIR)/lib$$d.$$e"; \
				if test "$(STRIP)" != ""; then $(STRIP) "$(INTDIR)/lib$$d.$$e"; fi; \
			fi; \
		done; \
	done
	cd $(INTDIR); \
	FOUND=; for d in lib*.so lib*.dylib; do if test -f "$$d"; then FOUND="$$FOUND $$d"; fi; done; \
	if test "$$FOUND" != ""; \
	then \
		$(AR) $(ARFLAGS) `basename $@` $$FOUND; \
		rm $$FOUND; \
		if test "$(RANLIB)" != ""; then $(RANLIB) `basename $@`; fi; \
	fi

$(SOMKPUB_INCLUDE):
	cp ../../somkpub/include/$$(basename $@) $@

$(SOMIDL_PLATFORM):
	cp ../../somidl/$(PLATFORM)/$$(basename $@) $@

$(SOMIDL_PUBLIC):
	cp ../../somidl/$$(basename $@) $@
