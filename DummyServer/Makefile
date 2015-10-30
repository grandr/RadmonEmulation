CC = g++
CDEBUG = -g
LDFLAGS += -g

CFLAGS = -Wall -ansi -pedantic -Wno-long-long -g
CFLAGS += $(CDEBUG)

# ROOT (for TRandom only)
ROOT_CFLAGS	= $(shell root-config --cflags)
ROOT_LIBS	= $(shell root-config --libs)

# DIMDIR = /opt/xdaq/
DIMDIR = /home/grandr/DIM/dim/



LIBS += -lpthread

# LIBS += $(DIMDIR)/lib/libdim.a
# LIBS +=  -L$(DIMDIR)/lib -ldim 

LIBS += $(DIMDIR)/linux/libdim.a
LIBS +=  -L$(DIMDIR)/linux -ldim 
LIBS += $(ROOT_LIBS)

# LIBFLAGS = -l$(LIBS)
LIBFLAGS = $(LIBS)



SRC_DIR = ../src
INC_DIR = ../inc

# SRC_DIR = /data/test/src
# INC_DIR = /data/test/inc

TARGET = dummyRadmon
SOURCE = dummyRadmon.cc drmSetup.cc radmonCommand.cc utils.cc

# INCLUDE = -I$(INC_DIR) -I$(DIMDIR)/include/dim
INCLUDE = -I$(INC_DIR) -I$(DIMDIR)/dim


CFLAGS += $(INCLUDE)
CFLAGS += $(ROOT_CFLAGS)
VPATH=$(SRC_DIR)

CFLAGS +=  -Wall -DMIPSEL -DPROTOCOL=1 -Dunix -Dlinux -fPIC
#ifneq ($(SHAREABLE),no)
# 	SHAREABLE = yes
# 	LIBFLAGS += -shared
#endif

OBJ=$(join $(addsuffix ./, $(dir $(SOURCE))), $(notdir $(SOURCE:.cc=.o)))

## Fix dependency destination to be .dep relative to the src dir
DEPENDS=$(join $(addsuffix .dep/, $(dir $(SOURCE))), $(notdir $(SOURCE:.cc=.d)))

## Default rule executed
all: $(TARGET)
	@true

## Clean Rule
clean:
	@-rm -f $(OBJ) $(DEPENDS)

distclean:
	@-rm -f $(TARGET) $(OBJ) $(DEPENDS)


## Rule for making the actual target
$(TARGET): $(OBJ)
	@echo "============="
	@echo "Linking the target $@"
	@echo "============="
	@$(CC) $(CFLAGS) -o $@ $^ $(LIBFLAGS)
	@echo -- Link finished --

## Generic compilation rule
%.o : %.cc
	@mkdir -p $(dir $@)
	@echo "============="
	@echo "Compiling $<"
	@$(CC) $(CFLAGS) -c $< -o $@


## Rules for object files from cc files

%.o : %.cc
	@mkdir -p $(dir $@)
	@echo "============="
	@echo "Compiling $<"
	@$(CC) $(CFLAGS) -c $< -o $@

# Rule for "other directory"  You will need one per "other" dir
# $(SRC_DIR)/../obj/%.o : %.cc
# 	@mkdir -p $(dir $@)
# 	@echo "============="
# 	@echo "Compiling $<"
# 	@$(CC) $(CFLAGS) -c $< -o $@

## Make dependancy rules
# ../.dep/%.d: %.cc
# 	@mkdir -p $(dir $@)
# 	@echo "============="
# 	@echo Building dependencies file for $*.o
# 	@$(SHELL) -ec '$(CC) -M $(CFLAGS) $< | sed "s^$*.o^../obj/$*.o^" > $@'
# 
# ## Dependency rule for "other" directory
# $(SRC_DIR)/../.dep/%.d: %.cc
# 	@mkdir -p $(dir $@)
# 	@echo "============="
# 	@echo Building dependencies file for $*.o
# 	@$(SHELL) -ec '$(CC) -M $(CFLAGS) $< | sed	"s^$*.o^$(OTHERDIR)/../obj/$*.o^" > $@'

## Include the dependency files
-include $(DEPENDS)
