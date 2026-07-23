#!/bin/sh -ex
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

#  This script is intended as the overarching build script and the additional
#  arguments will be passed to make
#
#  The recommendations are
#
#  Darwin  - makedefs/unix/makeall.sh PREFIX=/usr/local/share/somlite
#  Linux   - makedefs/unix/makeall.sh PREFIX=/usr/lib/somlite
#  NetBSD  - makedefs/unix/makeall.sh PREFIX=/usr/pkg/somlite
#  OpenBSD - makedefs/unix/makeall.sh PREFIX=/usr/local/somlite
#  FreeBSD - makedefs/unix/makeall.sh PREFIX=/usr/local/somlite

test "$0" = "makedefs/unix/makeall.sh"

case "$(uname)" in
	Darwin )
		make $@
		make test $@
		makedefs/darwin/makeall.sh $@
		makedefs/darwin/merge.sh $@
		make dist $@
		;;
	* )
		for d in all test dist
		do
			make $d $@
		done
		;;
esac
