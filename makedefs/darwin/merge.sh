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
#

thinfile()
{
	RC=1

	if lipo -info "$1" >/dev/null 2>/dev/null
	then
		OUTPUT=`lipo -info "$1"`
		case "$OUTPUT" in
		Non-fat* )
			RC=0
			;;
		* )
			;;
		esac
	fi

	return $RC
}

if test -z "$PLATFORM"
then
	PLATFORM=$(config/unix/config.guess)
fi

test -n "$PLATFORM"
ls -ld "products/$PLATFORM"
test -d "products/$PLATFORM"

OSVERS="$(uname -r)"

ARCH_LIST="ppc i386 ppc64 x86_64 arm64"

PLATFORM_LIST=

for ARCH in $ARCH_LIST
do
	OTHER="$ARCH-apple-darwin$OSVERS"

	if test -d "products/$OTHER"
	then
		PLATFORM_LIST="$PLATFORM_LIST $OTHER"
	fi
done

echo source from $PLATFORM_LIST

(
	set -e
	cd "products/$PLATFORM"
	find * -type f | while read N
	do
		if thinfile "$N"
		then
			echo "$N"
		fi
	done
) | (
	set -e

	while read N
	do
		SRCLIST=

		for P in $PLATFORM_LIST
		do
			lipo -info "products/$P/$N"
			SRCLIST="$SRCLIST products/$P/$N"
		done

		if test -n "$SRCLIST"
		then
			TGTFILE="products/$PLATFORM/$N"
			TMPFILE="$TGTFILE.tmp"

			lipo $SRCLIST -create -output "$TMPFILE"
			mv "$TMPFILE" "$TGTFILE"
			lipo -info "$TGTFILE"
		fi
	done
)
