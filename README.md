This is a SQLite extension that provides integration with the libexif library. After the extension is loaded, two new SQL functions become available:

```
FILE_EXIF_READ(PATHNAME, IFD, TAG): retrieve the value of Exif tag IFD/TAG
BLOB_EXIF_READ(BLOB, IFD, TAG)    : same as FILE_EXIF, but reads Exif contents from a BLOB instead of a file
```

Usage example from the SQLite shell:

```
.load "sqlite3ext_exif-1"

SELECT FILE_EXIF_READ('20231030_150218.jpg', 'EXIF_IFD_0',    'Orientation');      -- returns a string like 'Top-left'
SELECT FILE_EXIF_READ('20231030_150218.jpg', 'EXIF_IFD_EXIF', 'DateTimeOriginal'); -- returns a string like '2023:10:30 15:02:18'
SELECT FILE_EXIF_READ('20231030_150218.jpg', 'EXIF_IFD_EXIF', 'FNumber');		   -- returns a string like 'F/2.2'
SELECT FILE_EXIF_READ('20231030_150218.jpg', 'EXIF_IFD_EXIF', 'ISOSpeedRatings');  -- returns a string like '40'
SELECT FILE_EXIF_READ('20231030_150218.jpg', 'EXIF_IFD_EXIF', 'ExposureTime');	   -- returns a string like '1/1379 sec.'
SELECT FILE_EXIF_READ('20231030_150218.jpg', 'EXIF_IFD_GPS',  'GPSLatitude');	   -- returns a string like '35, 18, 21.89599'
SELECT FILE_EXIF_READ('20231030_150218.jpg', 'EXIF_IFD_GPS',  'GPSLatitudeRef');   -- returns a string like 'N'
SELECT FILE_EXIF_READ('20231030_150218.jpg', 'EXIF_IFD_GPS',  'GPSLongitude');	   -- returns a string like '139, 29, 1.92542'
SELECT FILE_EXIF_READ('20231030_150218.jpg', 'EXIF_IFD_GPS',  'GPSLongitudeRef');  -- returns a string like 'E'
SELECT FILE_EXIF_READ('20231030_150218.jpg', 'EXIF_IFD_GPS',  'GPSAltitude');	   -- returns a string like '42'
SELECT FILE_EXIF_READ('20231030_150218.jpg', 'EXIF_IFD_GPS',  'GPSAltitudeRef');   -- returns a string like 'Sea level'
```

See [test/test001-basic.sql](test/test001-basic.sql) for a few more usage examples.

### How to compile

`libexif` is a mandatory dependency and must be already be installed on the system; and command `gcc ... -lexif` must not fail.
`libexif` is LGPL and can be built from source code, which is available [here](https://github.com/libexif/libexif/).

Once this preliminary is satisfied, proceed with the usual configure/make sequence:


```
	./configure
	make all
	ls -l src/.libs/sqlite3ext_exif*.{so,dll} # binary is generated in this folder
```

### How to compile (statically link libexif)

It is possible to perform an alternative build that links libexif statically:

```
	./configure --with-libexifstatic
	make all
	ls -l src/.libs/sqlite3ext_exif*.{so,dll} # binary is generated in this folder
	ldd src/.libs/sqlite3ext_exif*.{so,dll}   # libexif will not appear in the dependencies list
```

### How to compile (statically link everything)

The following build script compiled successfully a .so module with no dynamic dependencies at all:

```
make all CFLAGS="-fPIC -static" LIBS=" -Wl,-Bstatic,-lsqlite3,-lexif,-Bdynamic"

gcc -shared -nodefaultlibs \
  -o src/.libs/sqlite3ext_exif.so \
  -Wl,--whole-archive,-L./src/.libs,-l:sqlite3ext_exif.a,--no-whole-archive \
  -Wl,-Bstatic,-lsqlite3,-lexif,-Bdynamic

ldd src/.libs/sqlite3ext_exif.so
```

It's been tested on this Linux setup:

```
$ uname -a

Linux mytestmachine 6.12.63+deb13-amd64 #1 SMP PREEMPT_DYNAMIC Debian 6.12.63-1 (2025-12-30) x86_64 GNU/Linux

$ gcc --version

gcc (Debian 14.2.0-19) 14.2.0
Copyright (C) 2024 Free Software Foundation, Inc.
This is free software; see the source for copying conditions.  There is NO
warranty; not even for MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
```

### How to run the test suite

```
	./configure
	make all  # compile binaries before running the test
	make check # after the tests are run, inspect test-suite.log and test001-output
```

The tests have been confirmed to pass on this MinGW64 environment in Windows:

```
	# OS is: Microsoft Windows 11 Home 10.0.26200 build 26200

	$ uname -a
	MINGW64_NT-10.0-26200 PC-ROSS 3.6.4-23a25d49.x86_64 2025-07-16 16:15 UTC x86_64 Msys
	
	$ which gcc
	/mingw64/bin/gcc
	
	$ gcc --version
	gcc.exe (Rev8, Built by MSYS2 project) 15.1.0

	$ autoconf --version
	autoconf (GNU Autoconf) 2.72

	$ make --version
	GNU Make 4.4.1
	Built for x86_64-pc-msys
```

and on this Linux VM:

```
$ uname -a

Linux mytestmachine 6.12.63+deb13-amd64 #1 SMP PREEMPT_DYNAMIC Debian 6.12.63-1 (2025-12-30) x86_64 GNU/Linux

$ gcc --version

gcc (Debian 14.2.0-19) 14.2.0
Copyright (C) 2024 Free Software Foundation, Inc.
This is free software; see the source for copying conditions.  There is NO
warranty; not even for MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
```

