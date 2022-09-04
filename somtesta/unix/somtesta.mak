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

TARGET=$(OUTDIR_TESTS)/somtesta$(EXESUFFIX)
INCL=	-I$(INTDIR) \
		-I.. \
		-I../../somidl/$(PLATFORM) \
		-I../../somkpub/include		\
		-I../../somtk/include		\
		$(STDINCL)
OBJS=$(INTDIR)/somtesta.o
SOMTESTA_IR=$(OUTDIR_ETC)/somtesta.ir
SOMTESTA_H=$(INTDIR)/somtesta.h

all: $(TARGET)

clean:
	$(CLEAN) $(OBJS) $(TARGET) $(SOMTESTA_IR) $(SOMTESTA_H)

test: $(TARGET) $(SOMTESTA_IR)
	SOMIR=$(SOMTESTA_IR) $(EXEC_TEST) $(TARGET)

$(SOMTESTA_IR): ../somtesta.idl $(OUTDIR_ETC)/som.ir
	cp $(OUTDIR_ETC)/som.ir $@
	SOMIR=$@ $(OUTDIR_BIN)/sc -sir -u ../somtesta.idl -I ../../somidl
	ls -ld $@

$(SOMTESTA_H): ../somtesta.idl
	$(OUTDIR_BIN)/sc -sh ../somtesta.idl -I ../../somidl -o $(INTDIR)
	ls -ld $@

$(INTDIR)/somtesta.o: ../src/somtesta.c $(SOMTESTA_H)
	$(CC_EXE) $(STDOPT) $(INCL) -c ../src/somtesta.c -o $@

$(TARGET): $(OBJS)
	$(LINKAPP) $(LINKAPP_HEAD) $(OBJS) -o $@ \
		`$(SHLB_REF) somir somir` \
		`$(SHLB_REF) somtc somtc` \
		`$(SHLB_REF) som som` \
		`$(SHLB_MAP) somtesta somtesta` \
		$(STDLIB) $(LINKAPP_TAIL)

dist install:

