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

param(
	[Parameter( Mandatory = $true, Position=0 )][string]$tool,
	[Parameter( Mandatory = $true)][string]$o,
	[string[]]$i,
	[switch]$p,
	[Parameter( ValueFromRemainingArguments, Position=0)][string[]]$args
)

Begin {
	$ErrorActionPreference = "Stop"
}

Process {
	$dirList=[System.Collections.ArrayList]::new()
	$argList=[System.Collections.ArrayList]::new()
	$cmdList=[System.Collections.ArrayList]::new()

	foreach ($arg in $args)
	{
		if ($arg[0] -eq '-')
		{
			$null = $argList.Add($arg)
		}
		else
		{
			$null = $dirList.Add($arg)
		}
	}

	$outDir = '.'

	$outName = $o
	$index =  $o.LastIndexOf('/')

	if ($index -gt 0)
	{
		$outDir = $o.SubString(0,$index)
		$outName = $o.SubString($index+1)
	}
	else
	{
		$index =  $o.LastIndexOf('\')

		if ($index -gt 0)
		{
			$outDir = $o.SubString(0,$index)
			$outName = $o.SubString($index+1)
		}
	}

	$index = $outName.LastIndexOf('.')
	$ext = $outName.SubString($index+1)
	$idlName = $outName.SubString(0,$index)+'.idl'

	foreach ($d in $dirList)
	{
		if (Test-Path -LiteralPath "$d\$idlName")
		{
			$idlName = "$d\$idlName"
			break
		}
	}

	$null = $cmdList.Add('-d')
	$null = $cmdList.Add($outDir)
	
	if ($ext -ne 'idl')
	{
		$null = $cmdList.Add("-s$ext")
	}

	foreach ($j in $i)
	{
		$null = $cmdList.Add("-I$j")
	}

	foreach ($arg in $argList)
	{
		$null = $cmdList.Add($arg)
	}

	if ($p)
	{
		$null = $cmdList.Add('-p')		
	}

	$null = $cmdList.Add($idlName)

	$cmd = "$tool $cmdList"

	Write-Output "idltool: $cmd"

	& $ENV:COMSPEC /C $cmd

	if ($LastExitCode)
	{
		throw $cmd
	}
}

End {
}
