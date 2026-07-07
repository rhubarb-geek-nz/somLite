# rhubarb-geek-nz/somLite
This is a fork of [somFree](https://somfree.sf.net) which I wrote over 20 years ago as a clone of [IBM SOM](https://en.wikipedia.org/wiki/IBM_System_Object_Model) 2.1 with bits of 3.0.

Historically both the [OS/2 Work Place Shell](https://en.wikipedia.org/wiki/Workplace_Shell) and [Apple's OpenDoc](https://en.wikipedia.org/wiki/OpenDoc) were built on bare SOM without DSOM and the IR.

This project is to restore the simplicity of the single `som.dll`.

## Build on Linux

With the build environment installed.

```
$ make
$ make test
$ make dist
```

This should result in a platform specific package.

## Build on Windows

The build is set up to make code signing easy.

```
C:> make
C:> make test
C:> make sign
C:> make dist
```

A signed MSI is the final output.

## What has gone?

The following were removed

* TypeCodes and Interface Repository, all though it worked very well for what it was, it was still `CORBA 1.1`
* `DSOM`, the wire protocol was `CORBA 2.0 IIOP`, but interfaces being `CORBA 1.1` were a mismatch
* Any attempt at reference counting
* The migrated `SOMDObject` methods
* `somcpp` used the Visual Studio `CL.EXE /E` for the pre-preprocessr, this is replaced by one written in C#
* `Subversion`, it is now hosted in `git`
* All the rest

## What was kept?

The samples from the first couple of chapters of Christina Lau's book [Object-Oriented Programming Using SOM and DSOM](https://www.amazon.com/Object-Oriented-Programming-Using-SOM-DSOM/dp/0471131237) remain.

## Running the samples

Running the samples can be done from a master Makefile, on Windows this looks like

```
C:> nmake -f Makefile.Win32 "SOMBASE=%ProgramFiles(x86)%\rhubarb-geek-nz\somLite"
```

On Linux this would be

```
$ make -f Makefile.Linux "SOMBASE=/usr/lib/somlite"
```

## Rewrite of somcpp

Instead of using `CL.EXE /E` a new implementation in [C#](toolbox2/somcpp/somcpp.cs) using [rhubarb-geek-nz.cpp](https://github.com/rhubarb-geek-nz/cpp) is used. This is compiled using `net48`.

## Packaging on Linux

The shared library is installed in a platform specific directory, ideally the same location as `libc.so`. The symbolic link has the same name as the SONAME.

```
$ dpkg-deb -c somlite-rte_1.0_armhf.deb
lrwxrwxrwx root/root         0 2026-06-28 01:16 usr/lib/arm-linux-gnueabihf/libsom.so.1 -> libsom.so.1.0
-r-xr-xr-x root/root    146728 2026-06-28 01:16 usr/lib/arm-linux-gnueabihf/libsom.so.1.0
```

Similarly

```
$ rpm -qlvp somlite-rte-1.0-1.aarch64.rpm
lrwxrwxrwx    1 root     root                       13 Jun 28 00:36 /usr/lib64/libsom.so.1 -> libsom.so.1.0
-r-xr-xr-x    1 root     root                   225152 Jun 28 00:36 /usr/lib64/libsom.so.1.0
```

and

```
$ tar tvfz somlite-rte-1.0-i586-1_slack15.0.tgz
dr-xr-xr-x root/root         0 2026-07-03 01:23 ./
-r-xr-xr-x root/root    127060 2026-07-03 01:23 lib/libsom.so.1.0
-rwxr-xr-x root/root        78 2026-07-03 01:23 install/doinst.sh
-rw-r--r-- root/root       243 2026-07-03 01:23 install/slack-desc
```


The compilers lay on top with a symbolic link to the shared library for compile time linking using the same architecture as the compilers.

```
$ dpkg-deb -c somlite-comp_1.0_armhf.deb
dr-xr-xr-x root/root         0 2026-06-28 01:16 usr/lib/somlite/
dr-xr-xr-x root/root         0 2026-06-28 01:16 usr/lib/somlite/lib/
lrwxrwxrwx root/root         0 2026-06-28 01:16 usr/lib/somlite/lib/libsom.so -> /usr/lib/arm-linux-gnueabihf/libsom.so.1
dr-xr-xr-x root/root         0 2026-06-28 01:16 usr/lib/somlite/man/
dr-xr-xr-x root/root         0 2026-06-28 01:16 usr/lib/somlite/man/man1/
-r--r--r-- root/root       423 2026-06-28 01:16 usr/lib/somlite/man/man1/somipc.1.gz
-r--r--r-- root/root       324 2026-06-28 01:16 usr/lib/somlite/man/man1/sc.1.gz
dr-xr-xr-x root/root         0 2026-06-28 01:16 usr/lib/somlite/bin/
lrwxrwxrwx root/root         0 2026-06-28 01:16 usr/lib/somlite/bin/somxh -> somcorba
-r-xr-xr-x root/root      4006 2026-06-28 01:16 usr/lib/somlite/bin/sc
-r-xr-xr-x root/root     70528 2026-06-28 01:16 usr/lib/somlite/bin/pdl
-r-xr-xr-x root/root    408136 2026-06-28 01:16 usr/lib/somlite/bin/somipc
lrwxrwxrwx root/root         0 2026-06-28 01:16 usr/lib/somlite/bin/somstars -> somcorba
-r-xr-xr-x root/root      1392 2026-06-28 01:16 usr/lib/somlite/bin/somcorba
```

The headers and idl are platform neutral

```
$ dpkg-deb -c somlite-dev_1.0_all.deb
dr-xr-xr-x root/root         0 2026-06-28 01:16 usr/lib/somlite/
dr-xr-xr-x root/root         0 2026-06-28 01:16 usr/lib/somlite/include/
-r--r--r-- root/root     39784 2026-06-28 01:16 usr/lib/somlite/include/somcm.xh
-r--r--r-- root/root      1073 2026-06-27 11:32 usr/lib/somlite/include/somltype.h
-r--r--r-- root/root      2742 2026-06-27 11:32 usr/lib/somlite/include/somcdev.h
-r--r--r-- root/root      1428 2026-06-27 11:32 usr/lib/somlite/include/som.h
-r--r--r-- root/root      3093 2026-06-28 01:16 usr/lib/somlite/include/somcm.idl
-r--r--r-- root/root      1331 2026-06-27 11:32 usr/lib/somlite/include/somnames.h
-r--r--r-- root/root      6035 2026-06-27 11:32 usr/lib/somlite/include/somcorba.h
-r--r--r-- root/root      2240 2026-06-27 11:32 usr/lib/somlite/include/somplatf.h
-r--r--r-- root/root      2013 2026-06-27 11:32 usr/lib/somlite/include/somtypes.h
-r--r--r-- root/root     15286 2026-06-27 11:32 usr/lib/somlite/include/somapi.h
-r--r--r-- root/root       860 2026-06-27 11:32 usr/lib/somlite/include/som.xh
-r--r--r-- root/root     29712 2026-06-28 01:16 usr/lib/somlite/include/somcm.h
-r--r--r-- root/root     63796 2026-06-28 01:16 usr/lib/somlite/include/somcls.h
-r--r--r-- root/root     35261 2026-06-28 01:16 usr/lib/somlite/include/somobj.h
-r--r--r-- root/root      1811 2026-06-27 11:32 usr/lib/somlite/include/sombtype.h
-r--r--r-- root/root     26830 2026-06-28 01:16 usr/lib/somlite/include/somobj.xh
-r--r--r-- root/root     67038 2026-06-28 01:16 usr/lib/somlite/include/somcls.xh
-r--r--r-- root/root     54406 2026-06-28 01:16 usr/lib/somlite/include/somcls.api
-r--r--r-- root/root      6473 2026-06-28 01:16 usr/lib/somlite/include/somobj.idl
-r--r--r-- root/root      8272 2026-06-28 01:16 usr/lib/somlite/include/somcls.idl
```

## Packaging on Darwin

Darwin did not include the MacOS X packaging or frameworks. If you need those then I recommend the original [somFree](https://sourceforge.net/projects/somfree/files/MacOS/) which uses formal packing, multiple architectures using lipo and assembled into a framework.


```
$ tar tvfz somlite-1.0-powerpc-apple-darwin7.0.0.tar.gz
dr-xr-xr-x root/wheel        0 2026-07-02 07:00:10 bin/
-r-xr-xr-x root/wheel    16496 2026-07-02 07:00:10 bin/pdl
-r-xr-xr-x root/wheel     4006 2026-07-02 07:00:10 bin/sc
-r-xr-xr-x root/wheel     2017 2026-07-02 07:00:11 bin/somcpp
-r-xr-xr-x root/wheel   482152 2026-07-02 07:00:10 bin/somipc
dr-xr-xr-x root/wheel        0 2026-07-02 07:00:10 include/
-r--r--r-- root/wheel     1428 2026-07-02 07:00:09 include/som.h
-r--r--r-- root/wheel      860 2026-07-02 07:00:10 include/som.xh
-r--r--r-- root/wheel    15286 2026-07-02 07:00:09 include/somapi.h
-r--r--r-- root/wheel     1811 2026-07-02 07:00:09 include/sombtype.h
-r--r--r-- root/wheel     2742 2026-07-02 07:00:09 include/somcdev.h
-r--r--r-- root/wheel    54406 2026-07-02 07:00:10 include/somcls.api
-r--r--r-- root/wheel    63796 2026-07-02 07:00:10 include/somcls.h
-r--r--r-- root/wheel     8272 2026-07-02 07:00:10 include/somcls.idl
-r--r--r-- root/wheel    67038 2026-07-02 07:00:10 include/somcls.xh
-r--r--r-- root/wheel    29712 2026-07-02 07:00:10 include/somcm.h
-r--r--r-- root/wheel     3093 2026-07-02 07:00:10 include/somcm.idl
-r--r--r-- root/wheel    39784 2026-07-02 07:00:10 include/somcm.xh
-r--r--r-- root/wheel     6035 2026-07-02 07:00:09 include/somcorba.h
-r--r--r-- root/wheel     1073 2026-07-02 07:00:09 include/somltype.h
-r--r--r-- root/wheel     1331 2026-07-02 07:00:09 include/somnames.h
-r--r--r-- root/wheel    35261 2026-07-02 07:00:10 include/somobj.h
-r--r--r-- root/wheel     6473 2026-07-02 07:00:10 include/somobj.idl
-r--r--r-- root/wheel    26830 2026-07-02 07:00:10 include/somobj.xh
-r--r--r-- root/wheel     2240 2026-07-02 07:00:09 include/somplatf.h
-r--r--r-- root/wheel     2013 2026-07-02 07:00:09 include/somtypes.h
dr-xr-xr-x root/wheel        0 2026-07-02 07:00:11 lib/
-r-xr-xr-x root/wheel   162080 2026-07-02 06:56:51 lib/libsom.1.0.dylib
lr-xr-xr-x root/wheel        0 2026-07-02 07:00:11 lib/libsom.1.dylib -> libsom.1.0.dylib
-r-xr-xr-x root/wheel    16880 2026-07-02 06:59:01 lib/libsom.dylib
```

## Packaging on FreeBSD

Native packages are created on FreeBSD

```
$ tar tvfz somlite-rte-1.0.0.pkg
-rw-r--r--  0 root   wheel     464 Jan  1  1970 +COMPACT_MANIFEST
-rw-r--r--  0 root   wheel     851 Jan  1  1970 +MANIFEST
lrwxr-xr-x  0 root   wheel       0 Jul  3 18:01 /lib/libsom.so.1 -> libsom.so.1.0
-r-xr-xr-x  0 root   wheel  223472 Jul  3 18:01 /lib/libsom.so.1.0
```

The remainder, somlite-comp-1.0.0.pkg and somlite-dev-1.0.0.pkg, install into /usr/local/somlite.

## Packaging on NetBSD

Native packages are created on NetBSD

```
$ tar tvfz somlite-rte-1.0.tgz
-rw-r--r--  0 root   wheel     204 Jul  2 22:20 +CONTENTS
-r--r--r--  0 root   wheel      28 Jul  2 22:20 +COMMENT
-r--r--r--  0 root   wheel      32 Jul  2 22:20 +DESC
-rw-r--r--  0 root   wheel     127 Jul  2 22:20 +BUILD_INFO
-r-xr-xr-x  0 root   wheel  164184 Jul  2 22:20 libsom.so.1.0
lrwxr-xr-x  0 root   wheel       0 Jul  2 22:20 libsom.so.1 -> libsom.so.1.0
```

These install into /usr/lib. the remainder install into /usr/pkg/somlite.

## Packagine on OpenBSD

Native packages are created on OpenBSD

```
$ tar tvfz somlite-rte-1.0.tgz
-r--r--r--  1 root     wheel          283 Jul  3 18:42 +CONTENTS
-r--r--r--  1 root     wheel          111 Jul  3 18:42 +DESC
-r-xr-xr-x  1 root     bin         254248 Jan  1  1970 libsom.so.1.0
lrwxr-xr-x  1 root     wheel            0 Jul  3 18:42 libsom.so.1 -> libsom.so.1.0
```

These install into /usr/lib. the remainder install into /usr/local/somlite.

## Postscript
I found the memory allocation rules for full SOM 3.0 very onerous and in the days of managed and reference counted languages and appear arcane. Microsoft's COM has sticter rules and there is rarely doubt about who owns what. After some Objective-C programming on Mac OS X I was struck with how similar it was to SOM, but with the difference that SOM worked across multiple languages. Objective-C had the advantage that it could add reference counting at the compiler stage. This is for those of you who think the system should have an object model at the binary layer for compiled native code, where you have the freedom to call `SOMClass::somLoadClassFile` to extend your application.

## Contributions

The goal of this project is to be as close to SOM 2.1 som.dll as reasonable. If there is any major difference in the behaviour then I welcome contributions, but make them small. Each PR should be about a single behaviour that is different so it can be evaluated on its own merits.
