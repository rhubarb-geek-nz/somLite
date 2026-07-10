#!/bin/sh -e
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

cd $(dirname $0)/../..

pwd

cpp -DLIST_OPTIONS config/src/config2.c | while read A B
do
	case "$A" in
		'#'* | '' )
			;;
		* )
			C=$(find * -type f | grep -v config/src/config2.c | xargs grep $A | wc -l)
			if test "$C" -eq 0
			then
				echo $A $C
			fi
			;;
	esac
done
