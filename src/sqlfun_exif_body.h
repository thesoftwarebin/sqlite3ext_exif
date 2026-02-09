#ifndef SQLFUN_EXIF_BODY_H
#define SQLFUN_EXIF_BODY_H

/** \brief read value of an EXIF tag from a JPEG-format file */
const char* exif_read_tag_from_file(const char* filename, const char* ifd, const char* tagname);

/** \brief read value of an EXIF tag from a JPEG-format byte buffer */
const char* exif_read_tag_from_buffer(const unsigned char* buffer, const unsigned int buffer_size, const char* ifd, const char* tagname);

#endif
