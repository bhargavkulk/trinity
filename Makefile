LEXER:= lexer
PARSER:= parser

TRINITY_PROGRAM:= test_program.tri

FLAGS:= -Wall -Wextra -Wno-unused-function -Isrc/include -std=c++17

SRC:= $(wildcard src/*.cc) src/$(PARSER).cc src/$(LEXER).cc
SRC += $(wildcard src/native/*.cc)
OBJ:= $(patsubst src/%.cc,obj/%.o,$(SRC))
BIN:= bin/neo

$(BIN): $(OBJ)
	mkdir -p bin
	g++ $^ -o $@

obj/%.o: src/%.cc
	mkdir -p obj
	mkdir -p obj/native
	g++ $(FLAGS) -c $^ -o $@

src/$(PARSER).cc: src/$(PARSER).yy
	bison src/$(PARSER).yy -do src/$(PARSER).cc -v --graph
	mv -f src/$(PARSER).hh src/include/$(PARSER).hh

src/$(LEXER).cc: src/$(LEXER).ll
	flex -o src/$(LEXER).cc src/$(LEXER).ll

run: $(BIN)
	mkdir -p log
	./$(BIN) $(TRINITY_PROGRAM)

clean:
	rm -rf src/$(LEXER).cc src/$(PARSER).cc src/include/$(PARSER).hh obj/* bin/* log/*

test:
	@echo "RUNNING TESTS..."
	@echo "test: 1_hello_world.tri"
	@./$(BIN) tests/1_hello_world.tri

	@echo "test: 2_vars.tri"
	@./$(BIN) tests/2_vars.tri

	@echo "test: 3_expr.tri"
	@./$(BIN) tests/3_expr.tri

	@echo "test: 4_factorial.tri"
	@./$(BIN) tests/4_factorial.tri

	@echo "test: 5loop_arr.tri"
	@./$(BIN) tests/5_loop_arr.tri

