# Makefile 

PATH_SRC=src
PATH_INCLUDE=include
PATH_BIN=.
PATH_OBJ=obj

INCLUDE_DIRS=-I "${PATH_INCLUDE}"  -I "${PATH_INCLUDE}/private"


CC=icc
CFLAG=-Werror-all -O2 -DNDEBUG=1 -ltbb -m64 ${INCLUDE_DIRS}
LDFLAG=-Werror-all -lstdc++ -ltbb -m64 ${INCLUDE_DIRS}



#*********************************
#
#	Target
#
#*********************************

all: source ${PATH_BIN}/run 

#*********************************
#
#	Binaire
#
#*********************************

${PATH_BIN}/run : ${PATH_OBJ}/input_reader.obj ${PATH_OBJ}/coords_maximum_subarray.obj ${PATH_OBJ}/problem_data.obj ${PATH_OBJ}/cache_problem_data.obj ${PATH_OBJ}/debug_algorithm.obj ${PATH_OBJ}/algorithm.obj ${PATH_OBJ}/main.obj
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

${PATH_OBJ}/cache_problem_data.obj: ${PATH_SRC}/cache_problem_data.cpp ${PATH_INCLUDE}/cache_problem_data.h
	$(CC) $(CFLAG) $(INCLUDE_DIRS) -o $@ -c $<

${PATH_OBJ}/problem_data.obj: ${PATH_SRC}/problem_data.cpp ${PATH_INCLUDE}/problem_data.h
	$(CC) $(CFLAG) $(INCLUDE_DIRS) -o $@ -c $<

${PATH_OBJ}/debug_algorithm.obj: ${PATH_SRC}/debug_algorithm.cpp ${PATH_INCLUDE}/debug_algorithm.h
	$(CC) $(CFLAG) $(INCLUDE_DIRS) -o $@ -c $<

${PATH_OBJ}/algorithm.obj: ${PATH_SRC}/algorithm.cpp ${PATH_INCLUDE}/algorithm.h
	$(CC) $(CFLAG) $(INCLUDE_DIRS) -o $@ -c $<

${PATH_OBJ}/coords_maximum_subarray.obj: ${PATH_SRC}/coords_maximum_subarray.cpp ${PATH_INCLUDE}/coords_maximum_subarray.h
	$(CC) $(CFLAG) $(INCLUDE_DIRS) -o $@ -c $<

${PATH_OBJ}/input_reader.obj:${PATH_SRC}/input_reader.cpp ${PATH_INCLUDE}/input_reader.h
	$(CC) $(CFLAG) $(INCLUDE_DIRS) -o $@ -c $<


#*********************************
#
#	Utilities
#
#*********************************

clean: clean_bin	
	-rm -R ${PATH_OBJ}/*

clean_bin:
	-rm  -R ${PATH_BIN}/*

source:
	source /opt/intel/Compiler/latest/bin/iccvars.sh intel64