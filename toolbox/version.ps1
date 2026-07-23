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
	[Parameter( Mandatory = $true )][string]$literalPath
)

$ErrorActionPreference = 'Stop'

$content = dumpbin /HEADERS $literalPath

if ($LastExitCode)
{
	throw $LastExitCode
}

$failed = $true
$stage = 0
$vers = $null

foreach ($line in $content)
{
	if ($line -eq 'OPTIONAL HEADER VALUES')
	{
		$stage = 1
	}
	else
	{
		if ($stage -eq 1)
		{
			$parts = $line.Trim().Split(' ')

			if ('image' -eq $parts[1])
			{
				if ('version' -eq $parts[2])
				{
					$vers = $parts[0]
					$failed = $false
					break
				}
			}
		}
	}
}

if ($failed)
{
	throw "Failed to get version from $literalPath with dumpbin"
}

$v2 = $vers.Split('.')

$f = Get-Item $literalPath

if (-not $f) { throw $literalPath }

$v3 = $f.VersionInfo.FileVersion

$v4 = "$v3".Split('.')

if (([int]$v2[0]) - ([int]$v4[0])) { throw "major problem, $vers vs $v3" }
if (([int]$v2[1]) - ([int]$v4[1])) { throw "minor problem, $vers vs $v3" }
