CC = gcc
CFLAGS = -Wall -Wextra -Werror

hangman: hangman.o

run:
	./hangman
clean:
	rm hangman hangman.o