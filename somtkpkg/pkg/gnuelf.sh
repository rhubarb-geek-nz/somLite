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

. ../version.sh

if test "$VERSION" = ""
then
	VERSION=0.0.0.1
fi

if test -z "$MAINTAINER"
then
	if git config user.email > /dev/null
	then
		MAINTAINER=$(git config user.email)
	else
		echo MAINTAINER not set 1>&2
		false
	fi
fi

FLAG=

INTDIR=.

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
		-p )
			PREFIX="$d"
			;;
		* )
			unknown option $d
			exit 1
		esac
		FLAG=
	fi
done

if test -z "$PREFIX"
then
	PKGBASE=usr/local
else
	PKGBASE=$(echo "$PREFIX" | sed 's/^\///')
fi

../pkg/mkfs.sh -d "$OUTDIR_DIST" -t "$INTDIR" -r "$OUTDIR" -h "../../somidl/$PLATFORM" -p "$PREFIX"

find "$INTDIR" -print | xargs ls -ld

RTEPREFIX=$(cd $INTDIR/somtk.rte; find * -name "libsom.so.*" | while read N; do dirname $N; break; done)
PKGPREFIX=$(dirname $PKGBASE)

PKGPREFIX="$RTEPREFIX" ../../toolbox/dir2rpm.sh "$INTDIR" "$INTDIR/somtk.rte" "$OUTDIR_DIST" <<EOF
Summary: somLite RTE
Name: somlite-rte
Version: $VERSION
Release: 1
Group: Applications/System
License: GPL
Prefix: /$RTEPREFIX

%description
Runtime Environment for somLite

EOF

PKGPREFIX="$PKGPREFIX" ../../toolbox/dir2rpm.sh "$INTDIR" "$INTDIR/somtk.comp" "$OUTDIR_DIST" <<EOF
Summary: somLite Compiler
Name: somlite-comp
Version: $VERSION
Release: 1
Group: Applications/System
License: GPL
Prefix: /$PKGPREFIX

%description
IDL Compiler for somLite

EOF

PKGPREFIX="$PKGPREFIX" ../../toolbox/dir2rpm.sh "$INTDIR" "$INTDIR/somtk.dev" "$OUTDIR_DIST" <<EOF
Summary: somLite Development Library
Name: somlite-dev
Version: $VERSION
Release: 1
Group: Applications/System
BuildArch: noarch
License: GPL
Prefix: /$PKGPREFIX

%description
Developer library for somLite

EOF

DPKGARCH=`../../toolbox/pkgtool.sh dpkg-arch "$OUTDIR/bin/somipc"`

PKGPREFIX="$PKGPREFIX" ../../toolbox/dir2deb.sh "$INTDIR" "$INTDIR/somtk.comp" "$OUTDIR_DIST" <<EOF
Package: somlite-comp
Version: $VERSION
Architecture: $DPKGARCH
Maintainer: $MAINTAINER
Section: misc
Priority: extra
Description: somLite compiler
 IDL compiler for somLite
 .
EOF

PKGPREFIX="$RTEPREFIX" ../../toolbox/dir2deb.sh "$INTDIR" "$INTDIR/somtk.rte" "$OUTDIR_DIST" <<EOF
Package: somlite-rte
Version: $VERSION
Architecture: $DPKGARCH
Maintainer: $MAINTAINER
Section: misc
Priority: extra
Description: somLite RTE
 Run Time Environment for somLite
 .
EOF

PKGPREFIX="$PKGPREFIX" ../../toolbox/dir2deb.sh "$INTDIR" "$INTDIR/somtk.dev" "$OUTDIR_DIST" <<EOF
Package: somlite-dev
Version: $VERSION
Architecture: all
Maintainer: $MAINTAINER
Section: misc
Priority: extra
Description: somLite Development Library
 Library and headers for somLite
 .
EOF

../../toolbox/dir2bsd.sh "$INTDIR" "$INTDIR/somtk.rte" "$OUTDIR_DIST" <<EOF
somlite-rte
$VERSION

$RTEPREFIX
somLite Runtime Environment
Runtime Environment for somLite
EOF

../../toolbox/dir2bsd.sh "$INTDIR" "$INTDIR/somtk.comp" "$OUTDIR_DIST" <<EOF
somlite-comp
$VERSION

$PKGPREFIX
somLite IDL Compiler
IDL Compiler for somLite
EOF

../../toolbox/dir2bsd.sh "$INTDIR" "$INTDIR/somtk.dev" "$OUTDIR_DIST" <<EOF
somlite-dev
$VERSION

$PKGPREFIX
somLite Development Library
Library and headers for somLite
EOF

while read BASEDIR PKGNAME PKGBASE
do
	../../toolbox/slackpkg.sh "$INTDIR" "$BASEDIR" "$OUTDIR_DIST" << EOF
$PKGNAME
$VERSION
$PKGBASE
$PKGNAME: somLite - Portable implementation of SOM
$PKGNAME:
$PKGNAME: A portable clean-room implementation of IBM's SOM.
$PKGNAME: 
$PKGNAME: 
$PKGNAME: 
$PKGNAME: 
$PKGNAME: 
$PKGNAME: 
$PKGNAME: 
$PKGNAME: 
EOF
done << EOF2
$INTDIR/somtk.dev	somlite-dev		$PKGPREFIX
$INTDIR/somtk.comp	somlite-comp	$PKGPREFIX
$INTDIR/somtk.rte	somlite-rte		$RTEPREFIX
EOF2

for d in somtk.rte somtk.comp somtk.dev
do
	if test -d "$INTDIR/$d"
	then
		chmod -R +w "$INTDIR/$d"
		rm -rf "$INTDIR/$d"
	fi
done

if test "$GTAR" = ""
then
	if ../../toolbox/pkgtool.sh gtar
	then
		GTAR=`../../toolbox/pkgtool.sh gtar`
	fi
fi

(
	set -e

	MACHINE="$PLATFORM"

	if test -f /etc/os-release
	then
		ARCH=`uname -m`
		ID=`.  /etc/os-release ; echo $ID`
		VERS=`.  /etc/os-release ; echo $VERSION_ID`
		for d in `.  /etc/os-release ; echo $ID $ID_LIKE`
		do
			case "$d" in
				debian )
					ARCH=`dpkg --print-architecture`
					;;
				* )
					;;
			esac
		done
		MACHINE="$ID-$VERS-$ARCH"
	fi

	(
		cd "$OUTDIR_DIST"

		for d in rpm deb pkg tgz
		do
			FILES=`echo *.$d`

			if ls $FILES >/dev/null 2>/dev/null
			then
				if test -z "$GTAR"
				then
					tar cf - $FILES | gzip > "somlite-$VERSION-$d-$MACHINE.tar.gz"
				else
					$GTAR --owner=0 --group=0 --create --gzip --file "somlite-$VERSION-$d-$MACHINE.tar.gz" $FILES
				fi

				rm $FILES
			fi
		done
	)

	(
		set -e

		cd "$OUTDIR"

		mkdir tmp tmp/bin tmp/lib tmp/include tmp/man tmp/man/man1

		cp include/* tmp/include

		for d in sc somipc somcpp pdl
		do
			if test -f "bin/$d"
			then
				cp "bin/$d" "tmp/bin/$d"
			fi
			if test -f "man/$d.1.gz"
			then
				cp "man/$d.1.gz" "tmp/man/man1/$d.1.gz"
			fi
		done

		(
			set -e

			cd lib

			tar cf - libsom.*
		) | (
			set -e

			cd tmp/lib

			tar xf -
		)

		chmod -R go-w tmp
		chmod -R go+r tmp
		chmod -x tmp/lib/libsom.*

		if test -z "$GTAR"
		then
			(
				cd tmp
				tar cf - $(find * -type f) $(find * -type l)
			) | gzip > "dist/somlite-$VERSION-$MACHINE.tar.gz"
		else
			$GTAR --owner=0 --group=0 --create --gzip --file "dist/somlite-$VERSION-$MACHINE.tar.gz" -C tmp $(cd tmp; find * -type f ; find * -type l)
		fi

		rm -rf tmp
	)
)
