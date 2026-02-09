# -*- coding: utf-8 -*-

if [ ! -f "${srcdir}/test/test001-basic.sql" ] ; then exit 99 ; fi

if [ -f "./src/.libs/sqlite3ext_exif-1.dll" ] ; then
	libtotest="./src/.libs/sqlite3ext_exif-1.dll"
elif [ -f "./src/.libs/sqlite3ext_exif.so" ] ; then
	libtotest="./src/.libs/sqlite3ext_exif"
else
	echo "error: cannot find the binary library to test (so or .dll file)"
	exit 99
fi
idir="${srcdir}/test/inputdata"

if sqlite3 :memory: ".load \"${libtotest}\"" ".param init" ".param set @idir \"${idir}\"" ".read \"${srcdir}/test/test001-basic.sql\"" | tee /dev/stderr | grep -q FAILED ; then
	# fail if at least one test has FAILED 
	exit 1
else
	# no tests are FAILED, they were either PASSED or SKIPPED 
	exit 0
fi
