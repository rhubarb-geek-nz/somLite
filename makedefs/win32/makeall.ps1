#Requires -PSEdition Desktop
#
#  Copyright 2026, Roger Brown
#
#  This file is part of rhubarb-geek-nz/somLite.
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
#  You should have received a copy of the GNU General Public License
#  along with this program.  If not, see <http://www.gnu.org/licenses/>
#

Param ( [string]$task = 'all' )

foreach ($arch in @{
		Platform = 'win32i86'
		VcVars = 'vcvars32.bat'
	},
	@{
		Platform = 'win64amd'
		VcVars = 'vcvars64.bat'
	},
	@{
		Platform = 'win64arm'	
		VcVars = 'vcvarsamd64_arm64.bat'
	}) {

	$VCVARS = "$env:ProgramFiles\Microsoft Visual Studio\18\Community\VC\Auxiliary\Build\" + $arch.VcVars

	$BEFORE = 'ECHO %PROCESSOR_ARCHITECTURE%'
	$MIDDLE = 'CALL MAKE.BAT test'

	if ($arch.Platform -eq 'win64arm')
	{
		$BEFORE = "SET SOMTOOLS_BIN=%CD%\products\win32i86\Release\bin`r`nMOVE samples\win32\samples.mak samples\win32\samples.bak"
		$MIDDLE = "MOVE samples\win32\samples.bak samples\win32\samples.mak"
	}

	@"
IF NOT EXIST "$VCVARS" EXIT 0
CALL "$VCVARS"
IF ERRORLEVEL 1 EXIT %ERRORLEVEL%
ECHO HOST=%PROCESSOR_ARCHITECTURE% TARGET=%VSCMD_ARG_TGT_ARCH%
$BEFORE
IF ERRORLEVEL 1 EXIT %ERRORLEVEL%
CALL MAKE.BAT clean
IF ERRORLEVEL 1 EXIT %ERRORLEVEL%
CALL MAKE.BAT
IF ERRORLEVEL 1 EXIT %ERRORLEVEL%
$MIDDLE
IF ERRORLEVEL 1 EXIT %ERRORLEVEL%
CALL MAKE.BAT sign
IF ERRORLEVEL 1 EXIT %ERRORLEVEL%
CALL MAKE.BAT dist
IF ERRORLEVEL 1 EXIT %ERRORLEVEL%
"@ | & "$env:COMSPEC"

	if ($LastExitCode -ne 0)
	{
		exit $LastExitCode
	}
}
