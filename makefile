APP       := app
SRC_DIR   := ./src
BIN_DIR   := ./bin
OBJ_DIR   := ./obj
VPATH := $(SRC_DIR)

CFLAGS := -std=c++11 -O3 -g
SOURCES=$(wildcard $(SRC_DIR)/*.cpp)
OBJECTS=$(SOURCES:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)


.PHONY: all
all: $(BIN_DIR)/$(APP)
	$< examples/03_test/points1.txt examples/03_test/points2.txt
	

$(BIN_DIR)/$(APP): $(OBJECTS) | $(BIN_DIR)
	$(CXX) $(LFLGAS) -o $@ $^

$(OBJ_DIR)/%.o: %.cpp | $(OBJ_DIR)
	$(CXX) $(CFLAGS) -o $@ -c $<

$(BIN_DIR):
	mkdir -p $@
$(OBJ_DIR):
	mkdir -p $@

.PHONY: clean
clean:
	rm -rf $(BIN_DIR) $(OBJ_DIR)