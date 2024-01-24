#*-----------------------------------------------------------------*/
#** Advanced Project
#*  MARTIN Benoit et GIREAUD Noémie
#*  Makefile for the project.
#**/
#*-----------------------------------------------------------------*/

# Compiler
CC = gcc

# Log
LOG = *log*.txt

# Source and Object Directories
SRC_DIR = src
OBJ_DIR = obj
TEST_DIR = test
VOTE_VERIFY_OBJ_DIR = $(OBJ_DIR)/verify_my_vote
VOTE_VERIFY_DIR = verify_my_vote

# Binary Directory
BIN_DIR = bin

# Doxygen document
DOXYGEN = docs

# Source Files excluding main.c
SOURCES = $(wildcard $(SRC_DIR)/lecture_csv/*.c) $(wildcard $(SRC_DIR)/methods/*.c) $(wildcard $(SRC_DIR)/datatypes/*.c) $(wildcard $(SRC_DIR)/utils_sd/*.c) $(wildcard $(TEST_DIR)/utils/utils.c)
# Object Files
OBJECTS = $(SOURCES:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# Verify My Vote Source Files
VOTE_VERIFY_SOURCES = $(wildcard $(VOTE_VERIFY_DIR)/sha256_utils.c) $(wildcard $(VOTE_VERIFY_DIR)/sha256.c)
# Verify My Vote Object Files
VOTE_VERIFY_OBJECTS = $(VOTE_VERIFY_SOURCES:$(VOTE_VERIFY_DIR)/%.c=$(VOTE_VERIFY_OBJ_DIR)/%.o)

# Test Source Files
TEST_SOURCES = $(wildcard $(TEST_DIR)/*.c)
# Test Exec Files
TEST_EXEC = $(TEST_SOURCES:$(TEST_DIR)/%.c=$(BIN_DIR)/%)

# Default C Standard
C_STANDARD = -std=c99

# Debug and Release Flags
DEBUG_FLAGS = -g -O0 -DDEBUG -fsanitize=address,undefined -fno-omit-frame-pointer -fno-optimize-sibling-calls -fno-omit-frame-pointer -W -Wall -Wextra -Werror -Wfatal-errors -Wno-unused-parameter -Wno-unused-variable -Wno-unused-function -Wno-unused-result
RELEASE_FLAGS = -O3 -DNDEBUG

# Check if DEBUG is set to yes
ifeq ($(DEBUG),yes)
CFLAGS = $(C_STANDARD) $(DEBUG_FLAGS)
else
CFLAGS = $(C_STANDARD) $(RELEASE_FLAGS)
endif

# Target Executables
TARGET = $(BIN_DIR)/main
VOTE_VERIFY_TARGET = $(BIN_DIR)/verify_my_vote
TEST_TARGET = $(BIN_DIR)/test

.PHONY: all
all: directories $(TARGET) $(TEST_EXEC)

.PHONY: main
main: directories $(TARGET)

.PHONY: test
test: directories $(TEST_EXEC)

.PHONY: verify_my_vote
verify_my_vote: directories $(VOTE_VERIFY_TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(SRC_DIR)/main.c $^ -o $@ $(CFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) -c $< -o $@ $(CFLAGS)

$(TEST_TARGET): $(TEST_EXEC)
	$(CC) $^ -o $@ $(CFLAGS)
	
$(BIN_DIR)/%: $(TEST_DIR)/%.c $(OBJECTS) 
	$(CC) $^ -o $@ $(CFLAGS)

$(VOTE_VERIFY_TARGET): $(VOTE_VERIFY_OBJECTS)
	$(CC) $(VOTE_VERIFY_DIR)/verify_my_vote.c $^ -o $@ $(CFLAGS)

$(VOTE_VERIFY_OBJ_DIR)/%.o: $(VOTE_VERIFY_DIR)/%.c
	$(CC) -c $< -o $@ $(CFLAGS)



.PHONY: directories
directories:
	@mkdir -p $(OBJ_DIR)/verify_my_vote $(OBJ_DIR)/lecture_csv $(OBJ_DIR)/methods $(OBJ_DIR)/datatypes $(OBJ_DIR)/utils_sd $(OBJ_DIR)/test $(VOTE_VERIFY_OBJ_DIR) $(BIN_DIR)

.PHONY: doc
doc:
	@doxygen Doxyfile

.PHONY: clean
clean:
	@rm -rf $(OBJ_DIR) $(BIN_DIR) $(DOXYGEN)
	@find . -type f -name '*.txt' ! \( -name 'help.txt' -o -name 'candidats.txt' \) -delete

blague:
	@ echo "Quelle mamie fait peur aux voleurs ?"
	@ echo "Mamie Traillette."
	@ echo "clap clap clap"

	
