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

. ../version.sh

if test -z "$VERSION"
then
	VERSION=0.0.0.1
fi

if test -z "$PREFIX"
then
	PREFIX="/usr/local"
fi

for d in bin lib include man/man1
do
	install -d "$DESTDIR/$PREFIX/$d"
done

install "$OUTDIR/bin/sc" "$OUTDIR/bin/somcpp" "$OUTDIR/bin/somipc" "$DESTDIR/$PREFIX/bin"

find "$OUTDIR/lib" -name "libsom.*" -type f | while read N
do
	BN=$(basename $N)
	install -m 644 "$N" "$DESTDIR/$PREFIX/lib"
done

find "$OUTDIR/lib" -name "libsom.*" -type l | while read N
do
	BN=$(basename $N)
	LN=$(readlink "$N")
	if test -h "$DESTDIR/$PREFIX/lib/$BN"
	then
		rm  "$DESTDIR/$PREFIX/lib/$BN"
	fi
	ln -s "$LN" "$DESTDIR/$PREFIX/lib/$BN"
done

find ../../somkpub/include -name "som*" -type f | while read N
do
	BN=$(basename $N)
	install -m 644 "$N" "$DESTDIR/$PREFIX/include"
done

find ../../somidl "../../somidl/$PLATFORM" -name "som*" -type f | while read N
do
	BN=$(basename $N)
	case "$BN" in
		somobj.* | somcls.* | somcm.* )
			install -m 644 "$N" "$DESTDIR/$PREFIX/include"
			;;
		* )
			;;
	esac
done

find "$OUTDIR/man" -type f | while read N
do
	BN=$(basename $N)
	case "$BN" in
		sc.1* | somipc.1* )
			install -m 644 "$N" "$DESTDIR/$PREFIX/man/man1"
			;;
		* )
			;;
	esac
done
