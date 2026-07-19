#!/bin/sh -ex
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

MAJOR=$(uname -r | sed y/\./\ / | while read A B C; do echo $A; done)

if test "$MAJOR" -lt 20
then
	if test "$MAJOR" -lt 11
	then
		ARCH_CANDIDATES="x86_64 i386 ppc ppc64"
	else
		ARCH_CANDIDATES="x86_64 i386"
	fi
else
	ARCH_CANDIDATES="arm64 x86_64"
fi

ARCH_LIST=

for A in $ARCH_CANDIDATES
do
	cat > makeall.c << EOF
#include <stdio.h>
int main(int argc,char **argv) { printf(""); return 0; }
EOF
	if cc -arch $A makeall.c
	then
		rm makeall.c a.out
		ARCH_LIST="$ARCH_LIST $A"
	else
		rm makeall.c
	fi
done

echo ARCH_LIST=$ARCH_LIST

for A in $ARCH_LIST
do
	PLATFORM="$A-apple-darwin$(uname -r)"
	echo $PLATFORM

	make "PLATFORM=$PLATFORM" "CFLAGS=-arch $A" "CXXFLAGS=-arch $A" $@
done
