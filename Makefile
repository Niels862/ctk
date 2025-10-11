CC 			:= gcc
CCSTD 		:= c99

SRC_DIR     := src
INCLUDE_DIR := include
BUILD_DIR   := build

TEST_DIR    := tests
TEST_BUILD  := $(BUILD_DIR)/tests

LIB_NAME    := libctk.a
MODE      	?= debug

ifeq ($(MODE),release)
  CCFLAGS := -O3 -DNDEBUG
else ifeq ($(MODE),debug)
  CCFLAGS := -O2 -g
else
  $(error Unknown build mode '$(MODE)'; use MODE=release or MODE=debug)
endif

CCFLAGS += -Wall -Wextra -Werror -pedantic -std=$(CCSTD)
CFLAGS  := -MMD -MP -I$(INCLUDE_DIR)

SRCS := $(shell find $(SRC_DIR) -name '*.c')
OBJS := $(SRCS:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)
DEPS := $(OBJS:.o=.d)

TEST_SRCS := $(shell find $(TEST_DIR) -maxdepth 1 -name '*.c')
TEST_BINS := $(patsubst $(TEST_DIR)/%.c,$(TEST_BUILD)/%,$(TEST_SRCS))
TEST_OBJS := $(patsubst $(TEST_DIR)/%.c,$(TEST_BUILD)/%.o,$(TEST_SRCS))
TEST_DEPS := $(TEST_OBJS:.o=.d)

.PHONY: all release debug clean

all: $(LIB_NAME) $(TEST_BINS)

release:
	$(MAKE) MODE=release

debug:
	$(MAKE) MODE=debug

# Library:
$(LIB_NAME): $(OBJS)
	@ar rcs $@ $(OBJS)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(CCFLAGS) -c $< -o $@

# Tests:
$(TEST_BUILD)/%.o: $(TEST_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(CCFLAGS) -c $< -o $@

$(TEST_BUILD)/%: $(TEST_BUILD)/%.o $(LIB_NAME)
	$(CC) $(CCFLAGS) $< -L. -lctk -o $@

clean:
	rm -rf $(BUILD_DIR) $(LIB_NAME)

-include $(DEPS)
