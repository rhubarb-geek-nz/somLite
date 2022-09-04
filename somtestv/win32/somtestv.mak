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
#  $Id$

!include $(MAKEDEFS)

OUTDIR=$(OUTDIR_TESTS)
INTDIR=$(BUILDTYPE)

APPNAME=somtestv

OBJS=	$(INTDIR)\$(APPNAME).obj	\
		$(INTDIR)\link386.obj		\
		$(INTDIR)\simple.obj

TARGET_EXE=$(OUTDIR)\$(APPNAME).exe
TARGET_PDB=$(OUTDIR)\$(APPNAME).pdb
TARGET_MAP=$(INTDIR)\$(APPNAME).map

PARTOPTS=	$(STDOPT)					\
			/DHAVE_CONFIG_H				\
			/D_CONSOLE					\
			/DWIN32_LEAN_AND_MEAN		\
			/I..\src					\
			/I$(INTDIR)					\
			/I..\..\include\$(PLATFORM)	\
			/I..\..\include\$(PLATFORM_DEF)	\
			/I..\..\include				\
			/I..\..\somidl\$(PLATFORM)	\
			/I..\..\somcdr\include		\
			/I..\..\somkpub\include		\
			/I..\..\somtk\include		\
			$(CC_OUT_PDB)$(TARGET_PDB)

PARTOPTSXX=	$(STDOPT)					\
			/DHAVE_CONFIG_HPP			\
			/D_CONSOLE					\
			/DWIN32_LEAN_AND_MEAN		\
			/I..\src					\
			/I$(INTDIR)					\
			/I..\..\include\$(PLATFORM)	\
			/I..\..\include\$(PLATFORM_DEF)	\
			/I..\..\include				\
			/I..\..\somidl\$(PLATFORM)	\
			/I..\..\somkpub\include		\
			/I..\..\somtk\include		\
			$(CC_OUT_PDB)$(TARGET_PDB)

all: $(TARGET_EXE)

clean:
	$(CLEAN) $(TARGET_EXE)				\
			$(TARGET_PDB)				\
			$(TARGET_MAP)				\
			$(OBJS)					\
			$(INTDIR)\$(APPNAME).res	\
			$(OUTDIR)\$(APPNAME).lib \
			$(INTDIR)\simple.h $(INTDIR)\simple.ih $(INTDIR)\simple.xh $(INTDIR)\simple.xih
	
$(TARGET_EXE): $(OBJS) $(OUTDIR) $(INTDIR)\$(APPNAME).res
	$(CC) $(CC_OUT_EXE)$@ $(OBJS)		\
		$(CC_OUT_PDB)$(TARGET_PDB)		\
		$(CC_LINK)						\
		$(LD_SUBSYSTEM_CONSOLE)			\
		$(LDFLAGS) $(INTDIR)\$(APPNAME).res
	$(POSTLINK_EXE) $@

$(INTDIR)\$(APPNAME).obj: ..\src\$(APPNAME).c $(INTDIR) $(INTDIR)\simple.h
	$(CC) /c $(PARTOPTS) $(CC_OUT_OBJ)$@ ..\src\$(APPNAME).c

$(INTDIR)\simple.obj: ..\src\simple.cpp $(INTDIR) $(INTDIR)\simple.xih $(INTDIR)\simple.xh
	$(CXX) /c $(PARTOPTSXX) $(CC_OUT_OBJ)$@ ..\src\simple.cpp

$(INTDIR)\link386.obj: ..\win32\link386.c $(INTDIR)
	$(CC) /c $(PARTOPTS) $(CC_OUT_OBJ)$@ ..\win32\link386.c

$(INTDIR):
	mkdir $@

$(INTDIR)\$(APPNAME).res: ..\win32\$(APPNAME).rc
	rc /nologo /r /I.. /fo$@ ..\win32\$(APPNAME).rc

$(INTDIR)\simple.h: ..\simple.idl
	$(OUTDIR_BIN)\sc.exe -sh -u ..\simple.idl -I..\..\somidl -o $(INTDIR)

$(INTDIR)\simple.ih: ..\simple.idl
	$(OUTDIR_BIN)\sc.exe -sih -u ..\simple.idl -I..\..\somidl -o $(INTDIR)

$(INTDIR)\simple.xh: ..\simple.idl
	$(OUTDIR_BIN)\sc.exe -sxh -u ..\simple.idl -I..\..\somidl -o $(INTDIR)

$(INTDIR)\simple.xih: ..\simple.idl
	$(OUTDIR_BIN)\sc.exe -sxih -u ..\simple.idl -I..\..\somidl -o $(INTDIR)

dist:

test:
	set PATH=$(OUTDIR_BIN);$(PATH)
	set SOMIR=$(OUTDIR_ETC)\som.ir
	$(TARGET_EXE)
