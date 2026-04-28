CXX 			= clang++

CXXFLAGS 		= -Wall -Wextra -std=c++17

BISONFLAGS 		= -d

EXEC			= vsopc

SRC				= main.cpp \
				  driver.cpp \
				  parser.cpp \
				  lexer.cpp \
				  semantic.cpp

OBJ	  			= $(SRC:.cpp=.o)


all: $(EXEC)

install-tools:
	sudo apt-get install -y flex bison

main.o: driver.hpp parser.hpp

driver.o: driver.hpp parser.hpp ast.hpp

parser.o: driver.hpp parser.hpp ast.hpp

lexer.o: driver.hpp parser.hpp

semantic.o: semantic.hpp ast.hpp

$(EXEC): $(OBJ)
	$(CXX) -o $@ $(LDFLAGS) $(OBJ)

parser.cpp: parser.ypp
	bison $(BISONFLAGS) -o parser.cpp $^

parser.hpp: parser.ypp
	bison $(BISONFLAGS) -o parser.cpp $^

lexer.cpp: lexer.lex
	flex $(LEXFLAGS) -o lexer.cpp $^

clean:
	@rm -f $(EXEC)
	@rm -f $(OBJ)
	@rm -f lexer.cpp
	@rm -f parser.cpp parser.hpp location.hh

.PHONY: clean

ARCHIVE = vsopcompiler.tar.xz
PROJECT_DIR = $(shell basename $(CURDIR))

submit: clean
	@cd .. && COPYFILE_DISABLE=1 tar -cJf $(PROJECT_DIR)/$(ARCHIVE) \
		--exclude='.git' \
		--exclude='.DS_Store' \
		$(PROJECT_DIR)/
	@echo "Archive created: $(ARCHIVE)"
	@tar -tJf $(ARCHIVE) | wc -l | xargs echo "Files in archive:"

.PHONY: clean submit