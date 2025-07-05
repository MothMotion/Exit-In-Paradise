SRC_DIR = ./src/
OBJ_DIR = ./obj/
LIB_DIR = ./lib/

TARGET_DIR = ./build/
TARGET = built_target

ifndef VERBOSE
.SILENT:
endif

SRC = $(wildcard $(SRC_DIR)*.cpp)
OBJ = $(patsubst $(SRC_DIR)%.cpp, $(OBJ_DIR)%.o, $(SRC))

GCC = g++
GCC_FLAGS = -Wall -Wextra -Iinclude

.PHONY: build clean check

build: $(TARGET_DIR)$(TARGET)
	@echo "Build complete!"

$(TARGET_DIR)$(TARGET): $(OBJ)
	@echo -e "Compiling $(TARGET)..."
	mkdir -p $(TARGET_DIR)
	$(GCC) $(GCC_FLAGS) -o $@ $^

DEP := $(parsubst $(OBJ_DIR)%.o, $(OBJ_DIR)%.d, $(OBJ))
-include $(DEP)
DEPFLAGS = -MMD -MF $(@:.o=.d)

$(OBJ_DIR)%.o: $(SRC_DIR)%.cpp
	@echo -e "Compiling $@"
	mkdir -p $(OBJ_DIR)
	$(GCC) $(GCC_FLAGS) -o $@ -c $< $(DEPFLAGS)

clean:
	rm $(OBJ_DIR)*.o
	@echo "Objects cleaned!"

check:
	@echo -e "Starting checking..."
	cppcheck --enable=all --inconclusive --library=posix --quiet ./ -I ./include/
	@echo -e "Checking done!"
