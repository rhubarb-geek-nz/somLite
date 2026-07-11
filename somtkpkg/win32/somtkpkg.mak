#
#  Copyright 2012, Roger Brown
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

APPNAME=somlite
INTDIR=$(BUILDTYPE)
OUTDIR_TMP=$(INTDIR)\content
MAKEDEFS_CFS=..\..\makedefs\$(PLATFORM)\$(BUILDTYPE)\makedefs.cfl
TARGET_DDF=$(INTDIR)\somtkpkg.ddf
TARGET_CAB=$(OUTDIR_DIST)\$(APPNAME)-$(VSCMD_ARG_TGT_ARCH).cab
TARGET_ZIP=$(OUTDIR_DIST)\$(APPNAME)-$(VSCMD_ARG_TGT_ARCH).zip
TARGET_MSI=$(OUTDIR_DIST)\$(APPNAME)-$(VSCMD_ARG_TGT_ARCH).msi
DDF2WXS_DLL=..\..\toolbox2\ddf2wxs\bin\$(BUILDTYPE)\net8.0\ddf2wxs.dll
MAKEZIP_DLL=..\..\toolbox2\makezip\bin\$(BUILDTYPE)\net8.0\makezip.dll
DEPVERS_H=..\..\include\win32\depvers.h

all:

clean:
	if exist $(OUTDIR_TMP) rmdir /S /Q $(OUTDIR_TMP)
	$(CLEAN) "$(TARGET_MSI)" "$(TARGET_CAB)" "$(TARGET_ZIP)" "$(TARGET_DDF)" setup.inf setup.rpt "$(OUTDIR_DIST)\$(APPNAME)-$(VSCMD_ARG_TGT_ARCH).wixpdb"
	$(CLEAN) somlite.wxs somlite.wixobj "$(TARGET_DDF).cabinet"
	
dist: $(TARGET_CAB) $(TARGET_MSI) $(TARGET_ZIP)

$(INTDIR) $(OUTDIR_TMP):
	mkdir $@

IDLSTEMS=somobj somcls somcm

$(OUTDIR_TMP)\include: $(OUTDIR_TMP)
	mkdir $@
	copy ..\..\somkpub\include\*.* $@
	for %d in ( $(IDLSTEMS) ) do copy ..\..\somidl\%d.idl $@
	for %d in ( $(IDLSTEMS) ) do copy ..\..\somidl\$(PLATFORM)\%d.* $@

$(TARGET_DDF): $(OUTDIR_TMP)\include ..\win32\somtkpkg.mak $(OUTDIR_TMP)\som.lib
	echo .Set CabinetName1=$(APPNAME)-$(VSCMD_ARG_TGT_ARCH).cab > $@
	echo .Set DiskDirectory1=$(OUTDIR_DIST) >> $@
	echo .Set CabinetFileCountThreshold=0 >> $@
	echo .Set FolderFileCountThreshold=0 >> $@
	echo .Set FolderSizeThreshold=0 >> $@
	echo .Set MaxCabinetSize=0 >> $@
	echo .Set MaxDiskFileCount=0 >> $@
	echo .Set MaxDiskSize=0 >> $@
	echo .Set DestinationDir=include >> $@
	PowerShell.exe /C "Get-ChildItem $(OUTDIR_TMP)\include -File -Recurse | ForEach-Object { $$_.FullName }" >>$@
	echo .Set DestinationDir=bin >> $@
	for %d in ( sc pdl somipc somcpp ) do echo $(OUTDIR_BIN)\%d.exe >> $@
	for %d in ( som ) do echo $(OUTDIR_BIN)\%d.dll >> $@
	echo .Set DestinationDir=lib >> $@
	echo $(OUTDIR_TMP)\som.lib >> $@

$(OUTDIR_TMP)\som.lib: $(OUTDIR_LIB)\som.lib
	COPY /Y $(OUTDIR_LIB)\som.lib $@

$(TARGET_MSI): "$(TARGET_DDF)" ..\pkg\license.rtf "$(DDF2WXS_DLL)" "$(DEPVERS_H)" 
	if exist $@ del $@
	if exist ..\pkg\$(PLATFORM).wxs dotnet "$(DDF2WXS_DLL)" -i ..\pkg\$(PLATFORM).wxs -o $(APPNAME).wxs -d "$(TARGET_DDF)" -h "$(DEPVERS_H)" -p somtkpkg
	if exist $(APPNAME).wxs "$(WIX)\bin\candle.exe" -nologo $(APPNAME).wxs -ext WixUtilExtension 
	if exist $(APPNAME).wixobj "$(WIX)\bin\light.exe" -nologo -cultures:null -out $@ $(APPNAME).wixobj -ext WixUtilExtension
	signtool sign /a /sha1 601A8B683F791E51F647D34AD102C38DA4DDB65F /fd SHA256 /t http://timestamp.digicert.com $@

$(TARGET_CAB): $(TARGET_DDF)
	if exist setup.inf del setup.inf
	if exist setup.rpt del setup.rpt
	makecab /F $(TARGET_DDF)

$(TARGET_ZIP): $(TARGET_DDF) "$(MAKEZIP_DLL)"
	dotnet "$(MAKEZIP_DLL)" -d $(TARGET_DDF) -o $@

test:

