#include <sqlite3ext.h>
#include <stdlib.h>
#include <string.h>
#include "sqlfun_exif.h"
#include "sqlfun_exif_body.h"

extern const sqlite3_api_routines *sqlite3_api;

void sqlfun_blob_exif_read(sqlite3_context * context, int argc, sqlite3_value ** argv) {
	const int            blob_buffer_size = sqlite3_value_bytes(argv[0]);
	const unsigned char* blob_buffer      = (unsigned char *) sqlite3_value_blob(argv[0]);
	const char*          ifd              = strdup(sqlite3_value_text(argv[1])); // using strdup because sqlite3_value_text return value may be destroyed at next sqlite3_value_text invocation
	const char*          tagname          = sqlite3_value_text(argv[2]);

	const const char*    tmp_result       = exif_read_tag_from_buffer(blob_buffer, blob_buffer_size, ifd, tagname);

	sqlite3_result_text(context, tmp_result, -1, SQLITE_TRANSIENT);

	free((void*)ifd);
}

void sqlfun_file_exif_read(sqlite3_context * context, int argc, sqlite3_value ** argv) {

	const char* filename = strdup(sqlite3_value_text(argv[0])); // using strdup because sqlite3_value_text return value may be destroyed at next sqlite3_value_text invocation
	const char* ifd      = strdup(sqlite3_value_text(argv[1])); // using strdup because sqlite3_value_text return value may be destroyed at next sqlite3_value_text invocation
	const char* tagname  = sqlite3_value_text(argv[2]);

	const char* tmp_result=exif_read_tag_from_file(filename, ifd, tagname);

	sqlite3_result_text(context, tmp_result, -1, SQLITE_TRANSIENT);

	free((void*)ifd);
	free((void*)filename);
}

