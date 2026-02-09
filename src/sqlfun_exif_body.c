#include "sqlfun_exif_body.h"
#include <stdlib.h>
#include <string.h>

#include <libexif/exif-data.h>
#include <libexif/exif-ifd.h>

/** \brief Remove first space and all subsequent characters; modifies buf */
static void keep_only_first_word(char *buf);

static void keep_only_first_word(char *buf)
{
    char *s = buf-1;
    for (; *buf; ++buf) {
        if (*buf != ' ')
            s = buf;
    }
    *++s = 0; /* nul terminate the string on the first of the final spaces */
}

/** \brief Show the tag contents if the tag exists */
const char* show_tag(const ExifData *d, const ExifIfd ifd, const ExifTag tag);

const char* show_tag(const ExifData *d, const ExifIfd ifd, const ExifTag tag){
    ExifEntry *entry = exif_content_get_entry(d->ifd[ifd], tag);

    if (entry!=NULL) {
        static char buf[1024];
        exif_entry_get_value(entry, buf, sizeof(buf));
        keep_only_first_word(buf);
        return buf;
    } else {
    	return "";
    }
}

const char* exif_read_tag_from_exifdata(ExifData *ed, const int ifd, const char* tagname);

const char* exif_read_tag_from_exifdata(ExifData *ed, const int ifd, const char* tagname){
	if (!ed) {
		return "";
	}
	if (ifd < (int)EXIF_IFD_0 || ifd >= (int)EXIF_IFD_COUNT){
		return "";
	}
	ExifTag tag=exif_tag_from_name(tagname);
	if (tag==0){
		exif_data_unref(ed);
		return "";
	}
	const char* tmp_result=show_tag(ed, (ExifIfd) ifd, tag);
	exif_data_unref(ed);
	return tmp_result;
}

const int exif_ifdname_to_ifdnumber(const char* ifd);

const int exif_ifdname_to_ifdnumber(const char* ifdname){
	if (!strcmp(ifdname, "EXIF_IFD_0")){
		return 0;
	} else if (!strcmp(ifdname, "EXIF_IFD_1")){
		return 1;
	} else if (!strcmp(ifdname, "EXIF_IFD_EXIF")){
		return 2;
	} else if (!strcmp(ifdname, "EXIF_IFD_GPS")){
		return 3;
	} else if (!strcmp(ifdname, "EXIF_IFD_INTEROPERABILITY")){
		return 4;
	} else {
		return -1;
	}
}

const char* exif_read_tag_from_file(const char* filename, const char* ifd, const char* tagname){
    ExifData *ed = exif_data_new_from_file(filename);
    return exif_read_tag_from_exifdata(ed, exif_ifdname_to_ifdnumber(ifd), tagname);
}

const char* exif_read_tag_from_buffer(const unsigned char* buffer, const unsigned int buffer_size, const char* ifd, const char* tagname){
    ExifData *ed = exif_data_new_from_data(buffer, buffer_size) ;
    return exif_read_tag_from_exifdata(ed, exif_ifdname_to_ifdnumber(ifd), tagname);
}
