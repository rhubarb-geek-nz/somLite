#!/bin/sh -e
#
#  Copyright 2026, Roger Brown
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

while read N
do
	IFS=/
	FULLPATH=

	for d in $N
	do
		if test -n "$d"
		then
			NEWPATH="$FULLPATH$IFS$d"

			if test -h "$NEWPATH"
			then
				M=$(readlink "$NEWPATH")

				case "$M" in
					/* )
						NEWPATH="$M"
						;;
					* )
						NEWPATH="$FULLPATH$IFS$M"
						;;
				esac
			fi

			FULLPATH=$(
				IFS=
				if test -d "$NEWPATH"
				then
					cd "$NEWPATH"
					pwd
				else
					M=$(basename "$NEWPATH")
					O=$(dirname "$NEWPATH")
					cd "$O"
					P=$(pwd)
					echo "$P/$M"
				fi
			)
		fi
	done

	echo "$FULLPATH"
done
