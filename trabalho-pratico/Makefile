CC := gcc

EXEC := programa-principal
FLAGS := -Wall -Wextra -Wdouble-promotion -Werror=pedantic -Werror=vla -pedantic-errors -Wfatal-errors 
DEBUG ?= 0
ifeq ($(DEBUG), 1)
	FLAGS += -O0 -g
else
	FLAGS += -O3 -march=native -mtune=native -flto
endif
LIBS := -lm `pkg-config --libs glib-2.0`
PKG_CONFIG := `pkg-config --cflags glib-2.0`
INC := -I includes/
SRC := $(wildcard src/*.c)
OBJ := $(SRC:src/%.c=build/%.o)

EXEC_TEST := programa-testes
FLAGS_TEST := $(FLAGS) -Wno-unused-function
INC_TEST := $(INC) -I lib/
SRC_TEST := $(wildcard tests/*.c)
OBJ_TEST := $(filter-out build/main.o, $(OBJ)) $(SRC_TEST:tests/%.c=build/%.o)

BUILD_DIR := $(shell mkdir -p build)
INCLUDE_FILES := $(wildcard includes/*.h)

.SUFFIXES:

.PHONY: all
all: $(EXEC)

$(EXEC): $(OBJ)
	@$(CC) $(FLAGS) $^ ${PKG_CONFIG} $(LIBS) -o $@ ; echo "[Compiling] $@"

build/%.o: src/%.c
	@$(CC) $(FLAGS) -c $< ${PKG_CONFIG} $(LIBS) $(INC) -o $@ ; echo "[Linking] $@"

.PHONY: rebuild
rebuild: clean all

.PHONY: test
test: clean $(EXEC_TEST)
	./$(EXEC_TEST)

$(EXEC_TEST): $(OBJ_TEST)
	@$(CC) $(FLAGS_TEST) $^ ${PKG_CONFIG} $(LIBS) -o $@ ; echo "[Compiling] $@"

build/%.o: tests/%.c
	@$(CC) $(FLAGS_TEST) -c $< ${PKG_CONFIG} $(LIBS) $(INC_TEST) -o $@ ; echo "[Linking] $@"

.PHONY: clean
clean:
	@rm -f programa-principal ; echo "[Cleaning] programa-principal"
	@rm -f programa-testes ; echo "[Cleaning] programa-testes"
	@rm -rf build/* ; echo "[Cleaning] build/"
	@rm -f Resultados/* ; echo "[Cleaning] Resultados/"

.PHONY: format
format:
	@clang-format -i --verbose $(SRC) $(INCLUDE_FILES) $(SRC_TEST)

.DELETE_ON_ERROR:
