CC = g++
CFLAGS = -g -Wall
LDFLAGS = -lwinmm -lfmt
TARGET = mu
SRC_DIR = src
INC_DIR = include
OBJ_DIR = obj
DEP_DIR = dep

SRCS := $(wildcard $(SRC_DIR)/*.cpp)
INCS := $(patsubst %,-I%,$(INC_DIR))
OBJS := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRCS))
DEPS := $(patsubst $(SRC_DIR)/%.cpp,$(DEP_DIR)/%.d,$(SRCS))

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) -o $@ $^ $(LDFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR) $(DEP_DIR)
	$(CC) -MM -MT $@ -MF $(DEP_DIR)/$*.d $(CFLAGS) $(INCS) $<
	$(CC) -o $@ -c $(CFLAGS) $(INCS) $<

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(DEP_DIR):
	mkdir -p $(DEP_DIR)

clean:
	rm -rf $(OBJ_DIR) $(DEP_DIR) $(TARGET)

-include $(DEPS)