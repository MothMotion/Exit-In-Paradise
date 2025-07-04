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
GCC_FLAGS = -Wall -Wextra

.PHONY: build clean check

build: $(TARGET)
	@echo "Build complete!"

$(TARGET_DIR)$(TARGET): $(OBJ)
	@echo -e "Compiling $(TARGET)..."
	mkdir -p $(TARGET_DIR)
	$(GCC) $(GCC_FLAGS) -o $@ $^

$(OBJ_DIR)%.o: $(SRC_DIR)%.cpp
	@echo -e "Compiling $@"
	$(GCC) $(GCC_FLAGS) -o $@ -c $<

clean:
	rm $(OBJ_DIR)*.o
	@echo "Build cleaned!"

check:
	@echo -e "Starting checking..."
	cppcheck --enable=all --inconclusive --library=posix --quiet ./
	@echo -e "Checking done!"
