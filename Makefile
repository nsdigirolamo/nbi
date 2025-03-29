SOURCE_DIR := src
INCLUDES_DIR := includes
OBJECTS_DIR := objs

CC := gcc
WARNINGS := -Wall -Wextra -Wpedantic -Werror
CFLAGS := $(WARNINGS) -I $(INCLUDES_DIR)

SOURCES := $(wildcard $(SOURCE_DIR)/*.c)
OBJECTS := $(patsubst $(SOURCE_DIR)/%.c,$(OBJECTS_DIR)/%.o,$(SOURCES))
DEPENDS := $(patsubst $(SOURCE_DIR)/%.c,$(OBJECTS_DIR)/%.d,$(SOURCES))

.PHONY := all clean

all: nbi

clean:
	$(RM) $(OBJECTS) $(DEPENDS) nbi

nbi: $(OBJECTS)
	$(CC) $(CFLAGS) $^ -o $@

-include $(DEPENDS)

$(OBJECTS_DIR)/%.o: $(SOURCE_DIR)/%.c Makefile | $(OBJECTS_DIR)
	$(CC) $(CFLAGS) -MMD -MP -c $< -o $@

$(OBJECTS_DIR):
	mkdir -p $@
