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

!include $(MAKEDEFS)

SOMTKLIB=$(OUTDIR_LIB)\som.lib

SOMKPUB_INCLUDE= \
	$(OUTDIR_INCLUDE)\som.h \
	$(OUTDIR_INCLUDE)\som.xh \
	$(OUTDIR_INCLUDE)\somapi.h \
	$(OUTDIR_INCLUDE)\sombtype.h \
	$(OUTDIR_INCLUDE)\somcdev.h \
	$(OUTDIR_INCLUDE)\somcorba.h \
	$(OUTDIR_INCLUDE)\somltype.h \
	$(OUTDIR_INCLUDE)\somnames.h \
	$(OUTDIR_INCLUDE)\somplatf.h \
	$(OUTDIR_INCLUDE)\somtypes.h

SOMIDL_PLATFORM= \
	$(OUTDIR_INCLUDE)\somcls.api \
	$(OUTDIR_INCLUDE)\somcls.h \
	$(OUTDIR_INCLUDE)\somcls.xh \
	$(OUTDIR_INCLUDE)\somcm.h \
	$(OUTDIR_INCLUDE)\somcm.xh \
	$(OUTDIR_INCLUDE)\somobj.h \
	$(OUTDIR_INCLUDE)\somobj.xh

SOMIDL_PUBLIC= \
	$(OUTDIR_INCLUDE)\somcls.idl \
	$(OUTDIR_INCLUDE)\somcm.idl \
	$(OUTDIR_INCLUDE)\somobj.idl

HEADERS=$(SOMIDL_PUBLIC) $(SOMKPUB_INCLUDE) $(SOMIDL_PLATFORM)

all: $(SOMTKLIB) $(HEADERS) $(OUTDIR_LIB)\som.lib

SOMLIBS=$(OUTDIR_LIB)\somobjva.lib \
		$(OUTDIR_DLL)\som.lib 

$(SOMTKLIB): $(SOMLIBS)
	if exist $@ del $@
	lib  $(SOMLIBS) /OUT:$@ 

clean:
	$(CLEAN) $(SOMTKLIB) $(HEADERS)

dist:

test:

$(OUTDIR_INCLUDE)\somobj.idl:
	copy ..\..\somidl\somobj.idl $@

$(OUTDIR_INCLUDE)\somcls.idl:
	copy ..\..\somidl\somcls.idl $@

$(OUTDIR_INCLUDE)\somcm.idl:
	copy ..\..\somidl\somcm.idl $@

$(OUTDIR_INCLUDE)\som.h:
	copy ..\..\somkpub\include\som.h $@

$(OUTDIR_INCLUDE)\som.xh:
	copy ..\..\somkpub\include\som.xh $@

$(OUTDIR_INCLUDE)\somapi.h:
	copy ..\..\somkpub\include\somapi.h $@

$(OUTDIR_INCLUDE)\sombtype.h:
	copy ..\..\somkpub\include\sombtype.h $@

$(OUTDIR_INCLUDE)\somcdev.h:
	copy ..\..\somkpub\include\somcdev.h $@

$(OUTDIR_INCLUDE)\somcorba.h:
	copy ..\..\somkpub\include\somcorba.h $@

$(OUTDIR_INCLUDE)\somltype.h:
	copy ..\..\somkpub\include\somltype.h $@

$(OUTDIR_INCLUDE)\somnames.h:
	copy ..\..\somkpub\include\somnames.h $@

$(OUTDIR_INCLUDE)\somplatf.h:
	copy ..\..\somkpub\include\somplatf.h $@

$(OUTDIR_INCLUDE)\somtypes.h:
	copy ..\..\somkpub\include\somtypes.h $@

$(OUTDIR_INCLUDE)\somcls.api:
	copy ..\..\somidl\$(PLATFORM)\somcls.api $@

$(OUTDIR_INCLUDE)\somcls.h:
	copy ..\..\somidl\$(PLATFORM)\somcls.h $@

$(OUTDIR_INCLUDE)\somcls.xh:
	copy ..\..\somidl\$(PLATFORM)\somcls.xh $@

$(OUTDIR_INCLUDE)\somobj.h:
	copy ..\..\somidl\$(PLATFORM)\somobj.h $@

$(OUTDIR_INCLUDE)\somobj.xh:
	copy ..\..\somidl\$(PLATFORM)\somobj.xh $@

$(OUTDIR_INCLUDE)\somcm.h:
	copy ..\..\somidl\$(PLATFORM)\somcm.h $@

$(OUTDIR_INCLUDE)\somcm.xh:
	copy ..\..\somidl\$(PLATFORM)\somcm.xh $@
