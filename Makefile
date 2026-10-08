# CSE 220 Homework 4
#
#   make        build everything into build/
#   make test   build if needed, then run all Criterion tests
#   make clean  remove build/
#
# Criterion is found through pkg-config when it is installed that way, which
# covers the lab machines and a Homebrew install on macOS. If pkg-config does
# not know about it, plain -lcriterion is used instead.

CC = gcc
CFLAGS = -Wall -Wextra -Werror -std=c11 -g -I.

BUILD = build
TARGET = $(BUILD)/hw4_tests

SOURCES = strgPtr.c caesar.c
TEST_SOURCES = tests/test_strgPtr.c tests/test_caesar.c
HEADERS = strgPtr.h caesar.h

OBJECTS = $(SOURCES:%.c=$(BUILD)/%.o)
TEST_OBJECTS = $(TEST_SOURCES:%.c=$(BUILD)/%.o)

CRITERION_CFLAGS := $(shell pkg-config --cflags criterion 2>/dev/null)
CRITERION_LIBS := $(shell pkg-config --libs criterion 2>/dev/null)
ifeq ($(strip $(CRITERION_LIBS)),)
CRITERION_LIBS := -lcriterion
endif

.PHONY: all test objects clean

all: $(TARGET)

# Compiles only your two source files, without Criterion. Handy for a quick
# syntax check before your tests are ready.
objects: $(OBJECTS)

$(TARGET): $(OBJECTS) $(TEST_OBJECTS)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $^ $(CRITERION_LIBS) -pthread -o $@

$(BUILD)/%.o: %.c $(HEADERS)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(CRITERION_CFLAGS) -c $< -o $@

test: $(TARGET)
	./$(TARGET)

clean:
	rm -rf $(BUILD)
