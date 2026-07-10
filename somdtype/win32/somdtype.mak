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

SC=sc.exe
PDL=pdl.exe

SOM_IDL=		..\..\somd\somdtype.idl			\
				..\..\somd\stexcep.idl

SOMIDL_IDL=..\..\somidl
SOMIDL_HEADERS=..\..\somidl\$(PLATFORM)

PRODUCTS_SC1=	$(SOMIDL_HEADERS)\stexcep.h		\
				$(SOMIDL_HEADERS)\stexcep.xh

PRODUCTS_SC2=

PRODUCTS_SC3=

PRODUCTS_SC4=

SOMDTYPE_SC=	$(SOMIDL_HEADERS)\somdtype.h	\
				$(SOMIDL_HEADERS)\somdtype.xh

PRODUCTS_PDL=	$(SOMIDL_IDL)\somdtype.idl		\
				$(SOMIDL_IDL)\stexcep.idl

PRODUCTS_SC=	$(PRODUCTS_SC1)					\
				$(PRODUCTS_SC2)					\
				$(PRODUCTS_SC3)					\
				$(PRODUCTS_SC4)

all:		$(PRODUCTS_PDL) $(PRODUCTS_SC) $(SOMDTYPE_SC)

clean:
	$(CLEAN) $(PRODUCTS_SC1) 
	$(CLEAN) $(PRODUCTS_SC2) 
	$(CLEAN) $(PRODUCTS_SC3) 
	$(CLEAN) $(PRODUCTS_SC4) 
	$(CLEAN) $(PRODUCTS_PDL) 
	$(CLEAN) $(SOMDTYPE_SC)

$(SOMIDL_HEADERS) $(SOMIDL_IDL):
	mkdir $@

$(PRODUCTS_PDL): $(SOMIDL_IDL) $(SOM_IDL)
	SET PATH=$(SOMTOOLS_BIN);$(PATH)
	PowerShell.exe ..\..\toolbox\idltool.ps1 "$(PDL)" ..\..\somd ..\..\somir -o $@ <NUL:

$(PRODUCTS_SC): $(SOMIDL_HEADERS) $(PRODUCTS_PDL)
	SET PATH=$(SOMTOOLS_BIN);$(PATH)
	PowerShell.exe ..\..\toolbox\idltool.ps1 "$(SC)" $(SOMIDL_IDL) -o $@ -I$(SOMIDL_IDL) <NUL:

$(SOMDTYPE_SC): $(SOMIDL_HEADERS) $(PRODUCTS_PDL)
	SET PATH=$(SOMTOOLS_BIN);$(PATH)
	PowerShell.exe ..\..\toolbox\idltool.ps1 "$(SC)" $(SOMIDL_IDL) -o $@ -I$(SOMIDL_IDL) -DEMIT_SOMDTYPES <NUL:

dist:


test:


