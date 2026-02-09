SUBDIRS = src 

if HAVESQLITE3SHELLFORTESTS
TESTS = test/test001-basic.sh
endif

EXTRA_DIST = \
	test/test001-basic.sh test/test001-basic.sql     \
	test/inputdata/20231030_150218.jpg               \
	.gitignore

clean-local:
	-rm -vrf test/test001-output
