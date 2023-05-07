HEADER_DIR = ./header
SRC_DIR = ./src
OBJ_DIR = ./obj
TARGET ?= poligonos

SRC = $(wildcard $(SRC_DIR)/*.cpp)
OBJ = $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRC))
CC = g++
CFLAGS = -I$(HEADER_DIR) -g -Wall -Wextra

$(shell mkdir -p $(OBJ_DIR))

all: $(TARGET)

$(TARGET): $(OBJ)
		$(CC) $(CFLAGS) -o $(TARGET) $(OBJ)

$(OBJ): $(OBJ_DIR)/%.o : $(SRC_DIR)/%.cpp
	$(CC) $(CFLAGS) -c $< -o $@

r: all
		./$(TARGET)

clean:
		@rm -f $(OBJ_DIR)/*.o vgcore* -d $(OBJ_DIR)

purge: clean
		@rm -f $(TARGET)

