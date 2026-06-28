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
		MAINTAINER="$(git config user.email)"
	else
		echo MAINTAINER not set 1>&2
		false
	fi
fi

test -n "$PKGROOT"

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
		* )
			unknown option $d
			exit 1
		esac
		FLAG=
	fi
done

../pkg/mkfs.sh -d "$OUTDIR_DIST" -t "$INTDIR" -r "$OUTDIR" -h "../../somidl/$PLATFORM"

find "$INTDIR" -print | xargs ls -ld

RTEROOT=$(cd $INTDIR/somtk.rte; find * -name "libsom.so.*" | while read N; do dirname $N; break; done)

PKGROOT="$RTEROOT" ../../toolbox/dir2rpm.sh "$INTDIR" "$INTDIR/somtk.rte" "$OUTDIR_DIST" <<EOF
Summary: somLite RTE
Name: somlite-rte
Version: $VERSION
Release: 1
Group: Applications/System
License: GPL
Prefix: /$RTEROOT

%description
Runtime Environment for somLite

EOF

../../toolbox/dir2rpm.sh "$INTDIR" "$INTDIR/somtk.comp" "$OUTDIR_DIST" <<EOF
Summary: somLite Compiler
Name: somlite-comp
Version: $VERSION
Release: 1
Group: Applications/System
License: GPL
Prefix: /$PKGROOT

%description
IDL Compiler for somLite

EOF

../../toolbox/dir2rpm.sh "$INTDIR" "$INTDIR/somtk.dev" "$OUTDIR_DIST" <<EOF
Summary: somLite Development Library
Name: somlite-dev
Version: $VERSION
Release: 1
Group: Applications/System
BuildArch: noarch
License: GPL
Prefix: /$PKGROOT

%description
Developer library for somLite

EOF

DPKGARCH=`../../toolbox/pkgtool.sh dpkg-arch "$OUTDIR/bin/somipc"`

../../toolbox/dir2deb.sh "$INTDIR" "$INTDIR/somtk.comp" "$OUTDIR_DIST" <<EOF
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

PKGROOT="$RTEROOT" ../../toolbox/dir2deb.sh "$INTDIR" "$INTDIR/somtk.rte" "$OUTDIR_DIST" <<EOF
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

../../toolbox/dir2deb.sh "$INTDIR" "$INTDIR/somtk.dev" "$OUTDIR_DIST" <<EOF
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

$PKGROOT
somLite Runtime Environment
Runtime Environment for somLite
EOF

../../toolbox/dir2bsd.sh "$INTDIR" "$INTDIR/somtk.comp" "$OUTDIR_DIST" <<EOF
somlite-comp
$VERSION

$PKGROOT
somLite IDL Compiler
IDL Compiler for somLite
EOF

../../toolbox/dir2bsd.sh "$INTDIR" "$INTDIR/somtk.dev" "$OUTDIR_DIST" <<EOF
somlite-dev
$VERSION
somlite-comp
$PKGROOT
somLite Development Library
Library and headers for somLite
EOF

while read BASEDIR PKGNAME
do
	../../toolbox/slackpkg.sh "$INTDIR" "$BASEDIR" "$OUTDIR_DIST" << EOF
$PKGNAME
$VERSION
$PKGROOT
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
$INTDIR/somtk.dev	somlite-dev
$INTDIR/somtk.comp	somlite-comp
$INTDIR/somtk.rte	somlite-rte
EOF2

for d in somtk.rte somtk.comp somtk.dev
do
	if test -d "$INTDIR/$d"
	then
		chmod -R +w "$INTDIR/$d"
		rm -rf "$INTDIR/$d"
	fi
done
