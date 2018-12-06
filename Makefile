CC := gcc
CXX := g++
CFLAGS := -g -Wall -O2

CXXFLAGS := ${CFLAGS}

FILES := $(wildcard *.c)
TARGETS := $(patsubst %.c, %, ${FILES})
FILES := $(wildcard *.cpp)
TARGETS += $(patsubst %.cpp, %, ${FILES})

DIRS := $(shell find . -maxdepth 1 -type d  | grep  '/')

.PHONY: all clean

all: ${TARGETS}
	@for i in ${DIRS}; do \
		${MAKE} -C $$i clean; done

clean:
	${RM} ${TARGETS}
	@for i in ${DIRS}; do \
		${MAKE} -C $$i clean; done
