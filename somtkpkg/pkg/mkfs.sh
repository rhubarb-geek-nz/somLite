#!/bin/sh -e
#
#  Copyright 2011, Roger Brown
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

FLAG=

INTDIR=.

LIBPREFIX=lib
LIBEXT=.so
LIBDIRNAME=lib
HEADERSRC=

for d in $@
do
	if test "$FLAG" = ""
	then
		FLAG="$d"
	else
		case "$FLAG" in
		-d )
			OUTDIR_DIST="$d"
			;;
		-r )
			OUTDIR="$d"
			;;
		-t )
			INTDIR="$d"
			;;
		-l )
			LIBDIRNAME="$d"
			;;
		-h )
			HEADERSRC="$d"
			;;
		* )
			echo unknown option $d
			exit 1
		esac
		FLAG=
	fi
done

if test -z "$OBJDUMP"
then
	OBJDUMP=objdump
fi

case "$INTDIR" in
/* )
	;;
* )
	INTDIR=`pwd`/$INTDIR
	;;
esac

copyBinFile()
{
	for y in $@
	do
		(
			cd `dirname "$y"`
			tar cf - `basename "$y"`
		) | (
			cd "$INTDIR/$PKGNAME/$PKGBASE/bin"
			tar xvf -
		)
	done
}

makeBinLink()
{
	(
		cd "$INTDIR/$PKGNAME/$PKGBASE/bin"
		ln -s "$1" "$2"
		ls -ld "$2"
	)
}

copyLibFile()
{
	for y in $@
	do
		(
			cd `dirname "$y"`
			tar cf - `basename "$y"`
		) | (
			cd "$INTDIR/$PKGNAME/$PKGBASE/$LIBDIRNAME"
			tar xvf -
		)
	done
}

copyIncFile()
{
	for y in $@
	do
		(
			cd `dirname "$y"`
			tar cf - `basename "$y"`
		) | (
			cd "$INTDIR/$PKGNAME/$PKGBASE/include"
			tar xvf -
		)
	done
}

copyLib()
{
	for x in $@
	do
		find "$OUTDIR/lib" -name "$LIBPREFIX"$x"$LIBEXT"\* | while read N
		do
			case "$N" in
			*$LIBEXT )
				echo not packaging "$N"
				;;
			* )
				copyLibFile "$N"
				;;
			esac
		done
		find "$OUTDIR/lib" -name $x.dll | while read N
		do
			copyLibFile "$N"
		done
	done
}

copyBin()
{
	for x in $@
	do
		find "$OUTDIR/bin" -name "$x" | while read N
		do
			copyBinFile "$N"
		done
	done
}

copyMan()
{
	for x in $@
	do
		for s in 1 8
		do
			find "$OUTDIR/man" -name "$x.$s*" | while read N
			do
				(
					cd "$OUTDIR/man"
					tar cf - `basename "$N"`
				) | (
					cd "$INTDIR/$PKGNAME/$PKGBASE/man/man$s"
					tar xvf -
				)
			done
		done
	done
}

copyTestBin()
{
	for x in $@
	do
		find "$OUTDIR/tests" -name "$x" | while read N
		do
			copyBinFile "$N"
		done
	done
}

copyIdl()
{
	for x in $@
	do
		cp ../../somidl/$x.idl "$INTDIR/$PKGNAME/$PKGBASE/include/$x.idl"
	done
}

rmdirs()
{
    find "$1" -type d | (
        RC=1
        while read N
        do
            if rmdir "$N" 2>/dev/null
            then
                RC=0
            fi
        done

        exit $RC
    )
}

for PKGNAME in somtk.rte somtk.comp somtk.dev
do
	find "$INTDIR/$PKGNAME" | while read N
	do
		if test -h "$N"
		then
			ls -ld "$N"
		else
			chmod +w "$N"
		fi
	done
	rm -rf "$INTDIR/$PKGNAME/$PKGBASE"
	mkdir -p "$INTDIR/$PKGNAME/$PKGBASE"
	mkdir "$INTDIR/$PKGNAME/$PKGBASE/include"
	mkdir "$INTDIR/$PKGNAME/$PKGBASE/bin"
	mkdir "$INTDIR/$PKGNAME/$PKGBASE/etc"
	mkdir "$INTDIR/$PKGNAME/$PKGBASE/$LIBDIRNAME"
	mkdir "$INTDIR/$PKGNAME/$PKGBASE/man"
	mkdir "$INTDIR/$PKGNAME/$PKGBASE/man/man1"
	mkdir "$INTDIR/$PKGNAME/$PKGBASE/man/man8"

	case $PKGNAME in
	somtk.comp )
		case `uname -s` in
		IRIX* )
			copyBin somcpp
			;;
		SunOS )
#			makeBinLink /usr/lib/cpp somcpp
			copyBin somcpp
			;;
		* )
			;;
		esac
		copyMan sc somipc
		copyBin sc somipc pdl
		cp ../../somtk/unix/somcorba.sh "$INTDIR/$PKGNAME/$PKGBASE/bin/somcorba"
		(
			cd "$INTDIR/$PKGNAME/$PKGBASE/bin"
			chmod +x somcorba
			ln -s somcorba somstars
			ln -s somcorba somxh
		)
		RTEROOT=$(cd "$INTDIR/somtk.rte"; find * -name libsom.so.* -type f | while read N; do dirname $N; done )
		ln -s "/$RTEROOT/libsom.so.1" "$INTDIR/$PKGNAME/$PKGBASE/lib/libsom.so"
		;;
	somtk.dev )
		if test -n "$HEADERSRC"
		then
			for F in somobj somcls somcm
			do
				cp  "$HEADERSRC"/$F.* "$INTDIR/$PKGNAME/$PKGBASE/include/"
			done
		fi
		copyIncFile ../../somkpub/include/*.h ../../somkpub/include/*.xh
		copyIdl somcls somobj somcm
		;;
	somtk.rte )
		copyLib som
		RTELIBDIR=usr/lib
		LIBCSO=

		for M in ` $OBJDUMP -p "$OUTDIR/bin/pdl" | grep NEEDED | while read A B
		do
			if test -z "$LIBCSO"
			then
				case "$A/$B" in
					NEEDED/libc.so.* )
						LIBCSO="$B"
						ldd "$OUTDIR/bin/pdl" | while read C D E F
						do
							if test "$B" = "$C"
							then
								if test -f "$E"
								then
									echo "$E"
								fi
							fi
						done
						;;
					* )
						;;
				esac
			fi
		done `
		do
			ls -ld "$M"
			N=
			while test "$N" != "$M"
			do
				N="$M"
				M=`echo "$M" | ../../toolbox/realpath.sh`
			done
			ls -ld "$M"
			if test ! -d "$M"
			then
				M=`dirname "$M"`
			fi
			RTELIBDIR=`echo $M | sed 's!^/!!' `
		done

		if test ! -d "/$RTELIBDIR"
		then
			RTELIBDIR=usr/lib
		fi

		mkdir -p "$INTDIR/$PKGNAME/$RTELIBDIR"
		mv "$INTDIR/$PKGNAME/$PKGBASE/lib/"* "$INTDIR/$PKGNAME/$RTELIBDIR"
		;;
	* )
		;;
	esac

	while rmdirs "$INTDIR/$PKGNAME"
	do
		date
	done

	if test "$STRIP" != ""
	then
		find "$INTDIR/$PKGNAME/$PKGBASE" -type f -name "lib*.so*" | while read SN
		do
			$STRIP "$SN"
		done
		find "$INTDIR/$PKGNAME/$PKGBASE" -type f -name "*.dll" | while read SN
		do
			$STRIP "$SN"
		done
		for APP in irdump pdl regimpl somdchk somdd somdsvr somipc somossvr
		do
			if test -x "$INTDIR/$PKGNAME/$PKGBASE/bin/$APP"
			then
				$STRIP "$INTDIR/$PKGNAME/$PKGBASE/bin/$APP"
			fi
		done
	fi

	if test -d "$INTDIR/$PKGNAME"
	then
		find "$INTDIR/$PKGNAME" | while read N
		do
			if test -h "$N"
			then
				ls -ld "$N"
			else
				chmod -w "$N"
			fi
		done
	fi
done

