SOURCE_DIR := src
INCLUDES_DIR := includes
OBJECTS_DIR := objs

CC := gcc
CFLAGS := -I $(INCLUDES_DIR) -Wall -Wextra -Werror -pedantic

SOURCES := $(wildcard $(SOURCE_DIR)/*.c)
OBJECTS := $(patsubst $(SOURCE_DIR)/%.c,$(OBJECTS_DIR)/%.o,$(SOURCES))
DEPENDS := $(patsubst $(SOURCE_DIR)/%.c,$(OBJECTS_DIR)/%.d,$(SOURCES))

WARNINGS := -Wall -Wextra

.PHONY := all clean

all: nbi

clean:
	$(RM) $(OBJECTS) $(DEPENDS) nbi

nbi: $(OBJECTS)
	$(CC) $(WARNINGS) $(CFLAGS) $^ -o $@

-include $(DEPENDS)

$(OBJECTS_DIR)/%.o: $(SOURCE_DIR)/%.c Makefile | $(OBJECTS_DIR)
	$(CC) $(WARNINGS) $(CFLAGS) -MMD -MP -c $< -o $@

$(OBJECTS_DIR):
	mkdir -p $@
