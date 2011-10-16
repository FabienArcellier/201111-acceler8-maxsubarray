# Makefile 

#A rajouter en ligne de commande
#TARGET=MTL 
#COMPILATEUR=GCC ou ICC

PATH_SRC=src
PATH_INCLUDE=include
PATH_TESTS=tests
PATH_BIN=bin
PATH_OBJ=obj

INCLUDE_DIRS=-I "${PATH_INCLUDE}" -I "${PATH_INCLUDE}/private"

ifeq ($(TEST), 1)
	UNIT_TEST=-DUNIT_TEST
endif

ifeq ($(TARGET),MTL)
  export LD_LIBRARY_PATH=/opt/mpfr/lib:/opt/gmp/lib:/opt/mpc/lib
endif

ifeq ($(TARGET),MTL)
  ifeq ($(COMPILATEUR),GCC)
    GCC_VERSION=4.5.1
    PREFIX=/opt/gcc/${GCC_VERSION}/bin
    CC=$(PREFIX)/gcc
    CFLAG=-Wall -lm -fopenmp -DNDEBUG=1 -O3 ${INCLUDE_DIRS}
    LDFLAG=-Wall -lm -fopenmp ${INCLUDE_DIRS}
  else
    CC=icc
    CFLAG=-Werror-all -O3 -DNDEBUG=1 -openmp -axSSE2 ${INCLUDE_DIRS}
    LDFLAG=-Werror-all -openmp -axSSE2 ${INCLUDE_DIRS}
  endif
endif

ifeq ($(TARGET),STATION)
  CC=g++
  CFLAG=-Wall -lm -O3 -DNDEBUG=1 -fopenmp ${INCLUDE_DIRS}
  LDFLAG=-Wall -lm -fopenmp ${INCLUDE_DIRS}
endif

#################################
#
#	Target
#
#################################

run: ${PATH_OBJ}/main.obj
	$(CC) $(LDFLAG) -o $@ $^

tests: main_tests

#################################
#
#	Binaire
#
#################################

${PATH_BIN}/main_tests: ${PATH_OBJ}/main.obj ${PATH_OBJ}/main_tests.obj
	$(CC) $(LDFLAG) -o $@ $^

#################################
#
#	Objects
#
#################################

${PATH_OBJ}/main.obj: ${PATH_SRC}/main.cpp ${PATH_INCLUDE}/main.h
	$(CC) $(CFLAG) -o $@ -c $< ${UNIT_TEST}

${PATH_OBJ}/main_tests.obj: ${PATH_TESTS}/main_tests.cpp
	$(CC) $(CFLAG) -o $@ -c $<

#################################
#
#	Utilities
#
#################################

clean:
	-rm -R ${PATH_BIN}/*.*