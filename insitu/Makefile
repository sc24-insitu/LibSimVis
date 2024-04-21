CC=mpicc.mpich 
LIB=lib
SRC=src
HEADER=$(SRC)/include
OBJ=obj

LOGGER=0	
LOGGER ?= 0

STANDALONE_LIB=0
STANDALONE_LIB ?= 0

# Libsim/VisIt library and header file location
LIBSIM_INC = -I/work/sw/build_visit/visit/build/include -I/work/sw/build_visit/visit/src/sim/V2/lib  
LIBSIM_LIB = -L/work/sw/build_visit/visit/build/lib 

CPPFLAGS=-I$(SRC) -I$(HEADER) 

CFLAGS=-D_GNU_SOURCE
ifeq ($(LOGGER), 1)
    CFLAGS:=$(CFLAGS) -DLOGGER_H -DDEBUGGING_MODE
endif

ifeq ($(STANDALONE_LIB), 1)
    CFLAGS:=$(CFLAGS) -DRUN_STANDALONE
OUTFILE=standalone_stage_manager.so
all: $(LIB) $(LIB)/$(OUTFILE)
endif

ifeq ($(STANDALONE_LIB), 0)
OUTFILE=stage_manager.so
all: $(LIB) $(LIB)/$(OUTFILE)
endif

$(LIB):
	mkdir $(LIB) $(OBJ)

$(LIB)/$(OUTFILE): $(OBJ)/sm.o $(HEADER)/data_stager.h
	$(CC) -Wall -g -O3 -Wunreachable-code $(CFLAGS) $(CPPFLAGS) $(LIBSIM_INC) -shared -fopenmp -fPIC $(HEADER)/data_stager.h -o $(LIB)/$(OUTFILE) $(OBJ)/sm.o -ldl -lsimV2 $(LIBSIM_LIB)

$(OBJ)/sm.o: $(SRC)/data_stager.c $(HEADER)/data_stager.h
	$(CC) -c -Wall -g -O3 -Wunreachable-code -Werror -fpic -fopenmp $(CFLAGS) $(CPPFLAGS) $(LIBSIM_INC) $(SRC)/data_stager.c -o $(OBJ)/sm.o 

clean:
	rm -rf $(OBJ)/*
