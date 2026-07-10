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

SOM_INTDIR=..\..\som\$(PLATFORM)\$(BUILDTYPE)
SOMKERNP_KIH=$(SOM_INTDIR)\somkernp.kih

SOM_HEADERS=	$(SOM_INTDIR)\somobj.h		\
				$(SOM_INTDIR)\somcls.h		\
				$(SOM_INTDIR)\somcm.h		\
				$(SOM_INTDIR)\somobj.ih		\
				$(SOM_INTDIR)\somcls.ih		\
				$(SOM_INTDIR)\somcm.ih		\
				$(SOM_INTDIR)\rhbsomuk.h

OUTPUTS=$(SOMKERNP_KIH) $(SOM_HEADERS)

all: $(SOM_INTDIR) $(OUTPUTS)

$(SOMKERNP_KIH): "$(SOMTOOLS_BIN)\$(SC)" ..\..\somkpub\som\somobj.idl ..\..\somkpub\som\somcls.idl ..\..\somkpub\som\somcm.idl
	SET PATH=$(SOMTOOLS_BIN);$(PATH)
	PowerShell.exe ..\..\toolbox\idltool.ps1 "$(SC)" ..\..\som -o $@ -p -D__GENERATE_SOM__ -I ..\..\somkpub\som,..\..\somidl <NUL:

$(SOM_HEADERS): "$(SOMTOOLS_BIN)\$(SC)"
	SET PATH=$(SOMTOOLS_BIN);$(PATH)
	PowerShell.exe ..\..\toolbox\idltool.ps1 "$(SC)" ..\..\somkpub\som ..\..\somcdr -o $@ -p -I ..\..\somkpub\som,..\..\somidl <NUL:

clean:
	$(CLEAN) $(OUTPUTS) 

$(SOM_INTDIR):
	mkdir $@

dist test:

