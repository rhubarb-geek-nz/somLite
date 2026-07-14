#!/bin/sh -e

. ../version.sh

if test "$VERSION" = ""
then
	VERSION=0.0.0.1
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
		* )
			unknown option $d
			exit 1
		esac
		FLAG=
	fi
done

mkdir -p "$INTDIR"

ROOTDIR="$INTDIR/root"

rm -rf "$ROOTDIR"

mkdir "$ROOTDIR"

DESTDIR="$ROOTDIR" ../pkg/install.sh

(
	set -e
	cd "$ROOTDIR"
	tar --owner=0 --group=0 --mode=-w --create --file - $(find * -type f) $(find * -type l)
) | bzip2 > "$OUTDIR_DIST/somlite-$VERSION-$PLATFORM.tar.bz2"

echo done
