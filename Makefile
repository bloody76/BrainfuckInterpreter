CC=gcc
FLAGS=-std=c99 -Wall -Wextra -Werror -pedantic
SRC=src/main.c
OUT=BrainfuckInterpreter

all:
	$(CC) $(FLAGS) $(SRC) -o $(OUT)

clean:
	@echo -e "\033[33mRule: Clean\033[0m"
	rm $(OUT)

test: all hello clean

hello:
	@echo -e "\033[33mHelloWorld test:\033[0m"
	./$(OUT) test.bf
