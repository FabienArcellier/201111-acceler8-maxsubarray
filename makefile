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

ifeq ($(TEST),1)
	UNIT_TEST=-DUNIT_TEST
endif

ifeq ($(GPROF),1)
	G_PROF=-pg
endif

ifeq ($(TARGET),MTL)
  export LD_LIBRARY_PATH=/opt/mpfr/lib:/opt/gmp/lib:/opt/mpc/lib
endif

ifeq ($(TARGET),MTL)
  ifeq ($(COMPILATEUR),GCC)
    GCC_VERSION=4.5.1
    PREFIX=/opt/gcc/${GCC_VERSION}/bin
    CC=$(PREFIX)/g++
    CFLAG=-Wall -lm -O2 -ftree-vectorizer-verbose=2 -march=native -funroll-loops -DNDEBUG=1 ${INCLUDE_DIRS} ${G_PROF}
    LDFLAG=-Wall -lm -O2 -lstdc++ -ftree-vectorizer-verbose=2 -march=native -funroll-loops ${INCLUDE_DIRS} ${G_PROF}
  else
    CC=icc
    CFLAG=-Werror-all -O2 -DNDEBUG=1 -march=native ${INCLUDE_DIRS}
    LDFLAG=-Werror-all -lstdc++ -march=native ${INCLUDE_DIRS}
  endif
endif

ifeq ($(TARGET),STATION)
  CC=g++
  CFLAG=-Wall -lm -O2 -ftree-vectorizer-verbose=2 -march=native -funroll-loops ${INCLUDE_DIRS} ${G_PROF}
  LDFLAG=-Wall -lm -O2 -lstdc++ -ftree-vectorizer-verbose=2 -march=native -funroll-loops ${INCLUDE_DIRS} ${G_PROF}
endif

#*********************************
#main_tests
#	Target
#
#*********************************

run: clean ${PATH_BIN}/run ${PATH_BIN}/verif copy_scenarios copy_benchmark

tests: clean ${PATH_BIN}/problem_data_tests ${PATH_BIN}/input_reader_tests ${PATH_BIN}/algorithm_tests ${PATH_BIN}/debug_algorithm_tests ${PATH_BIN}/verif_tests ${PATH_BIN}/main_tests ${PATH_BIN}/cache_problem_data_tests copy_scenarios copy_tests_file


#*********************************
#
#	Binaire
#
#*********************************

${PATH_BIN}/run : ${PATH_OBJ}/input_reader.obj ${PATH_OBJ}/problem_data.obj ${PATH_OBJ}/debug_algorithm.obj ${PATH_OBJ}/algorithm.obj ${PATH_OBJ}/main.obj
	$(CC) $(LDFLAG) -o $@ $^

${PATH_BIN}/verif : ${PATH_OBJ}/input_reader.obj ${PATH_OBJ}/problem_data.obj ${PATH_OBJ}/verif.obj
	$(CC) $(LDFLAG) -o $@ $^

${PATH_BIN}/main_tests: ${PATH_OBJ}/problem_data.obj ${PATH_OBJ}/main.obj ${PATH_OBJ}/main_tests.obj
	$(CC) $(LDFLAG) -o $@ $^

${PATH_BIN}/verif_tests: ${PATH_OBJ}/problem_data.obj ${PATH_OBJ}/verif.obj ${PATH_OBJ}/verif_tests.obj
	$(CC) $(LDFLAG) -o $@ $^

${PATH_BIN}/input_reader_tests: ${PATH_OBJ}/problem_data.obj ${PATH_OBJ}/input_reader.obj ${PATH_OBJ}/input_reader_tests.obj
	$(CC) $(LDFLAG) -o $@ $^

${PATH_BIN}/debug_algorithm_tests: ${PATH_OBJ}/problem_data.obj ${PATH_OBJ}/debug_algorithm.obj ${PATH_OBJ}/debug_algorithm_tests.obj
	$(CC) $(LDFLAG) -o $@ $^

${PATH_BIN}/algorithm_tests: ${PATH_OBJ}/problem_data.obj ${PATH_OBJ}/debug_algorithm.obj ${PATH_OBJ}/algorithm.obj ${PATH_OBJ}/algorithm_tests.obj
	$(CC) $(LDFLAG) -o $@ $^

${PATH_BIN}/problem_data_tests: ${PATH_OBJ}/problem_data.obj ${PATH_OBJ}/problem_data_tests.obj
	$(CC) $(LDFLAG) -o $@ $^

${PATH_BIN}/cache_problem_data_tests: ${PATH_OBJ}/problem_data.obj ${PATH_OBJ}/cache_problem_data.obj ${PATH_OBJ}/cache_problem_data_tests.obj 
	$(CC) $(LDFLAG) -o $@ $^

#*********************************
#
#	Objects
#
#*********************************

${PATH_OBJ}/main.obj: ${PATH_SRC}/main.cpp ${PATH_INCLUDE}/main.h
	$(CC) $(CFLAG) $(INCLUDE_DIRS) -o $@ -c $< ${UNIT_TEST}

${PATH_OBJ}/verif.obj: ${PATH_SRC}/verif.cpp ${PATH_INCLUDE}/verif.h
	$(CC) $(CFLAG) $(INCLUDE_DIRS) -o $@ -c $< ${UNIT_TEST}

${PATH_OBJ}/debug_algorithm.obj: ${PATH_SRC}/debug_algorithm.cpp ${PATH_INCLUDE}/debug_algorithm.h
	$(CC) $(CFLAG) $(INCLUDE_DIRS) -o $@ -c $<

${PATH_OBJ}/problem_data.obj: ${PATH_SRC}/problem_data.cpp ${PATH_INCLUDE}/problem_data.h
	$(CC) $(CFLAG) $(INCLUDE_DIRS) -o $@ -c $<

${PATH_OBJ}/algorithm.obj: ${PATH_SRC}/algorithm.cpp ${PATH_INCLUDE}/algorithm.h
	$(CC) $(CFLAG) $(INCLUDE_DIRS) -o $@ -c $<

${PATH_OBJ}/cache_problem_data.obj: ${PATH_SRC}/cache_problem_data.cpp ${PATH_INCLUDE}/cache_problem_data.h
	$(CC) $(CFLAG) $(INCLUDE_DIRS) -o $@ -c $<

${PATH_OBJ}/input_reader.obj:${PATH_SRC}/input_reader.cpp ${PATH_INCLUDE}/input_reader.h
	$(CC) $(CFLAG) $(INCLUDE_DIRS) -o $@ -c $<

${PATH_OBJ}/main_tests.obj: ${PATH_TESTS}/main_tests.cpp
	$(CC) $(CFLAG) $(INCLUDE_DIRS) -o $@ -c $<

${PATH_OBJ}/verif_tests.obj: ${PATH_TESTS}/verif_tests.cpp
	$(CC) $(CFLAG) $(INCLUDE_DIRS) -o $@ -c $<

${PATH_OBJ}/debug_algorithm_tests.obj: ${PATH_TESTS}/debug_algorithm_tests.cpp
	$(CC) $(CFLAG) $(INCLUDE_DIRS) -o $@ -c $<

${PATH_OBJ}/problem_data_tests.obj: ${PATH_TESTS}/problem_data_tests.cpp
	$(CC) $(CFLAG) $(INCLUDE_DIRS) -o $@ -c $<

${PATH_OBJ}/cache_problem_data_tests.obj: ${PATH_TESTS}/cache_problem_data_tests.cpp
	$(CC) $(CFLAG) $(INCLUDE_DIRS) -o $@ -c $<

${PATH_OBJ}/algorithm_tests.obj: ${PATH_TESTS}/algorithm_tests.cpp
	$(CC) $(CFLAG) $(INCLUDE_DIRS) -o $@ -c $<

${PATH_OBJ}/input_reader_tests.obj: ${PATH_TESTS}/input_reader_tests.cpp
	$(CC) $(CFLAG) $(INCLUDE_DIRS) -o $@ -c $<


#*********************************
#
#	Utilities
#
#*********************************

clean: clean_bin	
	-rm -R ${PATH_OBJ}/*

clean_bin:
	-rm -R ${PATH_BIN}/*

copy_tests_file:
	cp build/tests.sh ${PATH_BIN}/

copy_scenarios:
	-svn export --force ${PATH_TESTS}/scenarios ${PATH_BIN}/scenarios

copy_benchmark:
	cp tools/benchmark.sh ${PATH_BIN}/