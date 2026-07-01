#!/bin/sh -ex

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

mkdir -p "$ROOTDIR/bin" "$ROOTDIR/lib" "$ROOTDIR/include"

for d in h xh
do
	cp ../../somkpub/include/*.$d  "$ROOTDIR/include"
done

for d in somobj somcls somcm
do
	cp ../../somidl/$d.idl "$ROOTDIR/include"
	cp ../../somidl/$PLATFORM/$d.* "$ROOTDIR/include"
done

for d in sc pdl somipc somcpp
do
	cp "$OUTDIR/bin/$d"  "$ROOTDIR/bin/$d"
done

(
	cd "$OUTDIR/lib"
	tar cf - libsom.*
) | (
	cd "$ROOTDIR/lib"
	tar xvf -
)

(
	cd "$ROOTDIR"
	find * | xargs ls -ld
)

case "$MACOSX_DEPLOYMENT_TARGET" in
10.2 )
		(
			cd "$ROOTDIR"
			tar cf - *
		) | (
			gzip > "$OUTDIR_DIST/somlite-$VERSION-$PLATFORM.tar.gz"
		)
	;;
* )
	if ../../toolbox/pkgtool.sh gtar
	then
		GTAR=`../../toolbox/pkgtool.sh gtar`

		if test "$GTAR" != ""
		then
			(
				cd "$ROOTDIR"
				$GTAR --owner=0 --group=0 --mode=-w --create --file - *
			) | (
				gzip > "$OUTDIR_DIST/somlite-$VERSION-$PLATFORM.tar.gz"
			)
		fi
	fi
	;;
esac

echo done
