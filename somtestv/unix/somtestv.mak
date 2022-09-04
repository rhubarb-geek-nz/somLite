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

include $(MAKEDEFS)

TARGET_C=$(OUTDIR_TESTS)/somtestv-c$(EXESUFFIX)
TARGET_CPP=$(OUTDIR_TESTS)/somtestv-cpp$(EXESUFFIX)
OBJS_C=$(INTDIR)/somtestv.o $(INTDIR)/simple-c.o
OBJS_CPP=$(INTDIR)/somtestv.o $(INTDIR)/simple-cpp.o
INCL=	-I$(INTDIR) \
		-I.. \
		-I../src \
		-I../../somcdr/include \
		-I../../somidl/$(PLATFORM) \
		-I../../somkpub/include		\
		-I../../somtk/include		\
		$(STDINCL)
SIMPLE_H=$(INTDIR)/simple.h
SIMPLE_XH=$(INTDIR)/simple.xh
SIMPLE_IH=$(INTDIR)/simple.ih
SIMPLE_XIH=$(INTDIR)/simple.xih

all: $(TARGET_C) $(TARGET_CPP) 

clean:
	$(CLEAN) $(TARGET_C) $(OBJS_C) $(TARGET_CPP) $(OBJS_CPP) $(SIMPLE_H) $(SIMPLE_XH) $(SIMPLE_IH) $(SIMPLE_XIH)

test: $(TARGET_C) $(TARGET_CPP)
	$(EXEC_TEST) $(TARGET_C)
	$(EXEC_TEST) $(TARGET_CPP)

$(INTDIR)/somtestv.o: ../src/somtestv.c $(SIMPLE_H)
	$(CC_EXE) $(STDOPT) $(INCL) -c ../src/somtestv.c -o $@

$(INTDIR)/simple-cpp.o: ../src/simple.cpp $(SIMPLE_XH) $(SIMPLE_XIH)
	$(CXX_EXE) $(STDOPTXX) $(INCL) -c ../src/simple.cpp -o $@

$(INTDIR)/simple-c.o: ../src/simple.c $(SIMPLE_H) $(SIMPLE_IH)
	$(CC_EXE) $(STDOPT) $(INCL) -c ../src/simple.c -o $@

$(TARGET_CPP): $(OBJS_CPP)
	$(LINKAPPXX) $(LINKAPP_HEAD) $(OBJS_CPP) -o $@ \
		`$(SHLB_REF) somd somd` \
		`$(SHLB_REF) somem somem` \
		`$(SHLB_REF) somir somir` \
		`$(SHLB_REF) somcdr somcdr` \
		`$(SHLB_REF) somdcomm somdcomm` \
		`$(SHLB_REF) somref somref` \
		`$(SHLB_REF) somtc somtc` \
		`$(SHLB_REF) somos somos` \
		`$(SHLB_REF) som som` \
		$(UUIDLIBS) $(STDLIBXX) $(LINKAPP_TAIL)

$(TARGET_C): $(OBJS_C)
	$(LINKAPP) $(LINKAPP_HEAD) $(OBJS_C) -o $@ \
		`$(SHLB_REF) somd somd` \
		`$(SHLB_REF) somem somem` \
		`$(SHLB_REF) somir somir` \
		`$(SHLB_REF) somcdr somcdr` \
		`$(SHLB_REF) somdcomm somdcomm` \
		`$(SHLB_REF) somref somref` \
		`$(SHLB_REF) somtc somtc` \
		`$(SHLB_REF) somos somos` \
		`$(SHLB_REF) som som` \
		$(UUIDLIBS) $(STDLIB) $(LINKAPP_TAIL)

$(SIMPLE_H): ../simple.idl
	$(OUTDIR_BIN)/sc -sh ../simple.idl -I ../../somidl -o $(INTDIR)
	ls -ld $@

$(SIMPLE_XH): ../simple.idl
	$(OUTDIR_BIN)/sc -sxh ../simple.idl -I ../../somidl -o $(INTDIR)
	ls -ld $@

$(SIMPLE_XIH): ../simple.idl
	$(OUTDIR_BIN)/sc -sxih ../simple.idl -I ../../somidl -o $(INTDIR)
	ls -ld $@

$(SIMPLE_IH): ../simple.idl
	$(OUTDIR_BIN)/sc -sih ../simple.idl -I ../../somidl -o $(INTDIR)
	ls -ld $@

dist install:

