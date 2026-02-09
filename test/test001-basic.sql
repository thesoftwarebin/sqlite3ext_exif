.mode table
.headers off
.nullvalue NULL
.mode table

select
	*,
	case when (expected is null and file_exif_read is null and blob_exif_read is null) then 'PASSED'
		when (expected is null or file_exif_read is null or blob_exif_read is null) then 'FAILED'
		when expected=file_exif_read and expected=blob_exif_read then 'PASSED'
		else 'FAILED'
	end as result
	from (
		select
			*,
			file_exif_read(file, ifd, tag) as file_exif_read, 
			blob_exif_read(readfile(file), ifd, tag) as blob_exif_read
		from (
			          select @idir||'/20231030_150218.jpg' as file, 'EXIF_IFD_0' as ifd, 'Orientation' as tag, 'Top-left' as expected
			union all select @idir||'/20231030_150218.jpg',         'EXIF_IFD_EXIF',     'DateTimeOriginal',   '2023:10:30 15:02:18'
			union all select @idir||'/20231030_150218.jpg',         'EXIF_IFD_EXIF',     'FNumber',            'f/2.2'
			union all select @idir||'/20231030_150218.jpg',         'EXIF_IFD_EXIF',     'ISOSpeedRatings',    '40'
			union all select @idir||'/20231030_150218.jpg',         'EXIF_IFD_EXIF',     'ExposureTime',       '1/1379 sec.'
			union all select @idir||'/20231030_150218.jpg',         'EXIF_IFD_GPS',      'GPSLatitude',        '35, 18, 21.89599'
			union all select @idir||'/20231030_150218.jpg',         'EXIF_IFD_GPS',      'GPSLatitudeRef',     'N'
			union all select @idir||'/20231030_150218.jpg',         'EXIF_IFD_GPS',      'GPSLongitude',       '139, 29, 1.92542'
			union all select @idir||'/20231030_150218.jpg',         'EXIF_IFD_GPS',      'GPSLongitudeRef',    'E'
			union all select @idir||'/20231030_150218.jpg',         'EXIF_IFD_GPS',      'GPSAltitude',        '42'
			union all select @idir||'/20231030_150218.jpg',         'EXIF_IFD_GPS',      'GPSAltitudeRef',     'Sea level'
		)
	);

