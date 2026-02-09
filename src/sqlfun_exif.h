#ifndef SQLFUN_EXIF_H
#define SQLFUN_EXIF_H

#include "sqlite3ext.h"

void sqlfun_blob_exif_read(sqlite3_context * context, int argc, sqlite3_value ** argv);

void sqlfun_file_exif_read(sqlite3_context * context, int argc, sqlite3_value ** argv);

#endif
