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

which()
{
	(
		IFS=':'
		for d in $PATH
		do
			if test -x "$d/$1" && test -f "$d/$1"
			then
				echo "$d/$1"
				return 0
			fi
		done

		return 1
	)

	return $?
}

OSNAME=$(uname | tr '[:upper:]' '[:lower:]')
OSVERS=$(uname -r)

mkdir -p "$INTDIR"

ROOTDIR="$INTDIR/root"

rm -rf "$ROOTDIR"

mkdir "$ROOTDIR"

DESTDIR="$ROOTDIR" ../pkg/install.sh

(
	set -e
	cd "$ROOTDIR"
	tar --owner=0 --group=0 --create --file - $(find * -type f) $(find * -type l)
) | bzip2 > "$OUTDIR_DIST/somlite-$VERSION-$OSNAME$OSVERS.tar.bz2"

if which pkgbuild
then
	echo ROOTDIR=$ROOTDIR

	rm -rf "$INTDIR/sdk" "$INTDIR/tools"

	mkdir "$INTDIR/sdk" "$INTDIR/tools"

	PREFIX=$(cd $ROOTDIR; find * -type d -name bin | while read N; do M=$(dirname $N); echo "/$M"; done)

	echo PREFIX=$PREFIX

	mv "$ROOTDIR$PREFIX/man" "$INTDIR/tools/man"
	mv "$ROOTDIR$PREFIX/bin" "$INTDIR/tools/bin"
	mv "$ROOTDIR$PREFIX/include" "$INTDIR/sdk/include"

	find "$INTDIR/tools/man/man1" -name "*.1" -type f | xargs -n 1 gzip

	mkdir "$INTDIR/sdk/lib"

	mv "$ROOTDIR$PREFIX/lib/libsom.dylib" "$INTDIR/sdk/lib/libsom.dylib"

	while read SRCDIR IDENT PKG
	do
		pkgbuild --root "$SRCDIR" --identifier "$IDENT" --version "$VERSION" --install-location "$PREFIX" "$OUTDIR_DIST/$PKG-$VERSION-$OSNAME$OSVERS.pkg"
	done << EOF
$ROOTDIR$PREFIX nz.geek.rhubarb.somlite.rte somlite-rte
$INTDIR/sdk nz.geek.rhubarb.somlite.sdk somlite-sdk
$INTDIR/tools nz.geek.rhubarb.somlite.tools somlite-tools
EOF

	rm -rf "$INTDIR/sdk" "$INTDIR/tools"
fi

ls -l "$OUTDIR_DIST"

rm -rf "$ROOTDIR"

echo done
