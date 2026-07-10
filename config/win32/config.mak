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

!INCLUDE $(MAKEDEFS)

INTDIR=$(BUILDTYPE)
APPNAME=config
CONFIG_SRC=..\src
CONFIG_C=$(CONFIG_SRC)\config.c
CONFIG2_C=$(CONFIG_SRC)\config2.c
CONFIG2_CPP=$(CONFIG_SRC)\config2.cpp
CONFIG2_OBJ=.\$(INTDIR)\config2.obj
CONFIG_IP=..\..\include\$(PLATFORM_DEF)
CONFIG_I=..\..\include\$(PLATFORM)
CONFIG_H=$(CONFIG_I)\config.h
CONFIG_HPP=$(CONFIG_I)\config.hpp
CONFIG_LOG=$(INTDIR)\config.log
IMPLIB_DIR=$(OUTDIR_LIB)
OBJS=$(CONFIG2_OBJ)

all: checkenv $(OUTDIR_TOOLS) $(INTDIR) $(CONFIG_I) $(CONFIG_HPP)

checkenv:
	if "$(OUTDIR_BIN)" == "" exit 1
	if "$(OUTDIR_LIB)" == "" exit 1
	if "$(OUTDIR_DLL)" == "" exit 1
	if "$(OUTDIR_TESTS)" == "" exit 1
	if "$(OUTDIR_TOOLS)" == "" exit 1
	if "$(CLEAN)" == "" exit 1
	if "$(MIDL)" == "" exit 1
	if "$(MKTYPLIB)" == "" exit 1
	if "$(CC)" == "" exit 1
	if "$(CXX)" == "" exit 1
	if "$(CC_OUT_OBJ)" == "" exit 1
	if "$(CC_OUT_EXE)" == "" exit 1
	if "$(CC_OUT_DLL)" == "" exit 1
	if "$(RCFLAGS)" == "" exit 1
	if "$(LDFLAGS)" == "" exit 1
	if "$(STDOPT)" == "" exit 1
	if "$(STDOPTXX)" == "" exit 1
	
clean:
	$(CLEAN) $(CONFIG_PDB)		\
			 $(CONFIG_HPP)		\
			 $(CONFIG_H)		\
			 $(OBJS)			\
			 $(CONFIG_LOG)		\
			 $(INTDIR)\$(APPNAME).res
	$(CLEAN) $(INTDIR)\CONFIG3.EXE $(INTDIR)\CONFIG3.OBJ
	$(CLEAN) $(INTDIR)\CONFIG3.EXP $(INTDIR)\CONFIG3.LIB

$(CONFIG_H): ..\win32\config.ps1 $(CONFIG2_C) $(CONFIG2_CPP)
	set INCLUDE=IMPLIB_DIR;$(INCLUDE)
	set CONFIG2_C=$(CONFIG2_C)
	set CONFIG2_CPP=$(CONFIG2_CPP)
	set CONFIG_H=$(CONFIG_H)
	set CONFIG_HPP=$(CONFIG_HPP)
	set CONFIG_CC=$(CC) /I../src /DHAVE_CONFIG_H /I$(CONFIG_I)
	set CONFIG_CXX=$(CXX) /I../src /DHAVE_CONFIG_HPP /I$(CONFIG_I)
	set CONFIG_CC_EP=$(CC) /EP
	set CONFIG_CXX_EP=$(CXX) /EP /I../src
	set CONFIG_LINKOPTS=$(CC_OUT_OBJ)$(INTDIR)\CONFIG3.OBJ $(CC_OUT_EXE)$(INTDIR)\CONFIG3.EXE $(CC_LINK) $(LDFLAGS) $(LD_SUBSYSTEM_CONSOLE) $(LD_ENTRY_MAIN) $(LD_PDB_NONE)
	set CONFIG_LOG=$(CONFIG_LOG)
	$(CLEAN) $(CONFIG_HPP) $(CONFIG_H)
	PowerShell.exe ..\win32\config.ps1 /DWIN32_LEAN_AND_MEAN /I$(CONFIG_I) /I$(CONFIG_IP) /I$(CONFIG_SRC) $(CONFIG_OPTS)
	dir $@
	echo $(MAKE)
	$(CLEAN) $(INTDIR)\CONFIG3.EXE $(INTDIR)\CONFIG3.OBJ
	$(CLEAN) $(INTDIR)\CONFIG3.EXP $(INTDIR)\CONFIG3.LIB

$(CONFIG_HPP): $(CONFIG_H) 

$(INTDIR) $(IMPLIB_DIR) $(CONFIG_I):
	mkdir $@

dist:

test:

