#set target
#include subdirs
#SUBDIRS = src test

#
INCLUDES = -Iinclude
export INCLUDES
LIBS=-lpthread

test_dir=test
core_dir=src/core
util_dir=src/util

test_src=$(test_dir)/test.cpp

core_src=$(core_dir)/loader.cpp \
		 $(core_dir)/graphkinfe.cpp

util_src=$(util_dir)/filesplitor.cpp \
		 $(util_dir)/genericthread.cpp \
		 $(util_dir)/filereader.cpp \
		 $(util_dir)/time.cpp

#main body
AUTOMAKE_OPTIONS=foreign
noinst_PROGRAMS=gkinfetest
gkinfetest_SOURCES=$(test_src) \
				   $(core_src) \
				   $(util_src)

