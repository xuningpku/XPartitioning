#set target
#include subdirs
#SUBDIRS = src test

#
INCLUDES = -Iinclude
export INCLUDES
LIBS=-lm

test_dir=test
core_dir=src/core
util_dir=src/util

test_src=$(test_dir)/test.cpp

core_src=$(core_dir)/graphknife.cpp \
		 $(core_dir)/graphpartition.cpp \
		 $(core_dir)/homoheuristic.cpp \
		 $(core_dir)/heterheuristic.cpp \
		 $(core_dir)/partitionstatistic.cpp \
		 $(core_dir)/edgecutspartitioner.cpp

util_src=$(util_dir)/filesplitor.cpp \
		 $(util_dir)/filereader.cpp \
		 $(util_dir)/hashtable.cpp \
		 $(util_dir)/time.cpp

#main body
AUTOMAKE_OPTIONS=foreign
noinst_PROGRAMS=gknifedemo
gknifedemo_SOURCES=$(test_src) \
				   $(core_src) \
				   $(util_src)

