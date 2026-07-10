#!/usr/bin/env pwsh
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

param([string]$path)

$ErrorActionPreference = "Stop"

$done = @{}
$list = [System.Collections.ArrayList]::new()

Get-ChildItem $path -Recurse -File -Filter 'makedefs.cf' | ForEach-Object {
	$content = Get-Content -LiteralPath $_.FullName
	$hash = @{}
	foreach ($line in $content)
	{
		$words = $line.Split(' ')
		$name = $words[0]
		$hash[$name] = $words[1 .. $words.Length]
	}
	$null = $list.Add($hash)
}

while ($list.Count)
{
	$i = 0

	foreach ($hash in $list)
	{
		$blocked = $false

		$name = $hash['NAME'][0]

		$dependencies = $hash['DEPENDS'];

		if ($dependencies.Count)
		{
			foreach ($depends in $dependencies)
			{
				if ($depends)
				{
					if ($done[$depends])
					{
					}
					else
					{
						$blocked = $true
						break
					}
				}
			}

		}

		if ($blocked)
		{
			$i = $i + 1
		}
		else
		{
			break
		}
	}

	$hash = $list[$i]

	if (-not $hash)
	{
		Write-Error "no item at $i out of " + $list.Count
		break
	}

	$list.RemoveAt($i)

	foreach ($name in $hash['PROVIDES'])
	{
		if ($name)
		{
			$done[$name] = $true
		}
	}

	$hash['NAME']
}
