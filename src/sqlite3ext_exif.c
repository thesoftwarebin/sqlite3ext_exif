#include <stdlib.h>
/*#include <string.h>
#include <stdio.h>
#include <sqlite3ext.h>
#include <sys/stat.h>
#include <sys/fcntl.h>
*/
#include "sqlite3ext.h"
#include "sqlfun_exif.h"

SQLITE_EXTENSION_INIT1;

/* SQLite invokes this routine once when it loads the extension. */
int sqlite3_extension_init(sqlite3 * db, char **pzErrMsg, const sqlite3_api_routines * pApi){
	int retval=0;

	SQLITE_EXTENSION_INIT2(pApi);

	retval|=sqlite3_create_function(
		db,
		"blob_exif_read",
		3,
		SQLITE_UTF8,
		NULL,
		sqlfun_blob_exif_read,
		NULL,
		NULL
	);
	retval|=sqlite3_create_function(
		db,
		"file_exif_read",
		3,
		SQLITE_UTF8,
		NULL,
		sqlfun_file_exif_read,
		NULL,
		NULL
	);

	return retval;
}
