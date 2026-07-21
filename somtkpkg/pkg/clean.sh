#!/bin/sh -e
#
#  Copyright 2026, Roger Brown
#
#  This file is part of somLite.
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

INTDIR="$1"

for d in somtk.ir somtk.rte somtk.dsom somtk.comp somtk.util somtk.tests somtk.man root somtk.dev
do
	if test -d "$INTDIR/$d"
	then
		find "$INTDIR/$d" -type d -print | while read N
		do
			chmod +w "$N"
		done

		find "$INTDIR/$d" -type f -print | while read N
		do
			chmod +w "$N"
		done

		rm -rf "$INTDIR/$d"
	fi
done
