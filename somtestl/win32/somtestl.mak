#
#  Copyright 2008, Roger Brown
#
#  This file is part of somFree.
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

OUTDIR=$(OUTDIR_TESTS)
INTDIR=$(BUILDTYPE)
TESTCASE_SOMBASE_BIN=F:\IBMCPPW\BIN

APPNAME=somtestl

OBJS=	$(INTDIR)\$(APPNAME).obj	\
		$(INTDIR)\link386.obj 

TARGET_EXE=$(OUTDIR)\$(APPNAME).exe
TARGET_PDB=$(OUTDIR)\$(APPNAME).pdb
TARGET_MAP=$(INTDIR)\$(APPNAME).map
TARGET_DEF=..\$(PLATFORM_DEF)\$(APPNAME).def

PARTOPTS=	$(STDOPT)					\
			/DHAVE_CONFIG_H				\
			/D_CONSOLE	\
			/DWIN32_LEAN_AND_MEAN		\
			/I..\..\include\$(PLATFORM)	\
			/I..\..\include\$(PLATFORM_DEF)	\
			/I..\..\include				\
			/I..\..\somidl\$(PLATFORM)	\
			/I..\..\odincl\include		\
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
			 $(OUTDIR)\$(APPNAME).lib	\
			 $(OUTDIR)\$(APPNAME).exp
	
$(TARGET_EXE): $(OBJS) $(OUTDIR) $(INTDIR)\$(APPNAME).res $(TARGET_DEF)
	$(CC) $(CC_OUT_EXE)$@ $(OBJS)		\
		$(CC_OUT_PDB)$(TARGET_PDB)		\
		$(CC_LINK)						\
		$(LD_SUBSYSTEM_CONSOLE)			\
		$(LD_DEF)$(TARGET_DEF)			\
		$(LDFLAGS)						\
		$(LDFLAGS_NXCOMPAT) 			\
		$(INTDIR)\$(APPNAME).res
	$(POSTLINK_EXE) $@

$(INTDIR)\$(APPNAME).obj: ..\src\$(APPNAME).c $(INTDIR)
	$(CC) /c $(PARTOPTS) $(CC_OUT_OBJ)$@ ..\src\$(APPNAME).c

$(INTDIR)\link386.obj: ..\win32\link386.c $(INTDIR)
	$(CC) /c $(PARTOPTS) $(CC_OUT_OBJ)$@ ..\win32\link386.c

$(INTDIR):
	mkdir $@

$(INTDIR)\$(APPNAME).res: ..\win32\$(APPNAME).rc
	rc /nologo /r /I.. /fo$@ ..\win32\$(APPNAME).rc

dist:

test: test.$(PLATFORM)

test.win32i86:
	set PATH=$(TESTCASE_SOMBASE_BIN);%PATH%
	if exist "$(TESTCASE_SOMBASE_BIN)\SOM.DLL" $(TARGET_EXE)

test.win64amd test.win32arm test.win64arm:

