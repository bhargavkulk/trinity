LEXER:= lexer
PARSER:= parser

TRINITY_PROGRAM:= test_program.tri

FLAGS:= -Wall -Wextra -Wno-unused-function -Isrc/include -std=c++17

SRC:= $(wildcard src/*.cc) src/$(PARSER).cc src/$(LEXER).cc
OBJ:= $(patsubst src/%.cc,obj/%.o,$(SRC))
BIN:= bin/neo

$(BIN): $(OBJ)
	mkdir -p bin
	g++ $^ -o $@

obj/%.o: src/%.cc
	mkdir -p obj
	g++ $(FLAGS) -c $^ -o $@

src/$(PARSER).cc: src/$(PARSER).yy
	bison src/$(PARSER).yy -do src/$(PARSER).cc -v
	mv -f src/$(PARSER).hh src/include/$(PARSER).hh

src/$(LEXER).cc: src/$(LEXER).ll
	flex -o src/$(LEXER).cc src/$(LEXER).ll

run: $(BIN)
	mkdir -p log
	./$(BIN) $(TRINITY_PROGRAM)

clean:
	rm -f src/$(LEXER).cc src/$(PARSER).cc src/include/$(PARSER).hh obj/* bin/* log/*