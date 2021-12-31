# --------------------------------------------------------------
# Output settings
# --------------------------------------------------------------
QUIET := @
ECHO := @echo
ifneq ($(QUIET),@)
ECHO := @true
endif

# --------------------------------------------------------------
# Compiler settings
# --------------------------------------------------------------
CPP = g++ -std=c++11
C_FLAGS = -g -MP -MD -Wall
C_FLAGS += -Wextra -Wwrite-strings -Wno-parentheses

# --------------------------------------------------------------
# Directories
# --------------------------------------------------------------
SDIR = ./src
BDIR = ./build
IDIR = ./include
LDIR = -L ./lib

TDIR = ./test
TEST_BDIR = $(BDIR)/test
TEST_IDIR = $(IDIR)/test

# --------------------------------------------------------------
# Executables
# --------------------------------------------------------------
EXEC = runner
TARGET = ./bin/$(EXEC)
TESTER = ./bin/tester

# --------------------------------------------------------------
# Includes
# --------------------------------------------------------------
INC = $(patsubst %,-I%,$(IDIR))
TEST_INC = $(INC) $(patsubst %,-I%,$(TEST_IDIR))

# --------------------------------------------------------------
# Source extension
# --------------------------------------------------------------
SRCEXT = cc

# --------------------------------------------------------------
# Sources, Objects, and Libraries
# --------------------------------------------------------------
SOURCES = $(shell find $(SDIR) -type f -name *.$(SRCEXT))
OBJ = $(patsubst $(SDIR)/%,$(BDIR)/%,$(SOURCES:.$(SRCEXT)=.o))
TEST_SOURCES = $(shell find $(TDIR) -type f -name *.$(SRCEXT))
TEST_OBJ = $(patsubst $(TDIR)/%,$(TEST_BDIR)/%,$(TEST_SOURCES:.$(SRCEXT)=.o)) $(filter-out $(BDIR)/main.o, $(OBJ))
LIBS = 

# --------------------------------------------------------------
# Archieve name for tar and zip
# --------------------------------------------------------------
ARCHIVE_NAME = $(EXEC)-$(shell date '+%F')

# --------------------------------------------------------------
# Make settings
# --------------------------------------------------------------
.SUFFIXES:
.DELETE_ON_ERROR:

# --------------------------------------------------------------

.PHONY: all tester
all: $(TARGET)
tester: $(TESTER)

$(BDIR)/%.o: $(SDIR)/%.$(SRCEXT)
	$(QUIET) @mkdir -p $(dir $@)
	$(ECHO) "=============";
	$(ECHO) "Compiling $<";
	$(ECHO) "=============";
	$(QUIET) $(CPP) $(C_FLAGS) $(INC) -c -o $@ $< $(LIBS)
	$(ECHO) "[OK]  $@"

$(TEST_BDIR)/%.o: $(TDIR)/%.$(SRCEXT)
	$(QUIET) @mkdir -p $(dir $@)
	$(ECHO) "=============";
	$(ECHO) "Compiling test file $<";
	$(ECHO) "=============";
	$(QUIET) $(CPP) $(C_FLAGS) $(TEST_INC) -c -o $@ $< $(LIBS)
	$(ECHO) "[OK]  $@"

$(TARGET): $(OBJ)
	$(ECHO) "=============";
	$(ECHO) "Linking the target $@"
	$(ECHO) "=============";
	$(QUIET) $(CPP) $(LDIR) -o $@ $^ $(C_FLAGS) $(LIBS)
	$(ECHO) "[OK]  $@"
	$(ECHO) "-- Link finished --";

$(TESTER): $(TEST_OBJ)
	$(ECHO) "=============";
	$(ECHO) "Linking the target $@"
	$(ECHO) "=============";
	$(QUIET) $(CPP) $(LDIR) -o $@ $^ $(C_FLAGS) $(LIBS)
	$(ECHO) "[OK]  $@"
	$(ECHO) "-- Link finished --";

# --------------------------------------------------------------

.PHONY: test_memory
test_memory: $(TARGET)
	-valgrind --leak-check=full --track-origins=yes --show-leak-kinds=all ./$(EXEC) $(INPUT_FILE) $(RUN_FLAGS)

# --------------------------------------------------------------

.PHONY: clean clean_test clean_all
clean:
	$(ECHO) "Cleaning...";
	$(ECHO) "[CL] $(TARGET)"
	$(QUIET) -rm $(TARGET)
	$(ECHO) "[CL] $(BDIR)/*"
	$(QUIET) find $(BDIR) -name "*.o" -type f -delete
	$(QUIET) find $(BDIR) -name "*.d" -type f -delete

clean_test:
	$(ECHO) "Cleaning tests...";
	$(ECHO) "[CL] $(TESTER)"
	$(QUIET) -rm $(TESTER)
	$(ECHO) "[CL] $(BDIR)/*"
	$(QUIET) find $(BDIR) -name "*.o" -type f -delete
	$(QUIET) find $(BDIR) -name "*.d" -type f -delete

clean_all:
	$(ECHO) "Cleaning all...";
	$(ECHO) "[CL] $(TARGET)"
	$(QUIET) -rm $(TARGET)
	$(ECHO) "[CL] $(TESTER)"
	$(QUIET) -rm $(TESTER)
	$(ECHO) "[CL] $(BDIR)/*"
	$(QUIET) find $(BDIR) -name "*.o" -type f -delete
	$(QUIET) find $(BDIR) -name "*.d" -type f -delete

# --------------------------------------------------------------

.PHONY: tar archive zip
tar: clean_all
	$(ECHO) "Tarring...";
	$(ECHO) "[OK]  bin/$(ARCHIVE_NAME).tar.gz"
	$(QUIET) tar -czf bin/$(ARCHIVE_NAME).tar.gz . --exclude='bin' --exclude='build'

archive zip: clean_all
	$(ECHO) "Zipping...";
	$(ECHO) "[OK]  bin/$(EXEC)-$(shell date '+%F').zip"
	$(QUIET) zip -q -r bin/$(ARCHIVE_NAME).zip . -x bin/* build/*

-include $(OBJ:%.o=%.d) $(TEST_OBJ:%.o=%.d)

