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

test "$0" = "makedefs/unix/makeall.sh"

case "$(uname)" in
	Linux )
		for d in all test dist
		do
			make $d PREFIX=/usr/lib/somlite
		done
		;;
	Darwin )
		make
		make test
		makedefs/darwin/makeall.sh
		makedefs/darwin/merge.sh
		make dist PREFIX=/usr/local/share/somlite
		;;
	NetBSD )
		for d in all test dist
		do
			make $d PREFIX=/usr/pkg/somlite
		done
		;;
	FreeBSD )
		for d in all test dist
		do
			make $d PREFIX=/usr/local/somlite
		done
		;;
	OpenBSD )
		for d in all test dist
		do
			make $d PREFIX=/usr/local/somlite
		done
		;;
	* )
		make
		make test
		make dist
		;;
esac
