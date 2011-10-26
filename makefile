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
    LDFLAG=-Wall -lstdc++ -lm -fopenmp ${INCLUDE_DIRS}
  else
    CC=icc
    CFLAG=-Werror-all -O3 -DNDEBUG=1 -openmp -axSSE2 ${INCLUDE_DIRS}
    LDFLAG=-Werror-all -lstdc++ -openmp -axSSE2 ${INCLUDE_DIRS}
  endif
endif

ifeq ($(TARGET),STATION)
  CC=g++
  CFLAG=-Wall -lm -O3 -fopenmp ${INCLUDE_DIRS}
  LDFLAG=-Wall -lm -fopenmp -lstdc++ ${INCLUDE_DIRS}
endif

#*********************************
#
#	Target
#
#*********************************

run: ${PATH_OBJ}/main.obj
	$(CC) $(LDFLAG) -o $@ $^

tests: ${PATH_BIN}/problem_data_tests ${PATH_BIN}/algorithm_tests ${PATH_BIN}/main_tests copy_scenarios

#*********************************
#
#	Binaire
#
#*********************************

${PATH_BIN}/main_tests: ${PATH_OBJ}/problem_data.obj ${PATH_OBJ}/main.obj ${PATH_OBJ}/main_tests.obj
	$(CC) $(LDFLAG) -o $@ $^

${PATH_BIN}/problem_data_tests: ${PATH_OBJ}/problem_data.obj ${PATH_OBJ}/problem_data_tests.obj
	$(CC) $(LDFLAG) -o $@ $^

${PATH_BIN}/algorithm_tests: ${PATH_OBJ}/problem_data.obj ${PATH_OBJ}/algorithm.obj ${PATH_OBJ}/algorithm_tests.obj
	$(CC) $(LDFLAG) -o $@ $^

#*********************************
#
#	Objects
#
#*********************************

${PATH_OBJ}/main.obj: ${PATH_SRC}/main.cpp ${PATH_INCLUDE}/main.h
	$(CC) $(CFLAG) $(INCLUDE_DIRS) -o $@ -c $< ${UNIT_TEST}

${PATH_OBJ}/problem_data.obj: ${PATH_SRC}/problem_data.cpp ${PATH_INCLUDE}/problem_data.h
	$(CC) $(CFLAG) $(INCLUDE_DIRS) -o $@ -c $<

${PATH_OBJ}/algorithm.obj: ${PATH_SRC}/algorithm.cpp ${PATH_INCLUDE}/algorithm.h
	$(CC) $(CFLAG) $(INCLUDE_DIRS) -o $@ -c $<


${PATH_OBJ}/main_tests.obj: ${PATH_TESTS}/main_tests.cpp
	$(CC) $(CFLAG) $(INCLUDE_DIRS) -o $@ -c $<

${PATH_OBJ}/problem_data_tests.obj: ${PATH_TESTS}/problem_data_tests.cpp
	$(CC) $(CFLAG) $(INCLUDE_DIRS) -o $@ -c $<

${PATH_OBJ}/algorithm_tests.obj: ${PATH_TESTS}/algorithm_tests.cpp
	$(CC) $(CFLAG) $(INCLUDE_DIRS) -o $@ -c $<


#*********************************
#
#	Utilities
#
#*********************************

clean:
	-rm -R ${PATH_BIN}/*
	-rm -R ${PATH_OBJ}/*

copy_scenarios:
	-cp -R ${PATH_TESTS}/scenarios ${PATH_BIN}/scenarios