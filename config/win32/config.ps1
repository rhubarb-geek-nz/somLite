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
	[Parameter( ValueFromRemainingArguments, Position=0)][string]$args
)

$ErrorActionPreference = "Stop"

$configLog = $Env:CONFIG_LOG

foreach ($run in (@{
		LANG='C'
		CPP=$Env:CONFIG_CC_EP
		CC=$Env:CONFIG_CC		
		SRC=$Env:CONFIG2_C
		HDR=$Env:CONFIG_H
	},@{
		LANG='C++'
		CPP=$Env:CONFIG_CXX_EP
		CC=$Env:CONFIG_CXX
		SRC=$Env:CONFIG2_CPP
		HDR=$Env:CONFIG_HPP
	}))
{
	$CC = $run.CC
	$LANG = $run.LANG
	$SRC = $run.SRC
	$HDR = $run.HDR
	$CPP = $run.CPP
	$LINKOPTS = $env:CONFIG_LINKOPTS

	"$LANG $CC $SRC $HDR"

	$srcFile = $Env:CONFIG2_C
	$clExe = $Env:CONFIG_CC

	$content = (& $ENV:COMSPEC /C "$CPP $SRC /DLIST_OPTIONS")

	if ($LastExitCode)
	{
		throw $LastExitCode
	}

	$now = Get-Date

	Set-Content -Value "/* Generated $now */" -LiteralPath $HDR -Encoding OEM

	try
	{
		$options=[System.Collections.ArrayList]::new()

		$defines=[System.Collections.ArrayList]::new()

		$content | ForEach-Object {
			if ($_.Length)
			{
				$i = $_.IndexOf(32)
				$j = $_.IndexOf(9)
				if ($i -gt $j)
				{
					$i = $j
				}
				$name = $_.SubString(0,$i).Trim()
				$value = $_.SubString($i).Trim()

				if ($name)
				{
					if ($value.IndexOf(34) -eq 0)
					{
						$value=$value.SubString(1,$value.Length-2)
					}

					Write-Host "$value ... " -NoNewLine

					& $ENV:COMSPEC /C "echo $CC $SRC /DTRY_$name $LINKOPTS $args >>$configLog 2>&1"

					& $ENV:COMSPEC /C "$CC $SRC /DTRY_$name $LINKOPTS $args >>$configLog 2>&1"

					if ($LastExitCode -eq 0)
					{
						Add-Content -Value "#define $NAME 1" -LiteralPath $HDR -Encoding OEM

						Write-Host $name
					}
					else
					{
						Write-Host "no"
					}
				}
			}
		}

		$HDR = $null
	}
	finally
	{
		if ($HDR)
		{
			Remove-Item $HDR
		}
	}
}
